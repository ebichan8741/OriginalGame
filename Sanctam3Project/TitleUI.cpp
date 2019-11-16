#include "stdafx.h"
#include "Manager.h"
#include "Scene2D.h"
#include "TextureManager.h"
#include "TitleUI.h"


CTitleUI::CTitleUI(int nPriolity) : CScene2D(nPriolity)
{

}


CTitleUI::~CTitleUI()
{
}

HRESULT CTitleUI::Init()
{
    m_vPos = D3DXVECTOR3(0.0f + SCREEN_WIDTH * 0.5f, 0.0f + SCREEN_HEIGHT * 0.5f, 0.0f);
    m_vSize = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

    CScene2D::Init();
    return S_OK;
}

void CTitleUI::Uninit()
{
    CScene2D::Uninit();
}

void CTitleUI::Update()
{
    CScene2D::Update();
}

void CTitleUI::Draw()
{
    CScene2D::Draw();
}

CTitleUI* CTitleUI::Create()
{
    CTitleUI* titleUI;
    titleUI = new CTitleUI(PRIOLITY_0);
    titleUI->Init();

    titleUI->m_pTexture = CManager::GetTextureManager()->getResource(CManager::GetTextureManager()->getTextureName(TEXTURE_TITLE));

    return titleUI;
}