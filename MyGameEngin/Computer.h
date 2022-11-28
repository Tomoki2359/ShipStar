#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	enum
	{
		PR_Front,
		PR_Right,
		PR_Left
	};

	char UpdateDecider;	//�X�V�p�x�𐶐�

	const float Hate_ = 5.0f;	//���I�u�W�F�N�g�̉e���͂��w��(��قǒ���)
	const char Search_ = 15;	//���I�u�W�F�N�g�ɉe������鋗��
	const char Accuracy_ = 98;	//���f�̐��m��

	struct Priority
	{
		float Move_Front;	//����
		float Move_Left;	//���ړ�
		float Move_Right;	//�E�ړ�
	} PrCommand;	//�e�R�}���h�̗D�揇�ʂ𔻒�

	XMFLOAT3 Future_;
	void LookFuture();

	void PosRel(GameObject* pTarget);		//���I�u�W�F�N�g�Ƃ̈ʒu�֌W�𔻒�

	void RayCasting();

	void SetNextState(char M_STATUS);
	void ResetNextState(char M_STATUS);

	//�Ȃ������������
	void TurnDirection();

	void StayInside() override;

	void UseTurbo(float dist);

	char GetHighestPriority();

	void Reflect();

	std::pair<char, float> Deduction(float DistF, float DistL, float DistR);
public:
	//�R���X�g���N�^
	Computer(GameObject* parent);

	//�f�X�g���N�^
	~Computer();

	void UpdateState() override;

	void ChangeState();
};