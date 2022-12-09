#include "Button.h"
#include "../Engine/Image.h"
#include "../Engine/Camera.h"

//�R���X�g���N�^
Button::Button(GameObject* parent, std::string name)
	: GameObject(parent, name),change_(false), MousePos_(),alpha_(255),isPut(false),SIZE(1)
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
	SetFile();
	for (short i = 0; i < SIZE; i++)
	{
		hPict_[i] = Image::Load(fileName[i]);
	}
	InitialPoint();
}

//�X�V
void Button::Update()
{
	//�}�E�X�̈ʒu�̎擾
	MousePos_ = Input::GetMousePosition();

	//�����ꂽ���ǂ���
	if (isPut == false)
	{
		//�摜�̈ʒu
		if (IsImage() || change_)
		{
			TucheButton();
			if (Input::IsMouceDown(0) || Input::IsKeyDown(DIK_Z))
				isPut = true;
		}
		else
		{
			transform_.scale_.x = 1.0f;
			transform_.scale_.y = 1.0f;
		}
	}
	else
	{
		PutButton();
	}
	change_ = false;
}

//�`��
void Button::Draw()
{
	for (int i = 0; i < SIZE; i++)
	{
		Image::SetTransform(hPict_[i], transform_);
		Image::Draw(hPict_[i]);
	}
}

//�J��
void Button::Release()
{
}

//�I������Ă��邩�ǂ���
void Button::IsButton()
{
	change_ = true;
}

bool Button::IsImage()
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
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0.0f;

	//�}�E�X�ʒu(��)
	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	//�@ mousePosFront���x�N�g���ɕϊ�
	XMVECTOR vMousePosFront = XMLoadFloat3(&mousePosFront);
	//�A �@��invVP,invPrj,invView��������
	vMousePosFront = XMVector3TransformCoord(vMousePosFront, invVP);
	//�B mousePosBack���x�N�g���ɕϊ�
	XMVECTOR vMousePosBack = XMLoadFloat3(&mousePosBack);
	//�C �B��invVP, invPrj, invView��������
	vMousePosBack = XMVector3TransformCoord(vMousePosBack, invVP);

	//�D �A����C�Ɍ������ă��C������(�Ƃ肠�������f���ԍ���hModel_[0])
	RayCastData MousePos;
	XMStoreFloat3(&MousePos.start, vMousePosFront);

	XMStoreFloat3(&MousePos.dir, vMousePosBack - vMousePosFront);
	for (int i = 0; i < SIZE; i++)
	{
		Image::SetTransform(hPict_[i], transform_);
		Image::RayCast(hPict_[i], &MousePos);
		if (MousePos.hit)
		{
			return true;
		}
	}
	return false;
}

//���������ǂ����邩
void Button::PutButton()
{
	//�摜�������Ȃ��Ȃ��Ă������
	//if (alpha_ <= 0)
	//{
		KillMe();
	//}
	//alpha_ -= 3;
	//Image::AllSetAlpha(alpha_);
}

void Button::TucheButton()
{
	transform_.scale_.x = 1.1f;
	transform_.scale_.y = 1.1f;
}
