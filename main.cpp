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
            << "10: Detect Image Edges\n"
            << "11: Resizing Images\n"
            << "12: Blur Image\n";


    int n ;
    cin >> n;


     return 0;
}
