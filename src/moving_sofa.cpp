#include "moving_sofa_all_includes.cpp"

int main(int argc, char* argv[]) {
    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    plane.sofa.box.create_elems(300, 100);
    std::cout << plane.sofa.box.calculate_area() << "\n";
    char buf[256];
    auto output_filename = [&buf]() {
        static float i{};
        sprintf(buf, "output%04.f.png", i++);
    };
    auto render_frame = [&]() {
        output_filename();
        plane.render(buf);
    };
    auto cut_sofa = [&]() {
        for (size_t i{}; i < plane.sofa.box.area.elems_size; ++i) {
            if (true == plane.sofa.box.area.elems[i]) {
                auto elem_as_point = plane.sofa.box.area.elem_to_coord(i);
                if (plane.corridor.is_outside(elem_as_point)) {
                    plane.sofa.box.area.elems[i] = false;
                }
            }
        }
    };
    plane.corridor.move({-100.0f, 0});
    cut_sofa();
    for (float i{0}; i < 100; i += 2) {
        plane.corridor.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }

    // exit(0);

    render_frame();
    for (float i{0}; i < 100; i += 2) {
        plane.corridor.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";
    for (float i{0}; i < 90; i += 2) {
        plane.corridor.rotate(-2.0f, {400, 400});
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";
    for (float i{0}; i < 100; i += 2) {
        plane.corridor.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";

    return 0;
}