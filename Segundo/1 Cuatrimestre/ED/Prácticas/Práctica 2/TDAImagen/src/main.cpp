#include <iostream>

#include "imagen.h"

int main(int nargs, const char **vargs) {
    try {
        Imagen img(vargs[1]);
        Imagen img2(vargs[2]);
        img.morphing(img2, 255);
    } catch (int x) {
        std::cout << x;
    }
}
