#pragma once
#include "Parts.h"

//�����V�[�����Ǘ�����N���X
class WingParts : public Parts
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	WingParts(GameObject* parent);

	int GetPartsNum() override;

	void GingaUnion(int partsNum) override;

	void MastangUnion(int partsNum) override;

	void SindenUnion(int partsNum) override;

	void ZeroUnion(int partsNum) override;
};