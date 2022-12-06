#include "Ghost.h"
#include "Storage.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Option.h"

Ghost::Ghost(GameObject* parent)
	: Airframe(parent, "Ghost"), ProgFrame_(0), Endcount_(0)
{
	GhostData_Command_.clear();
	GhostData_Frame_.clear();

	//モードによって呼び出し元を変更
	switch (Option::GetMode())
	{
	case MODE_REPLAY:	//リプレイモードならば直前のデータを呼び出す
		Storage::CopyData(GhostData_Command_, GhostData_Frame_);
		break;
	case MODE_ONLYGHOST://ゴーストとの対戦、またはゴーストのみ再生ならばゴーストのデータを呼び出す
	case MODE_VSGHOST:
		Storage::LoadData(GhostData_Command_, GhostData_Frame_);
		break;
	default:
		break;
	}
}

Ghost::~Ghost()
{
	GhostData_Command_.clear();
	GhostData_Frame_.clear();
}

void Ghost::UpdateState()
{
	++ProgFrame_;
	if (!GhostData_Frame_.empty())
	{
		if (ProgFrame_ >= GhostData_Frame_.front())
		{
			ProgFrame_ = 0;							//経過フレームを0にする
			GhostData_Frame_.pop_front();			//Frameの先頭を消去
			NextState_ = GhostData_Command_.front();
			GhostData_Command_.pop_front();
		}
	}

	if (NextState_ & M_ACCEL)
	{
		Accelerate();
	}
	if (NextState_ & M_BREAK)
	{
		Decelerate();
	}
	if (NextState_ & M_TURNL)
	{
		TurnLeft();
	}
	if (NextState_ & M_TURNR)
	{
		TurnRight();
	}
	if (NextState_ & M_TURBO)
	{
		Turbo();
	}

	//現在のモードがリプレイまたはゴーストのみならば
	char mode = Option::GetMode();
	if (mode == MODE_REPLAY || mode == MODE_ONLYGHOST)
	{
		CallOnly();
	}
}

void Ghost::StayInside()
{
}

void Ghost::CallOnly()
{
	//Spaceキーを2回押したらリプレイ終了
	if (Input::IsKeyDown(DIK_SPACE))
	{
		Endcount_++;
	}

	if (GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
		return;
	}

	if (Endcount_ >= ReplayEnd_)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
		return;
	}
}