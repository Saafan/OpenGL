#pragma once

#include "Renderer.h"
#include "assimp/scene.h"
class Texture
{
private:
    unsigned int m_RendererID;
    unsigned int slot = 0;
    std::string m_FilePath;
    aiTextureType type = aiTextureType_DIFFUSE;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path, aiTextureType type = aiTextureType_DIFFUSE, bool alpha = true);
    ~Texture();

    void Bind(unsigned int slot);
    void Bind();
    void Unbind();
    //
    unsigned int SetSlot(unsigned int slot);
    bool alpha = false;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

    friend class Material;
};