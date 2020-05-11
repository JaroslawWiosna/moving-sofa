#include <cmath>

template <typename T> T rad2deg(T angle) {
    return angle * 180.0 / M_PI;
}

template <typename T> T deg2rad(T angle) {
    return angle * M_PI / 180.0;
}

struct Line;
Line make_line_from_castesian(Vec2f a, Vec2f b);
Line make_line_from_polar(Vec2f a, float len, float angle);
struct Line {
    Vec2f a; // begin
    Vec2f b; // end
    float len() const {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }
    float angle() const {
        const float dy = b.y - a.y;
        const float dx = b.x - a.x;
        // TODO(#5): in c++20 put [[unlikely]] before if
        if (dy == 0 && dx == 0) {
            return {};
        }
        if (dx == 0) {
            return dy > 0.0f ? 90.0f : 270.0f;
        }
        if (dy == 0) {
            return dx > 0.0f ? 0.0f : 180.0f;
        }
        return rad2deg(atan2(dy, dx));
    }
    void rotate(float angle) {
        Line rotated = make_line_from_polar(a, len(), this->angle() + angle);
        b = rotated.b;
    }
};

Line make_line_from_castesian(Vec2f a, Vec2f b) {
    return {a, b};
}

Line make_line_from_polar(Vec2f a, float len, float angle) {
    Vec2f b{a.x + (float)len * (float)cos(deg2rad(angle)),
            a.y + (float)len * (float)sin(deg2rad(angle))};

    return {a, b};
}
