#pragma once
#include "../Engine/GameObject.h"
#include "../CSVReader.h"
#include "../Option.h"

enum PARTS_NAME
{
	PARTS_GINGA,
	PARTS_MASTANG,
	PARTS_SINDEN,
	PARTS_ZERO,
	END_NAME
};
//�����V�[�����Ǘ�����N���X
class Parts : public GameObject
{
protected:
	int partsNum_;			//�p�[�c�ԍ�
	int catagoryNum_;
	std::string partsName_;	//�p�[�c��
	//short hModel_[CATEGORY_END];			//���f���ԍ�
	short hModel_;			//���f���ԍ�
	int colorNum_;
	PARTS_NUM parts_;

	void SetName();
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Parts(GameObject* parent);

	Parts(GameObject* parent, std::string name);		//�p���p�R���X�g���N�^

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	int GetParts();

	//�p�[�c�Ɉʒu�����킹��
	void Union(PARTS_NAME engineName, int partsNum);

	//�p���֌W
	//�p�[�c���Ă�
	void Load();

	//�p�[�c���Z�b�g����	
	//�����F �������@�p�[�c�ԍ�
	void SetParts(int partsNum);

	//�p�[�c�ԍ��̎擾
	//�߂�l: �p�[�c�ԍ�
	virtual int GetPartsNum() = 0;

	//�J���[�ԍ����Z�b�g����
	//����: �������@�J���[�ԍ�
	void SetColor(int colorNum);

	//�J���[�ԍ��̎擾
	//�߂�l�F �J���[�ԍ�
	int GetColor();

	//���x
	//�����F�������@���x
	void SetBrightness(float brightness);

	//��̓{�f�B�̂Ƃ��̈ʒu����
	//����: �������@�p�[�c�ԍ�
	virtual void GingaUnion(int partsNum) = 0;

	//�}�X�^���O�{�f�B�̂Ƃ��̈ʒu����
	//����: �������@�p�[�c�ԍ�
	virtual void MastangUnion(int partsNum) = 0;

	//�V���f���{�f�B�̂Ƃ��̈ʒu����
	//����: �������@�p�[�c�ԍ�
	virtual void SindenUnion(int partsNum) = 0;

	//�[���{�f�B�̂Ƃ��̈ʒu����
	//����: �������@�p�[�c�ԍ�
	virtual void ZeroUnion(int partsNum) = 0;
};