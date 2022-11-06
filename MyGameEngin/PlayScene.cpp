#include "PlayScene.h"
#include "Building.h"
#include "Computer.h"
#include "Course.h"
#include "GoalObject.h"
#include "Navigation.h"
#include "Player.h"
#include "Image/PlayBackground.h"
#include "Observer.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), PlayerList_(), CallNav_(NULL), UdCobj_(NULL),hPict_1(-1), hPict_2(-1), hPict_3(-1), timer(0),Start_(false)
{
}

PlayScene::~PlayScene()
{
	PlayerList_.clear();
}

//������
void PlayScene::Initialize()
{
	{
		pParticle_ = (Particle*)Instantiate<Particle>(this);

		//��
		EmitterData data;

		//��
		data.textureFileName = "Assets\\temporary\\Cloud.png";
		data.position = XMFLOAT3(-4, 1.5, -4);
		data.positionErr = XMFLOAT3(0.1, 0, 0.1);
		data.delay = 5;
		data.number = 1;
		data.lifeTime = 60;
		data.gravity = -0.002f;
		data.dir = XMFLOAT3(0, 1, 0);
		data.dirErr = XMFLOAT3(0, 0, 0);
		data.speed = 0.01f;
		data.speedErr = 0.0;
		data.size = XMFLOAT2(1.5, 1.5);
		data.sizeErr = XMFLOAT2(0.4, 0.4);
		data.scale = XMFLOAT2(1.01, 1.01);
		data.color = XMFLOAT4(1, 1, 0, 1);
		data.deltaColor = XMFLOAT4(0, -0.03, 0, -0.02);
		pParticle_->Start(data);
	}

	char PlayerNum = NULL;
	PlayerList_.clear();
	SetScreen(255, 255, 255);
	Instantiate<PlayBackground>(this);
	Instantiate<Course>(this);
	Instantiate<GoalObject>(this);
	Instantiate<Observer>(this);
	Instantiate<Building>(this);
	PlayerList_.push_back(Instantiate<Player>(this));
	PlayerNum += (char)PlayerList_.size();
	while (PlayerNum < 2)
	{
		PlayerList_.push_back(Instantiate<Computer>(this));
		PlayerNum++;
	}


	

	////�΂̕�
	//data.number = 3;
	//data.positionErr = XMFLOAT3(0.8, 0, 0.8);
	//data.dir = XMFLOAT3(0, 1, 0);
	//data.dirErr = XMFLOAT3(10, 10, 10);
	//data.size = XMFLOAT2(0.2, 0.2);
	//data.scale = XMFLOAT2(0.95, 0.95);
	//data.lifeTime = 120;
	//data.speed = 0.1f;
	//data.gravity = 0;
	//pParticle_->Start(data);

}

//�X�V
void PlayScene::Update()
{
	if (CallNav_ == 2 && !Initcomprete_)	//�J�n�t���[���͌�قǒ���
	{
		Instantiate<Navigation>(this);
		Initcomprete_ = true;
	}
	else if(!Initcomprete_ && CallNav_ < 5)
	{
		CallNav_++;
	}

	Player* pPlayer = (Player*)FindObject("Player");

	/*if (pPlayer->GetStart() && UdCobj_ > 300)
	{
		Navigation* pNav = (Navigation*)FindObject("Navigation");
		CourseOutObject* pCobj = (CourseOutObject*)FindObject("CourseOutObject");
		pCobj->SetPosition(pNav->GetLeft());
		UdCobj_ = NULL;
	}*/
	if (pPlayer->GetisGoal())
	{
		SCENE_CHANGE(SCENE_ID_RESULT);
	}
	//UdCobj_++;
}

//�`��
void PlayScene::Draw()
{
	
}

//�J��
void PlayScene::Release()
{
}

void PlayScene::SetStart(bool start)
{
	Start_ = start;
}

bool PlayScene::GetStart()
{
	return Start_;
}
