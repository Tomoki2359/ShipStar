#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class CouseMap : public GameObject
{
	int hPict_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CouseMap(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};