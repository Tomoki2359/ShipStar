#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <list>

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

	Course* pCourse_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;

	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;

	RayCastData L_side_;	//左側のレイ
	RayCastData R_side_;	//右側のレイ
	RayCastData Finder_;

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);

	const char Turn_ = 5;			//回転に使う
	const float Adjuster_ = 1.0f;	//位置の微調整に使う

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2つのXMFLOAT3を足す
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2つのXMFLOAT3の中間を割り出す
	//int ReturnShortest(float Left, float Right, float Upper, float Lower);
	//int ReturnLongest(float Left, float Right, float Upper, float Lower);

	void Scan();	//コースを読み取ってチェックポイントを設置する

public:
	Navigation(GameObject* parent);
	~Navigation();

	//初期化
	void Initialize() override;

	//開放
	void Release() override;


	std::list<XMFLOAT3> Checkpoint_;
};