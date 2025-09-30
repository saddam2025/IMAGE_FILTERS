#include <iostream>
#include <string>
#include <vector>
#include "Image_Class.h"
using namespace std;
void rotate(Image &newimg ,int angle) {
    int w = newimg.width;
    int h = newimg.height;
    int c = newimg.channels;
    if (angle == 90) {
        Image rotated;
        rotated.width = h;
        rotated.height = w;
        rotated.channels = c;
        if (rotated.imageData) {
            delete[] rotated.imageData;
        }
        rotated.imageData = new unsigned char [w*h*c];

        for (int y=0;y<h;y++) {
            for (int x=0;x<w;x++) {
                for (int z=0;z<c;z++) {
                    rotated(y,w-1-x,z) = newimg(x,y,z);
                }
            }
        }
        newimg = rotated;

    }
    else if (angle == 180) {
        Image rotated;
        rotated.width = w;
        rotated.height = h;
        rotated.channels = c;
        if (rotated.imageData) {
            delete[] rotated.imageData;
        }
        rotated.imageData = new unsigned char [w*h*c];
        for (int y=0;y<h;y++) {
            for (int x=0;x<w;x++) {
                for (int z=0;z<c;z++) {
                    rotated(w-1-x,h-1-y,z) = newimg(x,y,z);
                }
            }
        }
        newimg = rotated;

    }
    else if (angle == 270) {
        Image rotated;
        rotated.width = h;
        rotated.height = w;
        rotated.channels = c;
        if (rotated.imageData) {
            delete[] rotated.imageData;
        }
        rotated.imageData = new unsigned char [w*h*c];
        for (int y=0;y<h;y++) {
            for (int x=0;x<w;x++) {
                for (int z=0;z<c;z++) {
                    rotated(h-1-y,x,z) = newimg(x,y,z);
                }

            }
        }

    newimg = rotated;}
    else {
        return;
    }

}
void invert(Image &newimg) {
    int w = newimg.width;
    int h = newimg.height;
    int c = newimg.channels;
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            for (int z=0;z<c;z++) {
                newimg(x,y,z) = 255- newimg(x,y,z);
            }
        }
    }
}

int main() {
    cout << "Image processing program started!" << endl;

    string filename;
    cout << "Enter image file name: ";
    cin >> filename;

    Image img;
    if (!img.loadNewImage(filename)) {
        cout << "File does not exist\n";
        return 1;
    }

    cout << "Choose filter:\n"
         << "1: Grayscale Conversion\n"
         << "2: Black and White\n"
         << "3: Invert Image\n"
         << "4: Merge Images\n"
         << "5: Flip Image\n"
         << "6: Rotate Image\n";

    int n;
    cin >> n;
    if (n == 6) {
        int a;
        cout<<"select your angle ( 90 , 180 , 270 , 360 )"<<endl;
        cin>>a;
        rotate(img,a);
        img.saveImage("after_editing.png");
    }
    if (n == 3) {
        invert(img);
        img.saveImage("after_inverted.png");
    }

    cout << " Nice photo :) " << n << endl;

    return 0;
}