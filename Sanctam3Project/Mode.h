#pragma once
class CMode
{
public:
    virtual HRESULT Init(void) = 0;
    virtual void Uninit(void) = 0;
    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;
};

