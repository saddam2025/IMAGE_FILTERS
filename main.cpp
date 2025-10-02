#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

// filter 1: Grayscale
void Grayscale(Image &img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += img(i, j, k);
            }
            avg /= 3;
            img(i, j, 0) = avg;
            img(i, j, 1) = avg;
            img(i, j, 2) = avg;
        }
    }
}

// filter7: light dark
void filterLightDark(Image &img, double percent) {
    double factor = percent / 100.0; // 50% → 0.5، -50% → -0.5
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) { // R,G,B
                int value = img(x, y, c);
                value = static_cast<int>(value * (1 + factor));
                if (value > 255) value = 255;
                if (value < 0) value = 0;
                img(x, y, c) = static_cast<unsigned char>(value);
            }
        }
    }
}


    if (n == 1) { 
        Grayscale(img);
        cout << "Enter new file name to save: ";
        cin >> filename;
        img.saveImage(filename);
    }
    else if (n == 7) {
        
    double percent;
    cout << "Enter lighting change (-50 to 50 for 50% darken/lighten): ";
    cin >> percent;
    filterLightDark(img, percent);
    cout << "Image processed successfully!\n";



        cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
    }
    else {
        cout << "Invalid option!\n";
    }

    cout << "You chose option " << n << endl;

    return 0;
}
