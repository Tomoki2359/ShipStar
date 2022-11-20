#pragma once
#include <DirectXMath.h>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	//三角形の当たり判定
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//線分と平面の当たり判定
	//第一引数 : 線分の始点 第二引数 : 線分の終点 第三～第五引数 : ポリゴンの各頂点
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);

	//球と平面の当たり判定
	//第一引数 : 球の中心位置 第二引数 : 球の半径 第三～第五引数 : ポリゴンの各頂点
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);
	bool CircleToPlane(XMFLOAT3 center, float size, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float *dist);
	void ElasticCollision(XMFLOAT3 pos1, XMVECTOR* vMove1, XMFLOAT3 pos2, XMVECTOR* vMove2);

	bool InsidePlane(XMFLOAT3 pos, XMFLOAT3 HLt, XMFLOAT3 LwR);

	//整数を取得する関数
	//第一引数 : 対象の値 第二引数 : 求める最小の桁 第三引数 : 求める最大の桁
	int GetDigits(int value, int m, int n);

	//小数点以下の値を取得する関数
	//第一引数 : 対象の値 第二/三引数 小数第m～n位
	float GetFraction(float value, int m, int n);	//情報落ちして一部の値が取得できない
	//小数点以下の指定した桁を整数値で取得する関数
	int GetFraction(float value, int m);

	//特定の桁の数値を切り抜く関数
	//第一引数 : 対象の値 第二引数 : 小数第m位 第三引数 : 整数部分の最大の桁
	float GetNum(float value, int m, int n);
};
