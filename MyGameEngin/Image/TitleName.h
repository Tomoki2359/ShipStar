#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class TitleName : public GameObject
{
	int hPict_;    //���f���ԍ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleName(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};