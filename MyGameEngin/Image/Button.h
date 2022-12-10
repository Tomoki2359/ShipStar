#pragma once
#include "../Engine/GameObject.h"

//�����V�[�����Ǘ�����N���X
class Button : public GameObject
{
	bool* change_;	//�I������Ă��邩�ǂ���
protected:
	Transform* trans_;	//�}�E�X�̈ʒu
	XMFLOAT3 MousePos_;	//�O��̃}�E�X�̈ʒu
	LPCWSTR* fileName;	//�t�@�C���̖��O
	int alpha_;			//�����x
	short SIZE;			//�摜��
	short MODEL;			//���f����
	short* hPict_;    //���f���ԍ�
	short tucheNumber_;	//�G�ꂽ�ԍ�
	bool isPut;		//�����ꂽ���ǂ���
	bool first_;		//�����ꂽ���ǂ���
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

	virtual void FirstFind() {};

	//�I������Ă��邩�ǂ���
	void IsButton();

	//�����摜������ꍇ
	void IsButton(int number);

	//�����n�_
	virtual void InitialPoint() = 0;

	//�摜�̈ʒu�̔���
	void IsImage();

	//�L�[�{�[�h����̔���
	void IsKey();

	//�摜�����������̓���
	//�������Ⴄ��̓I�[�o���C�h
	virtual void PutButton();

	//�{�^���ɐG��Ă���Ƃ��̏���
	//�������Ⴄ��̓I�[�o�[���C�h
	//����:�������@�I������Ă���ԍ�
	virtual void TucheButton(int number);

	//�{�^���ɐG��Ă��Ȃ��Ƃ��̏���
	//�������Ⴄ��̓I�[�o�[���C�h
	//����:�������@�I������Ă���ԍ�
	virtual void NoTucheButton(int number);

	//�G����Ă���E�I������Ă���ȊO�̒ǉ�����
	//�K�v�Ȃ��̂̂݃I�[�o�[���C�h
	virtual bool IsAddCondition() { return true; };

	//�摜�t�@�C���̖��O���擾
	virtual void SetFile() = 0;
};