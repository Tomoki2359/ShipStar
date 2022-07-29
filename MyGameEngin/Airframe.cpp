#include "Airframe.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Player.h"
//コンストラクタ
Airframe::Airframe(GameObject* parent, std::string name)
	: GameObject(parent, name), hModel_(-1), aRotate_(false), dRotate_(false), lRotate_(false), rRotate_(false), cTurbo_(false), tTurbo_(0)
{
}

Airframe::~Airframe()
{
}

//初期化
void Airframe::Initialize()
{
	//ステータスの取得
	SetStatus();

	//モデルデータのロード
	hModel_ = Model::Load(failName_);
	assert(hModel_ >= 0);

	status_[MAX_SPEAD] = (float)((int)status_[MAX_SPEAD] * 10000000 / 216000) / 10000;	//最高速度
	status_[ACCELE] = (float)((int)status_[ACCELE] * 10000000 / 216000 / 60 / 7) / 10000;	//加速度
	status_[TURBO] = status_[TURBO] / 100 * 60;	//ターボ値
	Spead_ = 0;	//現在の速度
}

//更新
void Airframe::Update()
{
	//前進する
	if (Input::IsKey(DIK_W))
	{
		//加速分の速度を増やす
		Spead_ = Spead_ + status_[ACCELE];
	}

	//ブレーキする
	if (Input::IsKey(DIK_S))
	{
		//加速分の速度を減らす
		Spead_ = Spead_ - (status_[ACCELE] * 2);
		//速度が最大速度を超えたとき最大速度にする
		if (Spead_ <= 0)
		{
			Spead_ = 0;
		}
	}

	//左にカーブする
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 1.5;
		if (rRotate_ != true)
		{
			//左に曲がるときの傾き
			transform_.rotate_.z += 2;
			lRotate_ = true;
			if (transform_.rotate_.z >= 40)
			{
				transform_.rotate_.z = 40;
			}
		}
	}

	//右にカーブする
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 1.5;
		if (lRotate_ != true)
		{
			//右に曲がるときの傾き
			transform_.rotate_.z -= 2;
			rRotate_ = true;
			if (transform_.rotate_.z <= -40)
			{
				transform_.rotate_.z = -40;
			}
		}
	}

	//左に傾いている状態のとき
	if (lRotate_ == true)
	{
		//角度を戻す処理
		transform_.rotate_.z -= 1;
		if (transform_.rotate_.z <= 0)
		{
			lRotate_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//右に傾いている状態のとき
	if (rRotate_ == true)
	{
		//角度を戻す処理
		transform_.rotate_.z += 1;
		if (transform_.rotate_.z >= 0)
		{
			rRotate_ = false;
			transform_.rotate_.z = 0;
		}
	}

	//上昇する
	if (Input::IsKey(DIK_E))
	{
		//下降状態ではないとき
		if (dRotate_ != true)
		{
			//上昇状態にする
			transform_.rotate_.x -= 0.4;
			aRotate_ = true;
			//角度が15を超えたら15にする
			if (transform_.rotate_.x <= -25)
			{
				transform_.rotate_.x = -25;
			}
		}
	}

	//下降する
	if (Input::IsKey(DIK_Q))
	{
		//上昇状態ではないとき
		if (aRotate_ != true)
		{
			//下降状態にする
			transform_.rotate_.x += 0.4;
			dRotate_ = true;
			//角度が－15を超えたら-15にする
			if (transform_.rotate_.x >= 25)
			{
				transform_.rotate_.x = 25;
			}
		}
	}

	//上昇状態なら
	if (aRotate_ == true)
	{
		if (transform_.position_.y >= 15)
		{
			transform_.rotate_.x += 0.4;
		}
		transform_.rotate_.x += 0.2;
		if (transform_.rotate_.x >= 0)
		{
			aRotate_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//下降状態なら
	if (dRotate_ == true)
	{
		if (transform_.position_.y <= -5)
		{
			transform_.rotate_.x -= 0.4;
		}
		transform_.rotate_.x -= 0.2;
		if (transform_.rotate_.x <= 0)
		{
			dRotate_ = false;
			transform_.rotate_.x = 0;
		}
	}

	//5秒立ったらターボを使えるようにする
	if (tTurbo_ >= 300)
	{
		if (Input::IsKeyDown(DIK_C))
		{
			cTurbo_ = true;
			tTurbo_ = 0;
		}
	}

	//ターボ中の処理
	if (cTurbo_ == true)
	{
		//スピードを上げる
		Spead_ = status_[MAX_SPEAD] * 2.0;
		//時間が経ったら終わる
		if (tTurbo_ >= status_[TURBO])
		{
			cTurbo_ = false;
			tTurbo_ = 0;
		}
	}

	//速さや位置を一定にする
	Limit();

	//移動処理
	//速度をベクターに変換
	XMFLOAT3 Moob_ = { 0,0,Spead_ };
	XMVECTOR vMoob_ = XMLoadFloat3(&Moob_);

	//機体のX軸,Y軸の角度の取得
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate = mRotate * XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

	//現在地から機体の向きによって進む
	vMoob_ = XMVector3TransformCoord(vMoob_, mRotate);
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	vPos += vMoob_;
	XMStoreFloat3(&transform_.position_, vPos);

	//カメラをつかうかどうか
	if (sCamera_ == true)
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

	//ターボを貯める
	tTurbo_++;
}

//描画
void Airframe::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Airframe::Release()
{
}

//速さや位置などの限界
void Airframe::Limit()
{
	//速度が最大速度を超えたとき最大速度にする
	if (Spead_ >= status_[MAX_SPEAD])
	{
		Spead_ = status_[MAX_SPEAD];
	}

	//一定以上上昇しない
	if (transform_.position_.y >= 15)
	{
		transform_.position_.y = 15;
	}

	//一定以下下降しない
	if (transform_.position_.y <= -5)
	{
		transform_.position_.y = -5;
	}
}

//ステータスの取得
void Airframe::SetStatus()
{
	//あとでfor分でCSVから入れる
	status_[MAX_SPEAD] = 150;
	status_[ACCELE] = 200;
	status_[TURBO] = 150;
	status_[ENDURANCE] = 100;

	failName_ = "";
	sCamera_ = false;
}