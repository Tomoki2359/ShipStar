#pragma once
#include "Engine/GameObject.h"

//■■シーンを管理するクラス
class AirframeIcon : public GameObject
{
protected:
	short hPict_;			//モデル番号
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	AirframeIcon(GameObject* parent);

	AirframeIcon(GameObject* parent, std::string name);		//継承用コンストラクタ

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	virtual void Load() = 0;
};