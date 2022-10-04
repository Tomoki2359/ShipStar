#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <vector>

class Course;
class Airframe;
class Player;
class PlayScene;

class Navigation : public GameObject
{
	enum
	{
		left,
		right,
		front,
		back
	};

	enum
	{
		UPPER_LEFT,
		UPPER_RIGHT,
		LOWER_LEFT,
		LOWER_RIGHT,
		DIVISION_MAX
	};

	std::vector<XMFLOAT3> Checkpoint_;
	Course* pCourse_;
	Player* pPlayer_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;

	XMFLOAT3 Upper_Goal;
	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matU = XMFLOAT3(0.0f, 1.0f, 0.0f);
	const XMFLOAT3 matD = XMFLOAT3(0.0f, -1.0f, 0.0f);
	const XMFLOAT3 matB = XMFLOAT3(0.0f, 0.0f, 1.0f);
	const XMFLOAT3 matF = XMFLOAT3(0.0f, 0.0f, -1.0f);

	const char Turn_ = 5;			//��]�Ɏg��
	const float Adjuster_ = 1.0f;	//�ʒu�̔������Ɏg��
	const XMFLOAT3 Initial = XMFLOAT3(NULL, NULL, NULL);
	const int out = 10;

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2��XMFLOAT3�𑫂�
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2��XMFLOAT3�̒��Ԃ�����o��
	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	const short Range_ = 500;			//���悠����̑����͈�
	const char Sky_ = 100;			//���C���΂�����
	const char Move_ = 50;			//�ړ���
	const XMFLOAT3 Shot_ = XMFLOAT3(0.0f, -1.0f, 0.0f);	//�^���ɔ��˂��郌�C

	void Scan();	//�R�[�X��ǂݎ���ă`�F�b�N�|�C���g��ݒu����

	int GetShortest(RayCastData L, RayCastData R, RayCastData F, RayCastData B);

	int Correcter(float Target);	//15�����݂ɋ�������

public:
	friend Airframe;
	friend PlayScene;

	Navigation(GameObject* parent);
	~Navigation();

	//������
	void Initialize() override;

	void Update() override;

	//�J��
	void Release() override;

};