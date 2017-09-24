//
//  main.cpp
//  tableGammaCorrection
//
//  Created by Alex Musso Rojas on 23-09-17.
//  Copyright © 2017 company. All rights reserved.
//

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

double gammaCorrection(double lum, double gamma){
    return pow(lum/255, gamma) * 255;
}

int main(int argc, const char * argv[]) {
    if(argc < 3){
        cerr << "Usage: ./pixelGammaCorrection img gamma" << endl;
        return 1;
    }
    
    double gamma;
    cv::Mat srcImg, img;
    cv::MatIterator_<cv::Vec3b> it, end;
    double precalculatedTable[256];
    
    // Read input
    gamma = stod(argv[2]);
    srcImg = cv::imread(argv[1], 1);
    if(srcImg.empty()){
        cerr << "Error reading image: " << argv[1] << endl;
        return 1;
    }
    
    // Calculate table
    for(int i=0; i < 256; i++)
        precalculatedTable[i] = gammaCorrection(i, gamma);
    
    // Read image as YUV
    cv::cvtColor(srcImg, img, cv::COLOR_BGR2YUV);
    
    // Apply Gamma Correction for each pixel
    for(it = img.begin<cv::Vec3b>(), end = img.end<cv::Vec3b>(); it != end; it++)
        (*it)[0] = precalculatedTable[(*it)[0]];
    
    // Show images
    /*
    string title = "Correccion Gamma con y = ";
    cv::cvtColor(img, img, cv::COLOR_YUV2BGR);
    cv::imshow("Imagen Original", srcImg);
    cv::imshow(title + argv[2], img);
    cv::waitKey();
     */
    return 0;
}
