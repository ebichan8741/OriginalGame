#pragma once
class CManager
{
public:
    CManager();
    ~CManager();
    HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
    void Uninit();
    void Update();
    void Draw();
};

