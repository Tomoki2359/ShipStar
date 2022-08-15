#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum TITLE
{
	TITLE_START = 0,
	TITLE_OPTION,
	MAX_TITLE,
};

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	short title_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};