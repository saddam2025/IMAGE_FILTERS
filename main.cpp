#include <iostream>
#include <string>
#include <exception>
#include "Image_Class.h"
using namespace std;

 //Filter 2: Black and White
    void BlackandWhite(Image &img){
        int width = img.getWidth();
        int height = img.getHeight();
        int channels = img.getChannels();
        unsigned char* image = img.getData();

        for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
        int i = (y * width + x) * channels;  
        unsigned char r = image[i+0];
        unsigned char g = image[i + 1];
        unsigned char b = image[i + 2];
        
        int gray =(r+g+b) / 3;
        if (gray>=128){
          image[i+0]=  image[i + 1] = image[i + 2] =255 ;
        }
        else{
            image[i+0]=  image[i + 1] = image[i + 2] = 0;
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
    bool loadNewimage(const string&filename) ;

    ifstream file(filename);  // open file
    if (!file) {
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
             BlackandWhite(filename);  
             img.saveImage("output.png");
        }
    return 0;
}
