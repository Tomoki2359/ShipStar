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

	virtual void Load();

	virtual void SetParts(int partsNum);

	virtual int GetPartsNum() = 0;

	virtual void SetColor(int colorNum);

	virtual int GetColor();

	int GetParts();

	void RotationParts();
};