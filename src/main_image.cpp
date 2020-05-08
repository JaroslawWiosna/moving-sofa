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