#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum OPTION
{
	OPTION_BACK = 0,
	OPTION_BUTTON,
	OPTION_VOLUME,
	MAX_OPTION,
};

//■■シーンを管理するクラス
class OptionScene : public GameObject
{
	short option_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	OptionScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};