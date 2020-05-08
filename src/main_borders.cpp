struct Borders {
    std::array<Line, 2> horizontal_lines = {
        Line{{-3'000, 0}, {0, 0}},
        Line{{-3'000, -1'000}, {1'000, -1'000}},
    };
    std::array<Line, 2> vertical_lines = {
        Line{{0, 0}, {0, 3'000}},
        Line{{1'000, -1'000}, {1'000, 3'000}},
    };
};