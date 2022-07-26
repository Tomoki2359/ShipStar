#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum Logo_ID
{
	LOGO_TEAM,
	LOGO_SCHOOL,
	LOGO_MAX
};

class SplashScene : public GameObject
{
	const short change_;		//ロゴの変更
	const short startTime_;		//余白
	short hPict_[LOGO_MAX];
	short alpha_;				//透明度の調整
	short time_;				//表示するタイミング
	const short MoveAlpha_;		//透明度の変化速度
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