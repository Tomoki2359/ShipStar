#include "Observer.h"

//コンストラクタ
Observer::Observer(GameObject* parent)
    :GameObject(parent, "Observer"), PlaySceneStart_(false), Start_(false), hPict_1(-1), hPict_2(-1), hPict_3(-1), timer(0)
{
}

//デストラクタ
Observer::~Observer()
{
}

//初期化
void Observer::Initialize()
{
    //画像データのロード
    hPict_1 = Image::Load(L"Assets\\Count1.png");
    assert(hPict_1 >= 0);
    //画像データのロード
    hPict_2 = Image::Load(L"Assets\\Count2.png");
    assert(hPict_2 >= 0);
    //画像データのロード
    hPict_3 = Image::Load(L"Assets\\Count3.png");
    assert(hPict_3 >= 0);
    //画像データのロード
    hPict_4 = Image::Load(L"");
    assert(hPict_4 >= 0);

    pPlayScene = (PlayScene*)FindObject("PlayScene");
}

//更新
void Observer::Update()
{
    //PlaySceneStart_ = pPlayScene->GetStart();
    //カウントダウン
    if (PlaySceneStart_ != TRUE)
    {

        if (timer >= 240)
        {
            //終わったらPlaySceneのStart_をTRUEにする
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

//描画
void Observer::Draw()
{//カウントダウンの処理
        //あとでもっとスマートに
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

//開放
void Observer::Release()
{
}

void Observer::CountDown()
{

}
