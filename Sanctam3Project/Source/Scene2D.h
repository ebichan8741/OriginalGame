#pragma once

#include "Sanctam3Project.h"
#include "Scene.h"

class CScene2D : public CScene
{
public:
    CScene2D(int nPriolity);
    ~CScene2D();
    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();
    HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);
    void SetColor(D3DXCOLOR color);

private:
    bool m_bLoadTexture;

protected:
    D3DXVECTOR3 m_vPos;
    D3DXVECTOR3 m_vSize;
    D3DXVECTOR2 m_TexPos;
    D3DXVECTOR2 m_TexSize;
    LPDIRECT3DTEXTURE9 m_pTexture;
};

