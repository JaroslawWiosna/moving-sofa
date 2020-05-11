# moving-sofa
Animation of moving sofa problem

## Features
### Minimal features:
 1. Move (or rotate) sofa, or Corridor, whatever, calculate the area of sofa
 1. Generate a set of pictures, or a gif or video

### Nice-to-have:

 1. Machine-learning-ish way to calculate the largest area possible.
 1. Not only L-shaped, but Z-shaped or U-shaped Corridor
 1. Keep track of measurement uncertainty (float approx. etc.)
 1. `--demo` option that explains what is the problem all about.

## TODO:

 * [x] (#3) Procedurally rotate corridor
   * [x] by its corner
   * [x] by any point, even outside of corridor
 * [X] (#6) Calculate area of Sofa
 * [ ] Procedurally move corridor (from rhs to lhs)
 * [ ] Think about additive geometry in Corridor
   * This is not really needed, but in the future, when we have different shaped corridors, it would be easier to compose shapes.
 * [ ] CI on github
 * [ ] Display text on image
 * [ ] Camera with zoom
 * [ ] Summarize the project in this very README
