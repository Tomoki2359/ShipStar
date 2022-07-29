#pragma once
#include "Engine/GameObject.h"

enum STATUS_ID
{
	MAX_SPEAD,	//最高速度
	ACCELE,		//加速度
	TURBO,		//ターボ値
	ENDURANCE,	//耐久値
	MAX_STATUS	//最後尾
};

//■■シーンを管理するクラス
class Airframe : public GameObject
{
	short hModel_;    //モデル番号
	float Spead_;	//現在の速度
	bool aRotate_;	//上昇状態かどうか
	bool dRotate_;	//下降状態かどうか
	bool lRotate_;	//左に曲がっている状態かどうか
	bool rRotate_;	//右に曲がっている状態かどうか
	short tTurbo_;	//ターボ値を貯める
	bool cTurbo_;	//ターボ状態かどうか
public:
	float status_[MAX_STATUS];
	std::string failName_;
	bool sCamera_;	//カメラをつけるかどうか
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Airframe(GameObject* parent, std::string name);

	//デストラクタ
	~Airframe();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//速さや位置などの限界
	void Limit();

	//ステータスの取得
	virtual void SetStatus();
};