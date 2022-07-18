#pragma once
#pragma once
#include "GameObject.h"
#include "Direct3D.h"

class GameObject;

class SphereCollider
{
	GameObject* pGameObject_;
	XMFLOAT3 center_;
	float radius_;
public:
	SphereCollider(XMFLOAT3 center, float radius);
	float GetRadius();			//半径
	XMFLOAT3 GetCenter_();		//シェーダの位置
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }	//オブジェクトの取得
};