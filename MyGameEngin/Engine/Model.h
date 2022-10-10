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

	void SetAlpha(int hModel_, int alpha);	//�����x�̎擾
	void SetColor(int hModel_, int red, int green, int blue);	//RGB
	void AllRelease();

	//Z�o�b�t�@��ON/OFF
	//�����̂��̂�B��Č����Ȃ����̂�\�����������ꍇ��false
	void IsZBuffer(int hModel_, bool zBuffer);	
};
