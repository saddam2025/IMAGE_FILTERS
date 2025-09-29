#include <iostream>
#include <exception>
#include "Image_Class.h"
using namespace std;

int main() {
    try {
        cout << "Image processing program started!" << endl;
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}