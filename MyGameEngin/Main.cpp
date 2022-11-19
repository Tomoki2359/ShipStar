//�C���N���[�h
#include <algorithm>
#include <stdlib.h>
#include <Windows.h>
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Transform.h"
#include "Engine/Time.h"
#include "Engine/RootJob.h"
#include "Option.h"

#pragma comment(lib, "winmm.lib")

//�萔�錾
LPCWSTR WIN_CLASS_NAME = L"Celestial Contender";	//�E�B���h�E�N���X��
const int WINDOW_WIDTH = 1920;				//�E�B���h�E�̕�
const int WINDOW_HEIGHT = 1080;				//�E�B���h�E�̍���

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

RootJob* pRoot;

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);							//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;								//�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;						//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;								//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;						//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);				//�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				//�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;									//���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�w�i�i���j
	RegisterClassEx(&wc);									//�N���X��o�^

	HRESULT hr;

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,		//�E�B���h�E�N���X��
		L"Celestial Contender",	//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW,//�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,		//�\���ʒu���i���܂����j
		CW_USEDEFAULT,		//�\���ʒu��i���܂����j
		winW,				//�E�B���h�E��
		winH,				//�E�B���h�E����
		NULL,				//�e�E�C���h�E�i�Ȃ��j
		NULL,				//���j���[�i�Ȃ��j
		hInstance,			//�C���X�^���X
		NULL				//�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	//COM�̏�����
	hr = CoInitialize(nullptr);
	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
	if (FAILED(hr))
	{
		PostQuitMessage(0);
	}

	//DirectInput�̏�����
	Input::Initialize(hWnd);
	Camera::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Option::Init();
	pRoot = new RootJob(nullptr);
	pRoot->Initialize();

	Time::Initialize();

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));//�z��Ȃǒ��g��S�ĂO�ɂ���
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			timeBeginPeriod(1);

			static const char MAX_FPS = 60;

			static int i = 0;
			static DWORD countFps[MAX_FPS];
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			static DWORD lastUpdateTime = nowTime;

			//if (nowTime - startTime >= 1000)
			//{
				//WCHAR str[16];
				//wsprintf(str, L"%u", countFps);
				//SetWindowText(hWnd, str);

			startTime = nowTime;
			//}

			if ((nowTime - lastUpdateTime) * MAX_FPS <= 1000.0f)
			{
				continue;
			}
			//FPS�̍X�V
			Time::Update((short)*std::max_element(countFps, countFps + MAX_FPS));
			countFps[i] = 0;
			lastUpdateTime = nowTime;

			for (int j = NULL; j < MAX_FPS; j++)
			{
				countFps[j]++;
			}
			i++;
			if (i >= MAX_FPS)
			{
				i = NULL;
			}

			Input::Update();
			pRoot->UpdateSub();

			if (Input::IsKeyUp(DIK_ESCAPE))
			{
				static int cnt = 0;
				cnt++;
				if (cnt >= 3)
				{
					PostQuitMessage(0);
				}
			}


			//�Q�[���̏���
			Direct3D::BeginDraw();

			Camera::Update();

			//�`�揈��
			pRoot->DrawSub();



			Direct3D::EndDraw();

			timeEndPeriod(1);
		}
	}

	Model::Release();
	Image::Release();
	pRoot->ReleaseSub();
	SAFE_RELEASE(pRoot);

	Input::Release();
	Direct3D::Release();
	CoUninitialize();
	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)//msg�͏��(�L�[����͂�}�E�X���������Ȃ�)wParam��lParam�͒ǉ���񂪓���
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}