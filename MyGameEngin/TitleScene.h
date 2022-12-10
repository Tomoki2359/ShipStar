#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
//#include "Image/TitleStart.h"
//#include "Image/TitleOption.h"
//
//enum TITLE
//{
//	TITLE_START = 0,
//	TITLE_OPTION,
//	MAX_TITLE,
//};

//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	//short title_;		//選んだ画像
	//bool mouseMoob_;	//マウスが動いているかどうか
	//bool first_;		//画像のポインタを指定したかどうか

	////マウス操作
	//XMFLOAT3 mousePos_;		//前のマウスの位置
	//XMFLOAT3 mouseNext_;	//今のマウスの位置

	////画像のポインタ
	//TitleStart* pStart_;
	//TitleOption* pOption_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};