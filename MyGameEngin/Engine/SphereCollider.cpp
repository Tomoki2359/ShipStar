#include "SphereCollider.h"

SphereCollider::SphereCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	radius_ = radius;
}

//�R���C�_�[�̔��a
float SphereCollider::GetRadius()
{
	return radius_;
}

//�R���C�_�[�̒��S
XMFLOAT3 SphereCollider::GetCenter_()
{
	return center_;
}
