#pragma once
#include "../Engine/GameObject.h"

//画像を押したするときに継承するクラス
//使うときはコンストラクタでSIZE(画像数)とMODEL(モデル数)を決めて
//SetFile()とInitialPoint()を設定する(名前と位置)
//あとは必要なものだけオーバライドする

//■■シーンを管理するクラス
class Button : public GameObject
{
	bool* change_;	//選択されているかどうか
	bool first_;		//一回だけ処理をしたか
protected:
	//必ず設定するもの
	LPCWSTR* fileName;	//ファイルの名前
	
	//必要に応じて設定する
	Transform* trans_;	//画像の動き
	short SIZE;			//画像数
	short MODEL;		//モデル数

	//使うかもしれないもの
	XMFLOAT3 MousePos_;	//マウスの位置
	short* hPict_;    //モデル番号
	short tucheNumber_;	//触れた番号
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

	//選択するやり方
	//ON/OFF機能はついてない
	//画像の位置の判定
	void IsImage();

	//キーボード操作の判定
	void IsKey();

	//必ず設定する
	//画像ファイルの名前を取得
	virtual void SetFile() = 0;

	//初期地点
	virtual void InitialPoint() = 0;

	//必要に応じてオーバライド
	//ゲームオブジェクトを探すなど
	//一回やっておきたい処理
	virtual void FirstFind() {};

	//画像を押した時の処理
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
};