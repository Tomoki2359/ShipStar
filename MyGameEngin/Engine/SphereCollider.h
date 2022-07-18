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
	float GetRadius();			//���a
	XMFLOAT3 GetCenter_();		//�V�F�[�_�̈ʒu
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }	//�I�u�W�F�N�g�̎擾
};