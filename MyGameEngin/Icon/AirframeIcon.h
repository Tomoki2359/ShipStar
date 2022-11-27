#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class AirframeIcon : public GameObject
{
protected:
	short hPict_;			//モデル番号
	XMFLOAT3 InitialPos_;	//初期位置
	XMFLOAT3 AirframePos_;	//機体位置
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

	//継承関係
	//初期設定
	virtual void Load() = 0;

	virtual void AirframePos() = 0;
};