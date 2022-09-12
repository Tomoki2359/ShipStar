#pragma once
#include "Engine/GameObject.h"
#include "Navigation.h"

//�����V�[�����Ǘ�����N���X
class Course : public GameObject
{
	friend Navigation;

	int hModel_;    //���f���ԍ�
	const char Size_ = 25;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Course(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	int GetModelHandle() { return hModel_; }
};