#include "Observer.h"
#include "Engine/Math.h"
#include "Engine/Time.h"
#include <math.h>


//�R���X�g���N�^
Observer::Observer(GameObject* parent)
    :GameObject(parent, "Observer"), Start_(false), timer(-180), hPict_()
{
}

//�f�X�g���N�^
Observer::~Observer()
{
}

//������
void Observer::Initialize()
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
    Time::SetDisplayMode(false);
}

//�X�V
void Observer::Update()
{
    //�J�E���g�_�E��
    if (!Start_)
    {
        if (timer >= NULL)
        {
            Start_ = TRUE;
        }
        float CdSize = 1 + (-timer % 60) / 30.0f;
        transform_.scale_ = XMFLOAT3(CdSize, CdSize, CdSize);
    }
    if (Start_)
    {
        transform_.scale_ = XMFLOAT3(1.0f, 1.0f, 1.0f);
        Time::UnLock();
        transform_.position_.x = -1.0f;
        transform_.position_.y = 0.8f;
    }
    timer++;
}

//�`��
void Observer::Draw()
{//�J�E���g�_�E���̏���
        //���Ƃł����ƃX�}�[�g��
    if (timer > -180 && timer <= -120)
    {
        Image::SetTransform(hPict_[3], transform_);
        Image::Draw(hPict_[3]);
    }
    if (timer > -120  && timer <= -60)
    {
        Image::SetTransform(hPict_[2], transform_);
        Image::Draw(hPict_[2]);
    }
    if (timer > -60 && timer <= 0)
    {
        Image::SetTransform(hPict_[1], transform_);
        Image::Draw(hPict_[1]);
    }
    
    if (timer > 0)
    {
        Time::Draw(transform_, 2);
    }
}

//�J��
void Observer::Release()
{
}

void Observer::CountDown()
{

}
