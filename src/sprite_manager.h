#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>

#include <cstddef>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>

using SpriteID = size_t;

 // Manages textures and sprites in one place.
 // Reuses textures if the same file is registered again.
 // Creates new sprites and lets us access them using their SpriteID.

class SpriteManager {
public:
    sf::Texture& registerTexture(const std::string& filepath) {
        auto result = mTextures.try_emplace(filepath, filepath);
        return result.first->second;}
    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        mSprites.emplace_back(std::forward<Args>(args)...);
        return mSprites.size() - 1;}
    Sprite& getSprite(SpriteID id) {
        return mSprites.at(id);}
private:
    std::unordered_map<std::string, sf::Texture> mTextures;
    std::deque<Sprite> mSprites;};

#endif  // SPRITE_MANAGER_H
