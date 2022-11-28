#pragma once
#include "Parts.h"

//■■シーンを管理するクラス
class WingParts : public Parts
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	WingParts(GameObject* parent);

	int GetPartsNum() override;

	void GingaUnion(int partsNum) override;

	void MastangUnion(int partsNum) override;

	void SindenUnion(int partsNum) override;

	void ZeroUnion(int partsNum) override;
};