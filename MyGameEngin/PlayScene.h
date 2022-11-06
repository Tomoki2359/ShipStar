#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

#include "Engine/Particle.h"

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
	bool Initcomprete_ = false;
	int CallNav_;
	int UdCobj_;
	bool Start_ = false;
	int hPict_1;    //�摜�ԍ�
	int hPict_2;    //�摜�ԍ�
	int hPict_3;    //�摜�ԍ�
	int timer;

	Particle* pParticle_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	~PlayScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�Z�b�^�[
	void SetStart(bool start);

	//�Q�b�^�[
	bool GetStart();

	std::list<GameObject*> PlayerList_;
};