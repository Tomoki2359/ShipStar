#pragma once

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}

//シーン切り替えを行うマクロ
#define SCENE_CHANGE(SCENE_ID) SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager"); pSceneManager->ChangeScene(SCENE_ID);