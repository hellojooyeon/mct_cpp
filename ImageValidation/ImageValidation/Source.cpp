int *width_hist = { 0 };
int histmax = 20;
void scale_setting(int width, int height)
{
	int count = 0;
	int state = 0;

	width_hist = (int*)malloc(sizeof(int)*width);

	for (int i = 0; i < width; i++)
	{
		width_hist[i] = 0;
	}

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (flagRed[j*width + i] != 0)
			{
				count++;
				state = (state == 1 ? 1 : state + 1);
			}
			else
			{
				if (count != 0) state -= 1;
			}

			if (state <= -2 || i == width - 1)
			{
				if (count != 0) width_hist[count]++;
				count = 0;
				state = 0;
			}
		}
	}

	//int histmax = 1;
	histmax = 20;
	int h_width = 0;
	for (int i = histmax + 1; i < width; i++)
	{
		if (width_hist[histmax] < width_hist[i]) histmax = i;
		if (width_hist[i] == 0 && width_hist[i - 1] != 0) h_width = i;
	}

	Mat histogram_w = Mat(width_hist[histmax], h_width, CV_8UC3, Scalar(0));

	for (int i = 0; i < h_width; i++)
	{
		//cout<<width_hist[i]<<"\t";
		for (int j = 0; j < width_hist[histmax]; j++)
		{
			histogram_w.at<unsigned char>((width_hist[histmax] - j - 1), i * 3) = (width_hist[i] > j ? 255 : 0);
			histogram_w.at<unsigned char>((width_hist[histmax] - j - 1), i * 3 + 1) = (width_hist[i] > j ? 255 : 0);
			histogram_w.at<unsigned char>((width_hist[histmax] - j - 1), i * 3 + 2) = (width_hist[i] > j ? 255 : 0);
		}
	}

	//	imshow("test", histogram_w);
	imwrite("test.bmp", histogram_w);
	//cvWaitKey();

}
