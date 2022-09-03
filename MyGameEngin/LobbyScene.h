#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/LobbyCourse.h"
#include "Image/LobbyCustom.h"
#include "Image/LobbyPlay.h"

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
	bool mouseMoob_;	//マウスが動いているかどうか
	bool first_;		//画像のポインタを指定したかどうか

	//マウス操作
	XMFLOAT3 mousePos_;		//前のマウスの位置
	XMFLOAT3 mouseNext_;	//今のマウスの位置

	//画像のポインタ
	LobbyCourse* pCourse_;
	LobbyPlay* pPlay_;
	LobbyCustom* pCustom_;
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