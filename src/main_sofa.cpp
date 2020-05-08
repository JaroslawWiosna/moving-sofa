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
    const size_t length{4'000};
    const size_t width{1'000};
    bool* elem;
    Vec2i pos{-4'000, -1'000};
    bool& get(size_t i) {
        return elem[i];
    }
    bool& get(size_t x, size_t y) {
        assert(x < length);
        assert(y < width);
        return get(x + length * y);
    }
    // zoom == 2:
    // i = 0
    // width = 100
    // z==2, i==0 => 0,1,100,101
    // z==2, i==1 => 2,3,102,103
    // i = 49
    // z=2, i=49 => 98,99,198,199
    // z=2, i=50 => 200,201,300,301

    // z == 4 i == 0 =>
    // 0,1,2,3,100,101,102,103,200,201,202,203,300,301,302,303... z == 4 i == 1
    // => 4,5,6,7,105,106,107,108,204,205,206,207,304...

    Pixel get_cell(size_t i, int zoom) {
        static int hit{};
        ++hit;
        int trues{};
        int falses{};
        int row = i / length;
        int col = i % length;
        size_t x1{col * (size_t)zoom};
        size_t x2{x1 + zoom};
        size_t y1{row * (size_t)zoom};
        size_t y2{y1 + zoom};
        for (size_t x{x1}; x < x2; ++x) {
            for (size_t y{y1}; y < y2; ++y) {
                if (get(x + length * y)) {
                    ++trues;
                } else {
                    ++falses;
                }
            }
        }
        static int all_trues{};
        static int all_falses{};
        static int both{};
        static int all{};

        all++;
        if (trues != 0 && falses != 0) {
            both++;
            return SOFA_ELEM_BASED_MIXED_COLOR;
        } else if (trues == 0) {
            all_falses++;
            return SOFA_ELEM_BASED_OUTSIDE_COLOR;
        } else if (falses == 0) {
            all_trues++;
            return SOFA_ELEM_BASED_INSIDE_COLOR;
        }

        std::cout << "all_trues:" << all_trues << "\tall_falses:" << all_falses
                  << "\tboth:" << both << 
                 "\tall:" << all << "\n";
    }
};