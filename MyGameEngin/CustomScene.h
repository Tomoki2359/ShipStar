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
#include "Parts/PartsUnion.h"

enum BEFORE_CUSTOM
{
	BEFORE_BACK = 0,
	BEFORE_OK,
	BEFORE_ENGIN,
	BEFORE_BODY,
	BEFORE_WING,
	BEFORE_COOKPIT,
	BEFORE_MAX,
};

enum AFTER_CUSTOM
{
	AFTER_BACK = 0,
	AFTER_OK,
	AFTER_MAX,
};

//■■シーンを管理するクラス
class CustomScene : public GameObject
{
	short custom_;
	bool change_;	//本当に変更するかどうか
	bool mouseMoob_;	//マウスが動いているかどうか
	bool first_;		//画像のポインタを指定したかどうか

	//機体のパーツ番号
	int engineNum_;
	int bodyNum_;
	int wingNum_;
	int cookpitNum_;

	//機体の色番号
	int engineColor_;
	int bodyColor_;
	int wingColor_;
	int cookpitColor_;

	//明度関連
	float partsBrightness_;
	bool isBrightness_;

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

	//機体のパーツのポインタ
	EnginParts* pEngin_;
	BodyParts* pBody_;
	WingParts* pWing_;
	CookpitParts* pCookpit_;
	PartsUnion* pUnion_;
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

	//変更前
	void BeforeChange();

	//変更後
	void AfterChange();

	//パーツの変更
	//引数:第一引数 機体のパーツ:第二引数 パーツ番号:第三引数 パーツの色番号
	void PartsChange(Parts* parts, int& partsNum, int& partsColor);
};