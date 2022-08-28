#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum OPTION
{
	OPTION_BACK = 0,
	OPTION_BUTTON,
	OPTION_VOLUME,
	MAX_OPTION,
};

//�����V�[�����Ǘ�����N���X
class OptionScene : public GameObject
{
	short option_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	OptionScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};