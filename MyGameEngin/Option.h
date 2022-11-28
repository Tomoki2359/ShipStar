#pragma once
#include<Windows.h>
#include<string>

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

//�v���C���[�h
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