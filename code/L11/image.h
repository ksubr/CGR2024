#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Image {
public:
    // Constructor to initialize the image with width, height, and background color (optional)
    Image(int width, int height, int backgroundR = 255, int backgroundG = 255, int backgroundB = 255)
        : width(width), height(height) {
        // Initialize the image with the background color
        pixels.resize(width * height * 3);  // 3 components per pixel: R, G, B
        for (int i = 0; i < width * height; ++i) {
            pixels[i * 3 + 0] = backgroundR;
            pixels[i * 3 + 1] = backgroundG;
            pixels[i * 3 + 2] = backgroundB;
        }
    }

    // Function to set the color of a pixel at (x, y)
    void setPixel(int x, int y, int r, int g, int b) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            int index = (y * width + x) * 3;
            pixels[index + 0] = r;
            pixels[index + 1] = g;
            pixels[index + 2] = b;
        }
    }

    // Function to write the image to a .ppm file in P3 (text) format
    bool writePPM(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return false;
        }

        // Write the PPM header
        file << "P3\n";                 // Magic number (P3 for ASCII text format)
        file << width << " " << height << "\n";  // Image dimensions
        file << "255\n";                // Maximum color value

        // Write the pixel data
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int index = (y * width + x) * 3;
                file << pixels[index + 0] << " "    // Red
                     << pixels[index + 1] << " "    // Green
                     << pixels[index + 2] << "  ";  // Blue
            }
            file << "\n";  // Newline after each row
        }

        file.close();
        return true;
    }

private:
    int width, height;
    std::vector<int> pixels;  // Store pixel data as a flat vector (R, G, B for each pixel)
};

#endif  // IMAGE_HPP

