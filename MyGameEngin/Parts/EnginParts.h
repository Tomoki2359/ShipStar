#pragma once
#include "Parts.h"

//�����V�[�����Ǘ�����N���X
class EnginParts : public Parts
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EnginParts(GameObject* parent);

	//void SetPartsNum(int partsNum) override;

	int GetPartsNum() override;
};