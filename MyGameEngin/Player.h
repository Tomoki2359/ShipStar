#pragma once
#include "Airframe.h"

//■■シーンを管理するクラス
class Player : public Airframe
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	void SetStatus() override;
};