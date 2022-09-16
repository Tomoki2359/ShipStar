#pragma once
#include "Engine/GameObject.h"

//スタート・ゴールラインに置くオブジェクト
class GoalObject : public GameObject
{
	int hModel_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GoalObject(GameObject* parent);

	//デストラクタ
	~GoalObject();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;
};

