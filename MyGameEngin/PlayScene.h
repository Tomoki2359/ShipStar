#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	bool Initcomprete_ = false;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	std::list<GameObject*> PlayerList_;
};