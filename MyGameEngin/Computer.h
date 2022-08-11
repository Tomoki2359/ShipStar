#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	const char M_TURBO = 0x20;
	const char M_RISE = 0x10;
	const char M_DESCENT = 0x08;
	const char M_TURNL = 0x04;
	const char M_TURNR = 0x02;
	const char M_ACCEL = 0x01;
	//8�r�b�g�A�����珇��(����A����A�^�[�{�A�㏸�A���~�A���J�[�u�A�E�J�[�u�A�A�N�Z���u���[�L)
	//�L���̔���A�A�N�Z���u���[�L��1��true�A0��false�Ƃ���B
	char VirtualState_;	//���z�̎v�l���i�镔��(��)
	char NextState_;	//���̃t���[���̏��

	char UpdateDecider;	//�X�V�p�x�𐶐�

	void SetNextState(char M_STATUS);
	void ResetNextState(char M_STATUS);
public:
	//�R���X�g���N�^
	Computer(GameObject* parent);

	//�f�X�g���N�^
	~Computer();

	void UpdateState() override;

	void ChangeState();
};