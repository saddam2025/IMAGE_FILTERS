#include <iostream>
#include <string>
#include <cmath>
#include "Image_Class.h"
using namespace std;

// Filter 1: Grayscale
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

// Filter 2: Black and White
void BlackandWhite(Image &img) {
    int width = img.width;
    int height = img.height;
    int channels = img.channels;
    for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
            unsigned char r = img(x, y, 0);
            unsigned char g = img(x, y, 1);
            unsigned char b = img(x, y, 2);
            int gray =(r+g+b) / 3;
            if (gray >= 128) {
                img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = 255;
            } else {
                img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = 0;
            }
        }
    }
}

// Filter 3: Invert
void invert(Image &img) {
    int w = img.width;
    int h = img.height;
    int c = img.channels;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int z = 0; z < c; z++) {
                img(x, y, z) = 255 - img(x, y, z);
            }
        }
    }
}

// Filter 4: Merge Images
void mergeImages(Image &img1, Image &img2, Image &result) {
    if (img1.width != img2.width || img1.height != img2.height) {
        if (img1.width*img1.height > img2.width*img2.height)
            ResizingImages(img1, img2.width, img2.height);
        else
            ResizingImages(img2, img1.width, img1.height);
    }
    result = Image(img1.width, img1.height);
    for (int y = 0; y < img1.height; y++) {
        for (int x = 0; x < img1.width; x++) {
            for (int c = 0; c < img1.channels; c++) {
                result(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2;
            }
        }
    }
}

// Filter 5: Flip Image
void FlipImage(Image &img) {
    int width = img.width;
    int height = img.height;
    int channels = img.channels;
    cout << "Choose: 1.Vertical 2.Horizontal: ";
    int m;
    cin >> m;
    if (m == 1) {
        for (int y = 0; y < height/2; y++) {
            for (int x = 0; x < width; x++) {
                for (int c = 0; c < channels; c++) {
                    int temp = img(x, y, c);
                    img(x, y, c) = img(x, height-1-y, c);
                    img(x, height-1-y, c) = temp;
                }
            }
        }
    } else if (m == 2) {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width/2; x++) {
                for (int c = 0; c < channels; c++) {
                    int temp = img(x, y, c);
                    img(x, y, c) = img(width-1-x, y, c);
                    img(width-1-x, y, c) = temp;
                }
            }
        }
    }
}

// Filter 6: Rotate
void rotate(Image &img, int angle) {
    int w = img.width;
    int h = img.height;
    int c = img.channels;
    Image temp = img;
    if (angle == 90) {
        Image rotated(h, w);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                for (int z = 0; z < c; z++) {
                    rotated(y, w-1-x, z) = img(x, y, z);
                }
            }
        }
        img = rotated;
    } else if (angle == 180) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                for (int z = 0; z < c; z++) {
                    img(w-1-x, h-1-y, z) = temp(x, y, z);
                }
            }
        }
    } else if (angle == 270) {
        Image rotated(h, w);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                for (int z = 0; z < c; z++) {
                    rotated(h-1-y, x, z) = img(x, y, z);
                }
            }
        }
        img = rotated;
    }
}

// Filter 7: Light/Dark
void filterLightDark(Image &img, double percent) {
    double factor = percent / 100.0;
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                int val = img(x, y, c) * (1 + factor);
                if (val > 255) val = 255;
                if (val < 0) val = 0;
                img(x, y, c) = val;
            }
        }
    }
}

// Filter 8: Crop Images
void CropImages(Image &img) {
    int width = img.width;
    int height = img.height;
    int channels = img.channels;
    int x, y, w, h;
    cout << "Enter start point x, y: ";
    cin >> x >> y;
    cout << "Enter width height: ";
    cin >> w >> h;
    if (x < 0 || y < 0 || x+w > width || y+h > height) {
        cout << "Invalid crop dimensions!\n";
        return;
    }
    Image cropped(w, h);
    
    for (int i = 0; i< h; i++) {
        for (int j= 0; j< w; j++) {
            for (int c= 0; c < channels; c++) {
                cropped(j, i, c) = img(j+x, i+y, c);
            }
        }
    }
    img = cropped;
}

// Filter 9: Frame
void frame(Image &img) {
    int w = img.width;
    int h = img.height;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (x < 20 || x >= w-20 || y < 20 || y >= h-20) {
                img.setPixel(x, y, 0, 100);
                img.setPixel(x, y, 1, 25);
                img.setPixel(x, y, 2, 90);
            }
        }
    }
}

void frameb(Image &img) {
    int w = img.width;
    int h = img.height;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (x < 20 || x >= w-20 || y < 20 || y >= h-20) {
                int r = 100;
                int g = (x+y) % 256;
                int b = (x+y) % 256;
                img.setPixel(x, y, 0, r);
                img.setPixel(x, y, 1, g);
                img.setPixel(x, y, 2, b);
            }
        }
    }
}

// Filter 10: Detect Edges
void convertToGrayscale(Image &img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char g = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = g;
        }
    }
}

void detectEdges(Image &img) {
    convertToGrayscale(img);
    Image copy = img;
    for (int y = 1; y < img.height-1; y++) {
        for (int x = 1; x < img.width-1; x++) {
            int gx = -copy(x-1, y-1, 0) - 2*copy(x-1, y, 0) - copy(x-1, y+1, 0)
                     + copy(x+1, y-1, 0) + 2*copy(x+1, y, 0) + copy(x+1, y+1, 0);
            int gy = -copy(x-1, y-1, 0) - 2*copy(x, y-1, 0) - copy(x+1, y-1, 0)
                     + copy(x-1, y+1, 0) + 2*copy(x, y+1, 0) + copy(x+1, y+1, 0);
            int mag = sqrt(gx*gx + gy*gy) / 1.5;
            if (mag > 255) mag = 255;
            unsigned char inv = 255 - mag;
            img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = inv;
        }
    }
}

// Filter 11: Resize
void ResizingImages(Image &img) {
    int width = img.width;
    int height = img.height;
    int channels = img.channels;
    cout << "choose resize by: 1.New dimensions \n 2.Ratio: ";
    int m;
    cin >> m;
    int w, h;
    if (m == 1) {
        cout << "Enter new width and height: ";
        cin >> w >> h;
    }
    else if(m==2) {
        double ratio;
        cout << "Enter the ratio: ";
        cin >> ratio;
        w = width*ratio;
        h = height*ratio;
    }
    Image resized(w, h);
    
    double scaleX = width / w;
    double scaleY = height / h;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int c = 0; c < channels; c++) {
                resized(x, y, c) = img((int)(x*scaleX), (int)(y*scaleY), c);
            }
        }
    }
    img = resized;
}

// Filter 12: Blur
void blur(Image &img, int r=10) {
    Image temp = img;
    for (int y = r; y < img.height - r; y++) {
        for (int x = r; x < img.width - r; x++) {
            int sr = 0, sg = 0, sb = 0, count = 0;
            for (int dy = -r; dy <= r; dy++) {
                for (int dx = -r; dx <= r; dx++) {
                    sr += temp.getPixel(x+dx, y+dy, 0);
                    sg += temp.getPixel(x+dx, y+dy, 1);
                    sb += temp.getPixel(x+dx, y+dy, 2);
                    count++;
                }
            }
            img.setPixel(x, y, 0, sr/count);
            img.setPixel(x, y, 1, sg/count);
            img.setPixel(x, y, 2, sb/count);
        }
    }
}
// Check valid extension
bool isValidExtension(const string &name) {
    if (name.length() < 4) return false;
    string ext = name.substr(name.length()-4);
    return ext == ".jpg" || ext == ".png" || ext == ".bmp";
}

// Save current image
void saveImageWithCheck(Image &img, const string &currentFile) {
    cin.ignore();
    string saveName;
    cout << "Enter file name to save (or press Enter to use current): ";
    getline(cin, saveName);
    if (saveName.empty()) saveName = currentFile;
    if (!isValidExtension(saveName)) {
        cout << "Invalid extension! Save aborted.\n";
    } else {
        img.saveImage(saveName);
        cout << "Image saved successfully!\n";
    }
}

// Load new image
bool loadNewImage(Image &img, string &filename) {
    char saveBefore;
    cout << "Do you want to save the current image before loading a new one? (y/n): ";
    cin >> saveBefore;
    if (saveBefore=='y'||saveBefore=='Y') saveImageWithCheck(img, filename);
    cout << "Enter new image file name: ";
    cin >> filename;
    if (!isValidExtension(filename) || !img.loadNewImage(filename)) {
        cout << "Invalid file or file does not exist. Current image unchanged.\n";
        return false;
    }
    return true;
}

// Print menu
void printMenu() {
    cout << "\nMenu Options:\n"
         << "1. Grayscale\n2. Black & White\n3. Invert\n4. Merge\n5. Flip\n"
         << "6. Rotate\n7. Light/Dark\n8. Crop\n9. Frame\n10. Detect Edges\n"
         << "11. Resize\n12. Blur\n13. Load New Image\n14. Save Image\n15. Exit\n";
}

// Main function
int main() {
    string filename;
    cout << "Enter image file to work on: ";
    cin >> filename;

    if(!isValidExtension(filename)) {
        cout << "Invalid file extension.\n";
        return 1;
    }

    Image img(filename);
    if(!img.loadNewImage(filename)) {
        cout << "File does not exist.\n";
        return 1;
    }

    while(true) {
        printMenu();
        int n;
        cin >> n;

        if(n==1) {
            Grayscale(img);
        }
        else if(n==2) {
            BlackandWhite(img);
        }
        else if(n==3) {
            invert(img);
        }
        else if(n==4) {
            string file2;
            cout << "Second image file: ";
            cin >> file2;

            Image img2(file2);
            if(!img2.loadNewImage(file2)) {
                cout << "File not exist.\n";
            } else {
                Image res(0,0);
                mergeImages(img,img2,res);
                img=res;
            }
        }
        else if(n==5) {
            FlipImage(img);
        }
        else if(n==6) {
            int angle;
            cout << "Angle 90/180/270: ";
            cin >> angle;
            rotate(img,angle);
        }
        else if(n==7) {
            double p;
            cout << "Light/Dark %: ";
            cin >> p;
            filterLightDark(img,p);
        }
        else if(n==8) {
            CropImages(img);
        }
        else if(n==9) {
            int f;
            cout << "Frame 1=simple 2=fancy: ";
            cin >> f;
            if(f==1) frame(img);
            else if(f==2) frameb(img);
        }
        else if(n==10) {
            detectEdges(img);
        }
        else if(n==11) {
            ResizingImages(img);
        }
        else if(n==12) {
            blur(img);
        }
        else if(n==13) {
            loadNewImage(img, filename);
        }
        else if(n==14) {
            saveImageWithCheck(img, filename);
        }
        else if(n==15) {
            char saveBeforeExit;
            cout << "Save before exit? (y/n): ";
            cin >> saveBeforeExit;
            if(saveBeforeExit=='y'||saveBeforeExit=='Y') {
                saveImageWithCheck(img, filename);
            }
            cout << "Exiting program.\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}

