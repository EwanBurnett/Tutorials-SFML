#include "ResourceManager.h"
#include <assert.h>

ResourceManager* ResourceManager::sInstance = nullptr;

ResourceManager::ResourceManager()
{
	//Singleton management.
	assert(sInstance == nullptr);
	sInstance = this;
}

sf::Texture& ResourceManager::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;

	//check if texture is already loaded
	auto pairFound = texMap.find(filename);

	//if yes, return the texture
	if (pairFound != texMap.end())
		return pairFound->second;
	else //Else, load the texture and return it
	{
		//create a new element in the texture map
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

sf::SoundBuffer& ResourceManager::GetSoundBuffer(std::string const& filename)
{
	auto& sBufMap = sInstance->m_SoundBuffers;

	//check if texture is already loaded
	auto pairFound = sBufMap.find(filename);

	//if yes, return the texture
	if (pairFound != sBufMap.end())
		return pairFound->second;
	else //Else, load the texture and return it
	{
		//create a new element in the texture map
		auto& soundBuffer = sBufMap[filename];
		soundBuffer.loadFromFile(filename);
		return soundBuffer;
	}
}

sf::Font& ResourceManager::GetFont(std::string const& filename)
{
	auto& fontMap = sInstance->m_Fonts;

	//check if texture is already loaded
	auto pairFound = fontMap.find(filename);

	//if yes, return the texture
	if (pairFound != fontMap.end())
		return pairFound->second;
	else //Else, load the texture and return it
	{
		//create a new element in the texture map
		auto& font = fontMap[filename];
		font.loadFromFile(filename);
		return font;
	}
}

ResourceManager* ResourceManager::GetResourceManagerInstance()
{
	return sInstance;
}
