#pragma once

#include "Sanctam3Project.h"

// �e�N�X�`����
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

    // �e�N�X�`����ǂݍ���
    bool Load(std::string key);

    // �e�N�X�`�����擾����
    LPDIRECT3DTEXTURE9 getResource(std::string key);
    std::string getTextureName(TEX_PARAM texParam) { return m_aTexName[texParam]; }

    bool Release(std::string key);

private:
    std::map<std::string, LPDIRECT3DTEXTURE9> m_TexMap;   // �e�N�X�`���}�b�v
    std::vector<std::string> m_aTexName =
    {
        "Data/Texture/title.png"
    };
};

