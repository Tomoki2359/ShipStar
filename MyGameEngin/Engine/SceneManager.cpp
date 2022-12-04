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

//������
void SceneManager::Initialize()
{
    //�ŏ��̃V�[��������
    currentSceneID_ = SCENE_ID_SPLASH;
    nextSceneID_ = currentSceneID_;
    Instantiate<SplashScene>(this);
}


void SceneManager::Update()
{
    //���̃V�[�������݂̃V�[���ƈႤ �� �V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
    if (currentSceneID_ != nextSceneID_)
    {
        //�w�i���O���[���F�ɖ߂�
        SetScreen(0, 128, 128);

        //���̃V�[���̃I�u�W�F�N�g��S�폜
        KillAllChildren();

        //���[�h�����f�[�^��S�폜
        Model::AllRelease();
        Image::AllRelease();

        //�J���������̈ʒu�ɖ߂�
        Camera::InitCamera();

        //���̃V�[�����쐬
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