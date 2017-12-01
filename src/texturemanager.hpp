#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager
{
private:

    /* Array of textures used */
    std::map<std::string, sf::Texture> textures;

    public:

    /* Add a texture from a file */
    void addTexture(const std::string& name, const std::string &filename);

    /* Translate an id into a reference */
    sf::Texture& getRef(const std::string& texture);

    /* Constructor */
    TextureManager();
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
