#include "stdafx.h"
#include "Manager.h"
#include "Renderer.h"
#include "SceneModel.h"

//モデル情報構造体
typedef struct
{
    std::string pFilename;	// ファイル名
} MODELPARAM;

MODELPARAM g_aModelParam[MODEL_MAX] = {
    "Data/Model/AK_47.x",
};

CSceneModel::CSceneModel(int nPriolity) :CScene(nPriolity)
{
}

CSceneModel::~CSceneModel()
{
}

HRESULT CSceneModel::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    return S_OK;
}

void CSceneModel::Uninit(void)
{
    // メッシュ情報の解放
    if (m_ModelInfo.pMesh != NULL)
    {
        //m_ModelInfo.pMesh->Release();
        m_ModelInfo.pMesh = NULL;
    }

    // 頂点バッファ解放
    if (m_ModelInfo.pBuff != NULL)
    {
        m_ModelInfo.pBuff->Release();		//マテリアルバッファーの解放
        m_ModelInfo.pBuff = NULL;
    }

    // テクスチャの解放
    for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
    {
        if (m_ModelInfo.pMatTex[i] != NULL)
        {
            m_ModelInfo.pMatTex[i]->Release();
            m_ModelInfo.pMatTex[i] = NULL;
        }
    }

    // マテリアル情報の解放
    if (m_ModelInfo.pMat != NULL)
    {
        m_ModelInfo.pMat = NULL;
    }
}

void CSceneModel::Update(void)
{

}

void CSceneModel::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;
    D3DMATERIAL9 matDef;
    D3DXMATRIX mtxWorld;
    D3DXMATRIX mtxTrans;
    D3DXMATRIX mtxRotY;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_3D);

    //m_ModelInfo->pMat = (D3DXMATERIAL*)m_ModelInfo->pBuff->GetBufferPointer();

    pDevice->GetMaterial(&matDef);		//マテリアル情報設定(現在の情報再設定)

    for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
    {
        //マテリアルの設定
        pDevice->SetMaterial(&m_ModelInfo.pMat[i].MatD3D);
        //テクスチャの設定
        if (m_ModelInfo.pMat[i].pTextureFilename != NULL) {     // テクスチャが存在する
            pDevice->SetTexture(0, m_ModelInfo.pMatTex[i]);
        }
        else {                                                  // テクスチャが存在しない
            pDevice->SetTexture(0, NULL);
        }
        //メッシュの描画
        m_ModelInfo.pMesh->DrawSubset(i);
    }

    pDevice->SetMaterial(&matDef);		//マテリアル情報設定(現在の情報再設定)
}

void CSceneModel::LoadModel(MODEL_LABEL label)
{
    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //Xモデルの表示(Xモデルからメッシュを作る)
    if (FAILED(D3DXLoadMeshFromX(g_aModelParam[label].pFilename.c_str(), D3DXMESH_MANAGED, pDevice, NULL, &m_ModelInfo.pBuff, NULL, &m_ModelInfo.NumMat, &m_ModelInfo.pMesh)))
    {
        //エラー時
        MessageBox(NULL, "Xモデルの読み込みに失敗しました", "終了メッセージ", MB_OK);
    }

    //マテリアル情報取得
    m_ModelInfo.pMat = (D3DXMATERIAL*)m_ModelInfo.pBuff->GetBufferPointer();

    //テクスチャがあるか？
    if (m_ModelInfo.pMat[0].pTextureFilename != NULL)
    {
        for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
        {
            //ハードディスクからテクスチャを読み込む
            if (FAILED(D3DXCreateTextureFromFile(pDevice, m_ModelInfo.pMat[i].pTextureFilename, &m_ModelInfo.pMatTex[i])))
            {
                //エラー時
                MessageBox(NULL, "テクスチャの読み込みに失敗しました", "終了メッセージ", MB_OK);
            }
        }
    }
}