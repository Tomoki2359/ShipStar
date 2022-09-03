#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class Button : public GameObject
{
	int hPict_;    //���f���ԍ�
	bool change_;	//�I������Ă��邩�ǂ���
protected:
	XMFLOAT3 MousePos_;	//�}�E�X�̈ʒu
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Button(GameObject* parent);

	Button(GameObject* parent, std::string name);		//�p���p�R���X�g���N�^

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�I������Ă��邩�ǂ���
	void IsButton();

	//�����n�_
	virtual void InitialPoint() = 0;

	//�摜�̈ʒu�̔���
	virtual bool IsImage() = 0;

	//�摜�t�@�C���̖��O���擾
	virtual LPCWSTR SetFile() = 0;
};