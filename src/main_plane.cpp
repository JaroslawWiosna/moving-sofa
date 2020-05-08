struct Plane {
    Sofa sofa{};
    Borders borders{};
    Camera camera{};
    void move(Vec2i a);
    void rotate();
    void render(const char*);
};

void Plane::move(Vec2i a) {
    sofa.pos += a;

    auto pxl_inside_border = [this](int x, int y) -> bool {
        if (x < (borders.vertical_lines[1].a.x) &&
            y > (borders.horizontal_lines[1].a.y) &&
            y < (borders.horizontal_lines[0].a.y)) {
            return true;
        }
        if (x < (borders.vertical_lines[1].a.x) &&
            x > (borders.vertical_lines[0].a.x) &&
            y > (borders.horizontal_lines[1].a.y)) {
            return true;
        }
        return false;
    };
    for (size_t y{}; y < sofa.width; ++y) {
        for (size_t x{}; x < sofa.length; ++x) {
            if (!pxl_inside_border(sofa.pos.x + x, sofa.pos.y + y)) {
                sofa.elem[y * sofa.length + x] = false;
            }
        }
    }
}

void Plane::rotate() {
    assert(!"Not implemented Plane::rotate()");
}

void Plane::render(const char* filename) {
    Image image{};
    image.width = camera.size.x;
    image.height = camera.size.y;
    image.pixels = new Pixel[image.width * image.height];
    const Pixel BACKGROUND{150, 255, 150, 255};
    const Pixel SOFA_OUTSIDE_COLOR{255, 170, 170, 255};
    const Pixel SOFA_INSIDE_COLOR{255, 120, 120, 255};
    const Pixel BORDER_COLOR{120, 170, 255, 255};
    fill_img_with_color(image, BACKGROUND);

    // SOFA AS A WHOLE

    size_t sofa_x1 = (sofa.pos.x - camera.pos.x) / camera.zoom;
    size_t sofa_x2 =
        (sofa.pos.x - camera.pos.x + (int)sofa.length) / camera.zoom;
    size_t sofa_y1 = (sofa.pos.y - camera.pos.y) / camera.zoom;
    size_t sofa_y2 =
        (sofa.pos.y - camera.pos.y + (int)sofa.width) / camera.zoom;

    std::cout << "sofa.pos.x == " << sofa.pos.x << "\n";
    std::cout << "sofa.pos.y == " << sofa.pos.y << "\n";

    std::cout << "sofa_x1 == " << sofa_x1 << "\n";
    std::cout << "sofa_x2 == " << sofa_x2 << "\n";
    std::cout << "sofa_y1 == " << sofa_y1 << "\n";
    std::cout << "sofa_y2 == " << sofa_y2 << "\n";

    for (size_t y = sofa_y1; y < std::min(sofa_y2, image.height); ++y) {
        for (size_t x = sofa_x1; x < std::min(sofa_x2, image.height); ++x) {
            image.pixels[y * image.width + x] = SOFA_OUTSIDE_COLOR;
        }
    }

    // BORDERS

    const int line_width = 50;
    for (const auto& line : borders.horizontal_lines) {
        size_t line_x1 = (line.a.x - camera.pos.x) / camera.zoom;
        size_t line_x2 = (line.b.x + line_width - camera.pos.x) / camera.zoom;
        size_t line_y1 = (line.a.y - camera.pos.y) / camera.zoom;
        size_t line_y2 = (line.a.y + line_width - camera.pos.y) / camera.zoom;
        for (size_t y = line_y1; y < std::min(line_y2, image.height); ++y) {
            for (size_t x = line_x1; x < std::min(line_x2, image.width); ++x) {
                image.pixels[y * image.width + x] = BORDER_COLOR;
            }
        }
    }

    for (const auto& line : borders.vertical_lines) {
        size_t line_x1 = (line.a.x - camera.pos.x) / camera.zoom;
        size_t line_x2 = (line.b.x - camera.pos.x + line_width) / camera.zoom;
        size_t line_y1 = (line.a.y - camera.pos.y) / camera.zoom;
        size_t line_y2 = (line.b.y - camera.pos.y + line_width) / camera.zoom;
        for (size_t y = line_y1; y < std::min(line_y2, image.height); ++y) {
            for (size_t x = line_x1; x < std::min(line_x2, image.height); ++x) {
                image.pixels[y * image.width + x] = BORDER_COLOR;
            }
        }
    }

    // TODO: pxl_inside_border is not fully implemented
    auto pxl_inside_border = [this](int x, int y) -> bool {
        if (x < (borders.vertical_lines[1].a.x - camera.pos.x) / camera.zoom &&
            y > (borders.horizontal_lines[1].a.y - camera.pos.y) /
                    camera.zoom &&
            y < (borders.horizontal_lines[0].a.y - camera.pos.y) /
                    camera.zoom) {
            return true;
        }
        if (x < (borders.vertical_lines[1].a.x - camera.pos.x) / camera.zoom &&
            x > (borders.vertical_lines[0].a.x - camera.pos.x) / camera.zoom &&
            y > (borders.horizontal_lines[1].a.y - camera.pos.y) /
                    camera.zoom) {
            return true;
        }
        return false;
    };

    // SOFA INSIDE

    // for (size_t y = sofa_y1; y < std::min(sofa_y2, image.height); ++y) {
    //     for (size_t x = sofa_x1; x < std::min(sofa_x2, image.height); ++x) {
    //         if (pxl_inside_border(x, y)) {
    //             image.pixels[y * image.width + x] = SOFA_INSIDE_COLOR;
    //         }
    //     }
    // }

    // SOFA BUT RENDERED BASED ON ELEM
    int i{};
    for (size_t y = sofa_y1; y < std::min(sofa_y2, image.height); ++y) {
        for (size_t x = sofa_x1; x < std::min(sofa_x2, image.height); ++x) {
            image.pixels[y * image.width + x] =
                sofa.get_cell(i, camera.zoom);
                ++i;
        }
    }


    save_image_as_png(image, filename);
    delete[](image.pixels);
}
