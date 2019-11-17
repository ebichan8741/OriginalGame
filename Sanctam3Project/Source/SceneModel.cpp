#include "stdafx.h"
#include "Manager.h"
#include "Renderer.h"
#include "SceneModel.h"

//���f�����\����
typedef struct
{
    std::string pFilename;	// �t�@�C����
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

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    return S_OK;
}

void CSceneModel::Uninit(void)
{
    // ���b�V�����̉��
    if (m_ModelInfo.pMesh != NULL)
    {
        //m_ModelInfo.pMesh->Release();
        m_ModelInfo.pMesh = NULL;
    }

    // ���_�o�b�t�@���
    if (m_ModelInfo.pBuff != NULL)
    {
        m_ModelInfo.pBuff->Release();		//�}�e���A���o�b�t�@�[�̉��
        m_ModelInfo.pBuff = NULL;
    }

    // �e�N�X�`���̉��
    for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
    {
        if (m_ModelInfo.pMatTex[i] != NULL)
        {
            m_ModelInfo.pMatTex[i]->Release();
            m_ModelInfo.pMatTex[i] = NULL;
        }
    }

    // �}�e���A�����̉��
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

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_3D);

    //m_ModelInfo->pMat = (D3DXMATERIAL*)m_ModelInfo->pBuff->GetBufferPointer();

    pDevice->GetMaterial(&matDef);		//�}�e���A�����ݒ�(���݂̏��Đݒ�)

    for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
    {
        //�}�e���A���̐ݒ�
        pDevice->SetMaterial(&m_ModelInfo.pMat[i].MatD3D);
        //�e�N�X�`���̐ݒ�
        if (m_ModelInfo.pMat[i].pTextureFilename != NULL) {     // �e�N�X�`�������݂���
            pDevice->SetTexture(0, m_ModelInfo.pMatTex[i]);
        }
        else {                                                  // �e�N�X�`�������݂��Ȃ�
            pDevice->SetTexture(0, NULL);
        }
        //���b�V���̕`��
        m_ModelInfo.pMesh->DrawSubset(i);
    }

    pDevice->SetMaterial(&matDef);		//�}�e���A�����ݒ�(���݂̏��Đݒ�)
}

void CSceneModel::LoadModel(MODEL_LABEL label)
{
    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

    //X���f���̕\��(X���f�����烁�b�V�������)
    if (FAILED(D3DXLoadMeshFromX(g_aModelParam[label].pFilename.c_str(), D3DXMESH_MANAGED, pDevice, NULL, &m_ModelInfo.pBuff, NULL, &m_ModelInfo.NumMat, &m_ModelInfo.pMesh)))
    {
        //�G���[��
        MessageBox(NULL, "X���f���̓ǂݍ��݂Ɏ��s���܂���", "�I�����b�Z�[�W", MB_OK);
    }

    //�}�e���A�����擾
    m_ModelInfo.pMat = (D3DXMATERIAL*)m_ModelInfo.pBuff->GetBufferPointer();

    //�e�N�X�`�������邩�H
    if (m_ModelInfo.pMat[0].pTextureFilename != NULL)
    {
        for (int i = 0; i < (int)m_ModelInfo.NumMat; i++)
        {
            //�n�[�h�f�B�X�N����e�N�X�`����ǂݍ���
            if (FAILED(D3DXCreateTextureFromFile(pDevice, m_ModelInfo.pMat[i].pTextureFilename, &m_ModelInfo.pMatTex[i])))
            {
                //�G���[��
                MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", "�I�����b�Z�[�W", MB_OK);
            }
        }
    }
}