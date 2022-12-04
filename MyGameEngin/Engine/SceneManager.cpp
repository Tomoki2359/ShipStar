#include "SceneManager.h"
#include "../SplashScene.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "../LobbyScene.h"
#include "../CustomScene.h"
#include "../MatchingScene.h"
#include "../ResultScene.h"
#include "../OptionScene.h"
#include "../VolumeScene.h"
#include "../ButtonScene.h"
#include "Camera.h"
#include "Image.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
    : GameObject(parent, "SceneManager"), currentSceneID_(), nextSceneID_()
{
}

SceneManager::~SceneManager()
{
}

//初期化
void SceneManager::Initialize()
{
    //最初のシーンを準備
    currentSceneID_ = SCENE_ID_SPLASH;
    nextSceneID_ = currentSceneID_;
    Instantiate<SplashScene>(this);
}


void SceneManager::Update()
{
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //背景をグリーン色に戻す
        SetScreen(0, 128, 128);

        //そのシーンのオブジェクトを全削除
        KillAllChildren();

        //ロードしたデータを全削除
        Model::AllRelease();
        Image::AllRelease();

        //カメラを元の位置に戻す
        Camera::InitCamera();

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
        case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
        case SCENE_ID_OPTION: Instantiate<OptionScene>(this); break;
        case SCENE_ID_BUTTON: Instantiate<ButtonScene>(this); break;
        case SCENE_ID_VOLUME: Instantiate<VolumeScene>(this); break;
        case SCENE_ID_LOBBY: Instantiate<LobbyScene>(this); break;
        case SCENE_ID_CUSTOM: Instantiate<CustomScene>(this); break;
        case SCENE_ID_MATCHING: Instantiate<MatchingScene>(this); break;
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
        case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
        }

        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID next)
{
    nextSceneID_ = next;
}