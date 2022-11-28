#pragma once
#include<Windows.h>
#include<string>

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

//プレイモード
enum Mode
{
	MODE_VSCOM,
	MODE_SOLO,
	MODE_REPLAY,
	MODE_VSGHOST,
	MODE_ONLYGHOST
};

namespace Option
{
	void Init();

	void SetParts(PARTS_NUM Parts);
	int GetParts(PARTS parts);

	void SetCourse(char course);
	char GetCourse();
	std::string GetCourseName();

	void SetColor(int color,PARTS category);
	int GetColor(PARTS category);

	void SetMode(char mode);
	char GetMode();
};