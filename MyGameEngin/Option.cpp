#include "Option.h"
namespace Option
{
	PARTS_NUM PartsList;
	char Course;

	void Init()
	{
		ZeroMemory(&PartsList, sizeof(PartsList));
		Course = NULL;
	}

	void SetParts(PARTS_NUM Parts)
	{
		PartsList = Parts;
	}

	PARTS_NUM GetParts()
	{
		return PartsList;
	}
	void SetCourse(char course)
	{
		Course = course;
	}

	char GetCourse()
	{
		return Course;
	}
}