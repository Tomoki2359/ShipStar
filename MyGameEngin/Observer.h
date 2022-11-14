#pragma once
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Engine/Image.h"

//◆◆◆を管理するクラス
class Observer : public GameObject
{
    bool Start_;
    int hPict_[10];
    int timer;
public:
    //コンストラクタ
    Observer(GameObject* parent);

    //デストラクタ
    ~Observer();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //カウントダウンをする
    void CountDown();
};