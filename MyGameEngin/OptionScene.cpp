#include "OptionScene.h"
#include "Image/BackButton.h"

//�R���X�g���N�^
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene")
{
}

//������
void OptionScene::Initialize()
{
	Instantiate<BackButton>(this);
	SetScreen(0, 0, 0);
}

//�X�V
void OptionScene::Update()
{
	if (FindObject("BackButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_TITLE);
	}
}

//�`��
void OptionScene::Draw()
{
}

//�J��
void OptionScene::Release()
{
}