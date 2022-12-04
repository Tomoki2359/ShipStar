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

	//明度
	//引数：第一引数　モデル番号；第二引数　明度
	void SetBrightness(int hModel_, float brightness);
	//透明度
	//引数：第一引数　モデル番号：第二引数　透明度(0～255)
	void SetAlpha(int hModel_, int alpha);	
	//RGB
	//引数：第一引数　モデル番号 :第二引数　色(0～255)
	void SetColor(int hModel_, int red, int green, int blue);	
	void AllRelease();

	//ZバッファのON/OFF
	//遠くのものや隠れて見えないものを表示させたい場合はfalse
	void IsZBuffer(int hModel_, bool zBuffer);	
};
