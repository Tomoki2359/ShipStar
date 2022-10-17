#pragma once
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Engine/Image.h"

//◆◆◆を管理するクラス
class Observer : public GameObject
{
    PlayScene* pPlayScene;
    bool PlaySceneStart_;
    bool Start_;
    int hPict_1;    //画像番号
    int hPict_2;    //画像番号
    int hPict_3;    //画像番号
    int hPict_4;    //画像番号
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