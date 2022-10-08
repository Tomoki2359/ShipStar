#include "Airframe.h"
#include "Course.h"
#include "Engine/Math.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include <algorithm>
#include <math.h>

//コンストラクタ
Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), cAscent_(false), speed_(0.0f), PrevHeight_(10.0f),
	cDescent_(false), lCurve_(false), rCurve_(false), cTurbo_(false), tTurbo_(NULL), Lap_(-1), Side_(true),
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
	PartsSet = { NULL, NULL, NULL, NULL, NULL, NULL };

	//ステータスの取得
	SetStatus();

	//モデルデータのロード
	//パーツを呼び出せるようになったら消す
	hModel_ = Model::Load(fileName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEED] = (float)((int)status_[MAX_SPEED] * 10000000 / 216000) / 10000;	//最高速度
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//加速度
	status_[TURBO] = status_[TURBO] / 100 * 60;	//ターボ値
	speed_ = 0;	//現在の速度
}

//更新
void Airframe::Update()
{
	//3秒後にスタートする
	if (start_)
	{
		pNav_ = (Navigation*)FindObject("Navigation");

		//PassPoint();
		LapMeasure();
		JudgeGoal();

		PrevPosition_ = transform_.position_;
		//継承先で呼び出す
		UpdateState();

		//左に傾いている状態のとき
		if (lCurve_ == true)
		{
			//角度を戻す処理
			transform_.rotate_.z -= 1;
			if (transform_.rotate_.z <= 0)
			{
				lCurve_ = false;
				transform_.rotate_.z = 0;
			}
		}

		//右に傾いている状態のとき
		if (rCurve_ == true)
		{
			//角度を戻す処理
			transform_.rotate_.z += 1;
			if (transform_.rotate_.z >= 0)
			{
				rCurve_ = false;
				transform_.rotate_.z = 0;
			}
		}
		
		//上昇状態なら
		if (cAscent_ == true)
		{
			if (transform_.position_.y >= 15)
			{
				transform_.rotate_.x += 0.4f;
			}
			transform_.rotate_.x += 0.2f;
			if (transform_.rotate_.x >= 0)
			{
				cAscent_ = false;
				transform_.rotate_.x = 0;
			}
		}

		//下降状態なら
		if (cDescent_ == true)
		{
			if (transform_.position_.y <= -5)
			{
				transform_.rotate_.x -= 0.4f;
			}
			transform_.rotate_.x -= 0.2f;
			if (transform_.rotate_.x <= 0)
			{
				cDescent_ = false;
				transform_.rotate_.x = 0;
			}
		}

		//速さや位置を一定にする
		Limit();

		//ターボ中の処理
		if (cTurbo_ == true)
		{
			//スピードを上げる
			speed_ = status_[MAX_SPEED] * 2.0f;
			//時間が経ったら終わる
			if (tTurbo_ >= status_[TURBO])
			{
				cTurbo_ = false;
				tTurbo_ = 0;
			}
		}

		//ターボ値を貯める
		tTurbo_++;
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

	//移動処理
	//速度をベクターに変換
	XMFLOAT3 Move_ = { 0,0,speed_ };
	XMVECTOR vMove_ = XMLoadFloat3(&Move_);

	//回転の値を矯正する
	ResetOverRotate(&transform_.rotate_.x);
	ResetOverRotate(&transform_.rotate_.y);
	ResetOverRotate(&transform_.rotate_.z);

	//機体のX軸,Y軸の角度の取得
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//現在地から機体の向きによって進む
	vMove_ = XMVector3TransformCoord(vMove_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMove_;
	XMStoreFloat3(&transform_.position_, vPos);

	JudgeSide();

	if (Side_)	//コース内にいる場合
	{
		StayInside();
	}
	else		//コース外にいる場合
	{
		speed_ *= 0.97f;
		StayOutside();
	}
	//CourseoutSaver();

	//カメラを使用するかどうか
	if (cCamera_ == true)
	{
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

	////一定以上上昇しない
	//if (transform_.position_.y >= 15)
	//{
	//	transform_.position_.y = 15;
	//}

	////一定以下下降しない
	//if (transform_.position_.y <= -5)
	//{
	//	transform_.position_.y = -5;
	//}
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
	if (speed_ > 0)
	{
		transform_.rotate_.y += 1.5f;
	}
	if (lCurve_ != true)
	{
		//右に曲がるときの傾き
		transform_.rotate_.z -= 2;
		rCurve_ = true;
		if (transform_.rotate_.z <= -40)
		{
			transform_.rotate_.z = -40;
		}
	}
}

void Airframe::TurnLeft()
{
	if (speed_ > 0)
	{
		transform_.rotate_.y -= 1.5f;
	}
	if (rCurve_ != true)
	{
		//左に曲がるときの傾き
		transform_.rotate_.z += 2;
		lCurve_ = true;
		if (transform_.rotate_.z >= 40)
		{
			transform_.rotate_.z = 40;
		}
	}
}

void Airframe::Rise()
{
	//下降状態ではないとき
	if (cDescent_ != true)
	{
		//上昇状態にする
		transform_.rotate_.x -= 0.4f;
		cAscent_ = true;
		//角度が15を超えたら15にする
		if (transform_.rotate_.x <= -25)
		{
			transform_.rotate_.x = -25;
		}
	}
}

void Airframe::Descent()
{
	//上昇状態ではないとき
	if (cAscent_ != true)
	{
		//下降状態にする
		transform_.rotate_.x += 0.4f;
		cDescent_ = true;
		//角度が－15を超えたら-15にする
		if (transform_.rotate_.x >= 25)
		{
			transform_.rotate_.x = 25;
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

void Airframe::CourseoutSaver()
{
	XMFLOAT3 fRay = XMFLOAT3(0.0f, -1.0f, 0.0f);

	Course* pCourse = (Course*)FindObject("Course");
	int hCourseModel = pCourse->GetModelHandle();

	RayCastData data;
	data.start = transform_.position_;   //レイの発射位置
	data.dir = fRay;				      //レイの方向
	Model::RayCast(hCourseModel, &data); //レイを発射

	if (!data.hit)
	{
		speed_ *= 0.97f;
	}
}

float Airframe::Getdistance(XMFLOAT3 a, XMFLOAT3 b)
{
	float answer;
	XMFLOAT3 c = XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	answer = (float)sqrt(pow(c.x, 2.0) + pow(c.y, 2.0) + pow(c.z, 2.0));
	return answer;
}

//void Airframe::PassPoint()
//{
//	for (auto it = PassageChecker_.begin(); it != PassageChecker_.end(); it++)
//	{
//		float dist = Getdistance(transform_.position_, (*it).Point);
//		if(dist < 35 && (*it).Pass == false)
//		{
//			(*it).Pass = true;
//		}
//	}
//}

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