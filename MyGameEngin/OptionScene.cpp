#include "OptionScene.h"
#include "Image/ButtonArrangement.h"
#include "Image/OptionImage.h"
#include "Image/Background.h"

//�R���X�g���N�^
OptionScene::OptionScene(GameObject* parent)
	: GameObject(parent, "OptionScene")
{
}

//������
void OptionScene::Initialize()
{
	Instantiate<Background>(this);
	Instantiate<ButtonArrangement>(this);
	Instantiate<OptionImage>(this);
	SetScreen(0, 0, 0);
}

//�X�V
void OptionScene::Update()
{
}

//�`��
void OptionScene::Draw()
{
}

//�J��
void OptionScene::Release()
{
}