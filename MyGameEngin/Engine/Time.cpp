#include "Time.h"
#include "Image.h"
#include "Math.h"
#include "Transform.h"

#include <string>

namespace Time
{
	//60�i�@
	const char HEX = 60;

	//�\������
	const char Dig = 2;

	//�����Ԃ̑傫��
	const float Interval = 0.1f;

	int hPict_[10];
	char Hours;
	char Minuts;
	double Seconds;
	bool OnlySec;	//�b�݂̂̕\�L�ɂ��邩
	bool Lock_;		//���݂̏�ԂŌŒ肷�邩

	void Initialize()
	{
		std::string texS = "Assets\\Numbers\\Num";
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
		float fps = (FPS - 1) * 1.0005f;
		if (Lock_) { return; }	//Lock����Ă�����X�V���Ȃ�
		Seconds += 1.0 / fps;
	}

	void Reset()
	{
		Hours = NULL;
		Minuts = NULL;
		Seconds = NULL;
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
		Transform Tr = tr;

		if (OnlySec)	//�b�̂ݕ\���̏ꍇ
		{
			int Digit = (int)log10(Seconds);

			//���������̕\��
			for (int i = NULL; i <= Digit; i++)
			{
				int Pic = Math::GetDigits((int)Seconds, (Digit - i), (Digit - i));
				Tr.position_.x += Interval;
				Image::SetTransform(hPict_[Pic], Tr);
				Image::Draw(hPict_[Pic]);
			}
		}
		else
		{
			int sec = Seconds;

			sec %= HEX;

			//��/���̍X�V
			Minuts = Seconds / HEX;
			Hours = Minuts / HEX;
			Minuts %= HEX;

			if (Hours > NULL)	//Hours���܂߂��\��
			{
				int Pic = Math::GetDigits(Hours, NULL, NULL);
				Tr.position_.x += Interval;
				Image::SetTransform(hPict_[Pic], Tr);
				Image::Draw(hPict_[Pic]);

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(Minuts, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(sec, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
			else if (Minuts > NULL)	//Minuts���܂߂��\��
			{
				int Digit = (int)log10(Minuts);
				for (int i = NULL; i <= Digit; i++)
				{
					int Pic = Math::GetDigits(Minuts, (Digit - i), (Digit - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(sec, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
			else
			{
				int Digit = (int)log10(Seconds);

				//���������̕\��
				for (int i = NULL; i <= Digit; i++)
				{
					int Pic = Math::GetDigits(Seconds, (Digit - i), (Digit - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
		}

		//���������̕\��
		const float Dec = 0.8f;		//�����_�ȉ��̕\���͏k������
		Tr.scale_ = { Dec, Dec, Dec };
		Tr.position_.y -= 0.02f;		//�k�����������ɉ�����
		for (int i = 1; i <= digit; i++)
		{
			int Pic = Math::GetFraction((float)Seconds, i);
			Tr.position_.x += Interval;
			Image::SetTransform(hPict_[Pic], Tr);
			Image::Draw(hPict_[Pic]);
		}
	}

	float GetTime()
	{
		return Seconds;
	}
}