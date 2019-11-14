#pragma once

class CRenderer;
CRenderer* GetRenderer();

class CManager
{
public:
    CManager();
    ~CManager();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
    void Uninit();
    void Update();
    void Draw();

    static CRenderer* GetRenderer();

private:
    static CRenderer* m_pRenderer;
};

