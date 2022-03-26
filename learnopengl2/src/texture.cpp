#include "texture.h"

Texture::Texture(std::string texturePath, int channels) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    int width, height, channelCount;
    unsigned char* imageData = stbi_load(texturePath.c_str(), &width, &height, &channelCount, 0);
    stbi_set_flip_vertically_on_load(true);

    if (!imageData) {
        std::cout << "Failed to load texture file - " << texturePath << std::endl;
        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imageData);
}

void Texture::use(Shader shader, std::string uniformId, int slotId, int slotValue) {
    glActiveTexture(slotId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    shader.setUniform1i(uniformId.c_str(), slotValue);
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &textureId);
}