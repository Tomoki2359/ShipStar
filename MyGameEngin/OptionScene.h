#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/BackButton.h"
#include "Image/OptionButton.h"
#include "Image/OptionVolume.h"

enum OPTION
{
	OPTION_BACK = 0,
	OPTION_BUTTON,
	OPTION_VOLUME,
	MAX_OPTION,
};

//■■シーンを管理するクラス
class OptionScene : public GameObject
{
	short option_;
	bool mouseMoob_;	//マウスが動いているかどうか
	bool first_;		//画像のポインタを指定したかどうか

	//マウス操作
	XMFLOAT3 mousePos_;		//前のマウスの位置
	XMFLOAT3 mouseNext_;	//今のマウスの位置

	//画像のポインタ
	BackButton* pBack_;
	OptionButton* pButton_;
	OptionVolume* pVolume_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	OptionScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};