#pragma once
#include "Navigation.h"
#include "CSVReader.h"
#include "Option.h"
#include "Engine/GameObject.h"

const short Past = 120;

//各状態の定義
const char M_TURBO = 0x20;
const char M_TURNL = 0x04;
const char M_TURNR = 0x02;
const char M_ACCEL = 0x01;
const char M_BREAK = 0x08;

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
	const float RotationRate_Y = 1.5f;
	const float RotationRate_Z = 2.0f;
	const float RotationMax_Z = 40.0f;

	XMFLOAT3 RespawnPos_[Past];
	XMFLOAT3 RespawnRot_[Past];
	short RespawnUpdate_;

	short hModel_;   //モデル番号
	bool cAscent_;	//上昇状態かどうか
	bool cDescent_;	//下降状態かどうか
	bool lCurve_;	//左に曲がっている状態かどうか
	bool rCurve_;	//右に曲がっている状態かどうか
	CSVReader csv;	//csvを読み込むための関数
	bool start_;	//スタートしたかどうか
	short timeCount_;	//レース時間の管理とカウントダウン
	bool Side_;		//内側にいるか外側にいるか(trueで内側、falseで外側)

	XMFLOAT3 PrevPosition_;	//直前の位置

	Navigation* pNav_;

	short Lap_;		//周回数(不正対策)

	bool IsGoal_;	//ゴールした判定

	void LapMeasure();	//周回数の判定

	void JudgeGoal();	//ゴールの判定

	void ComCorrection();

	void ResetOverRotate(float* rotate);	//0~360°に留めておく為のもの

	void Respawn();			//復帰処理

	void FixInclination();	//回転の調整
	void TurboProcess();	//ターボ処理
	void MoveProcess();		//移動処理
	void ChaseCamera();		//カメラを追わせる

protected:
	//8ビット、上位ビットから順に(未定、未定、ターボ、上昇、下降、左カーブ、右カーブ、アクセルブレーキ)
	//有無の判定、アクセルブレーキは1がtrue、0がfalseとする。
	char VirtualState_;	//仮想の思考を司る部分(仮)
	char NextState_;	//次のフレームの状態

	float speed_;	//現在の速度
	void JudgeSide();
	void JudgeSide(RayCastData& data);
	bool JudgeSide(XMFLOAT3 pos);

	short tTurbo_;	//ターボ値を貯める
	bool cTurbo_;	//ターボ状態かどうか
	XMFLOAT3 GetDistance(GameObject* pTarget);

	virtual void StayInside() = 0;

public:
	PARTS_NUM PartsSet;
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

	void SetPartsNum(char engine, char body, char wing, char cockpit, char pattern);

	//ステータスの取得
	void SetStatus();

	//加速
	void Accelerate();

	//減速
	void Decelerate();

	//右カーブ
	void TurnRight();

	//左カーブ
	void TurnLeft();

	//ターボ
	void Turbo();

	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	bool GetisGoal() { return IsGoal_; }

	bool GetStart() { return start_; }

	float GetSpeed() { return speed_; }
};