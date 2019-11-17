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

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    //���_���̐ݒ�
    if (FAILED(MakeVertex(pDevice)))
    {
        return E_FAIL;
    }

    return S_OK;
}

void CScene3D::Uninit(void)
{
    //�e�N�X�`���̔j��
    if (m_pTexture != NULL && m_bLoadTexture == true)
    {
        m_pTexture->Release();
        m_pTexture = NULL;
    }

    //���_�o�b�t�@���
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

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    //�X�g���[���̐ݒ�
    pDevice->SetStreamSource(0,				//�X�g���[���ԍ�(�p�C�v�ԍ�)
        m_pVtxBuff,				            //�X�g���[���̌��ɂȂ钸�_�o�b�t�@
        0,									//�I�t�Z�b�g(�o�C�g)
        sizeof(VERTEX_3D));					//��̒��_�f�[�^�̃T�C�Y(�X�g���C�h��)

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTexture);

    //�v���~�e�B�u�̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
        0,										//�I�t�Z�b�g(���_��)
        NUM_POLYGON);							//�v���~�e�B�u�̐�
}

HRESULT CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
    VERTEX_3D* pVtx;

    //���_�o�b�t�@
    if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,		//�쐬���������_�o�b�t�@�̃T�C�Y
        D3DUSAGE_WRITEONLY,							//�g�p���@
        FVF_VERTEX_3D,								//
        D3DPOOL_MANAGED,							//�������Ǘ����@(�f�o�C�X�ɂ��C��)
        &m_pVtxBuff,
        NULL)))
    {
        return E_FAIL;
    }

    //���z�A�h���X���擾����
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(0.0f - (m_vSize.x * 0.5f), 0.0f + (m_vSize.y * 0.5f), 0.0f);
    pVtx[1].pos = D3DXVECTOR3(0.0f + (m_vSize.x * 0.5f), 0.0f + (m_vSize.y * 0.5f), 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f - (m_vSize.x * 0.5f), 0.0f - (m_vSize.y * 0.5f), 0.0f);
    pVtx[3].pos = D3DXVECTOR3(0.0f + (m_vSize.x * 0.5f), 0.0f - (m_vSize.y * 0.5f), 0.0f);

    //�@���̐ݒ�
    pVtx[0].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[1].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[2].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
    pVtx[3].normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

    //�e�N�X�`���̒��_���W
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    //���_�J���[�̐ݒ�(0�`255�̐����l)
    pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
    pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

    m_pVtxBuff->Unlock();		//���b�N����

    return 0;
}