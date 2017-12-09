#include "texturemanager.hpp"

// Add a texture from a file
void TextureManager::addTexture(const std::string& name, const std::string& filename)
{
    /* Load the texture */
    sf::Texture tex;
    tex.loadFromFile(filename);

    /* Add it to the list of textures */
    this->textures[name] = tex;

    return;
}

// Translate an id into a reference
sf::Texture& TextureManager::getRef(const std::string& texture)
{
    return this->textures.at(texture);
}

//sf::Sprite TextureManager::getSprite(int index){
//    sf::Sprite ret;
//    ret.setTexture(textures[index]);
//}

TextureManager::TextureManager() {
    addTexture("road0", "img/road.png");
    addTexture("roadNE", "img/roadNE.png");
    addTexture("roadNS", "img/roadNS.png");
    addTexture("roadNW", "img/roadNW.png");
    addTexture("roadES", "img/roadES.png");
    addTexture("roadEW", "img/roadEW.png");
    addTexture("roadSW", "img/roadSW.png");
    addTexture("roadNES", "img/roadNES.png");
    addTexture("roadNEW", "img/roadNEW.png");
    addTexture("roadNSW", "img/roadNSW.png");
    addTexture("roadESW", "img/roadESW.png");
    addTexture("roadNESW", "img/roadNESW.png");
    addTexture("building", "img/building0.png");
    addTexture("grass", "img/grass1.png");
}
