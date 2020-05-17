#include "moving_sofa_all_includes.cpp"

struct Argvs {
    float radius = 95.0f;
    float rotation_step = 0.5f;
    bool generate_pngs = false;
    bool final_png = true;

    static Argvs parse(int argc, char* argv[]) {
        Argvs result;
        for (int i{1}; i < argc; ++i) {
            if (0 == strcmp(argv[i], "--radius")) {
                result.radius = atof(argv[++i]);
                continue;
            }
            if (0 == strcmp(argv[i], "--step")) {
                result.rotation_step = atof(argv[++i]);
                continue;
            }
            if (0 == strcmp(argv[i], "--pngs")) {
                result.generate_pngs = true;
                continue;
            }
            if (0 == strcmp(argv[i], "--nofinal-png")) {
                result.final_png = false;
                continue;
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    auto argvs = Argvs::parse(argc, argv);
    char radius_as_cstr[256];
    if (argvs.radius < 10.0f ) {
        sprintf(radius_as_cstr, "00%1.2f", argvs.radius);
    } else if (argvs.radius < 100.0f ) {
        sprintf(radius_as_cstr, "0%2.2f", argvs.radius);
    } else {
        sprintf(radius_as_cstr, "%3.2f", argvs.radius);
    }
    
    Plane plane{};
    plane.sofa.box.create_elems(500, 100);
    char output_filename[256];
    char text_to_display_on_image[256];
    sprintf(text_to_display_on_image, ":-)");
    auto generate_output_filename = [&output_filename]() {
        static float i{};
        sprintf(output_filename, "output%04.f.png", i++);
    };
    auto render_frame = [&]() {
        if (!argvs.generate_pngs) {
            return;
        }
        generate_output_filename();
        sprintf(text_to_display_on_image, "Area: %1.4f, R = %s",
                plane.sofa.box.calculate_area() / 10000.f,
                radius_as_cstr);
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
    // 0deg -> 50,200   == (100 - 50 * cos(ang), 200 + 50 * sin(ang) )
    // 90deg -> 100,250 == (100 - 50 * cos(ang), 200 + 50 * sin(ang) )
    const float radius{argvs.radius};
    for (float i{0}; i < 90; i += argvs.rotation_step) {
        Vec2f rotation_point{100.0f - radius * float(cos(deg2rad(i))),
                             200.0f + radius * float(sin(deg2rad(i)))};
        Line line{plane.walls.box.pos,
                  plane.walls.box.pos + rotation_point};
        line.rotate(plane.walls.box.rotation);
        plane.walls.rotate(-1.0f * argvs.rotation_step, line.b);
        cut_sofa();
        render_frame();
    }
    while (plane.walls.box.pos.x > 200.0f) {
        plane.walls.move({-95.0f, 0});
        cut_sofa();
        render_frame();
    }
    std::cout << radius_as_cstr << " " << plane.sofa.box.calculate_area() << "\n";

    if (argvs.final_png) {
        sprintf(output_filename, "output_rad_%s_step_%01.2f.png", radius_as_cstr, argvs.rotation_step);
        sprintf(text_to_display_on_image, "Area: %1.4f, R: %s",
            plane.sofa.box.calculate_area() / 10000.f,
            radius_as_cstr);
        plane.render(output_filename, text_to_display_on_image);
    }
    return 0;
}
