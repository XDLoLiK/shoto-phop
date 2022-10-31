#include "texture_manager.hpp"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (auto entry : m_textures)
		delete entry.second;

	m_textures.clear();
}

void TextureManager::loadTexture(const std::string& path)
{
	Texture* tex = new Texture(path);
	m_textures.insert(std::make_pair(path, tex));
}

void TextureManager::loadTextures(const std::string& path)
{
	auto textures = std::filesystem::directory_iterator(path);

	for (const auto& entry : textures)
		loadTexture(entry.path());
}

void TextureManager::loadDeafultTextures()
{
	std::string defaultPath = "skins";
	loadTextures(defaultPath);
}

const Texture* TextureManager::getTexture(const std::string& name) const
{	
	if (!m_textures.contains(name))
		return nullptr;

	return (*m_textures.find(name)).second;
}
