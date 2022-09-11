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
	void Draw(int hModel_);
	void Release();

	void SetAlpha(int hModel_, int alpha);	//�����x�̎擾
	void SetColor(int hModel_, int red, int green, int blue);	//RGB
	void AllRelease();
};
