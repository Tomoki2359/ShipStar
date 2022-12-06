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
//���v���C�̂݃��U���g��ʂ���̌Ăяo������Ƃ���
enum Mode
{
	MODE_VSCOM,		//�R���s���[�^�Ƃ̑ΐ�
	MODE_SOLO,		//���g�̂�
	MODE_REPLAY,	//���v���C
	MODE_VSGHOST,	//�S�[�X�g�Ƃ̑ΐ�
	MODE_ONLYGHOST	//�S�[�X�g�݂̂̍Đ�
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