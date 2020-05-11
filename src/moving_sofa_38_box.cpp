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