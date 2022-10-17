#include "Observer.h"

//�R���X�g���N�^
Observer::Observer(GameObject* parent)
    :GameObject(parent, "Observer"), PlaySceneStart_(false), Start_(false), hPict_1(-1), hPict_2(-1), hPict_3(-1), timer(0)
{
}

//�f�X�g���N�^
Observer::~Observer()
{
}

//������
void Observer::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_1 = Image::Load(L"Assets\\Count1.png");
    assert(hPict_1 >= 0);
    //�摜�f�[�^�̃��[�h
    hPict_2 = Image::Load(L"Assets\\Count2.png");
    assert(hPict_2 >= 0);
    //�摜�f�[�^�̃��[�h
    hPict_3 = Image::Load(L"Assets\\Count3.png");
    assert(hPict_3 >= 0);
    //�摜�f�[�^�̃��[�h
    hPict_4 = Image::Load(L"");
    assert(hPict_4 >= 0);

    pPlayScene = (PlayScene*)FindObject("PlayScene");
}

//�X�V
void Observer::Update()
{
    //PlaySceneStart_ = pPlayScene->GetStart();
    //�J�E���g�_�E��
    if (PlaySceneStart_ != TRUE)
    {

        if (timer >= 240)
        {
            //�I�������PlayScene��Start_��TRUE�ɂ���
            //pPlayScene->SetStart(TRUE);
            timer = 0;
            PlaySceneStart_ = TRUE;
        }
        timer++;

    }
    //Start_ = pPlayScene->GetStart();
    if (PlaySceneStart_ == TRUE)
    {
        transform_.position_.y += 1000;
    }
}

//�`��
void Observer::Draw()
{//�J�E���g�_�E���̏���
        //���Ƃł����ƃX�}�[�g��
    if (timer > 0 && timer <= 60)
    {
        Image::SetTransform(hPict_3, transform_);
        Image::Draw(hPict_3);
    }
    if (timer > 60  && timer <= 120)
    {
        Image::SetTransform(hPict_2, transform_);
        Image::Draw(hPict_2);
    }
    if (timer > 120 && timer <= 180)
    {
        Image::SetTransform(hPict_1, transform_);
        Image::Draw(hPict_1);
    }
    
}

//�J��
void Observer::Release()
{
}

void Observer::CountDown()
{

}
