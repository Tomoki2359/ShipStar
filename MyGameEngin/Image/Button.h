#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class Button : public GameObject
{
	bool change_;	//�I������Ă��邩�ǂ���
protected:
	XMFLOAT3 MousePos_;	//�}�E�X�̈ʒu
	LPCWSTR* fileName;	//�t�@�C���̖��O
	int alpha_;			//�����x
	short SIZE;			//�摜��
	short* hPict_;    //���f���ԍ�
	bool isPut;		//�����ꂽ���ǂ���
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
	bool IsImage();

	//�摜�����������̓���
	//�������Ⴄ��̓I�[�o���C�h
	virtual void PutButton();

	//�{�^���ɐG��Ă���Ƃ��̏���
	//�������Ⴄ��̓I�[�o�[���C�h
	virtual void TucheButton();

	//�摜�t�@�C���̖��O���擾
	virtual void SetFile() = 0;
};