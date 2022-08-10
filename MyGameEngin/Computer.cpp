#include "Computer.h"
#include "Engine/Model.h"
#include "Course.h"
#include "Player.h"

Computer::Computer(GameObject* parent)
	: Airframe(parent, "Computer"), VirtualState_(NULL), NextState_(NULL)
{
}

Computer::~Computer()
{
}

void Computer::UpdateState()
{
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData Straight;	//�^�������Ƀ��C���΂�
	Straight.start = transform_.position_;   //���C�̔��ˈʒu
	Straight.dir = XMFLOAT3(0, -1, 1);       //���C�̕���	�R�[�X���ł����炻�ꂼ�������ύX����
	Model::RayCast(hCourseModel, &Straight); //���C�𔭎�

	RayCastData Right;		//�΂߉E�Ƀ��C���΂�
	Right.start = transform_.position_;   //���C�̔��ˈʒu
	Right.dir = XMFLOAT3(1, -1, 1);       //���C�̕���
	Model::RayCast(hCourseModel, &Right); //���C�𔭎�

	RayCastData Left;		//�΂ߍ��Ƀ��C���΂�
	Left.start = transform_.position_;   //���C�̔��ˈʒu
	Left.dir = XMFLOAT3(-1, -1, 1);       //���C�̕���
	Model::RayCast(hCourseModel, &Left); //���C�𔭎�

	if (Straight.hit && Right.hit && Left.hit)
	{
		SetNextState(M_ACCEL);
		if (Straight.dist > Right.dist && Straight.dist > Left.dist)	//�^�������ɔ�΂������C���ł����������ꍇ
		{
			ResetNextState(M_TURNR);
			ResetNextState(M_TURNL);
		}
		if (Right.dist > Straight.dist && Right.dist > Left.dist)
		{
			SetNextState(M_TURNR);
			ResetNextState(M_TURNL);
		}
		if (Left.dist > Straight.dist && Left.dist > Right.dist)
		{
			SetNextState(M_TURNL);
			ResetNextState(M_TURNR);
		}
	}

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

void Computer::SetNextState(char M_STATUS)
{
	if (!(NextState_ & M_STATUS))
	{
		NextState_ += M_STATUS;
	}
}

void Computer::ResetNextState(char M_STATUS)
{
	if (NextState_ & M_STATUS)
	{
		NextState_ -= M_STATUS;
	}
}
