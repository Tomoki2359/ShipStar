#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/BackButton.h"
#include "Image/OKButton.h"

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
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�}�E�X����
	XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	//�摜�̃|�C���^
	BackButton* pBack_;
	OKButton* pOK_;
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