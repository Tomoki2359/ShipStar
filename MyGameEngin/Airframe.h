#pragma once
#include "Navigation.h"
#include "CSVReader.h"
#include "Option.h"
#include "Engine/GameObject.h"

const short Past = 120;

//�e��Ԃ̒�`
const char M_TURBO = 0x20;
const char M_TURNL = 0x04;
const char M_TURNR = 0x02;
const char M_ACCEL = 0x01;
const char M_BREAK = 0x08;

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
	const float RotationRate_Y = 1.5f;
	const float RotationRate_Z = 2.0f;
	const float RotationMax_Z = 40.0f;

	XMFLOAT3 RespawnPos_[Past];
	XMFLOAT3 RespawnRot_[Past];
	short RespawnUpdate_;

	short hModel_;   //���f���ԍ�
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

	void LapMeasure();	//���񐔂̔���

	void JudgeGoal();	//�S�[���̔���

	void ComCorrection();

	void ResetOverRotate(float* rotate);	//0~360���ɗ��߂Ă����ׂ̂���

	void Respawn();			//���A����

	void FixInclination();	//��]�̒���
	void TurboProcess();	//�^�[�{����
	void MoveProcess();		//�ړ�����
	void ChaseCamera();		//�J������ǂ킹��

protected:
	//8�r�b�g�A��ʃr�b�g���珇��(����A����A�^�[�{�A�㏸�A���~�A���J�[�u�A�E�J�[�u�A�A�N�Z���u���[�L)
	//�L���̔���A�A�N�Z���u���[�L��1��true�A0��false�Ƃ���B
	char VirtualState_;	//���z�̎v�l���i�镔��(��)
	char NextState_;	//���̃t���[���̏��

	float speed_;	//���݂̑��x
	void JudgeSide();
	void JudgeSide(RayCastData& data);
	bool JudgeSide(XMFLOAT3 pos);

	short tTurbo_;	//�^�[�{�l�𒙂߂�
	bool cTurbo_;	//�^�[�{��Ԃ��ǂ���
	XMFLOAT3 GetDistance(GameObject* pTarget);

	virtual void StayInside() = 0;

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

	//�^�[�{
	void Turbo();

	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	bool GetisGoal() { return IsGoal_; }

	bool GetStart() { return start_; }

	float GetSpeed() { return speed_; }
};