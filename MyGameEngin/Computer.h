#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	enum
	{
		PR_Front,
		PR_Right,
		PR_Left
	};

	//各状態の定義
	const char M_TURBO = 0x20;
	const char M_TURNL = 0x04;
	const char M_TURNR = 0x02;
	const char M_ACCEL = 0x01;
	//8ビット、上位ビットから順に(未定、未定、ターボ、上昇、下降、左カーブ、右カーブ、アクセルブレーキ)
	//有無の判定、アクセルブレーキは1がtrue、0がfalseとする。
	char VirtualState_;	//仮想の思考を司る部分(仮)
	char NextState_;	//次のフレームの状態

	char UpdateDecider;	//更新頻度を生成

	const float Hate_ = 5.0f;	//他オブジェクトの影響力を指定(後ほど調整)
	const char Search_ = 15;	//他オブジェクトに影響される距離
	const char Accuracy_ = 95;	//判断の正確さ

	struct Priority
	{
		float Move_Front;	//正面
		float Move_Left;	//左移動
		float Move_Right;	//右移動
	} PrCommand;	//各コマンドの優先順位を判定

	XMFLOAT3 Future_;
	void LookFuture();

	void PosRel(GameObject* pTarget);		//他オブジェクトとの位置関係を判定

	void RayCasting();

	void SetNextState(char M_STATUS);
	void ResetNextState(char M_STATUS);

	//曲がる方向を示す
	void TurnDirection();

	void StayInside() override;

	void UseTurbo(float dist);

	char GetHighestPriority();
public:
	//コンストラクタ
	Computer(GameObject* parent);

	//デストラクタ
	~Computer();

	void UpdateState() override;

	void ChangeState();
};