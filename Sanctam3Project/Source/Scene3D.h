#pragma once
#include "Scene.h"

class CScene3D : public CScene
{
public:
    CScene3D(int nPriolity);
    ~CScene3D();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);

    HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

private:
    bool m_bLoadTexture;

protected:
    D3DXVECTOR3 m_vPos;
    D3DXVECTOR3 m_vSize;
    D3DXVECTOR2 m_TexPos;
    D3DXVECTOR2 m_TexSize;
    LPDIRECT3DTEXTURE9 m_pTexture;
};

