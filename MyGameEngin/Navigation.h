#pragma once
#include"Engine/GameObject.h"
#include"Engine/Model.h"
#include <vector>

class Course;
class Airframe;
class Player;
class PlayScene;

class Navigation : public GameObject
{
	enum
	{
		left,
		right,
		front,
		back
	};

	enum
	{
		UPPER_LEFT,
		UPPER_RIGHT,
		LOWER_LEFT,
		LOWER_RIGHT,
		DIVISION_MAX
	};

	std::vector<XMFLOAT3> Checkpoint_;
	Course* pCourse_;
	Player* pPlayer_;
	XMFLOAT3 Left_;
	XMFLOAT3 Right_;

	XMFLOAT3 Upper_Goal;
	XMFLOAT3 Left_Goal;
	XMFLOAT3 Right_Goal;

	const XMFLOAT3 matL = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matR = XMFLOAT3(1.0f, 0.0f, 0.0f);
	const XMFLOAT3 matU = XMFLOAT3(0.0f, 1.0f, 0.0f);
	const XMFLOAT3 matD = XMFLOAT3(0.0f, -1.0f, 0.0f);
	const XMFLOAT3 matB = XMFLOAT3(0.0f, 0.0f, 1.0f);
	const XMFLOAT3 matF = XMFLOAT3(0.0f, 0.0f, -1.0f);

	const char Turn_ = 5;			//回転に使う
	const float Adjuster_ = 1.0f;	//位置の微調整に使う
	const XMFLOAT3 Initial = XMFLOAT3(NULL, NULL, NULL);
	const int out = 10;

	XMFLOAT3 XMFLOAT3PRUSXMFLOAT3(XMFLOAT3 fl3a, XMFLOAT3 fl3b);	//2つのXMFLOAT3を足す
	XMFLOAT3 XMFLOAT3AVERAGE(XMFLOAT3 fl3a, XMFLOAT3 fl3b);			//2つのXMFLOAT3の中間を割り出す
	float Getdistance(XMFLOAT3 a, XMFLOAT3 b);

	const short Range_ = 500;			//一区画あたりの走査範囲
	const char Sky_ = 100;			//レイを飛ばす高さ
	const char Move_ = 50;			//移動量
	const XMFLOAT3 Shot_ = XMFLOAT3(0.0f, -1.0f, 0.0f);	//真下に発射するレイ

	void Scan();	//コースを読み取ってチェックポイントを設置する

	int GetShortest(RayCastData L, RayCastData R, RayCastData F, RayCastData B);

	int Correcter(float Target);	//15°刻みに矯正する

public:
	friend Airframe;
	friend PlayScene;

	Navigation(GameObject* parent);
	~Navigation();

	//初期化
	void Initialize() override;

	void Update() override;

	//開放
	void Release() override;

};