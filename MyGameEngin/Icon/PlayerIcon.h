#pragma once
#include "AirframeIcon.h"
#include "../Player.h"

//�����V�[�����Ǘ�����N���X
class PlayerIcon : public AirframeIcon
{
	Player* pPlayer_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayerIcon(GameObject* parent);

	void Load() override;

	void AirframePos() override;

	void Release() override;
};