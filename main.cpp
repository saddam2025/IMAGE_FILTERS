#include <iostream>
#include <string>
#include <vector>
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

    //Filter 5: Flip Image
    void FlipImage (Image &img){

        int width = img.width;
        int height = img.height;
        int channels = img.channels;

        cout << "choose : \n 1.Flipped Vertical \n 2.Flipped Horizontally " ;
        int m ;
        cin>>m ;

        if(m==1){
        for (int y = 0; y < height/2; y++) {
        for (int x = 0; x < width; x++) {
        for(int c =0 ; c<channels ; c++){
            int temp = img(x,y,c) ;
            img(x, y, c) = img( x,height-1- y, c);
            img(x,height-1- y, c) = temp;
        }
    }
}

        if(m==2){
        for (int y = 0; y < height; y++) {
        for (int x = 0; x < width/2; x++) {
        for(int c =0 ; c<channels ; c++){
            int temp = img(x,y,c) ;
            img(x, y, c) = img(width - 1 - x, y, c);
            img(width - 1 - x, y, c) = temp;
            }
          }
        }

   }
 }
}

//Filter 8: Crop Images
void CropImages(Image &img){
    int width =img.width;
    int height =img.height;
    int channels =img.channels;

    int x,y,w,h ;
    cout << "Enter starting point (x y):" ;
    cin >> x >> y ;
    cout << "Enter crop width and height:" ;
    cin >> w >>h ;

    if (x<0|| y<0|| x+w>width || y+h>height ) {
    cout << "Invalid crop dimensions!" << endl;
    return;
}
   Image cropped(w,h);

   for (int i=0 ;i<h ; i++){
    for (int j=0 ;j<w ; j++){
        for (int c=0 ; c<channels;c++){
         cropped(j,i,c) = img(j+x, i+y, c);


        }
    }
   }
  img=cropped;
}

//Filter 11: Resizing Images
void ResizingImages(Image &img){
    int width = img.width;
    int height = img.height;
    int channels = img.channels;

    cout<<"choose resizing by : 1.new dimensions\n 2.ratio ";
    int m ;
    cin>>m ;
    int h,w;
    if(m==1){
        cout<<"inter new width and higth ";
        cin >> h >> w ;
        }

    if (m==2){
        double ratio ;
        cout <<"inter the ratio ";
        cin >>ratio ;
        w= ratio*width;
        h= ratio*height;
    }
        Image resizing(w,h) ;

        double scalex = width / w ;
        double scaley = height / h ;

        for (int y=0 ;y<h ; y++){
        for (int x=0 ;x<w ; x++){
        for (int c=0 ; c<channels;c++){
            int oldx =(int) (x*scalex) ;
            int oldy= (int) (y*scaley);
            resizing(x, y, c) = img(oldx, oldy, c);
        }
    }
}
    img= resizing;

}
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

// Filter 4: Merge Images
void ResizingImages(Image &img, int newW, int newH) {
    int width = img.width;
    int height = img.height;
    int channels = img.channels;

    Image resized(newW, newH);

    double scaleX = (double)width / newW;
    double scaleY = (double)height / newH;

    for (int y = 0; y < newH; y++) {
        for (int x = 0; x < newW; x++) {
            for (int c = 0; c < channels; c++) {
                int oldX = (int)(x * scaleX);
                int oldY = (int)(y * scaleY);
                resized(x, y, c) = img(oldX, oldY, c);
            }
        }
    }

    img = resized;
}
void mergeImages(Image &img1, Image &img2, Image &result) {
    if (img1.width == img2.width && img1.height == img2.height) {
        cout << "Images are the same size. Merging directly...\n";
        result = Image(img1.width, img1.height);
        for (int y = 0; y < img1.height; y++) {
            for (int x = 0; x < img1.width; x++) {
                for (int c = 0; c < img1.channels; c++) {
                    result(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2;
                }
            }
        }
    }
    else if (img1.width > img2.width || img1.height > img2.height) {
        cout << "First image is larger. Resizing first image...\n";
        ResizingImages(img1, img2.width, img2.height);
        result = Image(img2.width, img2.height);
        for (int y = 0; y < img2.height; y++) {
            for (int x = 0; x < img2.width; x++) {
                for (int c = 0; c < img1.channels; c++) {
                    result(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2;
                }
            }
        }
    }
    else {
        cout << "Second image is larger. Resizing second image...\n";
        ResizingImages(img2, img1.width, img1.height);
        result = Image(img1.width, img1.height);
        for (int y = 0; y < img1.height; y++) {
            for (int x = 0; x < img1.width; x++) {
                for (int c = 0; c < img1.channels; c++) {
                    result(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2;
                }
            }
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

    if (n == 1) {
        Grayscale(img);
        cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
    }
    else if (n == 4) {
        string file2;
        cout << "Enter second image file name: ";
        cin >> file2;
        Image img2(file2);
        if (!img2.loadNewImage(file2)) {
            cout << "Error: Second file not found.\n";
            return 1;
        }
        Image result(0, 0);
        mergeImages(img, img2, result);
        cout << "Enter output file name: ";
        cin >> filename;
        result.saveImage(filename);
    }
    else if (n == 7) {
        double percent;
        cout << "Enter lighting change (-50 to 50): ";
        cin >> percent;
        filterLightDark(img, percent);
        cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
    }
    else if (n == 10) {
        detectEdges(img);
        cout << "Enter new file name: ";
        cin >> filename;
        img.saveImage(filename);
        cout << "Edge detection done!\n";
    }

   
   
   

   

             if (n==2){
                 BlackandWhite(img);
                 img.saveImage("output.png");
                 cout << "Saved output.png\n";
             }

             else if(n==5){
                 FlipImage(img);
                 img.saveImage("output.png");
                 cout << "Saved output.png\n";
             }
             else if(n==8){
                 CropImages(img);
                 img.saveImage("output.png");
                 cout << "Saved output.png\n";
             }
             else if(n==11){
                 ResizingImages(img);
                 img.saveImage("output.png");
                 cout << "Saved output.png\n";
             }


    return 0;
}