struct Corridor;

struct SofaArea {
    Vec2f pos{300, 300};
    Vec2f size{300, 100};
    const int elem_per_hundred = 100;
    bool elems[100][300];
    SofaArea() {
        for (int y{}; y<100; ++y) {
            for (int x{}; x<300; ++x) {
                elems[y][x] = true;
            }        
        }
    }
    int area() const {
        int result{};
        for (int y{}; y<100; ++y) {
            for (int x{}; x<300; ++x) {
                if (elems[y][x]) {
                    ++result;
                }
            }        
        }
        assert(result>=0);
        assert(result<=30000);
        return result;
    }
    Vec2f elem_to_coord(int y, int x) {
        return {pos.x + x*1.0f, pos.y + x*1.0f};
    }
    Vec2f elem_to_coord(int i) {
        int y = i / 300;
        int x = i % 300;
        elem_to_coord(y, x);
    }
    void set_elem_to_false_if_on_corridor_wall(Corridor &corridor);
};

struct Box {
    Vec2f pos{};
    Vec2f size{};
    float rotation{};
    void rotate(float angle, Vec2f point) {
        Line line{point, pos};
        line.rotate(angle);
        pos = line.b;
        rotation += angle;
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
};
