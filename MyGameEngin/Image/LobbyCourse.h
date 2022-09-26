#pragma once
#include "Button.h"

//■■シーンを管理するクラス
class LobbyCourse : public Button
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LobbyCourse(GameObject* parent);

	//初期地点
	void InitialPoint() override;

	//画像の位置の判定
	//bool IsImage() override;

	//画像ファイルの名前を取得
	LPCWSTR SetFile() override;
};