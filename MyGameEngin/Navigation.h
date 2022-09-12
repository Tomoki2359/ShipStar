#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <vector>

class Course;

class Navigation : public GameObject
{
	enum
	{
		left,
		right,
		upper,
		lower
	};

	enum
	{
		UPPER_LEFT,
		UPPER_RIGHT,
		LOWER_LEFT,
		LOWER_RIGHT,
		DIVISION_MAX
	};

	Course* pCourse_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;



	RayCastData L_side_;	//�����̃��C
	RayCastData R_side_;	//�E���̃��C
	RayCastData Finder_;

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matU = XMFLOAT3(0.0f, 1.0f, 0.0f);

	const char Turn_ = 5;			//��]�Ɏg��
	const float Adjuster_ = 1.0f;	//�ʒu�̔������Ɏg��

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2��XMFLOAT3�𑫂�
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2��XMFLOAT3�̒��Ԃ�����o��
	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);
	//int ReturnShortest(float Left, float Right, float Upper, float Lower);
	//int ReturnLongest(float Left, float Right, float Upper, float Lower);

	const char Range_ = 10;			//���悠����̑����͈�
	const char Sky_ = 100;			//���C���΂�����
	const char Move_ = 2;			//�ړ���
	const XMFLOAT3 Shot_ = XMFLOAT3(0.0f, -1.0f, 0.0f);	//�^���ɔ��˂��郌�C

	void Scan();	//�R�[�X��ǂݎ���ă`�F�b�N�|�C���g��ݒu����

public:
	Navigation(GameObject* parent);
	~Navigation();

	//������
	void Initialize() override;

	//�J��
	void Release() override;

	std::vector<XMFLOAT3> Checkpoint_;

	XMFLOAT3 Upper_Goal;
	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;
};