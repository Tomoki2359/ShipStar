#include "Ghost.h"
#include "Storage.h"
#include "Engine/SceneManager.h"

Ghost::Ghost(GameObject* parent)
	: Airframe(parent, "Ghost"), ProgFrame_(0)
{
	GhostData_Command_.clear();
	GhostData_Frame_.clear();
	Storage::CopyData(GhostData_Command_, GhostData_Frame_);
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
			ProgFrame_ = 0;							//Œo‰ßƒtƒŒ[ƒ€‚ğ0‚É‚·‚é
			GhostData_Frame_.pop_front();			//Frame‚Ìæ“ª‚ğÁ‹
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

	if (GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
}

void Ghost::StayInside()
{
}
