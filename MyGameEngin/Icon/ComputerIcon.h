#pragma once
#include "AirframeIcon.h"
#include "../Computer.h"

//�����V�[�����Ǘ�����N���X
class ComputerIcon : public AirframeIcon
{
	Computer* pComputer_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ComputerIcon(GameObject* parent);

	void Load() override;

	void AirframePos() override;

	void Release() override;
};