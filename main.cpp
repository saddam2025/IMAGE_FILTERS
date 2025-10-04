#include <iostream>
#include <string>
#include"Image_Class.h"
using namespace std;
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
            << "6: Rotate Image\n"
            << "7: Darken and Lighten Image\n"
            << "8: Crop Image\n"
            << "9: Adding a Frame to the Picture\n"
            << "10: Detect Image Edges\n";

            int n ;
            cin >> n;

     if (n == 1) { 
        Grayscale(img);
        cout << "Enter new file name to save: ";
        cin >> filename;
        img.saveImage(filename);
    }
    
    else if (n==2){
        BlackandWhite(img);
        img.saveImage("output.png");
        cout << "Saved output.png\n";
            }

      else if (n == 3) {
        invert(img);
        img.saveImage("after_inverted.png");
    } 
     else if (n == 3) {
        invert(img);
        img.saveImage("after_inverted.png");
    }
       
     else if(n==5){
       FlipImage(img);
        img.saveImage("output.png");
        cout << "Saved output.png\n";
    }

      else if (n == 6) {
        int a;
        cout<<"select your angle ( 90 , 180 , 270 , 360 )"<<endl;
        cin>>a;
        rotate(img,a);
        img.saveImage("after_editing.png");
    }
    else if (n == 7) {
    double percent;
    cout << "Enter lighting change (-50 to 50 for 50% darken/lighten): ";
    cin >> percent;
    filterLightDark(img, percent);
    cout << "Image processed successfully!\n";
      }
    else if(n==8){
        CropImages(img);
        img.saveImage("output.png");
        cout << "Saved output.png\n";
    }

     return 0;
}
