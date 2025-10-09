#include <iostream>
#include <string>
#include <vector>
#include "Image_Class.h"
using namespace std;


// Filter 1: Grayscale
void Grayscale(Image &img) {
    for (int i = 0; i < img.width; ++i)
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) avg += img(i, j, k);
            avg /= 3;
            img(i, j, 0) = img(i, j, 1) = img(i, j, 2) = avg;
        }
}

// Filter 2: Black and White
void BlackandWhite(Image &img) {
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++) {
            int gray = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            if (gray >= 128) gray = 255; else gray = 0;
            img(x, y, 0) = img(x, y, 1) = img(x, y, 2) = gray;
        }
}

// Filter 3: Invert
void invert(Image &img) {
    for (int y=0;y<img.height;y++)
        for (int x=0;x<img.width;x++)
            for (int c=0;c<img.channels;c++)
                img(x,y,c) = 255 - img(x,y,c);
}

void ResizingImages(Image &img, int newW, int newH);
// Filter 4: Merge Images
void mergeImages(Image &img1, Image &img2, Image &result) {
    // Resize if different sizes
    if (img1.width != img2.width || img1.height != img2.height) {
        if (img1.width*img1.height > img2.width*img2.height)
            ResizingImages(img1, img2.width, img2.height);
        else
            ResizingImages(img2, img1.width, img1.height);
    }
    result = Image(img1.width, img1.height);
    for (int y=0;y<img1.height;y++)
        for (int x=0;x<img1.width;x++)
            for (int c=0;c<img1.channels;c++)
                result(x,y,c) = (img1(x,y,c)+img2(x,y,c))/2;
}

// Filter 5: Flip Image
void FlipImage(Image &img){
    int choice;
    cout << "1: Vertical Flip, 2: Horizontal Flip: ";
    cin >> choice;
    int w=img.width, h=img.height, c=img.channels;
    if (choice==1)
        for(int y=0;y<h/2;y++)
            for(int x=0;x<w;x++)
                for(int ch=0;ch<c;ch++)
                    swap(img(x,y,ch), img(x,h-1-y,ch));
    else if(choice==2)
        for(int y=0;y<h;y++)
            for(int x=0;x<w/2;x++)
                for(int ch=0;ch<c;ch++)
                    swap(img(x,y,ch), img(w-1-x,y,ch));
}

// Filter 6: Rotate
void rotate(Image &img,int angle) {
    // Only 90,180,270 supported
    int w=img.width,h=img.height,c=img.channels;
    Image temp=img;
    if(angle==90){
        Image rotated(h,w);
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
                for(int ch=0;ch<c;ch++)
                    rotated(y,w-1-x,ch) = img(x,y,ch);
        img=rotated;
    }
    else if(angle==180)
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
                for(int ch=0;ch<c;ch++)
                    img(w-1-x,h-1-y,ch) = temp(x,y,ch);
    else if(angle==270){
        Image rotated(h,w);
        for(int y=0;y<h;y++)
            for(int x=0;x<w;x++)
                for(int ch=0;ch<c;ch++)
                    rotated(h-1-y,x,ch) = img(x,y,ch);
        img=rotated;
    }
}

// Filter 7: Light/Dark
void filterLightDark(Image &img, double percent) {
    double factor=percent/100.0;
    for(int y=0;y<img.height;y++)
        for(int x=0;x<img.width;x++)
            for(int c=0;c<3;c++){
                int val=img(x,y,c)*(1+factor);
                if(val>255) val=255;
                if(val<0) val=0;
                img(x,y,c)=val;
            }
}

// Filter 8: Crop
void CropImages(Image &img){
    int x,y,w,h;
    cout<<"Enter start x y: "; cin>>x>>y;
    cout<<"Enter width height: "; cin>>w>>h;
    if(x<0||y<0||x+w>img.width||y+h>img.height){cout<<"Invalid dimensions!\n"; return;}
    Image cropped(w,h);
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            for(int ch=0;ch<img.channels;ch++)
                cropped(j,i,ch)=img(j+x,i+y,ch);
    img=cropped;
}

// Filter 9: Frame
void frame(Image &img){ for(int y=0;y<img.height;y++) for(int x=0;x<img.width;x++) if(x<20||x>=img.width-20||y<20||y>=img.height-20){img.setPixel(x,y,0,100);img.setPixel(x,y,1,25);img.setPixel(x,y,2,90);} }
void frameb(Image &img){ for(int y=0;y<img.height;y++) for(int x=0;x<img.width;x++) if(x<20||x>=img.width-20||y<20||y>=img.height-20){int r=100,g=(x+y)%256,b=(x+y)%256;img.setPixel(x,y,0,r);img.setPixel(x,y,1,g);img.setPixel(x,y,2,b);} }

// Filter 10: Detect edges
void convertToGrayscale(Image &img){for(int y=0;y<img.height;y++) for(int x=0;x<img.width;x++){unsigned char g=(img(x,y,0)+img(x,y,1)+img(x,y,2))/3; img(x,y,0)=img(x,y,1)=img(x,y,2)=g;}}
void detectEdges(Image &img){
    convertToGrayscale(img);
    Image copy=img;
    for(int y=1;y<img.height-1;y++)
        for(int x=1;x<img.width-1;x++){
            int gx=-copy(x-1,y-1,0)-2*copy(x-1,y,0)-copy(x-1,y+1,0)+copy(x+1,y-1,0)+2*copy(x+1,y,0)+copy(x+1,y+1,0);
            int gy=-copy(x-1,y-1,0)-2*copy(x,y-1,0)-copy(x+1,y-1,0)+copy(x-1,y+1,0)+2*copy(x,y+1,0)+copy(x+1,y+1,0);
            int mag=sqrt(gx*gx+gy*gy)/1.5;
            if(mag>255) mag=255;
            unsigned char inv=255-mag;
            img(x,y,0)=img(x,y,1)=img(x,y,2)=inv;
        }
}

// Filter 11: Resize
void ResizingImages(Image &img){
    int w,h; double ratio;
    cout<<"Resize by 1.New dims 2.Ratio: "; int m; cin>>m;
    if(m==1){cout<<"Enter new width height: "; cin>>w>>h;}
    else{cout<<"Enter ratio: "; cin>>ratio; w=img.width*ratio; h=img.height*ratio;}
    Image resized(w,h);
    double scaleX=(double)img.width/w, scaleY=(double)img.height/h;
    for(int y=0;y<h;y++) for(int x=0;x<w;x++) for(int c=0;c<img.channels;c++)
        resized(x,y,c)=img((int)(x*scaleX),(int)(y*scaleY),c);
    img=resized;
}
void ResizingImages(Image &img,int newW,int newH){
    Image resized(newW,newH);
    double scaleX=(double)img.width/newW, scaleY=(double)img.height/newH;
    for(int y=0;y<newH;y++) for(int x=0;x<newW;x++) for(int c=0;c<img.channels;c++)
        resized(x,y,c)=img((int)(x*scaleX),(int)(y*scaleY),c);
    img=resized;
}

// Filter 12: Blur
void blur(Image &img,int r=10){
    Image temp=img;
    for(int y=r;y<img.height-r;y++) for(int x=r;x<img.width-r;x++){
        int sr=0,sg=0,sb=0,count=0;
        for(int dy=-r;dy<=r;dy++) for(int dx=-r;dx<=r;dx++){
            sr+=temp.getPixel(x+dx,y+dy,0); sg+=temp.getPixel(x+dx,y+dy,1); sb+=temp.getPixel(x+dx,y+dy,2); count++;
        }
        img.setPixel(x,y,0,sr/count); img.setPixel(x,y,1,sg/count); img.setPixel(x,y,2,sb/count);
    }
}

// Check valid extension
bool isValidExtension(const string &name) {
    if (name.length() < 4) return false;
    string ext = name.substr(name.length() - 4);
    return ext == ".jpg" || ext == ".png" || ext == ".bmp";
}

// Print menu
void printMenu() {
    cout << "\nMenu Options:\n"
         << "1. Grayscale\n2. Black & White\n3. Invert\n4. Merge\n5. Flip\n"
         << "6. Rotate\n7. Light/Dark\n8. Crop\n9. Frame\n10. Detect Edges\n"
         << "11. Resize\n12. Blur\n13. Load New Image\n14. Save Image\n15. Exit\n";
}

// Save current image with checking extension
void saveImageWithCheck(Image &img, const string &currentFile) {
    cin.ignore();
    string saveName;
    cout << "Enter file name to save (or press Enter to use current): ";
    getline(cin, saveName);
    if (saveName.empty()) saveName = currentFile;

    if (!isValidExtension(saveName)) cout << "Invalid extension! Save aborted.\n";
    else {
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

int main() {
    string filename;
    cout << "Enter image file to work on: ";
    cin >> filename;

    if (!isValidExtension(filename)) { cout << "Invalid file extension.\n"; return 1; }

    Image img(filename);
    if (!img.loadNewImage(filename)) { cout << "File does not exist.\n"; return 1; }

    while (true) {
    printMenu();
    int n;
    cin >> n;

    if (n == 1) Grayscale(img);
    else if (n == 2) BlackandWhite(img);
    else if (n == 3) invert(img);
    else if (n == 4) {
        string file2; cout << "Second image file: "; cin >> file2;
        Image img2(file2);
        if (!img2.loadNewImage(file2)) cout << "File not exist.\n";
        else { Image res(0,0); mergeImages(img,img2,res); img=res; }
    }
    else if (n == 5) FlipImage(img);
    else if (n == 6) { int angle; cout << "Angle 90/180/270: ";cin >> angle; rotate(img, angle); }
    else if (n == 7) { double p; cout << "Light/Dark %: "; cin >> p; filterLightDark(img, p); }
    else if (n == 8) CropImages(img);
    else if (n == 9) {
        int f; cout << "Frame 1=simple 2=fancy: "; cin >> f;
        if(f==1) frame(img); else if(f==2) frameb(img);
    }
    else if (n == 10) detectEdges(img);
    else if (n == 11) ResizingImages(img);
    else if (n == 12) blur(img);
    else if (n == 13) loadNewImage(img, filename);
    else if (n == 14) saveImageWithCheck(img, filename);
    else if (n == 15) {
        char saveBeforeExit; cout << "Save before exit? (y/n): "; cin >> saveBeforeExit;
        if(saveBeforeExit=='y'||saveBeforeExit=='Y') saveImageWithCheck(img, filename);
        cout << "Exiting program.\n"; break;
    }
    else cout << "Invalid choice!\n";
}


    return 0;
}
