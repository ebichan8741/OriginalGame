#pragma once
class CRenderer
{
public:
    CRenderer();
    ~CRenderer();

    HRESULT Init(HWND hWnd, bool bWindow);
    void Uninit();
    void Update();
    void DrawBegin();
    void DrawEnd();
    LPDIRECT3DDEVICE9 GetDevice();

    LPDIRECT3D9 m_pD3D;
    LPDIRECT3DDEVICE9 m_pD3DDevice;

};

