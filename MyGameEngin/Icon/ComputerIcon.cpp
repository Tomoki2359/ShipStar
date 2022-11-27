#include "ComputerIcon.h"
#include "../Engine/Image.h"

ComputerIcon::ComputerIcon(GameObject* parent)
	:AirframeIcon(parent, "ComputerIcon")
{
}

void ComputerIcon::Load()
{
	//モデルデータのロード
	hPict_ = Image::Load(L"Assets\\ComputerIcon.png");
	assert(hPict_ >= 0);

}

void ComputerIcon::AirframePos()
{
	pComputer_ = (Computer*)FindObject("Computer");
	assert(pComputer_ != nullptr);
	AirframePos_ = pComputer_->GetPosition();
}