#include <raylib.h>
#include <vector>

// So, what're we doing?
// We're going to make life easier for us.

struct PositionedTexture2D {
    Texture2D texture {};
    Vector2 position {};
};

namespace Assets {
    using std::array;
    using std::vector;
    using std::string;
    using std::initializer_list;
    using std::vector;

    vector<PositionedTexture2D> LoadPositionedImages(const vector<string>& image_paths, 
            const vector<Vector2>& positions) {
        auto count {image_paths.size()};
        vector<PositionedTexture2D> positioned_textures (count);

        for (auto i {0}; i < count; ++i) {
            auto image {LoadImage(image_paths[i].c_str())};
            positioned_textures[i] = 
                PositionedTexture2D(LoadTextureFromImage(image), positions[i]);
            UnloadImage(image);
        }

        return positioned_textures;
    }
};
