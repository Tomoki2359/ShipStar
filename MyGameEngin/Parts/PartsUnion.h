#pragma once
#include "../Engine/GameObject.h"
#include "BodyParts.h"
#include "CookpitParts.h"
#include "EnginParts.h"
#include "WingParts.h"

//スタート・ゴールラインに置くオブジェクト
class PartsUnion : public GameObject
{
	int hModel_;    //モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PartsUnion(GameObject* parent);

	//デストラクタ
	~PartsUnion();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//機体を回す
	void RotationParts();

	void TransPos();
};