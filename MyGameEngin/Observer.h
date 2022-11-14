#pragma once
#include "Engine/GameObject.h"
#include "PlayScene.h"
#include "Engine/Image.h"

//���������Ǘ�����N���X
class Observer : public GameObject
{
    bool Start_;
    int hPict_[10];
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