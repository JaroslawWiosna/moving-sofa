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
#include "main_borders.cpp"

struct Camera {
    Vec2i pos{-5'000, -1'500};
    Vec2i size{1'000, 1'000};
    int zoom{10};
};

#include "main_plane.cpp"

int main(int argc, char* argv[]) {
    Plane plane{};
    plane.render("output00.png");

    std::cout << "Step 1."
              << "\n";
    std::cout << "\tMove right"
              << "\n";

    plane.move({200, 0});
    plane.move({1400, 1100});
    plane.move({0, -200});

    plane.render("output01.png");

    exit(0);

    std::cout << "Step 2."
              << "\n";
    std::cout << "\tRotate (in the future: rotate and move in the same time"
              << "\n";

    plane.rotate();
    plane.render("output02.png");

    std::cout << "Step 3."
              << "\n";
    std::cout << "\tMove down"
              << "\n";

    plane.move({0, 800});
    plane.render("output03.png");

    return 0;
}
