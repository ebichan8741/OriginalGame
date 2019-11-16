#pragma once
#include "Scene2D.h"

class CTitleUI : CScene2D
{
public:
    CTitleUI(int nPriolity);
    ~CTitleUI();

    HRESULT Init();
    void Uninit();
    void Update();
    void Draw();

    static CTitleUI* Create();
};

