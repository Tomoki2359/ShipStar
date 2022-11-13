#include "Option.h"
namespace Option
{
	PARTS_NUM PartsList;
	char Course;
	int color_[PARTS_END];

	void Init()
	{
		ZeroMemory(&PartsList, sizeof(PartsList));
		Course = NULL;
	}

	void SetParts(PARTS_NUM Parts)
	{
		PartsList = Parts;
	}

	int GetParts(PARTS parts)
	{
		switch (parts)
		{
		case PARTS_ENGINE:
			return PartsList.ENGINE;
			break;
		case PARTS_BODY:
			return PartsList.BODY;
			break;
		case PARTS_WING:
			return PartsList.WING;
			break;
		case PARTS_COCKPIT:
			return PartsList.COCKPIT;
			break;
		default:
			break;
		}
	}

	void SetCourse(char course)
	{
		Course = course;
	}

	char GetCourse()
	{
		return Course;
	}
	void SetColor(int color, PARTS category)
	{
		color_[category] = color;
	}

	int GetColor(PARTS category)
	{
		return color_[category];
	}
}