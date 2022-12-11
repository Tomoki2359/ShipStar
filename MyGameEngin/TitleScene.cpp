#include "TitleScene.h"
#include "Engine/Image.h"
#include "Image/TitleName.h"
#include "Image/Background.h"
#include "Image/TitleImage.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), alpha(0), start_(true)
{
}

//������
void TitleScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<Background>(this);
	Instantiate<TitleName>(this);
	Instantiate<TitleImage>(this);
	Image::AllSetAlpha(0);
}

//�X�V
void TitleScene::Update()
{
	if (start_)
	{
		if (alpha == UINT8_MAX)
		{
			start_ = false;
		}
		Image::AllSetAlpha(alpha);
		alpha += 2;
	}
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}