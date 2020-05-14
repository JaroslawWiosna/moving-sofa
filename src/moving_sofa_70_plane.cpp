struct Plane {
    Sofa sofa{};
    Walls walls{};
    void rotate();
    void draw_start_and_finish(Image& image);
    void draw_sofa(Image& image);
    void draw_walls(Image& image);
    void render(const char* filename, const char* text);
};

void Plane::rotate() {
    assert(!"Not implemented Plane::rotate()");
}

const Pixel BACKGROUND{150, 255, 150, 255};
const Pixel SOFA_OUTSIDE_COLOR{255, 170, 170, 255};
const Pixel SOFA_INSIDE_COLOR{255, 120, 120, 255};
const Pixel START_COLOR{120, 170, 255, 255};
const Pixel FINISH_COLOR = START_COLOR;
const Pixel WALLS_COLOR{140, 140, 90, 255};

void Plane::draw_sofa(Image& image) {
    for (size_t y = (size_t)sofa.posy(); y < (sofa.posy() + sofa.width());
         ++y) {
        for (size_t x = (size_t)sofa.posx(); x < (sofa.posx() + sofa.length());
             ++x) {
            size_t index =
                sofa.box.area.closest_elem_index({float(x), float(y)});
            if (sofa.box.area.elems[index]) {
                image.pixels[y * 900 + x] = SOFA_INSIDE_COLOR;
            } else {
                image.pixels[y * 900 + x] = SOFA_OUTSIDE_COLOR;
            }
        }
    }
}

void Plane::draw_walls(Image& image) {
    Vec2f pA = walls.box.pos;
    Vec2f pB = walls.box.pos + Vec2f{walls.box.size.x, 0};
    Vec2f pD = walls.box.pos + Vec2f{0, walls.box.size.y};
    Vec2f pC = Vec2f{pB.x, pD.y};

    Line lineAB = {pA, pB};
    Line lineAC = {pA, pC};
    Line lineAD = {pA, pD};

    lineAB.rotate(walls.box.rotation);
    lineAC.rotate(walls.box.rotation);
    lineAD.rotate(walls.box.rotation);

    pB = lineAB.b;
    pC = lineAC.b;
    pD = lineAD.b;

    size_t x1{(size_t)pA.x};
    size_t x2{(size_t)pA.x};
    size_t y1{(size_t)pA.y};
    size_t y2{(size_t)pA.y};

    if (pB.x < x1) {
        x1 = (size_t)pB.x;
    }
    if (pC.x < x1) {
        x1 = (size_t)pC.x;
    }
    if (pD.x < x1) {
        x1 = (size_t)pD.x;
    }

    if (pB.x > x2) {
        x2 = (size_t)pB.x;
    }
    if (pC.x > x2) {
        x2 = (size_t)pC.x;
    }
    if (pD.x > x2) {
        x2 = (size_t)pD.x;
    }

    if (pB.y < y1) {
        y1 = (size_t)pB.y;
    }
    if (pC.y < y1) {
        y1 = (size_t)pC.y;
    }
    if (pD.y < y1) {
        y1 = (size_t)pD.y;
    }

    if (pB.y > y2) {
        y2 = (size_t)pB.y;
    }
    if (pC.y > y2) {
        y2 = (size_t)pC.y;
    }
    if (pD.y > y2) {
        y2 = (size_t)pD.y;
    }

    for (size_t y = y1; y < y2; ++y) {
        for (size_t x = x1; x < x2; ++x) {
            if (walls.contains({float(x), float(y)})) {
                image.pixels[y * 900 + x] = WALLS_COLOR;
            }
        }
    }
}

void Plane::draw_start_and_finish(Image& image) {
    const size_t line_width{5};
    for (size_t y = (size_t)10; y < 600 - 10; ++y) {
        for (size_t x = 250; x < 250 + line_width; ++x) {
            image.pixels[y * 900 + x] = FINISH_COLOR;
        }
    }
    for (size_t y = (size_t)10; y < 600 - 10; ++y) {
        for (size_t x = 650; x < 650 + line_width; ++x) {
            image.pixels[y * 900 + x] = START_COLOR;
        }
    }
}

void Plane::render(const char* filename, const char* text) {
    Image image{};
    image.width = 900;
    image.height = 600;
    image.pixels = new Pixel[image.width * image.height];
    fill_img_with_color(image, BACKGROUND);

    draw_start_and_finish(image);
    draw_sofa(image);
    draw_walls(image);
    freetype::put_text_area(image, text);

    save_image_as_png(image, filename);
    delete[](image.pixels);
}
