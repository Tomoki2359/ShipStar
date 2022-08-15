#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum LOBBY
{
	LOBBY_COURSE = 0,
	LOBBY_PLAY,
	LOBBY_CUSTOM,
	MAX_LOBBY,
};

//■■シーンを管理するクラス
class LobbyScene : public GameObject
{
	short lobby_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LobbyScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};