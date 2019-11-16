#include "stdafx.h"
#include "Scene.h"

CScene *CScene::m_Top[];

CScene::CScene(int nPriolity)
{
    //���X�g�̃g�b�v��ݒ�
    if (m_Top[nPriolity] == NULL)
    {
        m_Top[nPriolity] = this;
    }
    //���X�g�̃g�b�v�����܂��Ă���Ƃ�
    else
    {
        CScene *scene = m_Top[nPriolity];
        //���ւ̃|�C���^��NULL�̏ꏊ��T��
        while (scene->m_Next != NULL)
        {
            scene = scene->m_Next;
        }
        //���ւ̃|�C���^�������ɐݒ�
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

        //�X�V����
        while (scene != NULL)
        {
            sceneNext = scene->m_Next;
            scene->Update();
            scene = sceneNext;
        }

        //�������
        scene = m_Top[i];
        scenePrev = m_Top[i];
        while (scene != NULL)
        {
            //���ւ̃|�C���^��ۑ�
            sceneNext = scene->m_Next;

            //����\�񂪂���Ă��鎞
            if (scene->m_Delete == true)
            {
                //���X�g�̐擪�̏ꍇ
                if (scene == m_Top[i])
                {
                    m_Top[i] = scene->m_Next;
                }
                //�擪�ȊO
                else
                {
                    scenePrev->m_Next = scene->m_Next;
                }
                scene->Uninit();
                delete scene;
            }
            //�\�񂳂�Ă��Ȃ���
            else
            {
                //��������O��
                scenePrev = scene;
            }
            //���̃|�C���^��������
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