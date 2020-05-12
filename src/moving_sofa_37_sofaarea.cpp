struct Corridor;

struct SofaArea {
    Vec2f pos{300, 300};
    Vec2f size{300, 100};
    const int elem_per_hundred = 100;
    bool elems[100][300];
    SofaArea() {
        for (int y{}; y < 100; ++y) {
            for (int x{}; x < 300; ++x) {
                elems[y][x] = true;
            }
        }
    }
    int area() const {
        int result{};
        for (int y{}; y < 100; ++y) {
            for (int x{}; x < 300; ++x) {
                if (elems[y][x]) {
                    ++result;
                }
            }
        }
        assert(result >= 0);
        assert(result <= 30000);
        return result;
    }
    Vec2f elem_to_coord(int y, int x) {
        return {pos.x + x * 1.0f, pos.y + x * 1.0f};
    }
    Vec2f elem_to_coord(int i) {
        int y = i / 300;
        int x = i % 300;
        elem_to_coord(y, x);
    }
    bool coord_to_elem(Vec2f a) {
        int x = (int)a.x - pos.x;
        int y = (int)a.y - pos.y;
        return elems[y][x];
    }
    void set_elem_to_false_if_on_corridor_wall(Corridor& corridor);
};