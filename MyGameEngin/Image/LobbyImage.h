#pragma once
#include "Button.h"

//�����V�[�����Ǘ�����N���X
class LobbyImage : public Button
{
	const float POSITION;
	int alpha;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	LobbyImage(GameObject* parent);

	//�����n�_
	void InitialPoint() override;

	//�摜�t�@�C���̖��O���擾
	void SetFile() override;

	//���������̏���
	void PutButton() override;

	//�ǉ�����
	bool IsAddCondition() override;
};