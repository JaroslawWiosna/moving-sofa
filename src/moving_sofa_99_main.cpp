void test() {
    {
        Box box;
        box.pos = {500, 500};
        box.size = {100, 100};
        box.rotate(180, {500, 500});
        assert(box.contains({450, 550}));
    }
    {
        Box box;
        box.pos = {500, 500};
        box.size = {200, 200};
        box.rotate(180, {500, 500});
        assert(box.contains({450, 550}));
    }
    {
        Box box;
        box.pos = {500, 500};
        box.size = {100, 100};
        box.rotate(10, {500, 500});
        box.rotate(-10, {500, 500}); 
        assert(box.contains({550, 550}));
    }

}

int main(int argc, char* argv[]) {
    test();

    Plane plane{};
    plane.render("output00.png");

    exit(0);

    return 0;
}
