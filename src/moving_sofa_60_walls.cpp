struct Walls {
    Box box{{500, 200}, {300, 300}};
    // TODO(#17): inner boxes should be abstracted away for easier L-,Z-,U- shaped
    Box inner1{{500, 300}, {200, 100}};
    Box inner2{{600, 300}, {100, 200}};
    static constexpr size_t abs_rotation_points_arr_cap{1000};
    static constexpr size_t rel_rotation_points_arr_cap{1000};
    size_t abs_rotation_points_arr_size{};
    size_t rel_rotation_points_arr_size{};
    Vec2f abs_rotation_points[abs_rotation_points_arr_cap];
    Vec2f rel_rotation_points[rel_rotation_points_arr_cap];
    bool is_beetween_walls(Vec2f v);
    bool contains(Vec2f v);
    void move(Vec2f v) {
        box.move(v);
        inner1.move(v);
        inner2.move(v);
    }
    void rotate(float angle, Vec2f point) {
        box.rotate(angle, point);
        inner1.rotate(angle, point);
        inner2.rotate(angle, point);

        assert(abs_rotation_points_arr_size <= abs_rotation_points_arr_cap);
        abs_rotation_points[abs_rotation_points_arr_size++] = point;

        assert(rel_rotation_points_arr_size <= rel_rotation_points_arr_cap);
        Line line{box.pos, point};
        line.rotate(-1.0f * box.rotation);
        rel_rotation_points[rel_rotation_points_arr_size++] = line.b - box.pos;
        
    }
    void rotate(float angle) {
        rotate(angle, box.pos);
    }
};

bool Walls::is_beetween_walls(Vec2f v) {
    return inner1.contains(v) || inner2.contains(v);
}
bool Walls::contains(Vec2f v) {
    return box.contains(v) && !is_beetween_walls(v);
}
