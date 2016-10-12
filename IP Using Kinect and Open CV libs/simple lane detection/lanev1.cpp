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

CvScalar hsv_min = cvScalar(0, 0, 190, 0);

CvScalar hsv_max = cvScalar(255, 255, 256, 0);

int leftcount=0,leftacc=10,rightcount=0,rightacc=10,strcount=0,stracc=10;

float leftangle,rightangle;


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
    IplImage*  copythresholded   = cvCreateImage(cvSize(640, 480), IPL_DEPTH_8U, 1);
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




int l,r,i;
float left,right,angle,length;

  CvSeq* lines = 0;
  SerialPutc(ptr,'S');



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
        cvSetImageROI(rgbcopy, rect);
        cvCvtColor(rgbcopy, hsv_frame, CV_RGB2HSV);
        cvInRangeS(hsv_frame, hsv_min, hsv_max, thresholded);
        copythresholded =cvCloneImage( thresholded);

        cvCanny(thresholded, cannyImg, 50, 150, 3);
        thresholded =cvCloneImage( cannyImg );
        CvMemStorage* storage = cvCreateMemStorage(0);


        lines = cvHoughLines2( thresholded, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 40, 50, 30 );


        float slope,sloper,slopel,c,xa,xb,ya,yb;
        l=-1;r=-1;left=0;right=0;
        CvPoint* lane;
        for( i = 0; i < lines->total; i++ )
        {
            lane = (CvPoint*)cvGetSeqElem(lines,i);
            //CvPoint* line2 = (CvPoint*)cvGetSeqElem(lines,i);
            // cvLine( src, line[0], line[1], CV_RGB(255,0,0), 3, 8 );
           // cout<<"  1st point   "<<lane[0].x<<"   "<<lane[0].y<<"  2nd point   "<<lane[1].x<<"   "<<lane[1].y<<endl;
            slope=((float)lane[1].y - (float)lane[0].y) / ((float)lane[1].x - (float)lane[0].x);
           // cout<<"  slope=  "<<slope<<endl;
            angle= atan(slope);
           // cout<<"  angle= "<<angle*180/3.142<<endl;
            length=sqrt(((float)lane[1].x - (float)lane[0].x)*((float)lane[1].x - (float)lane[0].x)+((float)lane[1].y - (float)lane[0].y)*((float)lane[1].y - (float)lane[0].y) );
           // cout<<"  length=  "<<length<<endl;
            if(slope > 0 )
            {
               // cout<<" right lane "<<endl;
                if(length>right)
                {
                    right=length;
                    r=i;
                    sloper=slope;
                }
            }
            else
            {
                if(length>left)
                {
                    left=length;
                    l=i;
                    slopel=slope;
                }
            }
        }







        CvPoint line;
        CvPoint linea ;
        CvPoint line2 ;
        CvPoint line2a ;
        if(l==-1 && r==-1)
        {
            cout<<"  no lanes  "<<endl;
            line.x=x11;
            line.y=y22;
            linea.x=x11;
            linea.y=y11;
            line2.x=x22;
            line2.y=y11;
            line2a.x=x22;
            line2a.y=y22;
            /*
            cout<<"  final points=  "<<endl;
            cout<<" left 1st point   "<<line.x<<"   "<<line.y<<"  2nd point   "<<linea.x<<"   "<<linea.y<<endl;
            cout<<" right 1st point   "<<line2.x<<"   "<<line2.y<<"  2nd point   "<<line2a.x<<"   "<<line2a.y<<endl;
            cvLine( frame, line, linea, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, linea, CV_RGB(255,0,0), 3, 8 );
            */
        }
        else if(l==-1)
        {
            cout<<"  no left lanes  "<<endl;
            lane= (CvPoint*)cvGetSeqElem(lines,r);


            line2.x=lane[0].x+x11;
            line2.y=lane[0].y+y11;
            line2a.x=lane[1].x+x11;
            line2a.y=lane[1].y+y11;

            line.x=x11;
            line.y=line2a.y;
            linea.x=x11;
            linea.y=line2.y;



           /*





            c=line2a.y - (sloper*line2a.x);
            xa = (y1-c)/sloper;
            if( xa<=x1)
            {
                line2.x= x1;
            }
            xb = (y2-c)/sloper;
            if( xb>=x1)
            {
                line2a.x= x1;
            }
            */
            /*
            cout<<"  final points=  "<<endl;
            cout<<" left 1st point   "<<line.x<<"   "<<line.y<<"  2nd point   "<<linea.x<<"   "<<linea.y<<endl;
            cout<<" right 1st point   "<<line2.x<<"   "<<line2.y<<"  2nd point   "<<line2a.x<<"   "<<line2a.y<<endl;
            cvLine( frame, line, linea, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, linea, CV_RGB(255,0,0), 3, 8 );
            */
        }
        else if(r==-1)
        {
            cout<<"  no right lanes  "<<endl;
            //CvPoint* linel=(CvPoint*)cvGetSeqElem(lines,i);
            //          CvPoint* liner=(CvPoint*)cvGetSeqElem(lines,i);
            lane = (CvPoint*)cvGetSeqElem(lines,l);
            line.x=lane[0].x+x11;
            line.y=lane[0].y+y11;
            linea.x=lane[1].x+x11;
            linea.y=lane[1].y+y11;

            line2.x=x22;
            line2.y=linea.y;
            line2a.x=x22;
            line2a.y=line.y;
            /*
            cout<<"  final points=  "<<endl;
            cout<<" left 1st point   "<<line.x<<"   "<<line.y<<"  2nd point   "<<linea.x<<"   "<<linea.y<<endl;
            cout<<" right 1st point   "<<line2.x<<"   "<<line2.y<<"  2nd point   "<<line2a.x<<"   "<<line2a.y<<endl;
            cvLine( frame, line, linea, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, linea, CV_RGB(255,0,0), 3, 8 );
            */
        }
        else
        {
            //CvPoint*
            lane = (CvPoint*)cvGetSeqElem(lines,l);
            //CvPoint*
            line.x=lane[0].x+x11;
            line.y=lane[0].y+y11;
            linea.x=lane[1].x+x11;
            linea.y=lane[1].y+y11;
            lane = (CvPoint*)cvGetSeqElem(lines,r);
            line2.x=lane[0].x+x11;
            line2.y=lane[0].y+y11;
            line2a.x=lane[1].x+x11;
            line2a.y=lane[1].y+y11;
            /*
            cout<<"  final points=  "<<endl;
            cout<<" left 1st point   "<<line.x<<"   "<<line.y<<"  2nd point   "<<linea.x<<"   "<<linea.y<<endl;
            cout<<" right 1st point   "<<line2.x<<"   "<<line2.y<<"  2nd point   "<<line2a.x<<"   "<<line2a.y<<endl;
            cvLine( frame, line, linea, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line, line2a, CV_RGB(255,0,0), 3, 8 );
            cvLine( frame, line2, linea, CV_RGB(255,0,0), 3, 8 );
            */
        }

cvLine( rgbcopy, line, linea, CV_RGB(255,0,0), 3, 8 );
cvLine( rgbcopy, line2, line2a, CV_RGB(255,0,0), 3, 8 );
cvLine( rgbcopy, line, line2a, CV_RGB(255,0,0), 3, 8 );
cvLine( rgbcopy, line2, linea, CV_RGB(255,0,0), 3, 8 );

  slope=((float)line.y - (float)linea.y) / ((float)line.x - (float)linea.x);
            leftangle= atan(slope);
            leftangle=leftangle*180/3.142;
            if(leftangle > 0.00)
            leftangle=-leftangle;
cout<<"leftangle="<<leftangle<<endl;


            slope=((float)line2.y - (float)line2a.y) / ((float)line2.x - (float)line2a.x);
            rightangle= atan(slope);
            if(rightangle < 0.00)
            rightangle=-rightangle;
            rightangle=rightangle*180/3.142;
cout<<"rightangle="<<rightangle<<endl;



if((rightangle+leftangle)> 5)
            {

                cout<<"right turn"<<endl;
                txchar2=(char)80;

                txchar=(char)rightacc;
            }

            else if((rightangle+leftangle)< -5)
            {

                cout<<"left turn"<<endl;
                txchar2=(char)20;

                txchar=(char)leftacc;
            }


            else
            {


                cout<<"straight"<<endl;
                txchar2=(char)54;

                txchar=(char)stracc;

            }











        cvReleaseMemStorage(&storage);
        cvReleaseImageHeader(&rgb32);
        cvReleaseImage(&grey);
        cvReleaseImageHeader(&depth32);


        if( (cvWaitKey(10) & 255) == 27 ) break;

    }


    free(rgb32_data);
    free(depth32_data);
    cvDestroyWindow( "mywindow" );


}

