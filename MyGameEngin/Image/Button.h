#pragma once
#include "../Engine/GameObject.h"

//�摜������������Ƃ��Ɍp������N���X
//�g���Ƃ��̓R���X�g���N�^��SIZE(�摜��)��MODEL(���f����)�����߂�
//SetFile()��InitialPoint()��ݒ肷��(���O�ƈʒu)
//���Ƃ͕K�v�Ȃ��̂����I�[�o���C�h����

//�����V�[�����Ǘ�����N���X
class Button : public GameObject
{
	bool* change_;	//�I������Ă��邩�ǂ���
	bool first_;		//��񂾂�������������
protected:
	//�K���ݒ肷�����
	LPCWSTR* fileName;	//�t�@�C���̖��O
	
	//�K�v�ɉ����Đݒ肷��
	Transform* trans_;	//�摜�̓���
	short SIZE;			//�摜��
	short MODEL;		//���f����

	//�g����������Ȃ�����
	XMFLOAT3 MousePos_;	//�}�E�X�̈ʒu
	short* hPict_;    //���f���ԍ�
	short tucheNumber_;	//�G�ꂽ�ԍ�
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

	//�I���������
	//ON/OFF�@�\�͂��ĂȂ�
	//�摜�̈ʒu�̔���
	void IsImage();

	//�L�[�{�[�h����̔���
	void IsKey();

	//�K���ݒ肷��
	//�摜�t�@�C���̖��O���擾
	virtual void SetFile() = 0;

	//�����n�_
	virtual void InitialPoint() = 0;

	//�K�v�ɉ����ăI�[�o���C�h
	//�Q�[���I�u�W�F�N�g��T���Ȃ�
	//������Ă�����������
	virtual void FirstFind() {};

	//�摜�����������̏���
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
};