#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace std;
using namespace cv;

void mct()
{
	Mat src = imread("bbb (15).jpg", 3);//src image
	double alpha = 0.3; int beta = 50;//parameter for brightness

	resize(src, src, Size(450, 300), 0, 0, CV_INTER_NN);
	Mat bright = Mat::zeros(src.size(), src.type());

	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				bright.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(src.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	imwrite("bright.jpg", bright);

	Mat gray;//change the color dimension
	cvtColor(bright, gray, CV_RGB2GRAY);
	imwrite("gray.jpg", gray);

	int height = src.rows; int width = src.cols;
	Mat tmpImg = Mat::zeros(src.rows+2, src.cols+2, CV_8U);


	for (int y = 1; y < height+1; y++)
	{
		for (int x = 1; x < width+1; x++)
		{
			tmpImg.at<uchar>(y,x) = gray.at<uchar>(y-1, x-1);
		}
	}//copy the src in gray

	unsigned char result[9] = { 0, };
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 3; i++)
				{
					if (tmpImg.at<uchar>(y + i, x + j)<tmpImg.at<uchar>(y + 1, x + 1))
						result[j*3 + i] = 1;
				}
			}
			int sum = 0;
			for (int k = 0; k < 9; k++)
			{
				 sum+= result[k] * pow(2, 8 - k);//calculate the value
				 result[k] = 0;//initialize result array 
			}
			tmpImg.at<uchar>(y, x) = (unsigned char)sum; 
		}
	}

	imwrite("mct.jpg", tmpImg);//save the mct image

	waitKey();
}
int main()
{
	mct();
	
}
