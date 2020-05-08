#include <png.h>
#include <gif_lib.h>

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

#include "main_pixel.cpp"
#include "main_image.cpp"
#include "main_vec.cpp"
#include "main_sofa.cpp"
#include "main_line.cpp"
#include "main_corridor.cpp"
#include "main_plane.cpp"

int main(int argc, char* argv[]) {
    Plane plane{};
    plane.render("output00.png");

    exit(0);

    return 0;
}
