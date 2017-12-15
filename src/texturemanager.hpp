#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager
{
public:
    ///Constructor
    TextureManager();

    ///Member functions
    void addTexture(const std::string& name, const std::string &filename);
    sf::Texture& getRef(const std::string& texture);

private:
    ///Private member
    std::map<std::string, sf::Texture> textures; //Array of textures used
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
