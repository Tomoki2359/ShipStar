#pragma once
#include "../Engine/GameObject.h"
#include "../CSVReader.h"
#include "../Option.h"

enum PARTS_NAME
{
	PARTS_GINGA,
	PARTS_MASTANG,
	PARTS_SINDEN,
	PARTS_ZERO,
	END_NAME
};
//■■シーンを管理するクラス
class Parts : public GameObject
{
protected:
	int partsNum_;			//パーツ番号
	int catagoryNum_;
	std::string partsName_;	//パーツ名
	//short hModel_[CATEGORY_END];			//モデル番号
	short hModel_;			//モデル番号
	int colorNum_;
	PARTS_NUM parts_;

	void SetName();
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Parts(GameObject* parent);

	Parts(GameObject* parent, std::string name);		//継承用コンストラクタ

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetParts();

	//パーツに位置を合わせる
	void Union(PARTS_NAME engineName, int partsNum);

	//継承関係
	//パーツを呼ぶ
	void Load();

	//パーツをセットする	
	//引数： 第一引数　パーツ番号
	void SetParts(int partsNum);

	//パーツ番号の取得
	//戻り値: パーツ番号
	virtual int GetPartsNum() = 0;

	//カラー番号をセットする
	//引数: 第一引数　カラー番号
	void SetColor(int colorNum);

	//カラー番号の取得
	//戻り値： カラー番号
	int GetColor();

	//明度
	//引数：第一引数　明度
	void SetBrightness(float brightness);

	//銀河ボディのときの位置調整
	//引数: 第一引数　パーツ番号
	virtual void GingaUnion(int partsNum) = 0;

	//マスタングボディのときの位置調整
	//引数: 第一引数　パーツ番号
	virtual void MastangUnion(int partsNum) = 0;

	//シンデンボディのときの位置調整
	//引数: 第一引数　パーツ番号
	virtual void SindenUnion(int partsNum) = 0;

	//ゼロボディのときの位置調整
	//引数: 第一引数　パーツ番号
	virtual void ZeroUnion(int partsNum) = 0;
};