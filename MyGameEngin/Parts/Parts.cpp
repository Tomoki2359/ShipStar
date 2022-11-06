#include "Parts.h"
#include "../Engine/Model.h"

//�R���X�g���N�^
Parts::Parts(GameObject* parent, std::string name)
	: GameObject(parent, name)
{
	partsNum_ = 0;	
}



Parts::Parts(GameObject* parent)
	: Parts(parent, "Parts")
{
	partsNum_ = 0;	
}

//������
void Parts::Initialize()
{
	SetName();
	//hModel_ = Model::Load("Assets\\Parts\\" + partsName_);
	//hModel_ = Model::Load("Assets\\Parts\\ginga_engin.fbx");
	//assert(hModel_ >= 0);

	Load();
}

//�X�V
void Parts::Update()
{
}

//�`��
void Parts::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Parts::Release()
{
}

void Parts::Load()
{
	hModel_ = Model::Load(partsName_);
	assert(hModel_ >= 0);
}

void Parts::SetParts(int partsNum)
{
	partsNum_ = partsNum;
	SetName();
}

void Parts::SetColor(int colorNum)
{
	switch (colorNum)
	{
	case 0:
		Model::SetColor(hModel_, 0, 0, 0);
		break;
	case 1:
		Model::SetColor(hModel_, 255, 255, 255);
		break;
	case 2:
		Model::SetColor(hModel_, 255, 0, 0);
		break;
	case 3:
		Model::SetColor(hModel_, 0, 255, 0);
		break;
	case 4:
		Model::SetColor(hModel_, 0, 0, 255);
		break;
	default:
		break;
	}
}

int Parts::GetParts()
{
	return partsNum_;
}

void Parts::SetName()
{
	//���f���f�[�^�̃��[�h
	//CSVReader csv;
	//csv.Load("..\\Assets\\Parts\\partsName.csv");
	//partsName_ = csv.GetString(partsNum_ % PARTS_END, 0);
	switch (partsNum_)
	{
	case PARTS_GINGA:
		partsName_ = "Assets\\Parts\\ginga";
		break;
	case PARTS_MASTANG:
		partsName_ = "Assets\\Parts\\mastang";
		break;
	case PARTS_SINDEN:
		partsName_ = "Assets\\Parts\\sinden";
		break;
	case PARTS_ZERO:
		partsName_ = "Assets\\Parts\\zero";
		break;
	default:
		break;
	}

	switch (catagoryNum_)
	{
	case PARTS_ENGINE:
		partsName_ = partsName_ + "_engin.fbx";
		break;
	case PARTS_BODY:
		partsName_ = partsName_ + "_body.fbx";
		break;
	case PARTS_WING:
		partsName_ = partsName_ + "_wing.fbx";
		break;
	case PARTS_COCKPIT:
		partsName_ = partsName_ + "_cockpit.fbx";
		break;
	default:
		break;
	}
}