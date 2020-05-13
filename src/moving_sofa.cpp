#include "moving_sofa_all_includes.cpp"

int main(int argc, char* argv[]) {
    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    plane.sofa.box.create_elems(300, 100);
    std::cout << plane.sofa.box.calculate_area() << "\n";
    char output_filename[256];
    char text_to_display_on_image[256];
    sprintf(text_to_display_on_image, ":-)");
    auto generate_output_filename = [&output_filename]() {
        static float i{};
        sprintf(output_filename, "output%04.f.png", i++);
    };
    auto render_frame = [&]() {
        generate_output_filename();
        sprintf(text_to_display_on_image, "Area: %1.4f", plane.sofa.box.calculate_area() / 10000.f);
        plane.render(output_filename, text_to_display_on_image);
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