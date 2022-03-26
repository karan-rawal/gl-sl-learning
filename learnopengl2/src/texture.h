#ifndef APP_TEXTURE
#define APP_TEXTURE
#include <iostream>
#include "includes.h"
#include "shader.h"

class Texture
{
public:
    unsigned int textureId;
    Texture(std::string texturePath, int channels);
    void use(Shader shader, std::string uniformId, int slotId, int slotValue);
    ~Texture();
};
#endif