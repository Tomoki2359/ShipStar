#pragma once
#include "Airframe.h"

//�����V�[�����Ǘ�����N���X
class Player : public Airframe
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	void SetStatus() override;
};