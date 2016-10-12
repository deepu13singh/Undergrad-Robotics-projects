#include "stdafx.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "try11.h"


#include <stdio.h>

#include <iostream>
using namespace std;

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>

#include <math.h>

#include <float.h>

#include <limits.h>

#include <time.h>

#include <windows.h>

#include <ctype.h>

#include <tchar.h>

#include<conio.h>


int x11,y11,x22,y22;
char MAIN[]="COM2";

void PrintCommState(DCB dcb)
{
    //  Print some of the DCB structure values
    _tprintf(TEXT("\nBaudRate = %d, ByteSize = %d, Parity = %d, StopBits = %d\n"),
        dcb.BaudRate,
        dcb.ByteSize,
        dcb.Parity,
        dcb.StopBits
        );
}

void SerialPutc(HANDLE *hCom, char txchar)
{
BOOL bWriteRC;
static DWORD iBytesWritten;

bWriteRC = WriteFile(*hCom, &txchar, 1, &iBytesWritten,NULL);
if(!bWriteRC)
{
    printf("error");
}
cout<<bWriteRC;
return;
}

char SerialGetc(HANDLE *hCom)
{
char rxchar;
BOOL bReadRC;
static DWORD iBytesRead;

bReadRC = ReadFile(*hCom, &rxchar, 1, &iBytesRead, NULL);
if(!bReadRC)
{
    printf("error");
}
return rxchar;
}


int main()
{
    PBYTE rgb32_data = (PBYTE) malloc(640*480*(24/8));
    PDWORD depth32_data = (PDWORD) malloc(640*480*4);

    CLNUICamera cam = CreateNUICamera(GetNUIDeviceSerial(0));
    CLNUIMotor motor = CreateNUIMotor(GetNUIDeviceSerial(0));

    StartNUICamera(cam);

    cvNamedWindow("Image", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Depth", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Grey", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Depthrgb", CV_WINDOW_AUTOSIZE);

    IplImage* rgbcopy ;
    IplImage * red = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * green = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * blue = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage * alpha = cvCreateImage(cvSize(640, 480), 8, 1);
    IplImage *rgb32 = cvCreateImageHeader(cvSize(640, 480), 8, 3);
    IplImage *grey;
    IplImage *depth = cvCreateImage(cvSize(640, 480), 8, 3);
    IplImage *depth32 = cvCreateImageHeader(cvSize(640, 480), 8, 4);

    //lane detection images
    IplImage *  hsv_frame    = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 3);
    IplImage*  thresholded   = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
    IplImage* cannyImg = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);

    //area or boundary of lane detection
    CvRect rect = cvRect(x11,y11,x22,y22);






//Serial communication for movement initiation

    DCB dcb;//ip
    HANDLE hCom;//ip
    BOOL fSuccess;//ip

   TCHAR *pcCommPort = TEXT(MAIN); //  Most systems have a COM1 port for ip


   //  Open a handle to the specified com port.
   hCom = CreateFile( pcCommPort,
                    GENERIC_READ | GENERIC_WRITE,
                    0,    //  must be opened with exclusive-access
                    NULL, //  default security attributes
                    OPEN_EXISTING, //  must use OPEN_EXISTING
                    FILE_ATTRIBUTE_NORMAL,NULL//  hTemplate must be NULL for comm devices
                    );

   if (hCom == INVALID_HANDLE_VALUE)
   {
       //  Handle the error.
       printf ("CreateFile failed with error %d.\n", GetLastError());
       return (1);
   }
    SetupComm(hCom, 2, 128);

   dcb.DCBlength = sizeof(DCB);

   fSuccess = GetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("GetCommState failed with error %d.\n", GetLastError());
      return (2);
   }

   dcb.BaudRate = CBR_9600;     //  baud rate
dcb.ByteSize =8;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;

   fSuccess = SetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("SetCommState failed with error %d.\n", GetLastError());
      return (3);
   }

   //  Get the comm config again.
   fSuccess = GetCommState(hCom, &dcb);

   if (!fSuccess)
   {
      //  Handle the error.
      printf ("GetCommState failed with error %d.\n", GetLastError());
      return (2);
   }

   PrintCommState(dcb);       //  Output to console

   char txchar=14,txchar2=54;
   HANDLE *ptr=&hCom;

//end of initiation








    while(1)
     {
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


        rgbcopy = cvCloneImage( rgb32 );    //copy of rgb image for lane detection


        cvReleaseImageHeader(&rgb32);
        cvReleaseImage(&grey);
        cvReleaseImageHeader(&depth32);

        if( (cvWaitKey(10) & 255) == 27 ) break;

    }


    free(rgb32_data);
    free(depth32_data);
    cvDestroyWindow( "mywindow" );


}

