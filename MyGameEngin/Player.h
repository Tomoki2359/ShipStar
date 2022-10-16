#pragma once
#include "Airframe.h"

//■■シーンを管理するクラス
class Player : public Airframe
{
	void StayInside() override;
	void StayOutside() override;

	void UpdateCObject(XMFLOAT3 dir);
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	void UpdateState() override;

	//void SetStatus() override;
};