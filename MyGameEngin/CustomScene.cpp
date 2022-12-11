#include "CustomScene.h"
#include "Image/LobbyBackground.h"
#include "Image/CurrentStatus.h"
#include "Image/OriginalStatus.h"
#include "Image/ChangeStatus.h"
#include "Image/PartsList.h"
#include "Image/AfterCustomImage.h"
#include "Image/BeforCustomImage.h"
#include "Engine/Image.h"
#include "Engine/Model.h"

//�R���X�g���N�^
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene"), alpha(0), start_(true)
{
}

//������
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyBackground>(this);
	Instantiate<CurrentStatus>(this);
	Instantiate<PartsList>(this);
	Instantiate<OriginalStatus>(this);
	Instantiate<ChangeStatus>(this);
	Instantiate<BeforCustomImage>(this);
	Instantiate<AfterCustomImage>(this);
	Instantiate<PartsUnion>(this);
	Image::AllSetAlpha(0);
	Model::AllSetAlpha(0);
}

//�X�V
void CustomScene::Update()
{
	pUnion_ = (PartsUnion*)FindObject("PartsUnion");
	assert(pUnion_ != nullptr);
	pUnion_->RotationParts();
	if (start_)
	{
		if (alpha == UINT8_MAX)
		{
			start_ = false;
		}
		Image::AllSetAlpha(alpha);
		Model::AllSetAlpha(alpha);
		alpha += 2;
	}
}

//�`��
void CustomScene::Draw()
{
}

//�J��
void CustomScene::Release()
{
}
