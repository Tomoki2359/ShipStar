#include "SceneManager.h"
#include "../SplashScene.h"
#include "../TitleScene.h"
#include "Image.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
    : GameObject(parent, "SceneManager")
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

        //���̃V�[�����쐬
        switch (nextSceneID_)
        {
        case SCENE_ID_SPLASH: Instantiate<SplashScene>(this); break;
        case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
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