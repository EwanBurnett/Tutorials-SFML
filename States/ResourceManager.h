#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <map>

class ResourceManager
{ 
public:
	ResourceManager();

	static sf::Texture& GetTexture(std::string const& filename); //Returns a reference to the texture, at the specified location. Supported types are {.png}.
	static sf::SoundBuffer& GetSoundBuffer(std::string const& filename); //Returns a reference to a sound, at the specified location. Supported types are {.wav, .ogg}
	static sf::Font& GetFont(std::string const& filename); //Returns a reference to a font, at the specified location. Supported types are {.ttf, .rtf}

	static ResourceManager* GetResourceManagerInstance();

private:
	//Maps containing all loadable resources.
	std::map<std::string, sf::Texture> m_Textures; 
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;
	std::map<std::string, sf::Font> m_Fonts;

	//ResourceManager is a singleton. As such, only one instance can exist at a time.
	//Therefore, sInstance contains a static pointer to the single manager instance.
	static ResourceManager* sInstance;
};

