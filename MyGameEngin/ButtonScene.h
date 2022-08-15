#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum BUTTON
{
	BUTTON_BACK = 0,
	BUTTON_OK,
	MAX_BUTTON,
};

//�����V�[�����Ǘ�����N���X
class ButtonScene : public GameObject
{
	short button_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ButtonScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};