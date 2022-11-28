#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Storage.h"

void Player::StayInside()
{
}

//コンストラクタ
Player::Player(GameObject* parent)
	: Airframe(parent, "Player"), ProgFrame_(NULL)
{
	GhostData_Command_.clear();
	GhostData_Frame_.clear();
}

Player::~Player()
{
	GhostData_Command_.clear();
	GhostData_Frame_.clear();
}

void Player::UpdateState()
{
	//前進する
	if (Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
	{
		Accelerate();
		NextState_ += M_ACCEL;
	}
	//ブレーキする
	if (Input::IsKey(DIK_S) && !Input::IsKey(DIK_W))
	{
		Decelerate();
		NextState_ += M_BREAK;
	}
	//左にカーブする
	if (Input::IsKey(DIK_A) && !Input::IsKey(DIK_D))
	{
		TurnLeft();
		NextState_ += M_TURNL;
	}
	//右にカーブする
	if (Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	{
		TurnRight();
		NextState_ += M_TURNR;
	}

	//ターボ
	//300は順位によって発動する時間が変動する(最下位から5秒,10秒,15秒,20秒)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
		NextState_ = M_TURBO;
	}
	
	if (NextState_ != VirtualState_)
	{
		//変化が起きたらGhostDataに格納
		GhostData_Command_.push_back(NextState_);
		GhostData_Frame_.push_back(ProgFrame_);
		//経過フレームを0にする
		ProgFrame_ = 0;
		VirtualState_ = NextState_;
	}
	NextState_ = Initial_;
	ProgFrame_++;
}

void Player::ThrowData()
{
	Storage::ThrowData(GhostData_Command_, GhostData_Frame_);
}
