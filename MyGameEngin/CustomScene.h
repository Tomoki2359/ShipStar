#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Parts/PartsUnion.h"

//■■シーンを管理するクラス
class CustomScene : public GameObject
{
	PartsUnion* pUnion_;
	int alpha;
	bool start_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CustomScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};