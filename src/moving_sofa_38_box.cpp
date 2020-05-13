struct Area {
    Vec2f* pos = nullptr;
    Vec2f* size = nullptr;
    size_t elems_size{};
    size_t x_elem_cnt{};
    size_t y_elem_cnt{};
    bool* elems = nullptr;
    ~Area() {
        if (elems) {
            free(elems);
        }
    }
    static bool* create_elems(size_t x_elem_cnt, size_t y_elem_cnt) {
        bool* result = new bool[x_elem_cnt * y_elem_cnt];
        // TODO: memset should be faster that for-loop
        for (size_t i{0}; i < x_elem_cnt * y_elem_cnt; ++i) {
            result[i] = true;
        }
        return result;
    }
    // returns % (from 0.0f to 1.0f)
    float calculate_area() {
        size_t acc{};
        for (size_t i{}; i < elems_size; ++i) {
            if (elems[i]) {
                ++acc;
            }
        }
        return float(acc) / float(elems_size);
    }
    Vec2f elem_to_coord(size_t i) {
        const size_t x = i % x_elem_cnt;
        const size_t y = i / x_elem_cnt;

        const float x_step = size->x / x_elem_cnt;
        const float y_step = size->y / y_elem_cnt;

        const float half_x_step = x_step / 2.0f;
        const float half_y_step = y_step / 2.0f;

        // TODO In Area::elem_to_coord(size_t) rotation is ignored
        return {pos->x + half_x_step + x_step * x,
                pos->y + half_y_step + y_step * y};
    }
    Vec2f closest_point(Vec2f p) {
        const float x_step = size->x / x_elem_cnt;
        const float y_step = size->y / y_elem_cnt;

        const float half_x_step = x_step / 2.0f;
        const float half_y_step = y_step / 2.0f;

        const float THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST{10000.f};
        float min_dist_to_result_x{THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST};
        float result_x{};
        for (size_t x{}; x < x_elem_cnt; ++x) {
            float tmp_x = pos->x + half_x_step + x_step * x;
            if (abs(p.x - tmp_x) < min_dist_to_result_x) {
                min_dist_to_result_x = abs(p.x - tmp_x);
                result_x = tmp_x;
            }
        }
        float min_dist_to_result_y{THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST};
        float result_y{};
        for (size_t y{}; y < y_elem_cnt; ++y) {
            float tmp_y = pos->y + half_y_step + y_step * y;
            if (abs(p.y - tmp_y) < min_dist_to_result_y) {
                min_dist_to_result_y = abs(p.y - tmp_y);
                result_y = tmp_y;
            }
        }
        return {result_x, result_y};
    }
    size_t closest_elem_index(Vec2f p) {
        const float x_step = size->x / x_elem_cnt;
        const float y_step = size->y / y_elem_cnt;

        const float half_x_step = x_step / 2.0f;
        const float half_y_step = y_step / 2.0f;

        const float THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST{10000.f};
        float min_dist_to_result_x{THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST};
        float result_x{};
        size_t x_elem_index{};
        for (size_t x{}; x < x_elem_cnt; ++x) {
            float tmp_x = pos->x + half_x_step + x_step * x;
            if (abs(p.x - tmp_x) < min_dist_to_result_x) {
                min_dist_to_result_x = abs(p.x - tmp_x);
                result_x = tmp_x;
                x_elem_index = x;
            }
        }
        float min_dist_to_result_y{THIS_IS_REALLY_BIG_VALUE_TO_INIT_MIN_DIST};
        float result_y{};
        size_t y_elem_index{};
        for (size_t y{}; y < y_elem_cnt; ++y) {
            float tmp_y = pos->y + half_y_step + y_step * y;
            if (abs(p.y - tmp_y) < min_dist_to_result_y) {
                min_dist_to_result_y = abs(p.y - tmp_y);
                result_y = tmp_y;
                y_elem_index = y;
            }
        }
        return {x_elem_index + y_elem_index * x_elem_cnt};
    }
};

struct Box {
    Vec2f pos{};
    Vec2f size{};
    float rotation{};
    Area area{};
    void rotate(float angle, Vec2f point) {
        Line line{point, pos};
        line.rotate(angle);
        pos = line.b;
        rotation += angle;
    }
    void move(Vec2f v) {
        pos += v;
    }
    void rotate(float angle) {
        rotation += angle;
    }
    bool contains(Vec2f point) {
        Line line{pos, point};
        line.rotate(-rotation);
        Vec2f rotated_point{line.b};
        if (rotated_point.x > pos.x && rotated_point.x < pos.x + size.x &&
            rotated_point.y > pos.y && rotated_point.y < pos.y + size.y) {
            return true;
        }
        return false;
    }
    void create_elems(size_t x, size_t y) {
        if (area.elems == nullptr) {
            area.pos = &pos;
            area.size = &size;
            area.elems = Area::create_elems(x, y);
            area.x_elem_cnt = x;
            area.y_elem_cnt = y;
            area.elems_size = x * y;
        } else {
            assert(!"You explicitly wanted to allocate elems, but it was "
                    "allocated before.");
        }
    }
    float calculate_area() {
        if (area.elems == nullptr) {
            assert(!"create_elems(x,y) should be called first");
        }
        return area.calculate_area() * size.x * size.y;
    }
    Vec2f elem_to_coord(size_t i) {
        if (area.elems == nullptr) {
            assert(!"create_elems(x,y) should be called first");
        }
        return area.elem_to_coord(i);
    }
};
