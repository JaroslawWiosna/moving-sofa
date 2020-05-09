struct Sofa {
    Sofa() {
        elem = new bool[length * width];
        for (size_t i{}; i < length * width; ++i) {
            elem[i] = true;
        }
    }
    ~Sofa() {
        delete[] elem;
    }
    const size_t length{300};
    const size_t width{100};
    bool* elem;
    Vec2i pos{300, 300};
    bool& get(size_t i) {
        return elem[i];
    }
    bool& get(size_t x, size_t y) {
        assert(x < length);
        assert(y < width);
        return get(x + length * y);
    }
};