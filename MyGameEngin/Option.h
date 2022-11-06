#pragma once
#include<Windows.h>

struct PARTS_NUM
{
	char COST;		//コスト
	short ENGINE;	//エンジン
	short BODY;		//ボディ
	short WING;		//翼
	short COCKPIT;	//コックピット
	short PATTERN;	//模様
};

enum PARTS
{
	PARTS_ENGINE,	//エンジン
	PARTS_BODY,		//ボディ
	PARTS_WING,		//翼
	PARTS_COCKPIT,	//コックピット
	PARTS_END
};

namespace Option
{
	void Init();

	void SetParts(PARTS_NUM Parts);
	int GetParts(PARTS parts);

	void SetCourse(char course);
	char GetCourse();
};