struct Sofa {
    // Sofa() {
    //     elem = new bool[length() * width()];
    //     for (size_t i{}; i < length() * width(); ++i) {
    //         elem[i] = true;
    //     }
    // }
    // ~Sofa() {
    //     delete[] elem;
    // }
    Box box{{200, 300}, {500, 100}};
    // const size_t length{300};
    // const size_t width{100};
    bool* elem;
    // Vec2i pos{300, 300};

    float posx() const {
        return box.pos.x;
    }
    float posy() const {
        return box.pos.y;
    }
    float length() const {
        return box.size.x;
    }
    float width() const {
        return box.size.y;
    }
    bool& get(size_t i) {
        return elem[i];
    }
    bool& get(size_t x, size_t y) {
        assert(x < length());
        assert(y < width());
        return get(x + length() * y);
    }
};