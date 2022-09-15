#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <vector>

class Course;

class Navigation : public GameObject
{
	enum
	{
		left,
		right,
		upper,
		lower
	};

	enum
	{
		UPPER_LEFT,
		UPPER_RIGHT,
		LOWER_LEFT,
		LOWER_RIGHT,
		DIVISION_MAX
	};

	Course* pCourse_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matU = XMFLOAT3(0.0f, 1.0f, 0.0f);

	const char Turn_ = 5;			//回転に使う
	const float Adjuster_ = 1.0f;	//位置の微調整に使う

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2つのXMFLOAT3を足す
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2つのXMFLOAT3の中間を割り出す
	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	const short Range_ = 500;			//一区画あたりの走査範囲
	const char Sky_ = 100;			//レイを飛ばす高さ
	const char Move_ = 50;			//移動量
	const XMFLOAT3 Shot_ = XMFLOAT3(0.0f, -1.0f, 0.0f);	//真下に発射するレイ

	void Scan();	//コースを読み取ってチェックポイントを設置する

public:
	Navigation(GameObject* parent);
	~Navigation();

	//初期化
	void Initialize() override;

	//開放
	void Release() override;

	std::vector<XMFLOAT3> Checkpoint_;

	XMFLOAT3 Upper_Goal;
	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;
};