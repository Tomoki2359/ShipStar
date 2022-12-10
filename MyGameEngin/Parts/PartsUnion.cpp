#include "PartsUnion.h"
#include "../Engine/Model.h"

PartsUnion::PartsUnion(GameObject* parent)
	: GameObject(parent, "PartsUnion"), hModel_(-1)
{
}

PartsUnion::~PartsUnion()
{
}

void PartsUnion::Initialize()
{
	Instantiate<EnginParts>(this);
	Instantiate<BodyParts>(this);
	Instantiate<CookpitParts>(this);
	Instantiate<WingParts>(this);

	const float Scale = 0.75f;
	transform_.scale_ = XMFLOAT3(Scale, Scale, Scale);
}

void PartsUnion::Draw()
{
}

void PartsUnion::RotationParts()
{
	transform_.rotate_.y++;
}

void PartsUnion::TransPos()
{
	transform_.position_ = { -pParent_->GetPosition().x,0,0 };
}
