#include "skin_manager.hpp"

SkinManager::SkinManager()
{

}

SkinManager* SkinManager::getSkinManager()
{
	static SkinManager instance;
	return &instance;
}

SkinManager::~SkinManager()
{
	for (auto entry : m_textures)
		delete entry.second;

	m_textures.clear();
}

const Texture* SkinManager::loadSkin(const std::string& path)
{
	const Texture* tex = new Texture(path);
	m_textures.insert(std::make_pair(path, tex));

	return tex;
}

void SkinManager::loadSkins(const std::string& path)
{
	auto textures = std::filesystem::directory_iterator(path);

	for (const auto& entry : textures)
		loadSkin(entry.path());
}

void SkinManager::loadDeafultSkins()
{
	std::string defaultPath = "skins";
	loadSkins(defaultPath);
}

const Texture* SkinManager::getSkinByName(const std::string& name) const
{	
	if (!m_textures.contains(name))
		return nullptr;

	return (*m_textures.find(name)).second;
}
