#ifndef SKIN_MANAGER_HPP
#define SKIN_MANAGER_HPP

#include <vector>
#include <filesystem>
#include <map>

#include "texture.hpp"

class SkinManager
{
public:
	SkinManager();
	~SkinManager();

	const Texture* loadSkin (const std::string& path);
	void loadSkins(const std::string& path);
	const Texture* getSkinByName(const std::string& path) const;
	void loadDeafultSkins();

private:
	std::map<std::string, const Texture*> m_textures = {};
};

#endif // SKIN_MANAGER_HPP
