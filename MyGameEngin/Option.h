#pragma once
#include "Airframe.h"

namespace Option
{
	void Init();

	void SetParts(PARTS_NUM Parts);
	PARTS_NUM GetParts();

	void SetCourse(char course);
	char GetCourse();
};