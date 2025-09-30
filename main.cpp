#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;

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

    cout << "You chose option " << n << endl;

    return 0;
}