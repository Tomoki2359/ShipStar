#pragma once
#include "Airframe.h"

//■■シーンを管理するクラス
class Player : public Airframe
{
	XMFLOAT3 PrevPos_;
	int CountInside_;
	int CountOutside_;
	void StayInside() override;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	void UpdateState() override;

	//void SetStatus() override;
};