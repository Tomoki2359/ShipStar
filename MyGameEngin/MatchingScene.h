#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//�����V�[�����Ǘ�����N���X
class MatchingScene : public GameObject
{
	int alpha;
	bool start_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	MatchingScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};