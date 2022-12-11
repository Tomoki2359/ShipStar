#include "LobbyScene.h"
#include "Engine/Image.h"
#include "Image/LobbyBackground.h"
#include "Image/LobbyImage.h"

//�R���X�g���N�^
LobbyScene::LobbyScene(GameObject* parent)
	: GameObject(parent, "LobbyScene"),alpha(0),start_(true)
{
}

//������
void LobbyScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyBackground>(this);
	Instantiate<LobbyImage>(this);
	Image::AllSetAlpha(0);
}

//�X�V
void LobbyScene::Update()
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
void LobbyScene::Draw()
{
}

//�J��
void LobbyScene::Release()
{
}