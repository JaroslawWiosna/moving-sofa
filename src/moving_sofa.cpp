#include <png.h>
#include <gif_lib.h>

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>

#include "moving_sofa_10_pixel.cpp"
#include "moving_sofa_20_image.cpp"
#include "moving_sofa_30_vec.cpp"
#include "moving_sofa_35_line.cpp"

struct Box {
    Vec2f pos{};
    Vec2f size{};
    float rotation{};
    void rotate(int angle, Vec2f point) {
        Line line{point, pos};
        line.rotate(angle);
        pos = line.b;
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

#include "moving_sofa_40_sofa.cpp"
#include "moving_sofa_60_corridor.cpp"
#include "moving_sofa_70_plane.cpp"
#include "moving_sofa_99_main.cpp"
