
//
// outside out
// ------+
// inside|  out
// ---+  |
//  o |  | out
//    |  |
//

// 25pt of outside, 100pt of inside, 25pt of outside

struct Corridor {
    Box box{{700,300}, {150,150}};
    Box inner1{{700, 325}, {125, 100}};
    Box inner2{{825, 325}, {100, 125}};
    bool is_inside(Vec2f v);
    bool is_outside(Vec2f v);
    void rotate(int angle) {
        assert(!"TODO(#3): void Corridor::rotate(int angle)");
    }
};

bool Corridor::is_inside(Vec2f v) {
    return inner1.contains(v) || inner2.contains(v);
}
bool Corridor::is_outside(Vec2f v) {
    return box.contains(v) && !is_inside(v);
}
