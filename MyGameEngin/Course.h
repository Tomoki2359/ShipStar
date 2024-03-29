#pragma once
#include "Engine/GameObject.h"

//■■シーンを管理するクラス
class Course : public GameObject
{
	int hModel_;    //モデル番号
	const char Size_ = 25;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Course(GameObject* parent);

	~Course();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetModelHandle() { return hModel_; }
};