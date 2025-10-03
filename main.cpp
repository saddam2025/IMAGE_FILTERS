#include <iostream>
#include <string>
#include"Image_Class.h"
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
 }
}

//Filter 8: Crop Images
void CropImages(Image &img){
    int width = img.width;
    int height = img.height;
    int channels = img.channels;

    int x,y,w,h ;
    cout << "Enter starting point (x y):" ;
    cin >> x >> y ;
    cout << "Enter crop width and height:" ;
    cin >> w >>h ;

    if (x < 0 || y < 0 || x + w > width || y + h > height) {
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
