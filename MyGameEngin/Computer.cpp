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
	static char UpdateLimit = NULL;	//更新回数に制限をかけてみる
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

			if (PrCommand.Move_Front > PrCommand.Move_Right && PrCommand.Move_Front > PrCommand.Move_Left)	//真っ直ぐに飛ばしたレイが最も長かった場合
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
	
	//ターボ
	//300は順位によって発動する時間が変動する(最下位から5秒,10秒,15秒,20秒)
	if (tTurbo_ >= 300 && (VirtualState_ & M_TURBO))
	{
		tTurbo_ = NULL;
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

void Computer::TurnDirection()
{
	//レイ変換用
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR Straight = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	Straight = XMVector3TransformCoord(Straight, mRotate);
	Straight = XMVector3Normalize(Straight);
	XMFLOAT3 matS;
	XMStoreFloat3(&matS, Straight);

	//レイキャスト
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData Ray_Straight;	//真っ直ぐにレイを飛ばす
	Ray_Straight.start = transform_.position_;   //レイの発射位置
	Ray_Straight.dir = matS;					 //レイの方向
	Model::RayCast(hCourseModel, &Ray_Straight); //レイを発射

	if (Ray_Straight.dist < 5 && Ray_Straight.dist > 3 && Ray_Straight.hit)
	{
		Transform tr = transform_;
		tr.position_.z += Ray_Straight.dist;

		mRotate = XMMatrixRotationX(XMConvertToRadians(tr.rotate_.x));
		mRotate *= XMMatrixRotationY(XMConvertToRadians(tr.rotate_.y));
		//mRotate *= XMMatrixRotationZ(XMConvertToRadians(tr.rotate_.z));

		XMVECTOR Left = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR Right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

		Left = XMVector3TransformCoord(Left, mRotate);
		Right = XMVector3TransformCoord(Right, mRotate);

		XMFLOAT3 matL, matR;
		XMStoreFloat3(&matL, Left);
		XMStoreFloat3(&matR, Right);

		RayCastData Ray_Right;		//斜め右にレイを飛ばす
		Ray_Right.start = tr.position_;   //レイの発射位置
		Ray_Right.dir = matR;				      //レイの方向
		Model::RayCast(hCourseModel, &Ray_Right); //レイを発射

		RayCastData Ray_Left;		//斜め左にレイを飛ばす
		Ray_Left.start = tr.position_;   //レイの発射位置
		Ray_Left.dir = matL;				     //レイの方向
		Model::RayCast(hCourseModel, &Ray_Left); //レイを発射

		if (Ray_Right.dist > Ray_Left.dist)
		{
			PrCommand.Move_Right = Ray_Right.dist * 2;
		}
		if (Ray_Left.dist > Ray_Right.dist)
		{
			PrCommand.Move_Left = Ray_Left.dist * 2;
		}
	}
}

void Computer::StayInside()
{
}

void Computer::RayCasting()
{
	//レイ変換用
	XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//mRotate *= XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

	XMVECTOR Straight = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Left = XMVectorSet(-1.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Right = XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f);

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

	//レイキャスト
	Course* pCourse = (Course*)FindObject("Course");
	short hCourseModel = (short)pCourse->GetModelHandle();

	RayCastData Ray_Straight;	//真っ直ぐにレイを飛ばす
	Ray_Straight.start = transform_.position_;   //レイの発射位置
	Ray_Straight.dir = matS;					 //レイの方向
	Model::RayCast(hCourseModel, &Ray_Straight); //レイを発射
	if (Ray_Straight.hit)
	{
		PrCommand.Move_Front = Ray_Straight.dist;
	}
	else
	{
		PrCommand.Move_Front = -1;
	}

	RayCastData Ray_Right;		//斜め右にレイを飛ばす
	Ray_Right.start = transform_.position_;   //レイの発射位置
	Ray_Right.dir = matR;				      //レイの方向
	Model::RayCast(hCourseModel, &Ray_Right); //レイを発射
	if (Ray_Right.hit)
	{
		PrCommand.Move_Right = Ray_Right.dist;
	}
	else
	{
		PrCommand.Move_Right = -1;
	}

	RayCastData Ray_Left;		//斜め左にレイを飛ばす
	Ray_Left.start = transform_.position_;   //レイの発射位置
	Ray_Left.dir = matL;				     //レイの方向
	Model::RayCast(hCourseModel, &Ray_Left); //レイを発射
	if (Ray_Left.hit)
	{
		PrCommand.Move_Left = Ray_Left.dist;
	}
	else
	{
		PrCommand.Move_Left = -1;
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