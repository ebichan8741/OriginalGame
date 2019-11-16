#include "stdafx.h"
#include "Sanctam3Project.h"
#include "Manager.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureManager.h"
#include "Mode.h"
#include "TitleMode.h"

CRenderer* CManager::m_pRenderer = 0;
CTextureManager *CManager::m_TextureManager = 0;
CMode *CManager::m_Mode = new CTitleMode;
CMode *CManager::m_nextMode = m_Mode;

CManager::CManager()
{
}


CManager::~CManager()
{
}

HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
    m_pRenderer = new CRenderer;
    if (FAILED(m_pRenderer->Init(hWnd, true)))
    {
        return E_FAIL;
    }

    m_TextureManager = new CTextureManager;


    m_Mode->Init();

    return S_OK;
}

void CManager::Uninit()
{
    //ƒŒƒ“ƒ_ƒ‰[‚Ì”jŠü
    if (m_pRenderer != NULL)
    {
        m_pRenderer->Uninit();
        m_pRenderer = NULL;
    }

    if (m_Mode != NULL)
    {
        m_Mode->Uninit();
        m_Mode = NULL;
    }
}

void CManager::Update()
{
    m_pRenderer->Update();

    m_Mode->Update();

    CScene::UpdateAll();
}

void CManager::Draw()
{
    m_pRenderer->DrawBegin();

    m_Mode->Draw();

    CScene::DrawAll();

    m_pRenderer->DrawEnd();
}

CRenderer* CManager::GetRenderer(void)
{
    return CManager::m_pRenderer;
}
CTextureManager *CManager::GetTextureManager(void)
{
    return m_TextureManager;
}

void CManager::SetMode(CMode *nextMode)
{
    m_nextMode = nextMode;
}
