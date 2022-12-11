#pragma once
#include "Button.h"
#include "../Parts/PartsUnion.h"

//■■シーンを管理するクラス
class BeforCustomImage : public Button
{
	//機体のパーツのポインタ
	EnginParts* pEngin_;
	BodyParts* pBody_;
	WingParts* pWing_;
	CookpitParts* pCookpit_;

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

	short isNumber;
	XMFLOAT3 difference_;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	BeforCustomImage(GameObject* parent);

	//初期地点
	void InitialPoint() override;

	//画像ファイルの名前を取得
	void SetFile() override;

	void FirstFind() override;

	//押した時の処理
	void PutButton() override;

	//ボタンに触れているときの処理
	//引数:第一引数　選択されている番号
	void TucheButton(int number) override;

	bool IsAddCondition() override;

	//パーツの変更
	//引数:第一引数 機体のパーツ:第二引数 パーツ番号:第三引数 パーツの色番号
	void PartsChange(Parts* parts, int& partsNum, int& partsColor);

	void SetParts();
};