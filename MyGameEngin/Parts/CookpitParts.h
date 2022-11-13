#pragma once
#include "Parts.h"

//■■シーンを管理するクラス
class CookpitParts : public Parts
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CookpitParts(GameObject* parent);

	//void SetPartsNum(int partsNum) override;

	int GetPartsNum() override;
};