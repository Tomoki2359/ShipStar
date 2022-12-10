#pragma once
#include "../Engine/GameObject.h"

//■■シーンを管理するクラス
class Button : public GameObject
{
	bool* change_;	//選択されているかどうか
protected:
	Transform* trans_;	//マウスの位置
	XMFLOAT3 MousePos_;	//前回のマウスの位置
	LPCWSTR* fileName;	//ファイルの名前
	int alpha_;			//透明度
	short SIZE;			//画像数
	short MODEL;			//モデル数
	short* hPict_;    //モデル番号
	short tucheNumber_;	//触れた番号
	bool isPut;		//押されたかどうか
	bool first_;		//押されたかどうか
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

	virtual void FirstFind() {};

	//選択されているかどうか
	void IsButton();

	//複数画像がある場合
	void IsButton(int number);

	//初期地点
	virtual void InitialPoint() = 0;

	//画像の位置の判定
	void IsImage();

	//キーボード操作の判定
	void IsKey();

	//画像を押した時の動き
	//動きが違うやつはオーバライド
	virtual void PutButton();

	//ボタンに触れているときの処理
	//動きが違うやつはオーバーライド
	//引数:第一引数　選択されている番号
	virtual void TucheButton(int number);

	//ボタンに触れていないときの処理
	//動きが違うやつはオーバーライド
	//引数:第一引数　選択されている番号
	virtual void NoTucheButton(int number);

	//触れられている・選択されている以外の追加条件
	//必要なもののみオーバーライド
	virtual bool IsAddCondition() { return true; };

	//画像ファイルの名前を取得
	virtual void SetFile() = 0;
};