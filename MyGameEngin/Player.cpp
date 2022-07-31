#include "Player.h"
#include "Engine/Input.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: Airframe(parent, "Player")
{
}

Player::~Player()
{
}

void Player::UpdateState()
{
	//前進する
	if (Input::IsKey(DIK_W))
	{
		Accelerate();
	}
	//ブレーキする
	if (Input::IsKey(DIK_S))
	{
		Decelerate();
	}
	//左にカーブする
	if (Input::IsKey(DIK_A))
	{
		TurnLeft();
	}
	//右にカーブする
	if (Input::IsKey(DIK_D))
	{
		TurnRight();
	}
	//上昇する
	if (Input::IsKey(DIK_E))
	{
		Rise();
	}
	//下降する
	if (Input::IsKey(DIK_Q))
	{
		Descent();
	}
	//ターボ
	//300は順位によって発動する時間が変動する(最下位から5秒,10秒,15秒,20秒)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
	}
}

void Player::SetStatus()
{
	//あとでfor分でCSVから入れる
	status_[MAX_SPEED] = 150;
	status_[ACCELE] = 200;
	status_[TURBO] = 150;
	status_[ENDURANCE] = 100;

	//パーツを呼び出せるようになったら修正
	fileName_ = "Assets\\oden.fbx.";	//ファイルの名前
	cCamera_ = true;	//カメラON
	transform_.scale_.x = 0.25;
	transform_.scale_.y = 0.25;
	transform_.scale_.z = 0.25;
}