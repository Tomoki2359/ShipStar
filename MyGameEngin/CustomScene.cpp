#include "CustomScene.h"

//�R���X�g���N�^
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene"),mouseMoob_(true),custom_(-1),change_(false), first_(true)
{
}

//������
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<OKButton>(this);
	Instantiate<BackButton>(this);
	Instantiate<CurrentStatus>(this);
	Instantiate<PartsList>(this);
}

//�X�V
void CustomScene::Update()
{
	if (first_)
	{
		first_ = false;
		pBack_ = (BackButton*)FindObject("BackButton");
		assert(pBack_ != nullptr);
		pOK_ = (OKButton*)FindObject("OKButton");
		assert(pOK_ != nullptr);
		pCurrent_ = (CurrentStatus*)FindObject("CurrentStatus");
		assert(pCurrent_ != nullptr);
		pParts_ = (PartsList*)FindObject("PartsList");
		assert(pParts_ != nullptr);
	}
	if (Input::IsKeyDown(DIK_S))
	{
		custom_++;
		mouseMoob_ = false;
		if (custom_ >= MAX_CUSTOM)
		{
			custom_ = CUSTOM_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		custom_--;
		mouseMoob_ = false;
		if (custom_ < 0)
		{
			custom_ = CUSTOM_OK;
		}
	}

	//�}�E�X�����������ǂ���
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}
	//�ύX���邩�ǂ���
	if (change_ == false)
	{
		BeforeChange();
	}

	//�{���ɕύX���邩�ǂ���
	else if (change_ == true)
	{
		AfterChange();
	}
}

//�`��
void CustomScene::Draw()
{
}

//�J��
void CustomScene::Release()
{
}

void CustomScene::BeforeChange()
{
	if (FindObject("BackButton") == nullptr)
	{
		SCENE_CHANGE(SCENE_ID_LOBBY);
	}

	if (FindObject("OKButton") == nullptr)
	{
		pCurrent_->KillMe();
		pParts_->KillMe();
		Instantiate<FixeButton>(this);
		Instantiate<OriginalStatus>(this);
		Instantiate<ChangeStatus>(this);
		change_ = true;
	}

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (custom_ == CUSTOM_BACK)
		{
			pBack_->IsButton();
		}
		if (custom_ == CUSTOM_OK)
		{
			pOK_->IsButton();
		}
	}
}

void CustomScene::AfterChange()
{
	if (FindObject("BackButton") == nullptr)
	{
		Instantiate<BackButton>(this);
		Instantiate<OKButton>(this);
		Instantiate<CurrentStatus>(this);
		Instantiate<PartsList>(this);
		pFixe_->KillMe();
		pOriginal_->KillMe();
		pChange_->KillMe();
		first_ = true;
		change_ = false;
		return;
	}

	if (FindObject("FixeButton") == nullptr)
	{
		Instantiate<OKButton>(this);
		Instantiate<CurrentStatus>(this);
		Instantiate<PartsList>(this);
		pOriginal_->KillMe();
		pChange_->KillMe();
		first_ = true;
		change_ = false;
		SCENE_CHANGE(SCENE_ID_LOBBY);
		return;
	}
	pFixe_ = (FixeButton*)FindObject("FixeButton");
	assert(pFixe_ != nullptr);
	pOriginal_ = (OriginalStatus*)FindObject("OriginalStatus");
	assert(pOriginal_ != nullptr);
	pChange_ = (ChangeStatus*)FindObject("ChangeStatus");
	assert(pChange_ != nullptr);

	//�L�[����
	if (mouseMoob_ == false)
	{
		if (custom_ == CUSTOM_BACK)
		{
			pBack_->IsButton();
		}
		if (custom_ == CUSTOM_OK)
		{
			pFixe_->IsButton();
		}
	}
}
