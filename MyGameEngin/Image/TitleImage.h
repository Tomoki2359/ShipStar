#pragma once
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class TitleImage : public Button
{
	int alpha;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleImage(GameObject* parent);

	//�����n�_
	void InitialPoint() override;

	//�摜�t�@�C���̖��O���擾
	void SetFile() override;

	//���������̏���
	void PutButton() override;
};