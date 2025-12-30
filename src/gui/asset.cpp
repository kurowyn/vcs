#include "asset.hpp"

#include <string>

Texture2D Asset::CITY_FIELD = Texture2D();
Texture2D Asset::ADD_BUTTON = Texture2D();
Texture2D Asset::REMOVE_BUTTON = Texture2D();
Texture2D Asset::VIEW_BUTTON = Texture2D();
Texture2D Asset::PLUS_SIGN = Texture2D();
Texture2D Asset::HOUSE = Texture2D();
Texture2D Asset::PARK = Texture2D();
Texture2D Asset::FACTORY = Texture2D();
Texture2D Asset::RESIZED_PARK = Texture2D();
Texture2D Asset::RESIZED_HOUSE = Texture2D();
Texture2D Asset::RESIZED_FACTORY = Texture2D();
Texture2D Asset::VIEW_CITY_INFO_BUTTON = Texture2D();
Font Asset::DEFAULT_FONT = Font();
std::map<std::string, Texture2D> Asset::TEXTURE_MAP = {};
float Asset::BUILDING_SQUARE_PADDING = 0.0f;
float Asset::BUILDING_SQUARE_WIDTH = 0.0f;
float Asset::BUILDING_SQUARE_HEIGHT = 0.0f;
float Asset::BUTTON_PADDING = 0.0f;

void Asset::LoadAssets(void) {
    Image RESIZED_HOUSE_IMAGE{LoadImage("../assets/house_assets/house_1.png")};
    Image RESIZED_PARK_IMAGE{LoadImage("../assets/park_assets/park_1.png")};
    Image RESIZED_FACTORY_IMAGE{
        LoadImage("../assets/factory_assets/factory_1.png")};
    Image CITY_FIELD_IMAGE{LoadImage("../assets/city_assets/city_texture.png")};

    ImageAlphaCrop(&RESIZED_HOUSE_IMAGE, 0.0f);
    ImageAlphaCrop(&RESIZED_PARK_IMAGE, 0.0f);
    ImageAlphaCrop(&RESIZED_FACTORY_IMAGE, 0.0f);

    ImageResizeNN(&RESIZED_HOUSE_IMAGE, 50,
                  RESIZED_HOUSE_IMAGE.height * 50 / RESIZED_HOUSE_IMAGE.width);
    ImageResizeNN(&RESIZED_PARK_IMAGE, 50,
                  RESIZED_PARK_IMAGE.height * 50 / RESIZED_PARK_IMAGE.width);
    ImageResizeNN(
        &RESIZED_FACTORY_IMAGE, 50,
        RESIZED_FACTORY_IMAGE.height * 50 / RESIZED_FACTORY_IMAGE.width);

    Asset::DEFAULT_FONT = LoadFont("../assets/fonts/CascadiaMono.ttf");
    Asset::CITY_FIELD = LoadTextureFromImage(CITY_FIELD_IMAGE);
    Asset::ADD_BUTTON =
        LoadTexture("../assets/button_assets/neon_add_button.png");
    Asset::REMOVE_BUTTON =
        LoadTexture("../assets/button_assets/neon_remove_button.png");
    Asset::VIEW_BUTTON =
        LoadTexture("../assets/button_assets/neon_view_button.png");
    Asset::VIEW_CITY_INFO_BUTTON =
        LoadTexture("../assets/button_assets/neon_view_city_info_button.png");
    Asset::PLUS_SIGN = LoadTexture("../assets/city_assets/add_sign.png");
    Asset::HOUSE = LoadTexture("../assets/house_assets/house_1.png");
    Asset::PARK = LoadTexture("../assets/park_assets/park_1.png");
    Asset::FACTORY = LoadTexture("../assets/factory_assets/factory_1.png");
    Asset::RESIZED_PARK = LoadTextureFromImage(RESIZED_PARK_IMAGE);
    Asset::RESIZED_HOUSE = LoadTextureFromImage(RESIZED_HOUSE_IMAGE);
    Asset::RESIZED_FACTORY = LoadTextureFromImage(RESIZED_FACTORY_IMAGE);

    Asset::BUILDING_SQUARE_PADDING = 3.0f;
    Asset::BUILDING_SQUARE_WIDTH = 294.0f;
    Asset::BUILDING_SQUARE_HEIGHT = 294.0f;
    Asset::BUTTON_PADDING = 10.0f;

    Asset::TEXTURE_MAP["House"] = Asset::HOUSE;
    Asset::TEXTURE_MAP["Park"] = Asset::PARK;
    Asset::TEXTURE_MAP["Factory"] = Asset::FACTORY;
    Asset::TEXTURE_MAP["NONE"] = Texture2D();

    UnloadImage(RESIZED_HOUSE_IMAGE);
    UnloadImage(RESIZED_PARK_IMAGE);
    UnloadImage(RESIZED_FACTORY_IMAGE);
    UnloadImage(CITY_FIELD_IMAGE);
}
