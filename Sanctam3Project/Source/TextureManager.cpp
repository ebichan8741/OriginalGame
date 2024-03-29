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

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    // テクスチャを検索
    TexTable::const_iterator it = m_TexMap.find(key);
    if (it == m_TexMap.end()) {            // 見つからなかった場合
        HRESULT hr;
        LPDIRECT3DTEXTURE9 texture;
        hr = D3DXCreateTextureFromFile(pDevice,
            key.c_str(),
            &texture);
        if (FAILED(hr)) {
            MessageBox(NULL, key.c_str(), "LOAD ERROR!", MB_OK);
            return false;
        }

        // マップへ挿入する
        m_TexMap.insert(TexTable::value_type(key, texture));

    }

    return true;
}

LPDIRECT3DTEXTURE9 CTextureManager::getResource(string key)
{
    LPDIRECT3DDEVICE9 pDevice;

    //デバイスの取得
    pDevice = CManager::GetRenderer()->GetDevice();

    // テクスチャを検索
    TexTable::const_iterator it = m_TexMap.find(key);
    if (it != m_TexMap.end()) {       // 見つかった場合
                                      // テクスチャを返す
        return it->second;
    }
    else {                            // 見つからなかった場合
                                      // 検索した文字列をキーとして
                                      // 新しくマップにテクスチャを追加する
        HRESULT hr;
        LPDIRECT3DTEXTURE9 texture;
        hr = D3DXCreateTextureFromFile(pDevice,
            key.c_str(),
            &texture);
        if (FAILED(hr)) {
            // 生成できなかった場合はNULLポインタを返す
            MessageBox(NULL, key.c_str(), "LOAD ERROR!", MB_OK);
            return NULL;
        }

        // マップへ挿入する
        m_TexMap.insert(TexTable::value_type(key, texture));

        return texture;
    }
}
