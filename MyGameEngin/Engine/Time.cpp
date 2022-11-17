#include "Time.h"
#include "Image.h"
#include "Math.h"
#include "Transform.h"

#include <string>

namespace Time
{
	int hPict_[10];
	char Hours;
	short Minuts;
	float Seconds;
	bool OnlySec;

	void Initialize()
	{
		std::string texS = "Assets\\Count";
		std::string texF = ".png";
		//画像データのロード
		for (int i = 0; i < 10; i++)
		{
			std::string data = texS + std::to_string(i) + texF;
			hPict_[i] = Image::Load(data);
			assert(hPict_[i] > NULL);
		}
		Hours = NULL;
		Minuts = NULL;
		Seconds = NULL;
		OnlySec = false;
	}
	void SetDisplayMode(bool Mode)
	{
		OnlySec = Mode;
	}

	void Draw(int value, Transform tr)
	{
		int Digit = (int)log10(value);
		Transform Tr = tr;
		for (int i = 0; i <= Digit; i++)
		{
			int Pic = Math::GetDigits(value, (Digit - i), (Digit - i));
			Tr.position_.x = tr.position_.x + (i / 10.0f);
			Image::SetTransform(hPict_[Pic], Tr);
			Image::Draw(hPict_[Pic]);
		}
	}
	void Draw(float value, Transform tr)
	{
	}
}