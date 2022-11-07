#include "Airframe.h"
#include "Course.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include <algorithm>
#include <math.h>

//コンストラクタ
Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), cAscent_(false), speed_(NULL), RespawnPos_(), RespawnRot_(), RespawnUpdate_(NULL),
	cDescent_(false), lCurve_(false), rCurve_(false), cTurbo_(false), tTurbo_(NULL), Lap_(NULL), Side_(true),
	cCamera_(false), status_(), PartsSet(), start_(false), timeCount_(180), PrevPosition_(), pNav_(nullptr), IsGoal_(false)
{
}

Airframe::Airframe(GameObject* parent)
	: Airframe(parent, "Airframe")
{
}

Airframe::~Airframe()
{
}

//初期化
void Airframe::Initialize()
{
	csv.Load("Assets/PartsStatus.csv");

	//全てデフォルト値で初期化
	ZeroMemory(&PartsSet, sizeof(PartsSet));
	//ステータスの取得
	SetStatus();

	//モデルデータのロード
	//パーツを呼び出せるようになったら消す
	hModel_ = Model::Load(fileName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEED] = (float)((int)status_[MAX_SPEED] * 10000000 / 216000) / 10000;	//最高速度
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//加速度
	status_[TURBO] = status_[TURBO] / 100 * 60;	//ターボ値

	transform_.position_.z = 0.1f;
	PrevPosition_ = transform_.position_;
}

//更新
void Airframe::Update()
{
	//3秒後にスタートする
	if (start_)
	{
		pNav_ = (Navigation*)FindObject("Navigation");
		LapMeasure();
		JudgeGoal();
		PrevPosition_ = transform_.position_;

		//継承先で呼び出す
		UpdateState();

		FixInclination();

		//速さや位置を一定にする
		Limit();

		TurboProcess();
	}

	//カウントダウン
	else
	{
		//timeCount_が0以下になったら操作可能にする
		timeCount_--;	
		if (timeCount_ <= 0)
		{
			start_ = true;
		}
	}

	MoveProcess();
	JudgeSide();

	if (Side_)	//コース内にいる場合
	{
		StayInside();
		RespawnPos_[RespawnUpdate_] = PrevPosition_;
		RespawnRot_[RespawnUpdate_] = transform_.rotate_;
		RespawnUpdate_++;
		if (RespawnUpdate_ >= Past)	//配列の最大数は超えないようにする
		{
			cTurbo_ = false;
			tTurbo_ = NULL;
			RespawnUpdate_ = NULL;
		}
	}
	else		//コース外にいる場合
	{

		Respawn();
	}

	ChaseCamera();
}


void Airframe::JudgeSide()
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData data;
	data.start = transform_.position_;
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
	Side_ = data.hit;
}

void Airframe::JudgeSide(RayCastData& data)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
}

bool Airframe::JudgeSide(XMFLOAT3 pos)
{
	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData data;
	data.start = pos;
	data.dir = XMFLOAT3(NULL, -1.0, NULL);
	Model::RayCast(hCourseModel, &data);
	return data.hit;
}

//描画
void Airframe::Draw()
{
	//パーツを呼び出せるようになったら消す
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Airframe::Release()
{
	SAFE_RELEASE(pNav_);
}

//速さや位置などの限界
void Airframe::Limit()
{
	//速度が最大速度を超えたとき最大速度にする
	if (speed_ >= status_[MAX_SPEED])
	{
		speed_ = status_[MAX_SPEED];
	}
}

void Airframe::SetPartsNum(char engine, char body, char wing, char cockpit, char pattern)
{
	PartsSet.ENGINE = engine;
	PartsSet.BODY = body;
	PartsSet.WING = wing;
	PartsSet.COCKPIT = cockpit;
	PartsSet.PATTERN = pattern;

	SetStatus();
}

//ステータスの取得
void Airframe::SetStatus()
{
	//あとでfor分でCSVから入れる
	status_[MAX_SPEED] = (float)csv.GetValue(PARTS_WING ,PartsSet.WING);
	status_[ACCELE] = (float)csv.GetValue(PARTS_COCKPIT, PartsSet.COCKPIT);	//値250で逆進を確認
	status_[TURBO] = (float)csv.GetValue(PARTS_ENGINE, PartsSet.ENGINE);
	status_[ENDURANCE] = (float)csv.GetValue(PARTS_BODY, PartsSet.BODY);

	//パーツを呼び出せるようになったら修正
	//fileName_ = "";
	//cCamera_ = false;

	fileName_ = "Assets\\Airframe.fbx";	//ファイルの名前
	if (this->objectName_ == "Player")
	{
		cCamera_ = true;	//カメラON
	}
	else
	{
		cCamera_ = false;	//カメラOFF
	}

	const float Scale = 0.25f;
	transform_.scale_ = XMFLOAT3(Scale, Scale, Scale);
}

void Airframe::Accelerate()
{
	//加速分の速度を増やす
	speed_ = speed_ + status_[ACCELE];
}

void Airframe::Decelerate()
{
	//加速分の速度を減らす
	speed_ = speed_ - (status_[ACCELE] * 2);
	//速度が最大速度を超えたとき最大速度にする
	if (speed_ <= 0)
	{
		speed_ = 0;
	}
}

void Airframe::TurnRight()
{
	if (speed_ > NULL)
	{
		transform_.rotate_.y += RotationRate_Y;
	}
	if (lCurve_ != true)
	{
		//右に曲がるときの傾き
		transform_.rotate_.z -= RotationRate_Z;
		rCurve_ = true;
		if (transform_.rotate_.z <= -RotationMax_Z)
		{
			transform_.rotate_.z = -RotationMax_Z;
		}
	}
}

void Airframe::TurnLeft()
{
	if (speed_ > NULL)
	{
		transform_.rotate_.y -= RotationRate_Y;
	}
	if (rCurve_ != true)
	{
		//左に曲がるときの傾き
		transform_.rotate_.z += RotationRate_Z;
		lCurve_ = true;
		if (transform_.rotate_.z >= RotationMax_Z)
		{
			transform_.rotate_.z = RotationMax_Z;
		}
	}
}

void Airframe::Turbo()
{
	cTurbo_ = true;
	tTurbo_ = NULL;
}

XMFLOAT3 Airframe::GetDistance(GameObject* pTarget)
{
	float DisX = this->GetPosition().x - pTarget->GetPosition().x;
	float DisY = this->GetPosition().y - pTarget->GetPosition().y;
	float DisZ = this->GetPosition().z - pTarget->GetPosition().z;
	return XMFLOAT3(DisX, DisY, DisZ);
}

float Airframe::Getdistance(XMFLOAT3 a, XMFLOAT3 b)
{
	float answer;
	XMFLOAT3 c = XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	answer = (float)sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
	return answer;
}

void Airframe::JudgeGoal()
{
	if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal) && Lap_ > NULL)
	{
		IsGoal_ = true;
	}
}

void Airframe::ResetOverRotate(float* rotate)
{
	const int of = 360;
	const int uf = 0;

	if (*rotate > of)
	{
		*rotate -= of;
	}
	if (*rotate < uf)
	{
		*rotate += of;
	}
}

void Airframe::LapMeasure()
{
	//逆走でゴールラインを通過した場合
	if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal) &&
		PrevPosition_.z > transform_.position_.z)
	{
		Lap_--;
	}
	else if (Math::SegmentToPlane(PrevPosition_, transform_.position_, pNav_->Upper_Goal, pNav_->Left_Goal, pNav_->Right_Goal))
	{
		Lap_++;
	}
}

void Airframe::Respawn()
{
	transform_.position_ = RespawnPos_[RespawnUpdate_];			//所定の位置に戻す
	transform_.rotate_.x = RespawnRot_[RespawnUpdate_].x;		//回転も戻す
	transform_.rotate_.y = RespawnRot_[RespawnUpdate_].y;
	transform_.rotate_.z = NULL;
	speed_ = NULL;						//スピードを0にする
}

void Airframe::FixInclination()
{
	//左に傾いている状態のとき
	if (lCurve_)
	{
		//角度を戻す処理
		transform_.rotate_.z--;
		if (transform_.rotate_.z <= NULL)
		{
			lCurve_ = false;
			transform_.rotate_.z = NULL;
		}
	}

	//右に傾いている状態のとき
	if (rCurve_)
	{
		//角度を戻す処理
		transform_.rotate_.z++;
		if (transform_.rotate_.z >= NULL)
		{
			rCurve_ = false;
			transform_.rotate_.z = NULL;
		}
	}
}

void Airframe::TurboProcess()
{
	//ターボ中の処理
	if (cTurbo_)
	{
		//スピードを上げる
		speed_ = status_[MAX_SPEED] * 2.0f;
		//時間が経ったら終わる
		if (tTurbo_ >= status_[TURBO])
		{
			cTurbo_ = false;
			tTurbo_ = NULL;
		}
	}

	//ターボ値を貯める
	tTurbo_++;
}

void Airframe::MoveProcess()
{
	//移動処理
	XMVECTOR vMove_ = XMVectorSet(NULL, NULL, speed_, NULL);

	//機体のX軸,Y軸の角度の取得
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//現在地から機体の向きによって進む
	vMove_ = XMVector3TransformCoord(vMove_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMove_;
	XMStoreFloat3(&transform_.position_, vPos);
}

void Airframe::ChaseCamera()
{
	//カメラを使用するかどうか
	if (cCamera_)
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

		//カメラの設置
		XMFLOAT3 camPos;
		XMVECTOR vCam = XMVectorSet(0.0f, 5.0f, -10.0f, 0.0f);	//カメラの位置
		XMMATRIX mRotate_ = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));	//Y軸回転
		vCam = XMVector3TransformCoord(vCam, mRotate_);	//角度でカメラの位置を変更
		XMStoreFloat3(&camPos, vPos + vCam);	//カメラの位置と自分の位置を合わせる
		Camera::SetPosition(XMVectorSet(camPos.x, camPos.y, camPos.z, 1.0));

		//カメラは自分の位置を見てる
		XMVECTOR Pos_ = XMLoadFloat3(&transform_.position_);
		Camera::SetTarget(Pos_);
	}
}
