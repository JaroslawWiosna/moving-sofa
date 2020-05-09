
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
    Vec2<size_t> pos{700, 260};
    Vec2<size_t> size{150, 150};
    int rotation{};
    bool is_inside(Vec2<size_t> v);
    bool is_outside(Vec2<size_t> v);
};

bool Corridor::is_inside(Vec2<size_t> v) {
    if (v.y >= 25 && v.y <= 125 && v.x <= 125) {
        return true;
    }
    if (v.x >= 25 && v.x <= 125 && v.x >= 25) {
        return true;
    }    
    return false;
}
bool Corridor::is_outside(Vec2<size_t> v) {
    return !is_inside(v);
}
