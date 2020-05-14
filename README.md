# moving-sofa
Animation of moving sofa problem

**The development is ongoing**

## Demo

![demo](https://raw.githubusercontent.com/JaroslawWiosna/moving-sofa/images_for_readme/demo.gif "Demo")

![demo](https://raw.githubusercontent.com/JaroslawWiosna/moving-sofa/images_for_readme/demo01.gif "Demo")

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
 * [X] Procedurally move corridor (from rhs to lhs)
 * [x] Draw corridor, even when its rotated
 * [X] (#10) Decrease Image size
 * [X] (#9) Display text on image
 * [ ] (#14) Think about additive geometry in Corridor
   * This is not really needed, but in the future, when we have different shaped corridors, it would be easier to compose shapes.
 * [ ] (#13) Font path is hardcoded
 * [ ] Develop macros for unit testing
   * Naming of macros can be inspired by https://github.com/google/googletest/blob/master/googletest/docs/primer.md 
   * The idea is to develop macros which I need
   * GTest is great by I would like to postpone integrating GTEST into this very project, if possible, because I'd like to keep my project without dependencies.
 * [ ] CI on github
 * [ ] Camera with zoom
 * [ ] Change the **unit** from `100.0f` to `1.0f`  
 * [ ] Summarize the project in this very README
