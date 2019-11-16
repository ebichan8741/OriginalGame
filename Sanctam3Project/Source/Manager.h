#pragma once

class CRenderer;
CRenderer* GetRenderer();
class CTextureManager;
CTextureManager *GetTextureManager(void);
class CMode;
void SetMode(CMode *nextMode);

typedef enum {
    MODE_TITLE,
    MODE_GAME,
    MODE_RESULT,
    MODE_MAX
}MODE_TYPE;

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
    static CTextureManager *GetTextureManager(void);
    static MODE_TYPE GetMode(void);
    static void SetMode(CMode *nextMode);


    static MODE_TYPE mode;

private:
    static CRenderer* m_pRenderer;
    static CTextureManager *m_TextureManager;
    static CMode *m_Mode;
    static CMode *m_nextMode;
};

