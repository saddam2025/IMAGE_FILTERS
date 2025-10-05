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

// Filter 10: Detect Image Edges
void convertToGrayscale(Image &img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            unsigned char r = img(x,y,0);
            unsigned char g = img(x,y,1);
            unsigned char b = img(x,y,2);
            unsigned char gray = static_cast<unsigned char>((r + g + b) / 3);
            img(x,y,0) = img(x,y,1) = img(x,y,2) = gray;
        }
    }
}


void detectEdges(Image &img) {
    convertToGrayscale(img); 
    Image copy = img;        

    for (int y = 1; y < img.height - 1; ++y) {
        for (int x = 1; x < img.width - 1; ++x) {
            int gx = -copy(x-1,y-1,0) - 2*copy(x-1,y,0) - copy(x-1,y+1,0)
                     + copy(x+1,y-1,0) + 2*copy(x+1,y,0) + copy(x+1,y+1,0);
            int gy = -copy(x-1,y-1,0) - 2*copy(x,y-1,0) - copy(x+1,y-1,0)
                     + copy(x-1,y+1,0) + 2*copy(x,y+1,0) + copy(x+1,y+1,0);

            int magnitude = sqrt(gx*gx + gy*gy);
            magnitude /= 1.5;
            if (magnitude > 255) magnitude = 255;

            unsigned char inverted = static_cast<unsigned char>(255 - magnitude);
            img(x,y,0) = img(x,y,1) = img(x,y,2) = inverted;
        }
    }
}


    if (n == 1) { 
        Grayscale(img);
         cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
    else if (n == 7) {
        
    double percent;
    cout << "Enter lighting change (-50 to 50 for 50% darken/lighten): ";
    cin >> percent;
    filterLightDark(img, percent);
     cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
        
    else if (n == 10) {
    detectEdges(img); 
        cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
    }
    else {
        cout << "Invalid option!\n";
    }

     cout << "Edge detection done! Saved as " << filename << endl;

    return 0;
}
