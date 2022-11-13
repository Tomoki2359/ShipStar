#include "PartsUnion.h"
#include "../Engine/Model.h"
#include "BodyParts.h"
#include "CookpitParts.h"
#include "EnginParts.h"
#include "WingParts.h"

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