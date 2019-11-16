#include "stdafx.h"
#include "Manager.h"
#include "Scene.h"
#include "TextureManager.h"
#include "TitleMode.h"
#include "TitleUI.h"

HRESULT CTitleMode::Init()
{
    CTitleUI::Create();

    return S_OK;
}

void CTitleMode::Uninit()
{
    CScene::ReleaseAll();
}

void CTitleMode::Update()
{

}

void CTitleMode::Draw()
{

}