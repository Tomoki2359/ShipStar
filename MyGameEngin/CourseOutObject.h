#pragma once
#include "Engine/GameObject.h"

//スタート・ゴールラインに置くオブジェクト
class CourseOutObject : public GameObject
{
	int hModel_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CourseOutObject(GameObject* parent);

	//デストラクタ
	~CourseOutObject();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;
};