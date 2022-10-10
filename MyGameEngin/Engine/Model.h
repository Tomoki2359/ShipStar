#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

namespace Model
{
	int Load(std::string fileName);
	void SetTransform(int hModel_, Transform transform_);
	void RayCast(int handle, RayCastData* data);
	void PushOut(int handle, XMFLOAT3* position, float size, XMFLOAT3 dir);
	void Draw(int hModel_);
	void Release();

	void SetAlpha(int hModel_, int alpha);	//透明度の取得
	void SetColor(int hModel_, int red, int green, int blue);	//RGB
	void AllRelease();

	//ZバッファのON/OFF
	//遠くのものや隠れて見えないものを表示させたい場合はfalse
	void IsZBuffer(int hModel_, bool zBuffer);	
};
