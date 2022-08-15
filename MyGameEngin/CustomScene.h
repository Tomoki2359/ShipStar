#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum CUSTOM
{
	CUSTOM_BACK = 0,
	CUSTOM_OK,
	MAX_CUSTOM,
};

//■■シーンを管理するクラス
class CustomScene : public GameObject
{
	short custom_;
	bool mouseMoob_;
	bool change_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
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