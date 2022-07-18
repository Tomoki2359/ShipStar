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
	virtual ~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	void UpdateSub();
	virtual void Draw() = 0;
	void DrawSub();
	virtual void Release() = 0;
	void ReleaseSub();
	GameObject* FindChildObject(std::string childName);
	GameObject* GetRootJob();
	GameObject* FindObject(std::string childName);
	void KillMe();
	void KillAllChildren();
	Transform GetTrans();
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pGameObject);
	void RoundRobin(GameObject* pGameObject);
	void SetPosition(XMFLOAT3 position);
	void SetScreen(int red, int blue, int green);	//�X�N���[���̐F���擾
	virtual void OnCollision(GameObject* pGameObject) {};

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