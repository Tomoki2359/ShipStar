#pragma once
#include "Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class Building : public GameObject
{
	int hModel_;    //���f���ԍ�
	const char Size_ = 25;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Building(GameObject* parent);

	~Building();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};