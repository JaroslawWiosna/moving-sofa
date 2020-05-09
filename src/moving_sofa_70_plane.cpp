struct Plane {
    Sofa sofa{};
    Corridor corridor{};
    void rotate();
    void draw_start_and_finish(Image& image);
    void draw_sofa(Image& image);
    void draw_corridor(Image& image);
    void render(const char*);
};

void Plane::rotate() {
    assert(!"Not implemented Plane::rotate()");
}

const Pixel BACKGROUND{150, 255, 150, 255};
const Pixel SOFA_OUTSIDE_COLOR{255, 170, 170, 255};
const Pixel SOFA_INSIDE_COLOR{255, 120, 120, 255};
const Pixel START_COLOR{120, 170, 255, 255};
const Pixel FINISH_COLOR = START_COLOR;
const Pixel CORRIDOR_COLOR{140, 140, 90, 255};

void Plane::draw_sofa(Image& image) {
    for (size_t y = (size_t)sofa.pos.y; y < (sofa.pos.y + sofa.width); ++y) {
        for (size_t x = (size_t)sofa.pos.x; x < (sofa.pos.x + sofa.length);
             ++x) {
            image.pixels[y * 1000 + x] = SOFA_INSIDE_COLOR;
        }
    }
}

void Plane::draw_corridor(Image& image) {
    for (size_t y = (size_t)corridor.pos.y; y < (corridor.pos.y + corridor.size.y); ++y) {
        for (size_t x = (size_t)corridor.pos.x; x < (corridor.pos.x + corridor.size.x);
             ++x) {
            image.pixels[y * 1000 + x] = CORRIDOR_COLOR;
        }
    }}

void Plane::draw_start_and_finish(Image& image) {
    const size_t line_width{5};
    for (size_t y = (size_t)10; y < 800; ++y) {
        for (size_t x = 250; x < 250 + line_width;
             ++x) {
            image.pixels[y * 1000 + x] = FINISH_COLOR;
        }
    }
   for (size_t y = (size_t)10; y < 800; ++y) {
        for (size_t x = 650; x < 650 + line_width;
             ++x) {
            image.pixels[y * 1000 + x] = START_COLOR;
        }
    }

}

void Plane::render(const char* filename) {
    Image image{};
    image.width = 1000;
    image.height = 1000;
    image.pixels = new Pixel[image.width * image.height];
    fill_img_with_color(image, BACKGROUND);

    draw_start_and_finish(image);
    draw_corridor(image);
    draw_sofa(image);

    save_image_as_png(image, filename);
    delete[](image.pixels);
}
