#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <list>

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

	Course* pCourse_;
	std::list<XMFLOAT3> Checkpoint_;
	XMFLOAT3 Upper_;
	XMFLOAT3 Lower_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;

	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;
	XMFLOAT3 Upper_Goal;

	RayCastData L_side_;	//�����̃��C
	RayCastData R_side_;	//�E���̃��C
	RayCastData A_side_;	//�㕔�̃��C
	RayCastData U_side_;	//�����̃��C

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matA = XMFLOAT3(0.0f, 1.0f, 0.0f);
	const XMFLOAT3 matU = XMFLOAT3(0.0f, -1.0f, 0.0f);

	const char Turn_ = 5;			//��]�Ɏg��
	const float Adjuster_ = 1.0f;	//�ʒu�̔������Ɏg��

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2��XMFLOAT3�𑫂�
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2��XMFLOAT3�̒��Ԃ�����o��
	int ReturnShortest(float Left, float Right, float Upper, float Lower);
	int ReturnLongest(float Left, float Right, float Upper, float Lower);

	void Scan();	//�R�[�X��ǂݎ���ă`�F�b�N�|�C���g��ݒu����

public:
	Navigation(GameObject* parent);
	~Navigation();

	//������
	void Initialize() override;

	//�J��
	void Release() override;
};