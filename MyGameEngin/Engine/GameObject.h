#pragma once

#include <list>
#include <string>
#include "Direct3D.h"
#include "Input.h"
#include "SphereCollider.h"
#include "Transform.h"

class SphereCollider;

class GameObject
{
protected:
	std::list<GameObject*> childList_;
	Transform	transform_;
	GameObject* pParent_;
	SphereCollider* pCollider_;
	std::string	objectName_;
	bool killObject_;
public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	virtual ~GameObject() {}

	virtual void Initialize() {}
	virtual void Update() {}
	void UpdateSub();
	virtual void Draw() {}
	void DrawSub();
	virtual void Release() {}
	void ReleaseSub();

	///////////////////////////////����̃I�u�W�F�N�g����������֐��Q///////////////////////////
	GameObject* FindChildObject(std::string childName);
	GameObject* GetRootJob();
	GameObject* FindObject(std::string childName);

	////////////////////////////////�I�u�W�F�N�g���ł�����֐��Q////////////////////////////////
	void KillMe();
	void KillAllChildren();

	///////////////////////////////////////�����蔻��ꎮ///////////////////////////////////////
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pGameObject);
	void RoundRobin(GameObject* pGameObject);
	virtual void OnCollision(GameObject* pGameObject) {}

	///////////////////////////////transform�Ɋւ���Z�b�^�A�Q�b�^//////////////////////////////
	Transform GetTrans() { return transform_; }
	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }


	void SetScreen(short red, short blue, short green);	//�X�N���[���̐F���擾

	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* p;
		p = new T(parent);
		p->Initialize();
		childList_.push_back(p);
		return p;
	}
};