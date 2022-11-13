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

	virtual void Load();

	virtual void SetParts(int partsNum);

	virtual int GetPartsNum() = 0;

	virtual void SetColor(int colorNum);

	virtual int GetColor();

	int GetParts();

	void RotationParts();
};