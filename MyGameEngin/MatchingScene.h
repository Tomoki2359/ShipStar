#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
//#include "Image/BackButton.h"
//#include "Image/MatchingStart.h"
//
//enum MATCHING
//{
//	MATCHING_BACK = 0,
//	MATCHING_STRAT,
//	MAX_MATCHING,
//};

//■■シーンを管理するクラス
class MatchingScene : public GameObject
{
	//short matching_;
	//bool mouseMoob_;	//マウスが動いているかどうか
	//bool first_;		//画像のポインタを指定したかどうか

	////マウス操作
	//XMFLOAT3 mousePos_;		//前のマウスの位置
	//XMFLOAT3 mouseNext_;	//今のマウスの位置

	////画像のポインタ
	//BackButton* pBack_;
	//MatchingStart* pStart_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	MatchingScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};