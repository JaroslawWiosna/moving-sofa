struct Image {
    size_t width;
    size_t height;
    Pixel* pixels;
};

void fill_img_with_color(Image image, Pixel color) {
    const size_t n = image.width * image.height;
    assert(n > 0);
    for (size_t i = 0; i < n; ++i) {
        image.pixels[i] = color;
    }
}


int save_image_as_png(Image image, const char* filename) {
    png_image pimage{};
    pimage.width = image.width;
    pimage.height = image.height;
    pimage.version = PNG_IMAGE_VERSION;
    pimage.format = PNG_FORMAT_RGBA;

    return png_image_write_to_file(&pimage, filename, 0, image.pixels, 0,
                                   nullptr);
}

#include <ft2build.h>
#include FT_FREETYPE_H

namespace freetype {

void put_ftbitmap_onto_image(Image dest, FT_Bitmap* src, Pixel color, int x,
                             int y) {
    assert(src->pixel_mode == FT_PIXEL_MODE_GRAY);
    assert(src->num_grays == 256);

    for (size_t row = 0; (row < (size_t)src->rows); ++row) {
        if (row + y < dest.height) {
            for (size_t col = 0; (col < (size_t) src->width); ++col) {
                if (col + x < dest.width) {
                    float a = src->buffer[row * src->pitch + col] / 255.0f;
                    dest.pixels[(row + y) * dest.width + col + x].r =
                        a * color.r +
                        (1.0f - a) *
                            dest.pixels[(row + y) * dest.width + col + x].r;
                    dest.pixels[(row + y) * dest.width + col + x].g =
                        a * color.g +
                        (1.0f - a) *
                            dest.pixels[(row + y) * dest.width + col + x].g;
                    dest.pixels[(row + y) * dest.width + col + x].b =
                        a * color.b +
                        (1.0f - a) *
                            dest.pixels[(row + y) * dest.width + col + x].b;
                }   
            }   
        }   
    }   
}

void put_text_onto_image(Image image, FT_Face face, const char* text,
                         Pixel color, int* pen_x, int* pen_y) {
    for (size_t i = 0; text[i] != '\0'; ++i) {
        FT_UInt glyph_index = FT_Get_Char_Index(face, text[i]);

        auto error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
        assert(!error);

        error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
        assert(!error);

        put_ftbitmap_onto_image(image, &face->glyph->bitmap, color,
                                *pen_x + face->glyph->bitmap_left,
                                *pen_y - face->glyph->bitmap_top);

        *pen_x += face->glyph->advance.x >> 6;
    }   
}

void put_text_area(Image& image, const char* text) {
    FT_Library library;
    auto error = FT_Init_FreeType(&library);
    FT_Face face;
            Pixel red{233, 27, 27, 0};

    {
    // TODO: Font path is hardcoded
    const char *face_filepath = "/usr/share/fonts/stix/STIX-Regular.otf";
    FT_New_Face(library, face_filepath, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 12);

    Pixel red{233, 27, 27, 0};

    int x = 10;
    int y = 22;
    put_text_onto_image(image, face, "Moving sofa problem", red, &x,
                        &y);

    }
    
    const char *face_filepath = "/usr/share/fonts/liberation/LiberationMono-Regular.ttf";
    FT_New_Face(library, face_filepath, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 10);

    int x = 660;
    int y = 22;
    put_text_onto_image(image, face, "github.com/JaroslawWiosna/moving-sofa", red, &x,
                        &y);

FT_New_Face(library, face_filepath, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, 33);

    x = 333;
    y = 100;
    put_text_onto_image(image, face, text, red, &x,
                        &y);

}
} // namespace freetype
