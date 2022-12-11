#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//■■シーンを管理するクラス
class MatchingScene : public GameObject
{
	int alpha;
	bool start_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MatchingScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};