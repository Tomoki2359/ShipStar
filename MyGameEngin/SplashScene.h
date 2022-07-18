#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//■■シーンを管理するクラス
class SplashScene : public GameObject
{
	const int change_;		//ロゴの変更
	const int startTime_;	//余白
	int hPict_[2];
	int alpha_;				//透明度の調整
	int time_;				//表示するタイミング
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	SplashScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};