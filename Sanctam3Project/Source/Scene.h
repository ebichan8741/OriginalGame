#pragma once
#include "Sanctam3Project.h"

#define MAX_SCENE (256)

typedef enum
{
    PRIOLITY_0 = 0,
    PRIOLITY_1,
    PRIOLITY_2,
    PRIOLITY_3,
    PRIOLITY_4,
    PRIOLITY_MAX
}PRIOLITY;


class CScene
{
public:
    virtual HRESULT Init(void) = 0;
    virtual void Uninit(void) = 0;
    virtual void Update(void) = 0;
    virtual void Draw(void) = 0;

    CScene(int nPriolity);
    ~CScene();
    static void UpdateAll(void);
    static void DrawAll(void);
    static void ReleaseAll(void);
    void Release(void);

protected:
    float m_LengthSq;
    LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;

    static CScene *m_Top[PRIOLITY_MAX];
    CScene *m_Next;
    bool m_Delete;
};

