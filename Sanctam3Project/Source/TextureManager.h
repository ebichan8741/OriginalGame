#pragma once

#include "Sanctam3Project.h"

// テクスチャ列挙
typedef enum
{
    TEXTURE_TITLE = 0,
    TEXTURE_MAX
}TEX_PARAM;

class CTextureManager
{
public:
    CTextureManager();
    ~CTextureManager();

    // テクスチャを読み込む
    bool Load(std::string key);

    // テクスチャを取得する
    LPDIRECT3DTEXTURE9 getResource(std::string key);
    std::string getTextureName(TEX_PARAM texParam) { return m_aTexName[texParam]; }

    bool Release(std::string key);

private:
    std::map<std::string, LPDIRECT3DTEXTURE9> m_TexMap;   // テクスチャマップ
    std::vector<std::string> m_aTexName =
    {
        "Data/Texture/title.png"
    };
};

