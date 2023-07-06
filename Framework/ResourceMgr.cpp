#include "stdafx.h"
#include "ResourceMgr.h"

ResourceMgr::~ResourceMgr()
{
    UnLoadAll();
}

void ResourceMgr::UnLoadAll()
{
    for (auto pair : mapTexture)
    {
        delete pair.second;
    }
    mapTexture.clear();
    for (auto pair : mapFont)
    {
        delete pair.second;
    }
    mapTexture.clear();
    for (auto pair : mapSoundBuffer)
    {
        delete pair.second;
    }
    mapTexture.clear();
}


//생성자 때 한꺼번에 리소스를 만드는 게 아니라 씬을 로드할 때 마다 새로 할당
void ResourceMgr::Load(ResourceTypes t, const std::string path)
{

    switch (t)
    {
    case ResourceTypes::Texture:
    {
        auto it = mapTexture.find(path);
        if (mapTexture.end() == it)
        {
            auto texture = new sf::Texture();
            texture->loadFromFile(path);
            mapTexture.insert({ path, texture });
        }
    }
    break;
    case ResourceTypes::Font:
    {
        auto it = mapFont.find(path);
        if (mapFont.end() == it)
        {
            auto font = new sf::Font();
            font->loadFromFile(path);
            mapFont.insert({ path, font });
        }
    }
    break;
    case ResourceTypes::SoundBuffer:
    {
        auto it = mapSoundBuffer.find(path);
        if (mapSoundBuffer.end() == it)
        {
            auto sb = new sf::SoundBuffer();
            sb->loadFromFile(path);
            mapSoundBuffer.insert({ path, sb });
        }
    }
    break;
    }
 
    
    
}

void ResourceMgr::Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
{
    for (const auto& tuple : array)
    {
        Load(std::get<0>(tuple), std::get<1>(tuple));
    }
}

void ResourceMgr::Unload(ResourceTypes t, const std::string id)
{
    switch (t)
    {
    case ResourceTypes::Texture:
    {
        auto it = mapTexture.find(id);
        if (it != mapTexture.end());
        {
            delete it->second;  //first == Key, second == value
            mapTexture.erase(it);
        }
    }
    break;
    case ResourceTypes::Font:
    {
        auto it = mapFont.find(id);
        if (it != mapFont.end());
        {
            delete it->second;
            mapFont.erase(it);
        }
    }
    break;
    case ResourceTypes::SoundBuffer:
    {
        auto it = mapSoundBuffer.find(id);
        if (it != mapSoundBuffer.end());
        {
            delete it->second;
            mapSoundBuffer.erase(it);
        }
    }
    break;
    }
}

void ResourceMgr::Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
{
    for (const auto& tuple : array)
    {
        Unload(std::get<0>(tuple), std::get<1>(tuple));
    }
}

sf::Texture* ResourceMgr::GetTexture(const std::string& id)
{
    auto it = mapTexture.find(id);
    if (it != mapTexture.end())
    {
        return it->second;
    }
    return nullptr;
}

sf::Font* ResourceMgr::GetFont(const std::string& id)
{
    auto it = mapFont.find(id);
    if (it != mapFont.end())
    {
        return it->second;
    }
    return nullptr;
}

sf::SoundBuffer* ResourceMgr::GetSoundBuffer(const std::string& id)
{
    auto it = mapSoundBuffer.find(id);
    if (it != mapSoundBuffer.end())
    {
        return it->second;
    }
    return nullptr;
}
