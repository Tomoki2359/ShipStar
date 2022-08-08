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
