#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class PlayBackground : public GameObject
{
	short hPict_[2];    //���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayBackground(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};