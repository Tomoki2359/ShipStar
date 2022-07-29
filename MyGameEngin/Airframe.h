#pragma once
#include "Engine/GameObject.h"

enum STATUS_ID
{
	MAX_SPEAD,	//�ō����x
	ACCELE,		//�����x
	TURBO,		//�^�[�{�l
	ENDURANCE,	//�ϋv�l
	MAX_STATUS	//�Ō��
};

//�����V�[�����Ǘ�����N���X
class Airframe : public GameObject
{
	short hModel_;    //���f���ԍ�
	float Spead_;	//���݂̑��x
	bool aRotate_;	//�㏸��Ԃ��ǂ���
	bool dRotate_;	//���~��Ԃ��ǂ���
	bool lRotate_;	//���ɋȂ����Ă����Ԃ��ǂ���
	bool rRotate_;	//�E�ɋȂ����Ă����Ԃ��ǂ���
	short tTurbo_;	//�^�[�{�l�𒙂߂�
	bool cTurbo_;	//�^�[�{��Ԃ��ǂ���
public:
	float status_[MAX_STATUS];
	std::string failName_;
	bool sCamera_;	//�J���������邩�ǂ���
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Airframe(GameObject* parent, std::string name);

	//�f�X�g���N�^
	~Airframe();

	//������
	void Initialize() override;

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
};