#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>
#include <opencv2/imgproc/imgproc.hpp>


cv::Mat flatten(cv::Mat imarray){
	for(int j=1;j<imarray.rows-1;j++)
	{
		for (int i=1;i<imarray.cols-1;i++)
		{
			if((int)imarray.at<uchar>(j,i)>128){
				imarray.at<uchar>(j,i)=255;
			}
			else{
				imarray.at<uchar>(j,i)=0;
			}
		}
	}
	return imarray;
}
cv::Mat update(cv::Mat imarray){
	int count;
	bool live=false;
	for(int j=1;j<imarray.rows-1;j++)
	{
		for (int i=1;i<imarray.cols-1;i++)
		{
			count=0;
			for(int x=0;x<3;x++)
			{
				for (int y=0;y<3;y++)
				{
					if((int)imarray.at<uchar>(j-1+x,i-1+y)==0){count++;}

				}
			}
			live=false;
			if((int)imarray.at<uchar>(j,i)==0){
				live=true;
			}
			if(live && count <2){
				imarray.at<uchar>(j,i)=255;
			}
			if(live && count > 3){
				imarray.at<uchar>(j,i)=255;
			}
			if(!live && count == 3){
				imarray.at<uchar>(j,i)=0;
			}


		}
	}
	return imarray;
}

int main()
{
	cv::Mat imarray;
	cv::Mat colorMat = cv::imread("Lenna.png", CV_LOAD_IMAGE_UNCHANGED);
	cv::cvtColor(colorMat, imarray, cv::COLOR_BGR2GRAY);
	imarray=flatten(imarray);
	cv::imshow("Conway's game of life",imarray);
	cv::waitKey(3000);
	int numgens=200;
	for(int i=0;i<numgens; i++){
		imarray=update(imarray);
		cv::imshow("Conway's game of life",imarray);
		cv::waitKey(1);
	}
	//float kernel[3][3]={{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
	//After changing
	//cv::imshow("After",copy);
	//cv::waitKey(2000);
	cv::imwrite("out.jpg", imarray );
	//imarray.release();
	//copy.release();
  	return 0;
}
