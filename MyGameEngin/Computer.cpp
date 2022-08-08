#include "Computer.h"
#include "Player.h"

Computer::Computer(GameObject* parent)
	: Airframe(parent, "Computer"), VirtualState_(NULL), NextState_(M_TURNL)
{
}

Computer::~Computer()
{
}

void Computer::UpdateState()
{
	//�O�i����
	if (VirtualState_ & M_ACCEL)
	{
		Accelerate();
	}
	//�u���[�L����
	if (VirtualState_ & NULL)
	{
		Decelerate();
	}
	//�E�ɃJ�[�u����
	if (VirtualState_ & M_TURNR && !(VirtualState_ & M_TURNL))
	{
		TurnRight();
	}
	//���ɃJ�[�u����
	if (VirtualState_ & M_TURNL && !(VirtualState_ & M_TURNR))
	{
		TurnLeft();
	}
	//���~����
	if (VirtualState_ & M_DESCENT && !(VirtualState_ & M_RISE))
	{
		Descent();
	}
	//�㏸����
	if (VirtualState_ & M_RISE && !(VirtualState_ & M_DESCENT))
	{
		Rise();
	}
	
	//�^�[�{
	//300�͏��ʂɂ���Ĕ������鎞�Ԃ��ϓ�����(�ŉ��ʂ���5�b,10�b,15�b,20�b)
	if (tTurbo_ >= 300 && (VirtualState_ & M_TURBO))
	{
		tTurbo_ = 0;
		Turbo();
	}

	//��ԕω�������ꍇ�ɂ̂݌Ăяo��
	if (VirtualState_ != NextState_)
	{
		ChangeState();
	}
}

void Computer::ChangeState()
{
	VirtualState_ = NextState_;
}
