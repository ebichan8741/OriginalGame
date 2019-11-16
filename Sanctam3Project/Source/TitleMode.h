#pragma once

#include "Mode.h"

class CTitleMode : public CMode
{
public:
    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
};

