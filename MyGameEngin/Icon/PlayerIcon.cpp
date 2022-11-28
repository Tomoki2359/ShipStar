#include "PlayerIcon.h"
#include "../Engine/Image.h"

PlayerIcon::PlayerIcon(GameObject* parent)
	:AirframeIcon(parent, "PlayerIcon"), pPlayer_(nullptr)
{
}

void PlayerIcon::Load()
{
	//���f���f�[�^�̃��[�h
	hPict_ = Image::Load(L"Assets\\PlayerIcon.png");
	assert(hPict_ >= 0);

}

void PlayerIcon::AirframePos()
{
	pPlayer_ = (Player*)FindObject("Player");
	assert(pPlayer_ != nullptr);
	AirframePos_ = pPlayer_->GetPosition();
}

void PlayerIcon::Release()
{
	SAFE_RELEASE(pPlayer_);
}
