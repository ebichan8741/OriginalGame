#include "stdafx.h"
#include "Sanctam3Project.h"
#include "Manager.h"
#include "Renderer.h"
#include "Scene3D.h"

CScene3D::CScene3D(int nPriolity) :CScene(nPriolity)
{
    m_bLoadTexture = false;
}


CScene3D::~CScene3D()
{
    m_bLoadTexture = false;
}

HRESULT CScene3D::Init(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //頂点情報の設定
    if (FAILED(MakeVertex(pDevice)))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CScene3D::Uninit(void)
{
    //テクスチャの破棄
    if (m_pTexture != NULL && m_bLoadTexture == true)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }

    //頂点バッファ解放
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }
}

void CScene3D::Update(void)
{

}

void CScene3D::Draw(void)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    //ストリームの設定
    pDevice->SetStreamSource(0,				//ストリーム番号(パイプ番号)
        m_pVtxBuff,				            //ストリームの元になる頂点バッファ
        0,									//オフセット(バイト)
        sizeof(VERTEX_3D));					//一個の頂点データのサイズ(ストライド量)

    //頂点フォーマットの設定
    pDevice->SetFVF(FVF_VERTEX_3D);

    //テクスチャの設定
    pDevice->SetTexture(0, m_pTexture);

    //プリミティブの描画
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
        0,										//オフセット(頂点数)
        NUM_POLYGON);							//プリミティブの数
}

HRESULT CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
    VERTEX_3D* pVtx;

    //頂点バッファ
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,		//作成したい頂点バッファのサイズ
        D3DUSAGE_WRITEONLY,							//使用方法
        FVF_VERTEX_3D,								//
        D3DPOOL_MANAGED,							//メモリ管理方法(デバイスにお任せ)
        &m_pVtxBuff,
        NULL)))
    {
        return E_FAIL;
    }

    //仮想アドレスを取得する
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //頂点座標の設定
    pVtx[0].pos = D3DXVECTOR3(0.0f - (m_vSize.x * 0.5f), 0.0f + (m_vSize.y * 0.5f), 0.0f);
    pVtx[1].pos = D3DXVECTOR3(0.0f + (m_vSize.x * 0.5f), 0.0f + (m_vSize.y * 0.5f), 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f - (m_vSize.x * 0.5f), 0.0f - (m_vSize.y * 0.5f), 0.0f);
    pVtx[3].pos = D3DXVECTOR3(0.0f + (m_vSize.x * 0.5f), 0.0f - (m_vSize.y * 0.5f), 0.0f);

    //法線の設定
    pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //テクスチャの頂点座標
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //頂点カラーの設定(0～255の整数値)
    pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_pVtxBuff->Unlock();		//ロック解除

    return 0;
}