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

	RayCastData Straight;	//真っ直ぐにレイを飛ばす
	Straight.start = transform_.position_;   //レイの発射位置
	Straight.dir = XMFLOAT3(0, -1, 1);       //レイの方向	コースができたらそれぞれ方向を変更する
	Model::RayCast(hCourseModel, &Straight); //レイを発射

	RayCastData Right;		//斜め右にレイを飛ばす
	Right.start = transform_.position_;   //レイの発射位置
	Right.dir = XMFLOAT3(1, -1, 1);       //レイの方向
	Model::RayCast(hCourseModel, &Right); //レイを発射

	RayCastData Left;		//斜め左にレイを飛ばす
	Left.start = transform_.position_;   //レイの発射位置
	Left.dir = XMFLOAT3(-1, -1, 1);       //レイの方向
	Model::RayCast(hCourseModel, &Left); //レイを発射

	if (Straight.hit && Right.hit && Left.hit)
	{
		SetNextState(M_ACCEL);
		if (Straight.dist > Right.dist && Straight.dist > Left.dist)	//真っ直ぐに飛ばしたレイが最も長かった場合
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
