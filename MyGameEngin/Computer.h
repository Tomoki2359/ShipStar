#pragma once
#include "Airframe.h"

class Computer : public Airframe
{
	//各状態の定義
	const char M_TURBO = 0x20;
	const char M_RISE = 0x10;
	const char M_DESCENT = 0x08;
	const char M_TURNL = 0x04;
	const char M_TURNR = 0x02;
	const char M_ACCEL = 0x01;
	//8ビット、上位ビットから順に(未定、未定、ターボ、上昇、下降、左カーブ、右カーブ、アクセルブレーキ)
	//有無の判定、アクセルブレーキは1がtrue、0がfalseとする。
	char VirtualState_;	//仮想の思考を司る部分(仮)
	char NextState_;	//次のフレームの状態

	char UpdateDecider;	//更新頻度を生成

	struct Priority
	{
		float Move_Front;	//正面
		float Move_Left;	//左移動
		float Move_Right;	//右移動
		float Move_RISE;	//上移動
		float Move_Descent;	//下移動
	};

	Priority PrCommand;	//各コマンドの優先順位を判定

	void PosRel(GameObject* pTarget);		//他オブジェクトとの位置関係を判定

	void RayCasting();

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