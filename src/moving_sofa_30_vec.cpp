template <typename T> struct Vec2 {
    T x;
    T y;
    Vec2<T>& operator+=(const Vec2<T>& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    Vec2<T>& operator-=(const Vec2<T>& rhs) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }
    friend Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs) {
        lhs -= rhs;
        return lhs;
    }
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;