#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum RESULT
{
	RESULT_BACK = 0,
	RESULT_OK,
	MAX_RESULT,
};

//■■シーンを管理するクラス
class ResultScene : public GameObject
{
	short result_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
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