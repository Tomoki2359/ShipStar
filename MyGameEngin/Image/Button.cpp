#include "Button.h"
#include "../Engine/Image.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name), MousePos_(),isPut(false),SIZE(1),MODEL(0),first_(true),tucheNumber_(-1)
{
}

Button::Button(GameObject* parent)
	: Button(parent, "Button")
{
}

//������
void Button::Initialize()
{
	//���f���f�[�^�̃��[�h
	hPict_ = new short[SIZE];
	fileName = new LPCWSTR[SIZE];
	change_ = new bool[SIZE + MODEL];
	trans_ = new Transform[SIZE];
	SetFile();
	for (short i = 0; i < SIZE; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
		change_[i] = false;
	}
	for (short i = 0; i < MODEL; i++)
	{
		change_[i + SIZE] = false;
	}
	InitialPoint();
}

//�X�V
void Button::Update()
{
	//��x��������������
	if (first_)
	{
		FirstFind();
		first_ = false;
	}
	//�����ꂽ���ǂ���
	if (isPut == false)
	{
		//�L�[����
		IsKey();
		//�摜�̈ʒu
		IsImage();
		for (int i = 0; i < SIZE + MODEL; i++)
		{
			if (IsAddCondition() && change_[i])
			{
				TucheButton(i);
				if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
				{
					tucheNumber_ = i;
					isPut = true;
				}
			}
			else
			{
				NoTucheButton(i);
			}
		}
	}
	else
	{
		PutButton();
	}
}

//�`��
void Button::Draw()
{
	for (int i = 0; i < SIZE; i++)
	{
		Transform trans;
		trans = trans_[i];
		trans.position_.x = trans.position_.x + pParent_->GetPosition().x;
		trans.position_.y = trans.position_.y + pParent_->GetPosition().y;
		Image::SetTransform(hPict_[i], trans);
		Image::Draw(hPict_[i]);
	}
}

void Button::Release()
{
}

void Button::IsImage()
{
	XMFLOAT3 previousMousePos_ = MousePos_;
	MousePos_ = Input::GetMousePosition();
	if (MousePos_.x != previousMousePos_.x && MousePos_.y !=  previousMousePos_.y)
	{
		//�r���[�|�[�g�s��
		float w = (float)Direct3D::scrWidth / 2.0f;
		float h = (float)Direct3D::scrHeight / 2.0f;
		XMMATRIX vp = {
			w, 0,0,0,
			0,-h,0,0,
			0, 0,1,0,
			w, h,0,1
		};

		//�e�s��̋t�s��
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);
		XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
		XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

		//�}�E�X�ʒu(��O)
		XMFLOAT3 mousePosFront = MousePos_;
		mousePosFront.z = 0.0f;

		//�}�E�X�ʒu(��)
		XMFLOAT3 mousePosBack = MousePos_;
		mousePosBack.z = 1.0f;

		XMVECTOR vMousePosFront = XMLoadFloat3(&mousePosFront);
		vMousePosFront = XMVector3TransformCoord(vMousePosFront, invVP);
		XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
		vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP);

		for (int i = 0; i < SIZE; i++)
		{
			RayCastData MousePos;
			XMStoreFloat3(&MousePos.start, vMousePosFront);

			XMStoreFloat3(&MousePos.dir, vMousePosBack - vMousePosFront);
			change_[i] = false;
			//Image::SetTransform(hPict_[i], trans_[i]);
			Image::RayCast(hPict_[i], &MousePos);
			change_[i] = MousePos.hit;
		}
	}
}

void Button::IsKey()
{
	if (Input::IsKeyDown(DIK_S))
	{
		change_[tucheNumber_] = false;
		tucheNumber_++;
		if (tucheNumber_ >= SIZE + MODEL || tucheNumber_ < 0)
		{
			tucheNumber_ = 0;
		}
		change_[tucheNumber_] = true;
	}
	else if (Input::IsKeyDown(DIK_W))
	{
		change_[tucheNumber_] = false;
		tucheNumber_--;
		if (tucheNumber_ < 0 || tucheNumber_ >= SIZE + MODEL)
		{
			tucheNumber_ = SIZE + MODEL - 1;
		}
		change_[tucheNumber_] = true;
	}
}

//���������ǂ����邩
void Button::PutButton()
{
	KillMe();
}

void Button::TucheButton(int number)
{
	trans_[number].scale_.x = 1.1f;
	trans_[number].scale_.y = 1.1f;
}

void Button::NoTucheButton(int number)
{
	trans_[number].scale_.x = 1.0f;
	trans_[number].scale_.y = 1.0f;
}
