#pragma once
#include "Engine/GameObject.h"

enum STATUS_ID
{
	MAX_SPEED,	//最高速度
	ACCELE,		//加速度
	TURBO,		//ターボ値
	ENDURANCE,	//耐久値
	MAX_STATUS	//最後尾
};

//■■シーンを管理するクラス
class Airframe : public GameObject
{
	short hModel_;    //モデル番号
	float speed_;	//現在の速度
	bool cAscent_;	//上昇状態かどうか
	bool cDescent_;	//下降状態かどうか
	bool lCurve_;	//左に曲がっている状態かどうか
	bool rCurve_;	//右に曲がっている状態かどうか

protected:
	short tTurbo_;	//ターボ値を貯める
	bool cTurbo_;	//ターボ状態かどうか

public:
	float status_[MAX_STATUS];
	std::string fileName_;
	bool cCamera_;	//カメラをつけるかどうか
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Airframe(GameObject* parent);
	Airframe(GameObject* parent, std::string name);		//継承用コンストラクタ

	//デストラクタ
	~Airframe();

	//初期化
	void Initialize() override;

	virtual void UpdateState() = 0;

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

	//加速
	void Accelerate();

	//減速
	void Decelerate();

	//右カーブ
	void TurnRight();

	//左カーブ
	void TurnLeft();

	//上昇
	void Rise();

	//下降
	void Descent();

	//ターボ
	void Turbo();
};