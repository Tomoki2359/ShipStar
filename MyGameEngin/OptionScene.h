#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Image/BackButton.h"
#include "Image/OptionButton.h"
#include "Image/OptionVolume.h"

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
	bool mouseMoob_;	//�}�E�X�������Ă��邩�ǂ���
	bool first_;		//�摜�̃|�C���^���w�肵�����ǂ���

	//�}�E�X����
	XMFLOAT3 mousePos_;		//�O�̃}�E�X�̈ʒu
	XMFLOAT3 mouseNext_;	//���̃}�E�X�̈ʒu

	//�摜�̃|�C���^
	BackButton* pBack_;
	OptionButton* pButton_;
	OptionVolume* pVolume_;
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