#include "Computer.h"
#include "Engine/Model.h"
#include "Course.h"
#include "Player.h"

Computer::Computer(GameObject* parent)
	: Airframe(parent, "Computer"), VirtualState_(NULL), NextState_(NULL), UpdateDecider((rand() % 10) + 20)
{
}

Computer::~Computer()
{
}

void Computer::UpdateState()
{
	static char UpdateLimit = 0;	//�X�V�񐔂ɐ����������Ă݂�
	char Random = rand() % 100;

	if (UpdateLimit == 0)
	{
		XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
		mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

		XMVECTOR Straight = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
		XMVECTOR Left = XMVectorSet(-0.5f, -1.0f, 0.0f, 0.0f);
		XMVECTOR Right = XMVectorSet(0.5f, -1.0f, 0.0f, 0.0f);

		Straight = XMVector3TransformCoord(Straight, mRotate);
		Left = XMVector3TransformCoord(Left, mRotate);
		Right = XMVector3TransformCoord(Right, mRotate);

		Straight = XMVector3Normalize(Straight);
		Left = XMVector3Normalize(Left);
		Right = XMVector3Normalize(Right);

		XMFLOAT3 matS, matL, matR;
		XMStoreFloat3(&matS, Straight);
		XMStoreFloat3(&matL, Left);
		XMStoreFloat3(&matR, Right);

		Course* pCourse = (Course*)FindObject("Course");
		short hCourseModel = (short)pCourse->GetModelHandle();

		RayCastData Ray_Straight;	//�^�������Ƀ��C���΂�
		Ray_Straight.start = transform_.position_;   //���C�̔��ˈʒu
		Ray_Straight.dir = matS;					 //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Straight); //���C�𔭎�

		RayCastData Ray_Right;		//�΂߉E�Ƀ��C���΂�
		Ray_Right.start = transform_.position_;   //���C�̔��ˈʒu
		Ray_Right.dir = matR;				      //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Right); //���C�𔭎�

		RayCastData Ray_Left;		//�΂ߍ��Ƀ��C���΂�
		Ray_Left.start = transform_.position_;   //���C�̔��ˈʒu
		Ray_Left.dir = matL;				     //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Left); //���C�𔭎�

		if (Ray_Straight.hit && Ray_Right.hit && Ray_Left.hit)
		{
			SetNextState(M_ACCEL);
			if (Ray_Straight.dist > Ray_Right.dist && Ray_Straight.dist > Ray_Left.dist)	//�^�������ɔ�΂������C���ł����������ꍇ
			{
				if (Random < 90)
				{
					ResetNextState(M_TURNR);
					ResetNextState(M_TURNL);
				}
				else if (Random < 95)
				{
					SetNextState(M_TURNR);
					ResetNextState(M_TURNL);
				}
				else
				{
					SetNextState(M_TURNL);
					ResetNextState(M_TURNR);
				}
			}
			if (Ray_Right.dist > Ray_Straight.dist && Ray_Right.dist > Ray_Left.dist)
			{
				if (Random < 95)
				{
					SetNextState(M_TURNR);
					ResetNextState(M_TURNL);
				}
				else
				{
					ResetNextState(M_TURNR);
					ResetNextState(M_TURNL);
				}
				
			}
			if (Ray_Left.dist > Ray_Straight.dist && Ray_Left.dist > Ray_Right.dist)
			{
				if (Random < 95)
				{
					SetNextState(M_TURNL);
					ResetNextState(M_TURNR);
				}
				else
				{
					ResetNextState(M_TURNR);
					ResetNextState(M_TURNL);
				}
			}
		}
	}
	
	if (UpdateLimit >= UpdateDecider)
	{
		UpdateDecider = (rand() % 10) + 20;
		UpdateLimit = NULL;
	}
	else
	{
		UpdateLimit++;
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
