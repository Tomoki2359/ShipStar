#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum CUSTOM
{
	CUSTOM_BACK = 0,
	CUSTOM_OK,
	MAX_CUSTOM,
};

//�����V�[�����Ǘ�����N���X
class CustomScene : public GameObject
{
	short custom_;
	bool mouseMoob_;
	bool change_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	CustomScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};