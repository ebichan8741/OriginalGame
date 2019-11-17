#pragma once

#include "Sanctam3Project.h"
#include "Scene.h"

#define MAX_MATERIAL (17)

// モデル情報構造体
typedef struct {
    LPD3DXMESH pMesh;
    LPD3DXBUFFER pBuff;
    DWORD NumMat;
    LPDIRECT3DTEXTURE9 pMatTex[MAX_MATERIAL];
    D3DXMATERIAL* pMat;
}MODEL_INFO;

//モデル情報
typedef enum
{
    MODEL_PLAYER = 0,       //プレイヤーモデル
    MODEL_MAX
}MODEL_LABEL;

class CSceneModel : public CScene
{
public:
    CSceneModel(int nPriolity);
    ~CSceneModel();

    HRESULT Init(void);
    void Uninit(void);
    void Update(void);
    void Draw(void);
    void LoadModel(MODEL_LABEL label);

protected:
    D3DXVECTOR3 m_vAngle;
    MODEL_INFO m_ModelInfo;

private:

};

