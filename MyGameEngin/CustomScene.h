#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Parts/PartsUnion.h"

//�����V�[�����Ǘ�����N���X
class CustomScene : public GameObject
{
	PartsUnion* pUnion_;
	int alpha;
	bool start_;
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