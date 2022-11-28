#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Storage.h"

void Player::StayInside()
{
}

//�R���X�g���N�^
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
	//�O�i����
	if (Input::IsKey(DIK_W) && !Input::IsKey(DIK_S))
	{
		Accelerate();
		NextState_ += M_ACCEL;
	}
	//�u���[�L����
	if (Input::IsKey(DIK_S) && !Input::IsKey(DIK_W))
	{
		Decelerate();
		NextState_ += M_BREAK;
	}
	//���ɃJ�[�u����
	if (Input::IsKey(DIK_A) && !Input::IsKey(DIK_D))
	{
		TurnLeft();
		NextState_ += M_TURNL;
	}
	//�E�ɃJ�[�u����
	if (Input::IsKey(DIK_D) && !Input::IsKey(DIK_A))
	{
		TurnRight();
		NextState_ += M_TURNR;
	}

	//�^�[�{
	//300�͏��ʂɂ���Ĕ������鎞�Ԃ��ϓ�����(�ŉ��ʂ���5�b,10�b,15�b,20�b)
	if (tTurbo_ >= 300 && Input::IsKeyDown(DIK_C))
	{
		tTurbo_ = 0;
		Turbo();
		NextState_ = M_TURBO;
	}
	
	if (NextState_ != VirtualState_)
	{
		//�ω����N������GhostData�Ɋi�[
		GhostData_Command_.push_back(NextState_);
		GhostData_Frame_.push_back(ProgFrame_);
		//�o�߃t���[����0�ɂ���
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
