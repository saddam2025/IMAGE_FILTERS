#include <iostream>
#include <string>
#include"Image_Class.h"
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


int main(){
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
            << "6: Rotate Image\n";
            int n ;
            cin >> n;

       if (n == 1) { 
        Grayscale(img);
        cout << "Enter new file name to save: ";
        cin >> filename;
        img.saveImage(filename);
    }
    
    if (n==2){
        BlackandWhite(img);
        img.saveImage("output.png");
        cout << "Saved output.png\n";
            }
       
    if(n==5){
       FlipImage(img);
        img.saveImage("output.png");
        cout << "Saved output.png\n";
    }
      else if (n == 7) {
        
    double percent;
    cout << "Enter lighting change (-50 to 50 for 50% darken/lighten): ";
    cin >> percent;
    filterLightDark(img, percent);
    cout << "Image processed successfully!\n";
      }
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


     return 0;
}
