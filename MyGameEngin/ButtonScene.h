#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum BUTTON
{
	BUTTON_BACK = 0,
	BUTTON_OK,
	MAX_BUTTON,
};

//■■シーンを管理するクラス
class ButtonScene : public GameObject
{
	short button_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ButtonScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};