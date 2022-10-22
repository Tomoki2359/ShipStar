#include "Computer.h"
#include "Engine/Model.h"
#include "Course.h"
#include "Player.h"
#include "PlayScene.h"

Computer::Computer(GameObject* parent)
	: Airframe(parent, "Computer"), VirtualState_(NULL), NextState_(NULL), UpdateDecider((rand() % 10) + 20), PrCommand()
{
}

Computer::~Computer()
{
}

void Computer::UpdateState()
{
	static char UpdateLimit = NULL;	//�X�V�񐔂ɐ����������Ă݂�
	char Random = rand() % 100;

	if (UpdateLimit == NULL)
	{
		
		RayCasting();
		TurnDirection();

		if (PrCommand.Move_Front > NULL && PrCommand.Move_Right > NULL && PrCommand.Move_Left > NULL)
		{
			SetNextState(M_ACCEL);

			PlayScene* pPlayScene = (PlayScene*)FindObject("PlayScene");
			for (auto i = pPlayScene->PlayerList_.begin(); i != pPlayScene->PlayerList_.end(); i++)
			{
				if (*i != this)
				{
					PosRel(*i);
				}
			}
			/*GameObject* pPlayer = FindObject("Player");
			PosRel(pPlayer);*/

			if (PrCommand.Move_Front > PrCommand.Move_Right && PrCommand.Move_Front > PrCommand.Move_Left)	//�^�������ɔ�΂������C���ł����������ꍇ
			{
				ResetNextState(M_TURNR);
				ResetNextState(M_TURNL);
			}
			if (PrCommand.Move_Right > PrCommand.Move_Front && PrCommand.Move_Right > PrCommand.Move_Left)
			{
				if (Random < Accuracy_)
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
			if (PrCommand.Move_Left > PrCommand.Move_Front && PrCommand.Move_Left > PrCommand.Move_Right)
			{
				if (Random < Accuracy_)
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

			//if (/*PrCommand.Move_Above > PrCommand.Move_Front &&*/ PrCommand.Move_Above > PrCommand.Move_Under)
			//{
			//	if (Random < Accuracy_)
			//	{
			//		SetNextState(M_RISE);
			//		ResetNextState(M_DESCENT);
			//	}
			//	else
			//	{
			//		ResetNextState(M_RISE);
			//		ResetNextState(M_DESCENT);
			//	}
			//}
			//else if (/*PrCommand.Move_Under > PrCommand.Move_Front &&*/ PrCommand.Move_Under > PrCommand.Move_Above)
			//{
			//	if (Random < Accuracy_)
			//	{
			//		SetNextState(M_DESCENT);
			//		ResetNextState(M_RISE);
			//	}
			//	else
			//	{
			//		ResetNextState(M_RISE);
			//		ResetNextState(M_DESCENT);
			//	}
			//}
			//else
			//{
			//	ResetNextState(M_RISE);
			//	ResetNextState(M_DESCENT);
			//}
			HeightAdjustment();
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
		tTurbo_ = NULL;
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

void Computer::HeightAdjustment()
{
	//���C�ϊ��p
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMFLOAT3 Ray = XMFLOAT3(0.0f, -1.0f, 0.0f);

	//���C�L���X�g
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData RayCast;
	RayCast.start = transform_.position_;   //���C�̔��ˈʒu
	RayCast.dir = Ray;					 //���C�̕���
	Model::RayCast(hCourseModel, &RayCast); //���C�𔭎�
	if (RayCast.hit && RayCast.dist != PrevHeight_)
	{
		if (PrevHeight_ > RayCast.dist)
		{
			Descent();
		}
		else
		{
			Rise();
		}
		PrevHeight_ = RayCast.dist;
	}
}

void Computer::TurnDirection()
{
	//���C�ϊ��p
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR Straight = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	Straight = XMVector3TransformCoord(Straight, mRotate);
	Straight = XMVector3Normalize(Straight);
	XMFLOAT3 matS;
	XMStoreFloat3(&matS, Straight);

	//���C�L���X�g
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData Ray_Straight;	//�^�������Ƀ��C���΂�
	Ray_Straight.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Straight.dir = matS;					 //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Straight); //���C�𔭎�

	if (Ray_Straight.dist < 5 && Ray_Straight.dist > 3 && Ray_Straight.hit)
	{
		Transform tr = transform_;
		tr.position_.z += Ray_Straight.dist;

		mRotate = XMMatrixRotationX(XMConvertToRadians(tr.rotate_.x));
		mRotate *= XMMatrixRotationY(XMConvertToRadians(tr.rotate_.y));
		mRotate *= XMMatrixRotationZ(XMConvertToRadians(tr.rotate_.z));

		XMVECTOR Left = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR Above = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		XMVECTOR Under = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);

		Left = XMVector3TransformCoord(Left, mRotate);
		Right = XMVector3TransformCoord(Right, mRotate);
		Above = XMVector3TransformCoord(Above, mRotate);
		Under = XMVector3TransformCoord(Under, mRotate);

		XMFLOAT3 matL, matR, matA, matU;
		XMStoreFloat3(&matL, Left);
		XMStoreFloat3(&matR, Right);
		XMStoreFloat3(&matA, Above);
		XMStoreFloat3(&matU, Under);

		RayCastData Ray_Right;		//�΂߉E�Ƀ��C���΂�
		Ray_Right.start = tr.position_;   //���C�̔��ˈʒu
		Ray_Right.dir = matR;				      //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Right); //���C�𔭎�

		RayCastData Ray_Left;		//�΂ߍ��Ƀ��C���΂�
		Ray_Left.start = tr.position_;   //���C�̔��ˈʒu
		Ray_Left.dir = matL;				     //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Left); //���C�𔭎�

		RayCastData Ray_Above;	//��Ƀ��C���΂�
		Ray_Above.start = tr.position_;   //���C�̔��ˈʒu
		Ray_Above.dir = matA;					 //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Above); //���C�𔭎�

		RayCastData Ray_Under;	//���Ƀ��C���΂�
		Ray_Under.start = tr.position_;   //���C�̔��ˈʒu
		Ray_Under.dir = matU;					 //���C�̕���
		Model::RayCast(hCourseModel, &Ray_Under); //���C�𔭎�

		if (Ray_Right.dist > Ray_Left.dist)
		{
			PrCommand.Move_Right = Ray_Right.dist * 2;
		}
		if (Ray_Left.dist > Ray_Right.dist)
		{
			PrCommand.Move_Left = Ray_Left.dist * 2;
		}

		if (Ray_Above.dist > Ray_Under.dist)
		{
			PrCommand.Move_Above = Ray_Above.dist * 2;
		}
		if (Ray_Above.dist < Ray_Under.dist)
		{
			PrCommand.Move_Under = Ray_Under.dist * 2;
		}
	}
}

void Computer::StayInside()
{
}

void Computer::RayCasting()
{
	//���C�ϊ��p
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR Straight = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Left = XMVectorSet(-1.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Right = XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Above = XMVectorSet(0.0f, 1.0f, 1.0f, 0.0f);
	XMVECTOR Under = XMVectorSet(0.0f, -1.0f, 1.0f, 0.0f);

	Straight = XMVector3TransformCoord(Straight, mRotate);
	Left = XMVector3TransformCoord(Left, mRotate);
	Right = XMVector3TransformCoord(Right, mRotate);
	Above = XMVector3TransformCoord(Above, mRotate);
	Under = XMVector3TransformCoord(Under, mRotate);

	Straight = XMVector3Normalize(Straight);
	Left = XMVector3Normalize(Left);
	Right = XMVector3Normalize(Right);
	Above = XMVector3Normalize(Above);
	Under = XMVector3Normalize(Under);

	XMFLOAT3 matS, matL, matR, matA, matU;
	XMStoreFloat3(&matS, Straight);
	XMStoreFloat3(&matL, Left);
	XMStoreFloat3(&matR, Right);
	XMStoreFloat3(&matA, Above);
	XMStoreFloat3(&matU, Under);

	//���C�L���X�g
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData Ray_Straight;	//�^�������Ƀ��C���΂�
	Ray_Straight.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Straight.dir = matS;					 //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Straight); //���C�𔭎�
	if (Ray_Straight.hit)
	{
		PrCommand.Move_Front = Ray_Straight.dist;
	}
	else
	{
		PrCommand.Move_Front = -1;
	}

	RayCastData Ray_Right;		//�΂߉E�Ƀ��C���΂�
	Ray_Right.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Right.dir = matR;				      //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Right); //���C�𔭎�
	if (Ray_Right.hit)
	{
		PrCommand.Move_Right = Ray_Right.dist;
	}
	else
	{
		PrCommand.Move_Right = -1;
	}

	RayCastData Ray_Left;		//�΂ߍ��Ƀ��C���΂�
	Ray_Left.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Left.dir = matL;				     //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Left); //���C�𔭎�
	if (Ray_Left.hit)
	{
		PrCommand.Move_Left = Ray_Left.dist;
	}
	else
	{
		PrCommand.Move_Left = -1;
	}

	RayCastData Ray_Above;	//��Ƀ��C���΂�
	Ray_Above.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Above.dir = matA;					 //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Above); //���C�𔭎�
	if (Ray_Above.hit)
	{
		PrCommand.Move_Above = Ray_Above.dist;
	}
	else
	{
		PrCommand.Move_Above = -1;
	}

	RayCastData Ray_Under;	//���Ƀ��C���΂�
	Ray_Under.start = transform_.position_;   //���C�̔��ˈʒu
	Ray_Under.dir = matU;					 //���C�̕���
	Model::RayCast(hCourseModel, &Ray_Under); //���C�𔭎�
	if (Ray_Under.hit)
	{
		PrCommand.Move_Under = Ray_Under.dist;
	}
	else
	{
		PrCommand.Move_Under = -1;
	}
	
}

void Computer::PosRel(GameObject* pTarget)
{
	XMFLOAT3 dis = GetDistance(pTarget);
	XMVECTOR vec = XMLoadFloat3(&dis);
	XMVECTOR len = XMVector3Length(vec);
	float Length = XMVectorGetX(len);
	if(Length < Search_)
	{
		XMFLOAT3 Dis;
		XMStoreFloat3(&Dis, vec);
		if (Dis.x > NULL)
		{
			PrCommand.Move_Left += (Search_ - Length) / Hate_;
		}
		else if (Dis.x < NULL)
		{
			PrCommand.Move_Right += (Search_ - Length) / Hate_;
		}
	}
	else
	{
		return;
	}
}