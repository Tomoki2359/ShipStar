#pragma once
#include "AirframeIcon.h"
#include "../Computer.h"

//■■シーンを管理するクラス
class ComputerIcon : public AirframeIcon
{
	Computer* pComputer_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ComputerIcon(GameObject* parent);

	void Load() override;

	void AirframePos() override;

	void Release() override;
};