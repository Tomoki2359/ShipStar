#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
//#include "Image/TitleStart.h"
//#include "Image/TitleOption.h"
//
//enum TITLE
//{
//	TITLE_START = 0,
//	TITLE_OPTION,
//	MAX_TITLE,
//};

//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	//short title_;		//�I�񂾉摜
	//bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	//bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	////�}�E�X����
	//XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	//XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	////�摜�̃|�C���^
	//TitleStart* pStart_;
	//TitleOption* pOption_;
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