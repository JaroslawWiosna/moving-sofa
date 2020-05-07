#include <png.h>
#include <gif_lib.h>

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

const size_t IMAGE_WIDTH = 400;
const size_t IMAGE_HEIGHT = 400;

struct Pixel {
    uint8_t r, g,b,a;
};

struct Image {
    size_t width;
    size_t height;
    Pixel *pixels;
};

void fill_img_with_color(Image image, Pixel color) {
    const size_t n = image.width * image.height;
    assert(n>0);
    for (size_t i = 0; i < n; ++i) {
        image.pixels[i] = color;
    }
}


int save_image_as_png(Image image, const char* filename) {
    png_image pimage {};
    pimage.width = image.width;
    pimage.height = image.height;
    pimage.version = PNG_IMAGE_VERSION;
    pimage.format = PNG_FORMAT_RGBA;

    return png_image_write_to_file(&pimage, filename, 0, image.pixels, 0,
                                   nullptr);
}

template <typename T> struct Vec2 {
    T x;
    T y;
    Vec2<T>& operator+=(const Vec2<T>& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    friend Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs) {
        lhs += rhs;
        return lhs;
    }
};

using Vec2i = Vec2<int>;

struct Sofa {
    size_t length{350};
    size_t width{100};
    Vec2i pos{-400, -100};
};

struct Line {
    Vec2i a = {};
    Vec2i b = {};
};

struct Borders {
    std::array<Line, 2> horizontal_lines = {
        Line{{-300, 0}, {0, 0}},
        Line{{-300, -100}, {100, -100}},
    };
    std::array<Line, 2> vertical_lines = {
        Line{{0, 0}, {0, 300}},
        Line{{100, -100}, {100, 300}},
    };
};

struct Camera {
    Vec2i pos{-500,-150};
    Vec2i size{1000, 1000};
    int zoom {4};
};

struct Plane {
    Sofa sofa{};
    Borders borders{};
    Camera camera{};
    void move(Vec2i a);
    void rotate();
    void render_old(const char *);
    void render(const char *);
};

void Plane::move(Vec2i a) {
    sofa.pos += a;
}

void Plane::rotate() {
    assert(!"Not implemented Plane::rotate()");
}

void Plane::render(const char * filename) {
    Image image{};
    image.width = camera.size.x;
    image.height = camera.size.y;
    image.pixels = new Pixel[image.width * image.height];
    const Pixel BACKGROUND {150, 255, 150, 255};
    const Pixel SOFA_OUTSIDE_COLOR {255, 170, 170, 255};
    const Pixel SOFA_INSIDE_COLOR {255, 120, 120, 255};
    const Pixel BORDER_COLOR {120, 170, 255, 255};
    fill_img_with_color(image, BACKGROUND);

    // SOFA AS A WHOLE

    size_t sofa_x1 = (sofa.pos.x - camera.pos.x) / camera.zoom;
    size_t sofa_x2 = (sofa.pos.x - camera.pos.x + (int)sofa.length) / camera.zoom;
    size_t sofa_y1 = (sofa.pos.y - camera.pos.y) / camera.zoom;
    size_t sofa_y2 = (sofa.pos.y - camera.pos.y + (int)sofa.width) / camera.zoom;

    // std::cout << "sofa.pos.x == " << sofa.pos.x << "\n";
    // std::cout << "sofa.pos.y == " << sofa.pos.y << "\n";

    // std::cout << "sofa_x1 == " << sofa_x1 << "\n";
    // std::cout << "sofa_x2 == " << sofa_x2 << "\n";
    // std::cout << "sofa_y1 == " << sofa_y1 << "\n";
    // std::cout << "sofa_y2 == " << sofa_y2 << "\n";

    for (size_t y = sofa_y1; y < std::min(sofa_y2,image.height); ++y) {
        for (size_t x = sofa_x1; x < std::min(sofa_x2,image.height); ++x) {
            image.pixels[y * image.width + x] = SOFA_OUTSIDE_COLOR;
        }
    }

    // BORDERS

    const int line_width = 5;
    for (const auto& line : borders.horizontal_lines) {
        size_t line_x1 = (line.a.x - camera.pos.x) / camera.zoom;
        size_t line_x2 = (line.b.x + line_width - camera.pos.x) / camera.zoom;
        size_t line_y1 = (line.a.y - camera.pos.y) / camera.zoom;
        size_t line_y2 = (line.a.y + line_width - camera.pos.y) / camera.zoom;
        for (size_t y = line_y1; y < std::min(line_y2,image.height); ++y) {
            for (size_t x = line_x1; x < std::min(line_x2,image.width); ++x) {
                image.pixels[y * image.width + x] = BORDER_COLOR;
            }
        }        
    }

    for (const auto& line : borders.vertical_lines) {
        size_t line_x1 = (line.a.x - camera.pos.x) / camera.zoom;
        size_t line_x2 = (line.b.x - camera.pos.x + line_width ) / camera.zoom;
        size_t line_y1 = (line.a.y - camera.pos.y) / camera.zoom;
        size_t line_y2 = (line.b.y - camera.pos.y + line_width ) / camera.zoom;
        for (size_t y = line_y1; y < std::min(line_y2,image.height); ++y) {
            for (size_t x = line_x1; x < std::min(line_x2,image.height); ++x) {
                image.pixels[y * image.width + x] = BORDER_COLOR;
            }
        }        
    }

    // TODO: pxl_inside_border is not fully implemented
    auto pxl_inside_border = [this](int x, int y) -> bool {        
        if (x < (borders.vertical_lines[1].a.x - camera.pos.x) / camera.zoom) {
            return true;
        }
        return false;
    };

    // SOFA INSIDE

    for (size_t y = sofa_y1; y < std::min(sofa_y2,image.height); ++y) {
        for (size_t x = sofa_x1; x < std::min(sofa_x2,image.height); ++x) {
            if (pxl_inside_border(x, y)) {
            image.pixels[y * image.width + x] = SOFA_INSIDE_COLOR;
        }}
    }


    save_image_as_png(image, filename);
    delete[](image.pixels);
}


int main(int argc, char* argv[]) {
    Plane plane{};
    plane.render("output00.png");

    std::cout << "Step 1."
              << "\n";
    std::cout << "\tMove right"
              << "\n";

    plane.move({200, 0});
    plane.render("output01.png");

    exit(0);

    std::cout << "Step 2."
              << "\n";
    std::cout << "\tRotate (in the future: rotate and move in the same time"
              << "\n";

    plane.rotate();
    plane.render("output02.png");

    std::cout << "Step 3."
              << "\n";
    std::cout << "\tMove down"
              << "\n";

    plane.move({0, 80});
    plane.render("output03.png");

    return 0;
}
