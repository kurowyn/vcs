#ifndef ASSET_HPP
#define ASSET_HPP

#include <raylib.h>

#include <map>
#include <string>

class Asset {
    Asset(void) = delete;

   public:
    static Font DEFAULT_FONT;
    static Texture2D ADD_BUTTON;
    static Texture2D REMOVE_BUTTON;
    static Texture2D VIEW_BUTTON;
    static Texture2D VIEW_CITY_INFO_BUTTON;
    static Texture2D CITY_FIELD;
    static Texture2D PLUS_SIGN;
    static Texture2D HOUSE;
    static Texture2D RESIZED_HOUSE;
    static Texture2D PARK;
    static Texture2D RESIZED_PARK;
    static Texture2D FACTORY;
    static Texture2D RESIZED_FACTORY;
    static std::map<std::string, Texture2D> TEXTURE_MAP;
    static float BUILDING_SQUARE_PADDING;
    static float BUILDING_SQUARE_WIDTH;
    static float BUILDING_SQUARE_HEIGHT;
    static float BUTTON_PADDING;

    static void LoadAssets(void);
};

#endif  // ASSET_HPP
