#pragma once
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class OKButton : public Button
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	OKButton(GameObject* parent);

	//�����n�_
	void InitialPoint() override;

	//�摜�̈ʒu�̔���
	bool IsImage() override;

	//�摜�t�@�C���̖��O���擾
	LPCWSTR SetFile() override;
};