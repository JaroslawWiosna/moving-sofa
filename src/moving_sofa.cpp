#include <png.h>
#include <gif_lib.h>

#include <array>
#include <cassert>
#include <iostream>

#include "moving_sofa_10_pixel.cpp"
#include "moving_sofa_20_image.cpp"
#include "moving_sofa_30_vec.cpp"


#include <cmath>
struct Box {
    Vec2i pos{};
    Vec2i size{};
    int rotation{};
    void rotate(int angle, Vec2i point) {
        int len = sqrt(pow(pos.x - point.x,2) + pow(pos.y - point.y,2));

        // 360 == 2pi
        // x  == y

        // y = 2pi / 360 * x

        pos.x += len*cos(angle * 180 / 3.1415);
        pos.y += len*sin(angle * 180 / 3.1415);
        rotation += angle;
    }
    bool contains(Vec2i point) {
        Vec2i rotated_point {point};
        int len = sqrt(pow(pos.x - point.x,2) + pow(pos.y - point.y,2));
        rotated_point.x -= len*cos(-rotation * 180 / 3.1415);
        rotated_point.y -= len*sin(-rotation * 180 / 3.1415);

        if (rotated_point.x > pos.x && rotated_point.x < pos.x + size.x && 
        rotated_point.y > pos.y && rotated_point.y < pos.y + size.y) {
            return true;
        }

        return false;
    }
};

#include "moving_sofa_40_sofa.cpp"
#include "moving_sofa_50_line.cpp"
#include "moving_sofa_60_corridor.cpp"
#include "moving_sofa_70_plane.cpp"
#include "moving_sofa_99_main.cpp"
