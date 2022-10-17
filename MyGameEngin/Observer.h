#pragma once
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Engine/Image.h"

//���������Ǘ�����N���X
class Observer : public GameObject
{
    PlayScene* pPlayScene;
    bool PlaySceneStart_;
    bool Start_;
    int hPict_1;    //�摜�ԍ�
    int hPict_2;    //�摜�ԍ�
    int hPict_3;    //�摜�ԍ�
    int hPict_4;    //�摜�ԍ�
    int timer;

public:
    //�R���X�g���N�^
    Observer(GameObject* parent);

    //�f�X�g���N�^
    ~Observer();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�J�E���g�_�E��������
    void CountDown();
};