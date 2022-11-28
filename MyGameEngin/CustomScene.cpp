#include "CustomScene.h"
#include "Image/LobbyBackground.h"

//コンストラクタ
CustomScene::CustomScene(GameObject* parent)
	: GameObject(parent, "CustomScene"),mouseMoob_(true),custom_(-1),change_(false), first_(true)
	
{
}

//初期化
void CustomScene::Initialize()
{
	SetScreen(0, 0, 0);
	Instantiate<LobbyBackground>(this);
	Instantiate<OKButton>(this);
	Instantiate<BackButton>(this);
	Instantiate<CurrentStatus>(this);
	Instantiate<PartsList>(this);

	Instantiate<PartsUnion>(this);
}

//更新
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

		pEngin_ = (EnginParts*)FindObject("EnginParts");
		assert(pEngin_ != nullptr);
		engineNum_ = pEngin_->GetParts();
		engineColor_ = pEngin_->GetColor();
		pBody_ = (BodyParts*)FindObject("BodyParts");
		assert(pBody_ != nullptr);
		bodyNum_ = pBody_->GetParts();
		bodyColor_ = pBody_->GetColor();
		pWing_ = (WingParts*)FindObject("WingParts");
		assert(pWing_ != nullptr);
		wingNum_ = pWing_->GetParts();
		wingColor_ = pWing_->GetColor();
		pCookpit_ = (CookpitParts*)FindObject("CookpitParts");
		assert(pCookpit_ != nullptr);
		cookpitNum_ = pCookpit_->GetParts();
		cookpitColor_ = pCookpit_->GetColor();

		pUnion_ = (PartsUnion*)FindObject("PartsUnion");
		assert(pUnion_ != nullptr);
	}
	
	//マウスが動いたかどうか
	mousePos_ = mouseNext_;
	mouseNext_ = Input::GetMousePosition();
	if (mousePos_.x != mouseNext_.x && mousePos_.y != mouseNext_.y)
	{
		mouseMoob_ = true;
	}
	//変更するかどうか
	if (change_ == false)
	{
		BeforeChange();
	}

	//本当に変更するかどうか
	else if (change_ == true)
	{
		AfterChange();
	}

	pUnion_->RotationParts();
}

//描画
void CustomScene::Draw()
{
}

//開放
void CustomScene::Release()
{
}

void CustomScene::BeforeChange()
{
	if (Input::IsKeyDown(DIK_S))
	{
		custom_++;
		mouseMoob_ = false;
		if (custom_ >= BEFORE_MAX)
		{
			custom_ = BEFORE_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		custom_--;
		mouseMoob_ = false;
		if (custom_ < 0)
		{
			custom_ = BEFORE_COOKPIT;
		}
	}

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

	//キー操作
	if (mouseMoob_ == false)
	{
		if (custom_ == BEFORE_BACK)
		{
			pBack_->IsButton();
		}
		if (custom_ == BEFORE_OK)
		{
			pOK_->IsButton();
		}
		if (custom_ == BEFORE_ENGIN)
		{
			PartsChange(pEngin_, engineNum_, engineColor_);
		}
		if (custom_ == BEFORE_BODY)
		{
			PartsChange(pBody_, bodyNum_, bodyColor_);
		}
		if (custom_ == BEFORE_WING)
		{
			PartsChange(pWing_, wingNum_, wingColor_);
		}
		if (custom_ == BEFORE_COOKPIT)
		{
			PartsChange(pCookpit_, cookpitNum_, cookpitColor_);
		}
	}

	pEngin_->Union((PARTS_NAME)bodyNum_, engineNum_);
	pWing_->Union((PARTS_NAME)bodyNum_, wingNum_);
	pCookpit_->Union((PARTS_NAME)bodyNum_, cookpitNum_);
}

void CustomScene::AfterChange()
{
	if (Input::IsKeyDown(DIK_S))
	{
		custom_++;
		mouseMoob_ = false;
		if (custom_ >= AFTER_MAX)
		{
			custom_ = AFTER_BACK;
		}
	}
	if (Input::IsKeyDown(DIK_W))
	{
		custom_--;
		mouseMoob_ = false;
		if (custom_ < 0)
		{
			custom_ = AFTER_OK;
		}
	}

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
		PARTS_NUM parts_;
		parts_.BODY = pBody_->GetPartsNum();
		parts_.COCKPIT = pCookpit_->GetPartsNum();
		parts_.ENGINE = pEngin_->GetPartsNum();
		parts_.WING = pWing_->GetPartsNum();
		Option::SetParts(parts_);
		Option::SetColor(engineColor_, PARTS_ENGINE);
		Option::SetColor(bodyColor_, PARTS_BODY);
		Option::SetColor(wingColor_, PARTS_WING);
		Option::SetColor(cookpitColor_, PARTS_COCKPIT);
		SCENE_CHANGE(SCENE_ID_LOBBY);
		return;
	}
	pFixe_ = (FixeButton*)FindObject("FixeButton");
	assert(pFixe_ != nullptr);
	pOriginal_ = (OriginalStatus*)FindObject("OriginalStatus");
	assert(pOriginal_ != nullptr);
	pChange_ = (ChangeStatus*)FindObject("ChangeStatus");
	assert(pChange_ != nullptr);

	//キー操作
	if (mouseMoob_ == false)
	{
		if (custom_ == AFTER_BACK)
		{
			pBack_->IsButton();
		}
		if (custom_ == AFTER_OK)
		{
			pFixe_->IsButton();
		}
	}
}

void CustomScene::PartsChange(Parts* parts, int& partsNum, int& partsColor)
{

	if (Input::IsKeyDown(DIK_D))
	{
		partsNum++;
	}
	if (Input::IsKeyDown(DIK_A))
	{
		partsNum--;
	}
	if (Input::IsKeyDown(DIK_Z))
	{
		partsColor++;
		if (partsColor >= 5)
		{
			partsColor = 0;
		}
	}
	if (partsNum < PARTS_GINGA)
	{
		partsNum = PARTS_END - 1;
	}
	if (partsNum >= PARTS_END)
	{
		partsNum = PARTS_GINGA;
	}
	parts->SetColor(partsColor);
	parts->SetParts(partsNum);
	parts->Load();
	parts->Union((PARTS_NAME)bodyNum_, partsNum);
}
