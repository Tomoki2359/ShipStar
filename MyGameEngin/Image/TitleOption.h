#pragma once
#include "Button.h"

//■■シーンを管理するクラス
class TitleOption : public Button
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleOption(GameObject* parent);

	//初期地点
	void InitialPoint() override;

	//画像ファイルの名前を取得
	void SetFile() override;
};