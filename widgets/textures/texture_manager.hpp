#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <vector>
#include <filesystem>
#include <string>
#include <map>

#include "texture.hpp"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void loadTexture (const std::string& path);
	void loadTextures(const std::string& path);
	const Texture* getTexture(const std::string& name) const;
	void loadDeafultTextures();

private:
	std::map<std::string, Texture*> m_textures = {};
};

#endif // TEXTURE_MANAGER_HPP
