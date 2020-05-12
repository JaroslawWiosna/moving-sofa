#include "moving_sofa_all_includes.cpp"

int main(int argc, char* argv[]) {
    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    std::cout << plane.sofaArea.area() / 10000.0f << "\n";
    char buf[256];
    auto output_filename = [&buf](){
        static float i{};
        sprintf(buf, "output%04.f.png", i++);
    };
    auto render_frame = [&](){
        output_filename();
        plane.render(buf);
    };
    plane.corridor.move({-200.0f, 0});
    render_frame();
    for (float i{0}; i<100; i+=2) {
        plane.corridor.move({-2.0f, 0});
        plane.sofaArea.set_elem_to_false_if_on_corridor_wall(plane.corridor);
        render_frame();
    }
    std::cout << plane.sofaArea.area() / 10000.0f << "\n";
    for (float i{0}; i<90; i+=2) {
        plane.corridor.rotate(-2.0f, {400, 400});
        plane.sofaArea.set_elem_to_false_if_on_corridor_wall(plane.corridor);
        render_frame();
    }    
    std::cout << plane.sofaArea.area() / 10000.0f << "\n";
    return 0;
}