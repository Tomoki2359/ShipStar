#pragma once
#include "Button.h"
#include "../Parts/PartsUnion.h"

//�����V�[�����Ǘ�����N���X
class BeforCustomImage : public Button
{
	//�@�̂̃p�[�c�̃|�C���^
	EnginParts* pEngin_;
	BodyParts* pBody_;
	WingParts* pWing_;
	CookpitParts* pCookpit_;

	//�@�̂̃p�[�c�ԍ�
	int engineNum_;
	int bodyNum_;
	int wingNum_;
	int cookpitNum_;

	//�@�̂̐F�ԍ�
	int engineColor_;
	int bodyColor_;
	int wingColor_;
	int cookpitColor_;

	//���x�֘A
	float partsBrightness_;
	bool isBrightness_;

	short isNumber;
	XMFLOAT3 difference_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	BeforCustomImage(GameObject* parent);

	//�����n�_
	void InitialPoint() override;

	//�摜�t�@�C���̖��O���擾
	void SetFile() override;

	void FirstFind() override;

	//���������̏���
	void PutButton() override;

	//�{�^���ɐG��Ă���Ƃ��̏���
	//����:�������@�I������Ă���ԍ�
	void TucheButton(int number) override;

	bool IsAddCondition() override;

	//�p�[�c�̕ύX
	//����:������ �@�̂̃p�[�c:������ �p�[�c�ԍ�:��O���� �p�[�c�̐F�ԍ�
	void PartsChange(Parts* parts, int& partsNum, int& partsColor);

	void SetParts();
};