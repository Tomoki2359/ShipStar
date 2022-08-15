#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum VOLUME
{
	VOLUME_BACK = 0,
	VOLUME_OK,
	MAX_VOLUME,
};

//■■シーンを管理するクラス
class VolumeScene : public GameObject
{
	short volume_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	VolumeScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};