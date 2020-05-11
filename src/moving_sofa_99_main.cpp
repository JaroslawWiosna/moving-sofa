bool cmp_floats(float a, float b, float eps) {
    if (abs(a - b) < eps) {
        return true;
    } else {
        std::cout << "a==" << a << " b==" << b << " eps==" << eps << "\n";
        return false;
    }
}

void test() {
    {
        assert(cmp_floats(rad2deg(3.1415f), 180.0f, 0.005f));
        assert(cmp_floats(rad2deg(3.1415f / 2.0f), 90.1f, 1.005f));
        assert(cmp_floats(rad2deg(1.555f), 89.0f, 1.0f));
    }
    {
        auto line = make_line_from_polar({200, 200}, 50, 0);
        line.rotate(89);
        assert(cmp_floats(line.angle(), 89.0f, 0.005f));
        assert(line.b.x > 200);
        assert(line.b.y > 240);
    }
    { assert(cmp_floats(rad2deg(atan2(4, 4)), 45.0f, 0.005f)); }
    {
        Line line{{200, 200}, {300, 100}};
        assert(cmp_floats(line.angle(), -45.0f, 0.005f));
    }
    {
        // Line line{{500,500},{497,504}};
        // Line line{{0,0},{3,4}};
        // assert(cmp_floats(line.len(), 5.0f, 0.005f ));
        // assert(cmp_floats(line.angle(), 30.0f, 0.005f ));
    } {
        Box box;
        box.pos = {500, 500};
        box.size = {100, 100};
        box.rotate(45, {500, 500});
        assert(box.contains({495, 550}));
    }
    {
        Box box;
        box.pos = {500, 500};
        box.size = {100, 100};
        box.rotate(179, {500, 500});
        assert(box.contains({450, 450}));
    }
    {
        Box box;
        box.pos = {500.0f, 500.0f};
        box.size = {100.0f, 100.0f};
        box.rotate(10.0f, {500.0f, 500.0f});
        box.rotate(-10.0f, {500.0f, 500.0f});
        assert(box.contains({550.0f, 550.0f}));
    }
    {
        Box box;
        box.pos = {500.0f, 500.0f};
        box.size = {100.0f, 100.0f};
        box.rotate(45.0f, {500.0f, 500.0f});
        assert(box.contains({480.0f, 540.0f}));
    }
}

int main(int argc, char* argv[]) {
    test();

    std::cout << "This is " << argv[0] << "\n";

    Plane plane{};
    plane.render("output00.png");

    exit(0);

    return 0;
}
