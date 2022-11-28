#pragma once
#include "AirframeIcon.h"
#include "../Player.h"

//■■シーンを管理するクラス
class PlayerIcon : public AirframeIcon
{
	Player* pPlayer_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayerIcon(GameObject* parent);

	void Load() override;

	void AirframePos() override;

	void Release() override;
};