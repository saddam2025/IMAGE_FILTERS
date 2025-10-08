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
void blur(Image &newimg , int r =10) {
    int w = newimg.width;
    int h = newimg.height;
    Image temb=newimg;
    for (int y=r;y<h-r;y++) {
        for (int x=r;x<w-r;x++) {
            int sumr=0;
            int sumg=0;
            int sumb=0;
            int count=0;
            for (int dy = -r;dy<=r;dy++) {
                for (int dx = -r;dx<=r;dx++) {
                    sumr +=temb.getPixel(x+dx,y+dy,0);
                    sumg +=temb.getPixel(x+dx,y+dy,1);
                    sumb +=temb.getPixel(x+dx,y+dy,2);
                    count++;

                }
            }
            newimg.setPixel(x,y,0,sumr/count);
            newimg.setPixel(x,y,1,sumg/count);
            newimg.setPixel(x,y,2,sumb/count);
        }
    }
}
void frame(Image &newimg, int t=20) {
    int w = newimg.width;
    int h = newimg.height;
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            if (x <t||x>=w-t||y <t||y>=h-t) {
                newimg.setPixel(x,y,0,100);
                newimg.setPixel(x,y,1,25);
                newimg.setPixel(x,y,2,90);
            }
        }
    }
}
void frameb(Image &newimg, int t=20) {
    int w = newimg.width;
    int h = newimg.height;
    for (int y=0;y<h;y++) {
        for (int x=0;x<w;x++) {
            if (x<t||x>=w-t||y <t||y>=h-t) {
                int r=100;
                int g=(x+y)%256;
                int b=(y+x)%256;

                newimg.setPixel(x,y,0,r);
                newimg.setPixel(x,y,1,g);
                newimg.setPixel(x,y,2,b);

            }
        }
    }
}int main(){
    string filename ;
    cout << "Enter image file name " ;
    cin >> filename ;

    Image img(filename);
    if (!img.loadNewImage(filename)) {
        cout << "File does not exist";
        return 1 ;
    }
    cout << "Choose filter:\n"
            << "1: Grayscale Conversion\n"
            << "2: Black and White\n"
            << "3: Invert Image\n"
            << "4: Merge Images\n"
            << "5: Flip Image\n"
            << "6: Rotate Image\n"
            << "7: Darken and Lighten Image\n"
            << "8: Crop Image\n"
            << "9: Adding a Frame to the Picture\n"
            << "10: Detect Image Edges\n"
            << "11: Resizing Images\n"
            << "12: Blur Image\n";


    int n ;
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
    if (n==9) {
        int y;
        cout<<"IF you want a simple frame enter: 1 \n"
            <<"IF you want a decorated frame: 2 \n";
        cin>>y;
        if (y==1) {
            frame(img);
            img.saveImage("after_frame.png");
        }
        if (y==2) {
            frameb(img);
            img.saveImage("after_frame.png");
        }


    }

    if (n == 12) {
        blur(img);
        img.saveImage("after_blured.png");
    }

    return 0;
}
