#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//■■シーンを管理するクラス
class ResultScene : public GameObject
{
	int hPict_[10];
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ResultScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};