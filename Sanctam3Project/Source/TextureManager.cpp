#include "stdafx.h"

#include "Manager.h"
#include "Renderer.h"
#include "TextureManager.h"

using namespace std;
typedef map<string, LPDIRECT3DTEXTURE9> TexTable;

CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Load(string key)
{
    LPDIRECT3DDEVICE9 pDevice;

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`��������
    TexTable::const_iterator it = m_TexMap.find(key);
    if (it == m_TexMap.end()) {            // ������Ȃ������ꍇ
        HRESULT hr;
        LPDIRECT3DTEXTURE9 texture;
        hr = D3DXCreateTextureFromFile(pDevice,
            key.c_str(),
            &texture);
        if (FAILED(hr)) {
            MessageBox(NULL, key.c_str(), "LOAD ERROR!", MB_OK);
            return false;
        }

        // �}�b�v�֑}������
        m_TexMap.insert(TexTable::value_type(key, texture));

    }

    return true;
}

LPDIRECT3DTEXTURE9 CTextureManager::getResource(string key)
{
    LPDIRECT3DDEVICE9 pDevice;

    //�f�o�C�X�̎擾
    pDevice = CManager::GetRenderer()->GetDevice();

    // �e�N�X�`��������
    TexTable::const_iterator it = m_TexMap.find(key);
    if (it != m_TexMap.end()) {       // ���������ꍇ
                                      // �e�N�X�`����Ԃ�
        return it->second;
    }
    else {                            // ������Ȃ������ꍇ
                                      // ����������������L�[�Ƃ���
                                      // �V�����}�b�v�Ƀe�N�X�`����ǉ�����
        HRESULT hr;
        LPDIRECT3DTEXTURE9 texture;
        hr = D3DXCreateTextureFromFile(pDevice,
            key.c_str(),
            &texture);
        if (FAILED(hr)) {
            // �����ł��Ȃ������ꍇ��NULL�|�C���^��Ԃ�
            MessageBox(NULL, key.c_str(), "LOAD ERROR!", MB_OK);
            return NULL;
        }

        // �}�b�v�֑}������
        m_TexMap.insert(TexTable::value_type(key, texture));

        return texture;
    }
}
