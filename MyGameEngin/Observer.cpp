#include "Observer.h"

#include <math.h>

//コンストラクタ
Observer::Observer(GameObject* parent)
    :GameObject(parent, "Observer"), Start_(false), timer(-180), hPict_()
{
}

//デストラクタ
Observer::~Observer()
{
}

//初期化
void Observer::Initialize()
{
    std::string texS = "Assets\\Count";
    std::string texF = ".png";
    //画像データのロード
    for (int i = 0; i < 3; i++)
    {
        std::string data = texS + std::to_string(i + 1) + texF;
        hPict_[i] = Image::Load(data);
        assert(hPict_[i] > NULL);
    }
}

//更新
void Observer::Update()
{
    //カウントダウン
    if (Start_ != TRUE)
    {

        if (timer >= NULL)
        {
            Start_ = TRUE;
        }
        

    }
    if (Start_ == TRUE)
    {
        transform_.position_.x = -0.9f;
        transform_.position_.y = 0.8f;
    }
    timer++;
}

//描画
void Observer::Draw()
{//カウントダウンの処理
        //あとでもっとスマートに
    if (timer > -180 && timer <= -120)
    {
        Image::SetTransform(hPict_[2], transform_);
        Image::Draw(hPict_[2]);
    }
    if (timer > -120  && timer <= -60)
    {
        Image::SetTransform(hPict_[1], transform_);
        Image::Draw(hPict_[1]);
    }
    if (timer > -60 && timer <= NULL)
    {
        Image::SetTransform(hPict_[0], transform_);
        Image::Draw(hPict_[0]);
    }
    
    if (timer > NULL)
    {
        int time = timer / 60;
        int Digit = log10(time);
        Transform tr = transform_;
        for (int i = 1; i <= (Digit + 1); i++)
        {
            tr.position_.x = transform_.position_.x + (i / 10);
            Image::SetTransform(hPict_[(int)time - 1], transform_);
            Image::Draw(hPict_[(int)time - 1]);
        }
        
    }
}

//開放
void Observer::Release()
{
}

void Observer::CountDown()
{

}
