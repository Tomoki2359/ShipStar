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

	char UpdateDecider;	//更新頻度を生成

	const float Hate_ = 5.0f;	//他オブジェクトの影響力を指定(後ほど調整)
	const char Search_ = 15;	//他オブジェクトに影響される距離
	const char Accuracy_ = 98;	//判断の正確さ

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

	void Reflect();

	std::pair<char, float> Deduction(float DistF, float DistL, float DistR);
public:
	//コンストラクタ
	Computer(GameObject* parent);

	//デストラクタ
	~Computer();

	void UpdateState() override;

	void ChangeState();
};