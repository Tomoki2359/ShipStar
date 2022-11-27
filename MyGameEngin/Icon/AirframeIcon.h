#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class AirframeIcon : public GameObject
{
protected:
	short hPict_;			//���f���ԍ�
	XMFLOAT3 InitialPos_;	//�����ʒu
	XMFLOAT3 AirframePos_;	//�@�̈ʒu
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	AirframeIcon(GameObject* parent);

	AirframeIcon(GameObject* parent, std::string name);		//�p���p�R���X�g���N�^

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�p���֌W
	//�����ݒ�
	virtual void Load() = 0;

	virtual void AirframePos() = 0;
};