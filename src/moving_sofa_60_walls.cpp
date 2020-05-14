struct Walls {
    Box box{{600, 200}, {300, 300}};
    // TODO(#17): inner boxes should be abstracted away for easier L-,Z-,U- shaped
    Box inner1{{600, 300}, {200, 100}};
    Box inner2{{700, 300}, {100, 200}};
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