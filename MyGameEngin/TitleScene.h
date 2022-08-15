#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

enum TITLE
{
	TITLE_START = 0,
	TITLE_OPTION,
	MAX_TITLE,
};

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	short title_;
	bool mouseMoob_;
	XMFLOAT3 mousePos_;
	XMFLOAT3 mouseNext_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};