#pragma once
#include<Windows.h>

struct PARTS_NUM
{
	char COST;		//�R�X�g
	short ENGINE;	//�G���W��
	short BODY;		//�{�f�B
	short WING;		//��
	short COCKPIT;	//�R�b�N�s�b�g
	short PATTERN;	//�͗l
};

enum PARTS
{
	PARTS_ENGINE,	//�G���W��
	PARTS_BODY,		//�{�f�B
	PARTS_WING,		//��
	PARTS_COCKPIT,	//�R�b�N�s�b�g
	PARTS_END
};

namespace Option
{
	void Init();

	void SetParts(PARTS_NUM Parts);
	int GetParts(PARTS parts);

	void SetCourse(char course);
	char GetCourse();

	void SetColor(int color,PARTS category);
	int GetColor(PARTS category);
};