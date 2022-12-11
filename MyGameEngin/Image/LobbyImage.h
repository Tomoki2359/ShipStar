#pragma once
#include "Button.h"

//■■シーンを管理するクラス
class LobbyImage : public Button
{
	const float POSITION;
	int alpha;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LobbyImage(GameObject* parent);

	//初期地点
	void InitialPoint() override;

	//画像ファイルの名前を取得
	void SetFile() override;

	//押した時の処理
	void PutButton() override;

	//追加条件
	bool IsAddCondition() override;
};