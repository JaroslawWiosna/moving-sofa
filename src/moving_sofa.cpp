#include "moving_sofa_all_includes.cpp"

int main(int argc, char* argv[]) {
    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    for (float i{50}; i<100; i+=5) {
        plane.corridor.move({-1.0f * i, 0});
        plane.sofaArea.set_elem_to_false_if_on_corridor_wall(plane.corridor);
        std::cout << plane.sofaArea.area() / 10000.0f << "\n";
    }
    plane.render("output00.png");

    exit(0);

    return 0;
}