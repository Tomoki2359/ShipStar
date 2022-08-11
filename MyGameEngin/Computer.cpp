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
	static char UpdateLimit = 0;	//更新回数に制限をかけてみる
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

		RayCastData Ray_Straight;	//真っ直ぐにレイを飛ばす
		Ray_Straight.start = transform_.position_;   //レイの発射位置
		Ray_Straight.dir = matS;					 //レイの方向
		Model::RayCast(hCourseModel, &Ray_Straight); //レイを発射

		RayCastData Ray_Right;		//斜め右にレイを飛ばす
		Ray_Right.start = transform_.position_;   //レイの発射位置
		Ray_Right.dir = matR;				      //レイの方向
		Model::RayCast(hCourseModel, &Ray_Right); //レイを発射

		RayCastData Ray_Left;		//斜め左にレイを飛ばす
		Ray_Left.start = transform_.position_;   //レイの発射位置
		Ray_Left.dir = matL;				     //レイの方向
		Model::RayCast(hCourseModel, &Ray_Left); //レイを発射

		if (Ray_Straight.hit && Ray_Right.hit && Ray_Left.hit)
		{
			SetNextState(M_ACCEL);
			if (Ray_Straight.dist > Ray_Right.dist && Ray_Straight.dist > Ray_Left.dist)	//真っ直ぐに飛ばしたレイが最も長かった場合
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
	
	//前進する
	if (VirtualState_ & M_ACCEL)
	{
		Accelerate();
	}
	//ブレーキする
	if (VirtualState_ & NULL)
	{
		Decelerate();
	}
	//右にカーブする
	if (VirtualState_ & M_TURNR && !(VirtualState_ & M_TURNL))
	{
		TurnRight();
	}
	//左にカーブする
	if (VirtualState_ & M_TURNL && !(VirtualState_ & M_TURNR))
	{
		TurnLeft();
	}
	//下降する
	if (VirtualState_ & M_DESCENT && !(VirtualState_ & M_RISE))
	{
		Descent();
	}
	//上昇する
	if (VirtualState_ & M_RISE && !(VirtualState_ & M_DESCENT))
	{
		Rise();
	}
	
	//ターボ
	//300は順位によって発動する時間が変動する(最下位から5秒,10秒,15秒,20秒)
	if (tTurbo_ >= 300 && (VirtualState_ & M_TURBO))
	{
		tTurbo_ = 0;
		Turbo();
	}

	//状態変化がある場合にのみ呼び出す
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
