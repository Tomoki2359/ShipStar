#pragma once
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class AfterCustomImage : public Button
{
	XMFLOAT3 difference_;
	int alpha;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	AfterCustomImage(GameObject* parent);

	//�����n�_
	void InitialPoint() override;

	//�摜�t�@�C���̖��O���擾
	void SetFile() override;

	//���������̏���
	void PutButton() override;

	//�{�^���ɐG��Ă���Ƃ��̏���
	//����:�������@�I������Ă���ԍ�
	void TucheButton(int number) override;

	bool IsAddCondition() override;
};