#pragma once
#include "Navigation.h"
#include "CSVReader.h"
#include "Engine/GameObject.h"

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
	PARTS_PATTERN	//�͗l
};

enum STATUS_ID
{
	MAX_SPEED,	//�ō����x
	ACCELE,		//�����x
	TURBO,		//�^�[�{�l
	ENDURANCE,	//�ϋv�l
	MAX_STATUS	//�Ō��
};

//�����V�[�����Ǘ�����N���X
class Airframe : public GameObject
{
	//struct PASSAGE	//Checkpoint�Ƃ�����ʉ߂������̍\����
	//{
	//	XMFLOAT3 Point;
	//	bool Pass;
	//};
	//
	//std::vector<PASSAGE> PassageChecker_;

	XMFLOAT3 Respawn_;
	int SaveCount_;

	short hModel_;   //���f���ԍ�
	float speed_;	//���݂̑��x
	bool cAscent_;	//�㏸��Ԃ��ǂ���
	bool cDescent_;	//���~��Ԃ��ǂ���
	bool lCurve_;	//���ɋȂ����Ă����Ԃ��ǂ���
	bool rCurve_;	//�E�ɋȂ����Ă����Ԃ��ǂ���
	CSVReader csv;	//csv��ǂݍ��ނ��߂̊֐�
	bool start_;	//�X�^�[�g�������ǂ���
	short timeCount_;	//���[�X���Ԃ̊Ǘ��ƃJ�E���g�_�E��
	bool Side_;		//�����ɂ��邩�O���ɂ��邩(true�œ����Afalse�ŊO��)

	XMFLOAT3 PrevPosition_;	//���O�̈ʒu

	Navigation* pNav_;

	short Lap_;		//����(�s���΍�)

	bool IsGoal_;	//�S�[����������

	//void PassPoint();	//�e�`�F�b�N�|�C���g��ʉ߂���������

	void LapMeasure();	//���񐔂̔���

	void JudgeGoal();	//�S�[���̔���

	void JudgeSide();

	void ResetOverRotate(float* rotate);	//0~360���ɗ��߂Ă����ׂ̂���
protected:
	short tTurbo_;	//�^�[�{�l�𒙂߂�
	bool cTurbo_;	//�^�[�{��Ԃ��ǂ���
	XMFLOAT3 GetDistance(GameObject* pTarget);
	float PrevHeight_;

	virtual void StayInside() = 0;
	virtual void StayOutside() = 0;

public:
	PARTS_NUM PartsSet;
	float status_[MAX_STATUS];
	std::string fileName_;
	bool cCamera_;	//�J���������邩�ǂ���

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Airframe(GameObject* parent);
	Airframe(GameObject* parent, std::string name);		//�p���p�R���X�g���N�^

	//�f�X�g���N�^
	~Airframe();

	//������
	void Initialize() override;

	virtual void UpdateState() = 0;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//������ʒu�Ȃǂ̌��E
	void Limit();

	void SetPartsNum(char engine, char body, char wing, char cockpit, char pattern);

	//�X�e�[�^�X�̎擾
	void SetStatus();

	//����
	void Accelerate();

	//����
	void Decelerate();

	//�E�J�[�u
	void TurnRight();

	//���J�[�u
	void TurnLeft();

	//�㏸
	void Rise();

	//���~
	void Descent();

	//�^�[�{
	void Turbo();

	//�R�[�X�O�ɏo�Ȃ��悤�ɂ��Ă݂�
	void CourseoutSaver();

	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	bool GetisGoal() { return IsGoal_; }

	bool GetStart() { return start_; }
};