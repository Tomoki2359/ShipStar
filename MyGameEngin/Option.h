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
//リプレイのみリザルト画面からの呼び出し限定とする
enum Mode
{
	MODE_VSCOM,		//コンピュータとの対戦
	MODE_SOLO,		//自身のみ
	MODE_REPLAY,	//リプレイ
	MODE_VSGHOST,	//ゴーストとの対戦
	MODE_ONLYGHOST	//ゴーストのみの再生
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