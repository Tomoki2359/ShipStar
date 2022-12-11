#pragma once
#include "Button.h"

//■■シーンを管理するクラス
class AfterCustomImage : public Button
{
	XMFLOAT3 difference_;
	int alpha;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	AfterCustomImage(GameObject* parent);

	//初期地点
	void InitialPoint() override;

	//画像ファイルの名前を取得
	void SetFile() override;

	//押した時の処理
	void PutButton() override;

	//ボタンに触れているときの処理
	//引数:第一引数　選択されている番号
	void TucheButton(int number) override;

	bool IsAddCondition() override;
};