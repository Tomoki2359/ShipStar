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
	double Seconds;
	bool OnlySec;	//�b�݂̂̕\�L�ɂ��邩
	bool Lock_;		//���݂̏�ԂŌŒ肷�邩

	void Initialize()
	{
		std::string texS = "Assets\\Count";
		std::string texF = ".png";
		//�摜�f�[�^�̃��[�h
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
		Lock_ = true;
	}

	void Update(short FPS)
	{
		short fps = FPS - 1;
		if (Lock_) { return; }	//Lock����Ă�����X�V���Ȃ�
		Seconds += 1.0 / fps;
	}

	void Reset()
	{

	}

	void Lock()
	{
		Lock_ = true;
	}

	void UnLock()
	{
		Lock_ = false;
	}

	void SetDisplayMode(bool Mode)
	{
		OnlySec = Mode;
	}

	void Draw(Transform tr, int digit)
	{
		int Digit = (int)log10(Seconds);
		Transform Tr = tr;

		//���������̕\��
		for (int i = 0; i <= Digit; i++)
		{
			int Pic = Math::GetDigits(Seconds, (Digit - i), (Digit - i));
			Tr.position_.x = tr.position_.x + (i / 10.0f);
			Image::SetTransform(hPict_[Pic], Tr);
			Image::Draw(hPict_[Pic]);
		}

		//���������̕\��
		for (int i = 1; i <= digit; i++)
		{
			int Pic = (int)(Math::GetFraction((float)Seconds, i, i) * pow((double)10, (double)i));
			Tr.position_.x += (i / 10.0f);
			Image::SetTransform(hPict_[Pic], Tr);
			Image::Draw(hPict_[Pic]);
		}
	}
}