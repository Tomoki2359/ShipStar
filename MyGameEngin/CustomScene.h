#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/OKButton.h"
#include "Image/BackButton.h"
#include "Image/FixeButton.h"
#include "Image/CurrentStatus.h"
#include "Image/PartsList.h"
#include "Image/OriginalStatus.h"
#include "Image/ChangeStatus.h"

enum CUSTOM
{
	CUSTOM_BACK = 0,
	CUSTOM_OK,
	MAX_CUSTOM,
};

//■■シーンを管理するクラス
class CustomScene : public GameObject
{
	short custom_;
	bool change_;	//本当に変更するかどうか
	bool mouseMoob_;	//マウスが動いているかどうか
	bool first_;		//画像のポインタを指定したかどうか

	//マウス操作
	XMFLOAT3 mousePos_;		//前のマウスの位置
	XMFLOAT3 mouseNext_;	//今のマウスの位置

	//画像のポインタ
	BackButton* pBack_;
	OKButton* pOK_;
	CurrentStatus* pCurrent_;
	PartsList* pParts_;
	FixeButton* pFixe_;
	OriginalStatus* pOriginal_;
	ChangeStatus* pChange_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	CustomScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void BeforeChange();

	void AfterChange();
};