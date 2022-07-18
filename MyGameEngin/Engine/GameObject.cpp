#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) :
	killObject_(false),
	pParent_(parent),
	objectName_(name),
	pCollider_(nullptr)
{
	if (parent)
		transform_.pTransform_ = &parent->transform_;
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();
	Transform();
	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}

	//KillMe()���Ă΂ꂽ�����
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->killObject_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_RELEASE((*itr));
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}


	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->ReleaseSub();
	}
}

GameObject* GameObject::FindChildObject(std::string childName)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return nullptr;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g����T��
	while (it != end) {
		//�������O�̃I�u�W�F�N�g���������炻���Ԃ�
		if ((*it)->objectName_ == childName)
			return *it;

		//���̎q���i���j�ȍ~�ɂ��Ȃ����T��
		GameObject* obj = (*it)->FindChildObject(childName);
		if (obj != nullptr)
		{
			return obj;
		}

		//���̎q��
		it++;
	}

	//������Ȃ�����
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindObject(std::string childName)
{
	return GetRootJob()->FindChildObject(childName);
}

void GameObject::KillAllChildren()
{
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		(*itr)->ReleaseSub();
		SAFE_RELEASE((*itr));
		itr = childList_.erase(itr);
	}
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

//�����蔻��
void GameObject::Collision(GameObject* pGameObject)
{
	if (this == pGameObject || pGameObject->pCollider_ == nullptr)
	{
		return;
	}
	float x = (transform_.position_.x + pCollider_->GetCenter_().x) - (pGameObject->transform_.position_.x + pGameObject->pCollider_->GetCenter_().x);
	float y = (transform_.position_.y + pCollider_->GetCenter_().y) - (pGameObject->transform_.position_.y + pGameObject->pCollider_->GetCenter_().y);
	float z = (transform_.position_.z + pCollider_->GetCenter_().z) - (pGameObject->transform_.position_.z + pGameObject->pCollider_->GetCenter_().z);
	float radiusSum = pCollider_->GetRadius() + pGameObject->pCollider_->GetRadius();
	if (x * x + y * y + z * z <= radiusSum * radiusSum)
	{
		OnCollision(pGameObject);
	}
}

//�����蔻�肪���邩�ǂ����q�������킹�Ċm�F����
void GameObject::RoundRobin(GameObject* pGameObject)
{
	if (pCollider_ == nullptr)
	{
		return;
	}

	if (pGameObject->pCollider_)
	{
		Collision(pGameObject);
	}

	for (auto i = pGameObject->childList_.begin(); i != pGameObject->childList_.end(); i++)
	{
		RoundRobin(*i);
	}
}

//�I�u�W�F�N�g�̍폜
void GameObject::KillMe()
{
	killObject_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

//�X�N���[���̐F�̕ύX
void GameObject::SetScreen(int red, int blue, int green)
{
	Direct3D::SetColor((float)red / 255, (float)blue / 255, (float)green / 255);
}