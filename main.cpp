#include <iostream>
#include <string>
#include <exception>
#include "Image_Class.h"
using namespace std;

 //Filter 2: Black and White
         void BlackandWhite(Image &img){
            int width = img.width;
            int height = img.height;
            int channels = img.channels;

            for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
            unsigned char r = img(x, y, 0);
            unsigned char g = img(x, y, 1);
            unsigned char b = img(x, y, 2);
            
            int gray =(r+g+b) / 3;
            if (gray>=128){
            img(x, y, 0)=img(x, y, 1)=img(x, y, 2) =255 ;
            }
            else{
            img(x, y, 0)=img(x, y, 1)=img(x, y, 2)= 0;
            }
        }
    }
}

int main() {
    try {
        cout << "Image processing program started!" << endl;
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

   string filename ;
        cout << "Enter image file name " ;
        cin >> filename ;

        Image img(filename); 
        if (!loadNewimage(filename)) {
            cout << "File does not exist";
        }  
        cout << "Choose filter:\n"
            << "1: Grayscale Conversion\n"
            << "2: Black and White\n"
            << "3: Invert Image\n"
            << "4: Merge Images\n"
            << "5: Flip Image\n"
            << "6: Rotate Image\n";
            int n ;
            cin >> n;

            if (n==2){
                BlackandWhite(img);
                img.saveImage("output.png");
                cout << "Saved output.png\n";
            }
        return 0;
    }
