#include"cv.h"
#include<system.h>
#include "cxcore.h"
#include <stdio.h>
#include <sys/alt_alarm.h>
#include <unistd.h>
#include "altera_avalon_pio_regs.h"
#include <alt_types.h>
#include <sys/alt_cache.h>
#include <altera_avalon_mailbox.h>
#include<altera_avalon_mailbox_regs.h>



enum marker_colour{ pink , green /*, orange, yellow */} ;
typedef struct Coordinates {
  int  x	;
  int  y	;
  int area	;
};

Coordinates pink_color;
Coordinates green_color;
Coordinates pink_color_last;
Coordinates green_color_last;
Coordinates pink_color_last_last;
Coordinates green_color_last_last;


int minArea = 170 ;// 0.1*total area = 0.1*640*480=30720
int maxArea = 30720 ;//  0.0005*total area = 0.0005*640*480=170
int counterCAM = 0 ; /*this counter for the static gesture due to not to be detected more than one timestart 0 end 10 frames .*/
int countpink=0;
int countgreen=0;
int countclose=0;
int y_pink=0;
int y_green=0;
int flag=0;
alt_u32 HSV_MAT_Arr[307200];
void get_marker_center( IplImage* img_HSV ,enum marker_colour,struct Coordinates *xCor ,int tot_area );
void modifyCoordinates();
void getState(struct Coordinates pink ,struct Coordinates green,bool state[]);
int checkGesture(bool state[]);
void mouseFn();
void leftClickFn();
void rightClickFn();

marker_colour y ;


int main()
{
	alt_mailbox_dev* send_dev;
	send_dev = altera_avalon_mailbox_open(MAILBOX_0_NAME);
	int Report[4];
	int report;


	 alt_u32 s_message = 0;
	 int shiftedValueOfX,shiftedValueOfY;
	 int diffX  ;
	 int diffY  ;
		int time = 0;
		IplImage* img_IN = 0;
		IplImage* img_HSV = 0;
		int status = 0;
		CvSize siz;
		siz.height=480;
		siz.width=640;
		alt_u32 pixel = 0;
		alt_u32 prev_frame = 0;
		green_color_last.x	= 0 		;
		green_color_last.y	= 0		;
		pink_color_last.x	= 0		;
		pink_color_last.y = 0;

		green_color_last_last.x	= 0 		;
		green_color_last_last.y	= 0		;
		pink_color_last_last.x	= 0		;
		pink_color_last_last.y = 0;



		while(1){
			//time = alt_nticks()	;
			printf("start time = %d \n",time);

			//init
			pink_color.x=0;
			pink_color.y=0;
			green_color.x=0;
			green_color.y=0;
			pixel = 0;
			prev_frame = 0;
			img_IN = 0;
			img_HSV = 0;
			status = 0;
			Report[0]=0x00;
			Report[1]=0x00;
			Report[2]=0x00;
			Report[3]=0x00;
			report=0;
			/////////////////////////

		  IOWR_ALTERA_AVALON_PIO_DATA(FRAME_REQ_BASE,0);
		  prev_frame = IORD_ALTERA_AVALON_PIO_DATA(FRAME_COUNT_BASE);
		  while(IORD_ALTERA_AVALON_PIO_DATA(FRAME_COUNT_BASE) == prev_frame )
		     {
			  // printf(" STILL IN FRAME = %u ",prev_frame);
		     }

		  prev_frame = IORD_ALTERA_AVALON_PIO_DATA(FRAME_COUNT_BASE);

		  IOWR_ALTERA_AVALON_PIO_DATA(FRAME_REQ_BASE,1);
		  while(IORD_ALTERA_AVALON_PIO_DATA(FRAME_COUNT_BASE) < (prev_frame + 1))
		   {
				 //printf(" moved to  FRAME = %u ",prev_frame);

		   }

		  IOWR_ALTERA_AVALON_PIO_DATA(FRAME_REQ_BASE,0);

		  printf(" FINISHED AND FRAME_COUNT %u \n", IORD_ALTERA_AVALON_PIO_DATA(FRAME_COUNT_BASE));


		  alt_dcache_flush_all();

		//alt_u8 *sram = (alt_u8 *)0x10200000;
		//////////////////////////////////////////////////////////////////////
		img_IN = cvCreateImage( siz , IPL_DEPTH_8U, 4,true);
		img_IN->imageData= 		 (char *) 0x10200000 ;
		img_IN->imageDataOrigin= (char *)0x10200000 ;
		img_IN->widthStep=2560 ;
		//img_IN->widthStep=3200 ;
		img_IN->nChannels= 4 ;
		img_IN->align=4;
		img_IN->dataOrder=0;


/*
			for(int y=0;y<20;y++)
			{
				R=cvGet2D(img_IN,y,y).val[2];
				G=cvGet2D(img_IN,y,y).val[1];
				B=cvGet2D(img_IN,y,y).val[0];
				printf(" %d %d %d \n",B,G,R);

			}
			*/
		//IplImage* img_HSV = cvCreateImage(  siz, 8, 3);// points to the HSV image

		/*img_HSV = cvCreateImage( siz, IPL_DEPTH_8U, 3,false);// points to the HSV image
		img_HSV->widthStep=1920 ;
		//img_IN->widthStep=3200 ;
		img_HSV->nChannels= 3 ;
		img_HSV->align=4;
		img_HSV->dataOrder=0;*/
		//printf("before  cvcvtcolor \n");
		//time = alt_nticks()	;
				//printf(" before cvcvt  time = %d \n",time);
		 int i ;
			 void * addr_RGB_img  = (void *)0x10200000 ;

			// addr_HSV_img = (alt_u32*)malloc ( 640 * 480 * sizeof(*addr_HSV_img));
			 alt_u32 outputHSV;
			 alt_u32  param ;

			 int counterOfAddr = 0 ;
			 for (  i=0  ;i < (307200) ; i++,counterOfAddr+=4)
		    {
				 param = 0 ;
				 param =  (   ( (*((alt_u8*)addr_RGB_img+counterOfAddr))<<24 ) | ((*((alt_u8*)addr_RGB_img+counterOfAddr+1))<<16) | ((*((alt_u8*)addr_RGB_img+counterOfAddr+2))<<8)   ) ;
				 HSV_MAT_Arr[i]= ALT_CI_RGB2HSV_INST(param,0);
				 HSV_MAT_Arr[i]= ALT_CI_RGB2HSV_INST(param,0);


		   }

		//cvCvtColor(img_IN, img_HSV, CV_BGR2HSV);
		//time = alt_nticks()	;
				//printf("after cvcvt time = %d \n",time);
		//printf("before  cvcvtcolor \n");
		int tot_area = img_IN->height*img_IN->width; // 3shan lw area bta3et el sora bete5telef//

		int max = 0;


		bool state[4]	=	{	false	,	false	,	false	,	false	}	;


		////////////////////////////////////////////////////pink marker/////////////////////////////////////////////////////////////
		y = pink ;
	//	printf("before  get_marker_center pink \n");
		get_marker_center(img_HSV	,	y	, &pink_color,tot_area);
	/////////////////////////////////////////////////Green marker/////////////////////////////////////////////////////////////
		y = green ;
		//printf("before  get_marker_center green \n");
	get_marker_center(img_HSV	,	y	, &green_color,tot_area);



		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//	printf("before  get state \n");
		getState(pink_color,green_color,state);
	//	printf(" status %d %d  /n ",state[0],state[3]);
		 status	=	checkGesture(state);

		 printf("pink = %d  green = %d \n",state[3],state[1]);
		printf(" status %d  /n ",status);
	/*	switch ( status )
		{
		case 1 :
			{
				mouseFn();
					break	;
			 }
		case 2 :
			{
				leftClickFn();
				break	;
			}
		case 3 :
			{
				rightClickFn();
				break	;
			}*/
		if(status !=0)
		{
			if(status == 1)
			 {
				if( pink_color_last.x!=0 && pink_color_last.y!=0 )
					{
						// calculate differnece between frames .
						//	printf("current x %d  ,  last x %d\n",pink_color.x,pink_color_last.x);
						//	printf("current y %d  ,  last y %d\n",pink_color.y,pink_color_last.y);
							int diffX = pink_color.x - pink_color_last.x ;
							int diffY = pink_color.y - pink_color_last.y ;
							printf("diffX %d diffY %d\n",diffX,diffY);

						// calculate relative difference .
							shiftedValueOfX = (((double)(diffX-320)*254)/(double)640.0)+127 ;
							shiftedValueOfY = (((double)(diffY-240)*254)/(double)480.0)+127 ;
						}
					else
						{
							shiftedValueOfX  = 5	;
							shiftedValueOfY  = 5	;
						}
					printf("shiftedValueOf X:%d Y:%d \n",shiftedValueOfX,shiftedValueOfY);

					Report[1]=(shiftedValueOfX+127)<<8;
					Report[2]=(shiftedValueOfY+127)<<16;
					Report[0]=0;

			 }
			 else if (status == 2) //left click
			 {
				Report[0]=1;
				Report[1]=0;
				Report[2]=0;
			 }
			 else if (status == 3)//right click
			 {
				Report[0]=2;
				Report[1]=0;
				Report[2]=0;
			 }

			 s_message=report|Report[0]|Report[1]|Report[2];
			 altera_avalon_mailbox_post(send_dev, s_message);
			 altera_avalon_mailbox_post(send_dev, s_message);
			 altera_avalon_mailbox_post(send_dev, s_message);
			 altera_avalon_mailbox_post(send_dev, s_message);
			 printf("sent : %d \n ",s_message);
		}



		modifyCoordinates();


		time = alt_nticks()	;
		cvReleaseImage(&img_HSV);
		//cvReleaseImage(&img_IN);
		printf("End time = %d \n",time);
		}
	return 0 ;

}

 // x is enum yellow or orange green or pink

void get_marker_center( IplImage* img_HSV ,enum marker_colour x,struct Coordinates *xCor,int tot_area )
  {
	 char const * temp;
	 int time;
	 CvSize siz;
	siz.height=480;
	siz.width=640;
	 //IplImage* img_after_thresholding = cvCreateImage( siz, 8, 1, false);//points to the thresholded image
	 IplImage* img_OUT = cvCreateImage(siz , 8, 1,false);//points to  the output image


	    int cc =0 ;

	    alt_u16 *   ptr = (alt_u16*)malloc ( 640 * 480 * sizeof(*ptr));


		IplImage* img_after_thresholding = cvCreateImage( siz, 8, 1, false);//points to the thresholded image
		 img_after_thresholding->imageData= 		 (char *) ptr;
		 img_after_thresholding->imageDataOrigin= (char *)ptr;

	    alt_u32   param1 ;
	    alt_u32   param2 ;
	    alt_32   outputused ;
	    uchar zz1 ,zz2;
	 CvMemStorage* storage = cvCreateMemStorage(0);//for findcontour function
     CvSeq* first_contour = 0;//for findcontour function its a pointer to a linked list



	 switch(x)
	 {

		 case green  :
						{
							int i = 0 ;
							int j = 0 ;
							int cc = 0 ;
							for( cc=0; cc < 640*480 ; cc+=2 )
							{
								 param1 = HSV_MAT_Arr[cc];
								 param2 = HSV_MAT_Arr[cc+1];
									outputused= ALT_CI_CVINRANGE_GREEN_INST(param1,param2);
									*ptr = outputused ;

									ptr= ptr+1;
							}
							//time = alt_nticks()	;
							//printf("before cvinrange  time = %d \n",time);
							//cvInRangeS(img_HSV, cvScalar(50, 60, 60, 0), cvScalar(80, 300, 300, 0), img_after_thresholding);//this range of green color el marker el gdeed
							//time = alt_nticks()	;
							//printf("after cvinrange  time = %d \n",time);
							break;
						}

		 case pink    :
						{
							int i = 0 ;
							int j = 0 ;
							int cc = 0 ;

							 for(cc=0 ; cc<640*480; cc+=2)
							 {
								 param1 = HSV_MAT_Arr[cc];
								param2 = HSV_MAT_Arr[cc+1];
								outputused = ALT_CI_CVINRANGE_INST(param1,param2);
								*ptr = outputused ;

							   ptr=ptr+1;
							}


						//time = alt_nticks()	;
						//printf("before cvinrange  time = %d \n",time);
						//cvInRangeS(img_HSV, cvScalar(160, 100, 100, 0), cvScalar(185, 300, 300, 0), img_after_thresholding);//this range of pink color

						//time = alt_nticks()	;
						//printf("after cvinrange  time = %d \n",time);
						break;
						}


	 }

	//linked list of each contor the return content//,sizeof(CvContour),CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE,cvPoint(0, 0));
	 //time = alt_nticks()	;
	// printf("before  cvFindContours time = %d \n",time);
	  cvFindContours(img_after_thresholding,storage,&first_contour);
	  //time = alt_nticks()	;
	  //printf("after  cvFindContoursand before cvzero time = %d \n",time);
      cvZero( img_OUT );
      //time = alt_nticks()	;
      //printf("after  cvzero time = %d \n",time);

	   //  CV_RETR_CCOMP : changed to --> CV_RETR_EXTERNAL in order to "retriving only the extreme outer contours"
	  // because CV_RETR_CCOMP retrieves also the hole which isn't wanted in our case.
	 // cvPoint(0, 0) : added because we use the full image not ROI so we don't need any offset or shifting.
	   double area	=	0	;

	   static int Center_X = 0;
	   static int Center_Y = 0;
		 double cvContourAreaCalc ;
		 //time = alt_nticks()	;
		//printf("before  loop time = %d \n",time);
	   if(first_contour) // hna 3lashan law ml2tsh 7agaa aslun
	   {
		   cvContourAreaCalc = cvContourArea(first_contour,CV_WHOLE_SEQ);
		 while ( cvContourAreaCalc >(0.1*tot_area)|| cvContourAreaCalc <0.0005*tot_area)
		   {
				   if(first_contour->h_next)
						{
							first_contour = first_contour->h_next;
							 cvContourAreaCalc = cvContourArea(first_contour,CV_WHOLE_SEQ);


						}
				   else
					   break ;
			   }
		 //time = alt_nticks()	;
		 //printf("after while loop time = %d \n",time);
		 // cvContourAreaCalc = cvContourArea(first_contour,CV_WHOLE_SEQ) ;
		 if(!( cvContourAreaCalc >(maxArea) || cvContourAreaCalc < minArea))
		 {

				   CvScalar color = CV_RGB( rand(), rand(), rand() );
    			   cvDrawContours( img_OUT, first_contour, color, color, -1, CV_FILLED, 8 );//this one will draw the contour i have found


			///////////////////////////////////////////////Calculating Center/////////////////////////////////////////////////////
				 CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
	    		cvMoments(img_OUT, moments, 1);

			// The actual moment values
	    		 //time = alt_nticks()	;
	    		 //printf("before cvGetSpatialMoment  time = %d \n",time);
				double moment10 = cvGetSpatialMoment(moments, 1, 0);
				 //time = alt_nticks()	;
				//printf("after  cvGetSpatialMoment  time = %d \n",time);
				double moment01 = cvGetSpatialMoment(moments, 0, 1);
				 //time = alt_nticks()	;
				//printf("before  cvGetCentralMoment  time = %d \n",time);
				area = cvGetCentralMoment(moments, 0, 0);
				 //time = alt_nticks()	;
				//printf("after  cvGetCentralMoment and before division  time = %d \n",time);
				Center_X = (int)moment10/area;
				Center_Y = (int)moment01/area;
				//printf("after   division  time = %d \n",time);
				xCor->x		=	Center_X	;
			    xCor->y		=	Center_Y	;
			    xCor->area	=	(int)cvContourAreaCalc	;
			  }
			  	/////////////////////////////////////////////// end if ///////////////////////////////////////////////////////
			  else
			  {
					xCor->x		=	0	;
					xCor->y		=	0	;
					xCor->area	=	0	;
			  }



	   }
	   //time = alt_nticks()	;
	  // printf("after  looping  time = %d \n",time);


	 //cvReleaseImage(&img_after_thresholding);
	 cvReleaseImage(&img_OUT);



  }
  /*
   get state is function do ::
   check color found and other not found then get overall state
   state[0]->yellow
   state[1]->green
   state[2]->orange
   state[3]->pink
  */
  void getState(struct Coordinates pink,struct Coordinates green,	bool state[])
{


	if((green.x==0)&&(green.y==0))

		state[1]=0;

	else
			state[1]=1 ;


	if((pink.x==0)&&(pink.y==0))

		state[3]=0;

	else
			state[3]=1 ;


}
  /*
	returned values
	 0	::	HOLD ON
	 1	::	MOUSE
	 2	::	LEFTCLICK
	 3	::	RIGHTCLICK
	 4	::	CLOSE
	 .......
  */
  int checkGesture(bool state[])
{


	if((state[1]==0)&&(state[3]==0))
	{
		return	0	;
	}
	else if((state[1]==0)&&(state[3]==1))
	{
		return 1	; //MOUSE
	}
	else if((state[1]==1)&&(state[3]==1))
	{
		return 2	; //leftclick
	}
	else if((state[1]==1)&&(state[3]==0))
	{
		return 3	; //rightclick
	}


	return	0	;	//HOLD ON

}

void modifyCoordinates()
{
		/////////////////////////// MODIFY COORDINATES ///////////////////////////////////////////////////

			green_color_last_last.x				=	green_color_last.x			;
			green_color_last_last.y				=	green_color_last.y			;
			green_color_last_last.area			=	green_color_last.area		;
			pink_color_last_last.x				=	pink_color_last.x			;
			pink_color_last_last.y				=	pink_color_last.y			;
			pink_color_last_last.area			=	pink_color_last.area		;
			green_color_last.x			=	green_color.x		;
			green_color_last.y			=	green_color.y		;
			green_color_last.area		=	green_color.area	;
			pink_color_last.x			=	pink_color.x		;
			pink_color_last.y			=	pink_color.y		;
			pink_color_last.area		=	pink_color.area		;

	///////////////////////////  END MODIFY COORDINATES ///////////////////////////////////////////////////

}
void mouseFn()
{
	if(pink_color.x!=0)
		{

		 printf("MOUSE X:%d Y:%d \n  ",pink_color.x,pink_color.y);
		}
}
void leftClickFn()
{
	if(pink_color_last_last.x!=0)
		{

		 printf("Left Click X:%d Y:%d \n  ",pink_color.x,pink_color.y);
		}
}
void rightClickFn()
{
	if(green_color_last_last.x!=0)
		{

		 printf("RIGHT CLICK X:%d Y:%d \n  ",green_color.x,green_color.y);
		}
}
