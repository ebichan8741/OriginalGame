#include "stdafx.h"
#include "Sanctam3Project.h"
#include "Manager.h"
#include "Renderer.h"

CRenderer* CManager::m_pRenderer = 0;

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
}

void CManager::Update()
{
    m_pRenderer->Update();
}

void CManager::Draw()
{
    m_pRenderer->DrawBegin();

    m_pRenderer->DrawEnd();
}

CRenderer* CManager::GetRenderer(void)
{
    return CManager::m_pRenderer;
}