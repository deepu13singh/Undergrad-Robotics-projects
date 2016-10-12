#include "stdafx.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "try11.h"


using namespace std;

void displayKinectImage();

int main()
{
    displayKinectImage();
}

void displayKinectImage()
{
    PBYTE rgb32_data = (PBYTE) malloc(640*480*(24/8));
    PDWORD depth32_data = (PDWORD) malloc(640*480*4);
   // PBYTE depth32_data = (PBYTE) malloc(640*480*(24/8));

    CLNUICamera cam = CreateNUICamera(GetNUIDeviceSerial(0));
    CLNUIMotor motor = CreateNUIMotor(GetNUIDeviceSerial(0));

    StartNUICamera(cam);

    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Depth", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Grey", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Depthrgb", CV_WINDOW_AUTOSIZE);


    IplImage * red = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * green = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * blue = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * alpha = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage *rgb32 = cvCreateImageHeader(cvSize(640, 480), 8, 3);
    IplImage *grey;
    IplImage *depth = cvCreateImage(cvSize(640, 480), 8, 3);
    IplImage *depth32 = cvCreateImageHeader(cvSize(640, 480), 8, 4);;

    do {
        GetNUICameraColorFrameRGB24(cam, rgb32_data);
        GetNUICameraDepthFrameRGB32(cam, depth32_data);

        rgb32 = cvCreateImageHeader(cvSize(640,480), 8, 3);
        grey = cvCreateImage(cvSize(640, 480), 8, 1);
        depth32 = cvCreateImageHeader(cvSize(640, 480), 8, 4);

        cvSetData(rgb32, rgb32_data, rgb32->widthStep);
        cvSetData(depth32, depth32_data, depth32->widthStep);

        // Convert RGB32 to greyscale
        cvCvtColor(depth32, grey, CV_RGB2GRAY);

        cvShowImage("Image", rgb32);
        cvShowImage("Grey", grey);
        cvShowImage("Depth", depth32);

        cvCvtPixToPlane(depth32,red,green,blue,alpha);
        cvCvtPlaneToPix(red,green,blue, 0, depth);
        cvShowImage("Depthrgb", depth);

        cvReleaseImageHeader(&rgb32);
        cvReleaseImage(&grey);
        cvReleaseImageHeader(&depth32);

        cvWaitKey(1);

    } while (!GetAsyncKeyState(0x50));


    free(rgb32_data);
    free(depth32_data);

    //StopNUICamera(cam);

    //DestroyNUIMotor(motor);

    //DestroyNUICamera(cam);

}
