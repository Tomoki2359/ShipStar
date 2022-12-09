#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class Button : public GameObject
{
	bool change_;	//選択されているかどうか
protected:
	XMFLOAT3 MousePos_;	//マウスの位置
	LPCWSTR* fileName;	//ファイルの名前
	int alpha_;			//透明度
	short SIZE;			//画像数
	short* hPict_;    //モデル番号
	bool isPut;		//押されたかどうか
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
	bool IsImage();

	//画像を押した時の動き
	//動きが違うやつはオーバライド
	virtual void PutButton();

	//ボタンに触れているときの処理
	//動きが違うやつはオーバーライド
	virtual void TucheButton();

	//画像ファイルの名前を取得
	virtual void SetFile() = 0;
};