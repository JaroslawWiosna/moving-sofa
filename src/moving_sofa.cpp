#include "moving_sofa_all_includes.cpp"

int main(int argc, char* argv[]) {
    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    plane.sofa.box.create_elems(500, 100);
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
        sprintf(text_to_display_on_image, "Area: %1.4f",
                plane.sofa.box.calculate_area() / 10000.f);
        plane.render(output_filename, text_to_display_on_image);
    };
    auto cut_sofa = [&]() {
        for (size_t i{}; i < plane.sofa.box.area.elems_size; ++i) {
            if (true == plane.sofa.box.area.elems[i]) {
                auto elem_as_point = plane.sofa.box.area.elem_to_coord(i);
                if (plane.walls.contains(elem_as_point)) {
                    plane.sofa.box.area.elems[i] = false;
                }
            }
        }
    };
    plane.walls.move({-10.0f, 0});
    cut_sofa();
    for (float i{0}; i < 50; i += 2) {
        plane.walls.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }

    // exit(0);

    render_frame();
    for (float i{0}; i < 100; i += 2) {
        plane.walls.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";
    // 0deg -> 50,200   == (100 - 50 * cos(ang), 200 + 50 * sin(ang) )
    // 90deg -> 100,250 == (100 - 50 * cos(ang), 200 + 50 * sin(ang) )
    const float radius{95.0f};
    for (float i{0}; i < 90; i += 2) {
        Vec2f rotation_point{100.0f - radius * float(cos(deg2rad(i))),
                             200.0f + radius * float(sin(deg2rad(i)))};
        Line line{plane.walls.box.pos,
                  plane.walls.box.pos + rotation_point};
        line.rotate(plane.walls.box.rotation);
        plane.walls.rotate(-2.0f, line.b);
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";
    for (float i{0}; i < 100; i += 2) {
        plane.walls.move({-2.0f, 0});
        cut_sofa();
        render_frame();
    }
    std::cout << plane.sofa.box.calculate_area() << "\n";

    return 0;
}
