#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class Background : public GameObject
{
	short hPict_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Background(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};