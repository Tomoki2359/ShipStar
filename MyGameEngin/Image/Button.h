#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class Button : public GameObject
{
	int hPict_;    //モデル番号
	bool change_;	//選択されているかどうか
protected:
	XMFLOAT3 MousePos_;	//マウスの位置
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Button(GameObject* parent);

	Button(GameObject* parent, std::string name);		//継承用コンストラクタ

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//選択されているかどうか
	void IsButton();

	//初期地点
	virtual void InitialPoint() = 0;

	//画像の位置の判定
	virtual bool IsImage() = 0;

	//画像ファイルの名前を取得
	virtual LPCWSTR SetFile() = 0;
};