#include "stdafx.h"
#include "Scene.h"

CScene *CScene::m_Top[];

CScene::CScene(int nPriolity)
{
    //リストのトップを設定
    if (m_Top[nPriolity] == NULL)
    {
        m_Top[nPriolity] = this;
    }
    //リストのトップが決まっているとき
    else
    {
        CScene *scene = m_Top[nPriolity];
        //次へのポインタがNULLの場所を探す
        while (scene->m_Next != NULL)
        {
            scene = scene->m_Next;
        }
        //次へのポインタを自分に設定
        scene->m_Next = this;
    }

    this->m_Next = NULL;
}


CScene::~CScene()
{
}

void CScene::UpdateAll()
{
    CScene *scene;
    CScene *sceneNext;
    CScene *scenePrev;

    for (int i = 0; i < PRIOLITY_MAX; i++)
    {
        scene = m_Top[i];

        //更新処理
        while (scene != NULL)
        {
            sceneNext = scene->m_Next;
            scene->Update();
            scene = sceneNext;
        }

        //解放処理
        scene = m_Top[i];
        scenePrev = m_Top[i];
        while (scene != NULL)
        {
            //次へのポインタを保存
            sceneNext = scene->m_Next;

            //解放予約がされている時
            if (scene->m_Delete == true)
            {
                //リストの先頭の場合
                if (scene == m_Top[i])
                {
                    m_Top[i] = scene->m_Next;
                }
                //先頭以外
                else
                {
                    scenePrev->m_Next = scene->m_Next;
                }
                scene->Uninit();
                delete scene;
            }
            //予約されていない時
            else
            {
                //自分を一つ前に
                scenePrev = scene;
            }
            //次のポインタを自分に
            scene = sceneNext;
        }
    }
}

void CScene::DrawAll(void)
{
    CScene *scene;

    for (int i = 0; i < PRIOLITY_MAX; i++)
    {
        scene = m_Top[i];
        while (scene != NULL)
        {
            scene->Draw();
            scene = scene->m_Next;
        }
    }
}

void CScene::ReleaseAll(void)
{
    CScene *scene;
    CScene *sceneNext;

    for (int i = 0; i < PRIOLITY_MAX; i++)
    {
        scene = m_Top[i];
        while (scene != NULL)
        {
            sceneNext = scene->m_Next;
            scene->Uninit();
            delete scene;
            scene = sceneNext;
        }
        m_Top[i] = NULL;
    }
}

void CScene::Release(void)
{
    m_Delete = true;
}