#include <iostream>
#include <cmath>


const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_ITERATIONS = 255;

int mandelbrot(double x, double y) {
    std::complex<double> z = 0;
    std::complex<double> c(x, y);
    int iterations = 0;
    while (std::abs(z) < 2 && iterations < MAX_ITERATIONS) {
        z = z * z + c;
        iterations++;
    }
    return iterations;
}


void createImage(int image[]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double real = -2.5 + x * 3.5 / WIDTH;
            double imag = -2.0 + y * 2.0 / HEIGHT;
            int iterations = mandelbrot(real, imag);
            image[y * WIDTH + x] = iterations;
        }
    }
}


void writePPM(const char* filename, int image[]) {
    std::ofstream file(filename);
    file << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        int color = image[i] % 256;
        file << color << " " << color << " " << color << "\n";
    }
}

int main() {
    int image[WIDTH * HEIGHT];
    createImage(image);
    writePPM("mandelbrot.ppm", image);
    return 0;
}
