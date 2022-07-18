#include "SphereCollider.h"

SphereCollider::SphereCollider(XMFLOAT3 center, float radius)
{
	center_ = center;
	radius_ = radius;
}

//コライダーの半径
float SphereCollider::GetRadius()
{
	return radius_;
}

//コライダーの中心
XMFLOAT3 SphereCollider::GetCenter_()
{
	return center_;
}
