#pragma once
#include "Engine/GameObject.h"

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
	short hModel_;    //���f���ԍ�
	float speed_;	//���݂̑��x
	bool cAscent_;	//�㏸��Ԃ��ǂ���
	bool cDescent_;	//���~��Ԃ��ǂ���
	bool lCurve_;	//���ɋȂ����Ă����Ԃ��ǂ���
	bool rCurve_;	//�E�ɋȂ����Ă����Ԃ��ǂ���

protected:
	short tTurbo_;	//�^�[�{�l�𒙂߂�
	bool cTurbo_;	//�^�[�{��Ԃ��ǂ���

public:
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

	//�X�e�[�^�X�̎擾
	virtual void SetStatus();

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
};