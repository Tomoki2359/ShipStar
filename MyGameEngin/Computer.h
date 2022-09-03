#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	//�e��Ԃ̒�`
	const char M_TURBO = 0x20;
	const char M_RISE = 0x10;
	const char M_DESCENT = 0x08;
	const char M_TURNL = 0x04;
	const char M_TURNR = 0x02;
	const char M_ACCEL = 0x01;
	//8�r�b�g�A��ʃr�b�g���珇��(����A����A�^�[�{�A�㏸�A���~�A���J�[�u�A�E�J�[�u�A�A�N�Z���u���[�L)
	//�L���̔���A�A�N�Z���u���[�L��1��true�A0��false�Ƃ���B
	char VirtualState_;	//���z�̎v�l���i�镔��(��)
	char NextState_;	//���̃t���[���̏��

	char UpdateDecider;	//�X�V�p�x�𐶐�

	const float Hate_;	//���I�u�W�F�N�g�̉e���͂��w��(��قǒ���)
	const char Search_;	//���I�u�W�F�N�g�ɉe������鋗��

	struct Priority
	{
		float Move_Front;	//����
		float Move_Left;	//���ړ�
		float Move_Right;	//�E�ړ�
		float Move_Above;	//��ړ�
		float Move_Under;	//���ړ�
	};

	Priority PrCommand;	//�e�R�}���h�̗D�揇�ʂ𔻒�

	void PosRel(GameObject* pTarget);		//���I�u�W�F�N�g�Ƃ̈ʒu�֌W�𔻒�

	void RayCasting();

	void SetNextState(char M_STATUS);
	void ResetNextState(char M_STATUS);

	//�R�[�X�ꂩ��̍��������ɂ���
	void HeightAdjustment();

	//�Ȃ������������
	void TurnDirection();
public:
	//�R���X�g���N�^
	Computer(GameObject* parent);

	//�f�X�g���N�^
	~Computer();

	void UpdateState() override;

	void ChangeState();
};