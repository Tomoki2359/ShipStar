#pragma once
#include "Parts.h"

//�����V�[�����Ǘ�����N���X
class WingParts : public Parts
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	WingParts(GameObject* parent);

	//void SetPartsNum(int partsNum) override;

	int GetPartsNum() override;
};