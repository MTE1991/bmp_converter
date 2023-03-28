#include "lib/EasyBMP.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char *argv[]) {
    BMP image;

    if (argc < 2) {
        std::cout << "Not enough arguments provided!" << std::endl;
        exit(1);
    }
    
    image.ReadFromFile(argv[1]);

    // resolution:
    int height = image.TellHeight();
    int width = image.TellWidth();

    if (!strcmp(argv[argc - 1], "greyscale")) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // rgb values
                int red = image(j, i)->Red;
                int green = image(j, i)->Green;
                int blue = image(j, i)->Blue;

                // formula for convertion:
                int grayscale_value = (0.3 * red) + (0.59 * green) + (0.11 * blue);

                // change the pixels
                image(j, i)->Red = grayscale_value;
                image(j, i)->Green = grayscale_value;
                image(j, i)->Blue = grayscale_value;
            }
        }
        image.WriteToFile("out_bmp_bw.bmp");
    } else if (!strcmp(argv[argc - 1], "sepia")) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                // get pixel
                RGBApixel pixel = image.GetPixel(i, j);

                // rgb values
                int red = pixel.Red;
                int green = pixel.Green;
                int blue = pixel.Blue;

                // new rgb values for sepia convertion
                int newRed = (int)(0.393 * red + 0.769 * green + 0.189 * blue);
                int newGreen = (int)(0.349 * red + 0.686 * green + 0.168 * blue);
                int newBlue = (int)(0.272 * red + 0.534 * green + 0.131 * blue);

                // change pixel rgb values
                pixel.Red = std::min(newRed, 255);
                pixel.Green = std::min(newGreen, 255);
                pixel.Blue = std::min(newBlue, 255);

                // set the pixel with new rgb values
                image.SetPixel(i, j, pixel);
            }
        }
        image.WriteToFile("out_bmp_sepia.bmp");
    } else {
        std::cout << "Cannot perform convertion!" << std::endl;
        exit(1);
    }

    return 0;
}
