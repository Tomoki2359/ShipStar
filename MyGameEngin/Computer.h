#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	const char M_TURBO = 0x20;
	const char M_RISE = 0x10;
	const char M_DESCENT = 0x08;
	const char M_TURNL = 0x04;
	const char M_TURNR = 0x02;
	const char M_ACCEL = 0x01;
	//8ビット、左から順に(未定、未定、ターボ、上昇、下降、左カーブ、右カーブ、アクセルブレーキ)
	//有無の判定、アクセルブレーキは1がtrue、0がfalseとする。
	char VirtualState_;	//仮想の思考を司る部分(仮)
	char NextState_;	//次のフレームの状態

	char UpdateDecider;	//更新頻度を生成

	void SetNextState(char M_STATUS);
	void ResetNextState(char M_STATUS);
public:
	//コンストラクタ
	Computer(GameObject* parent);

	//デストラクタ
	~Computer();

	void UpdateState() override;

	void ChangeState();
};