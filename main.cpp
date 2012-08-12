#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#include "MeanShift.h"

using namespace cv;


int main(int argc, char* argv[])
{
	IplImage *img = cvLoadImage("input.png");

	// Mean shift
	int **ilabels = new int *[img->height];
	for(int i=0;i<img->height;i++) ilabels[i] = new int [img->width];
	int regionCount = MeanShift(img, ilabels);
	vector<int> color(regionCount);
	CvRNG rng= cvRNG(cvGetTickCount());
	for(int i=0;i<regionCount;i++)
		color[i] = cvRandInt(&rng);

	// Draw random color
	for(int i=0;i<img->height;i++)
		for(int j=0;j<img->width;j++)
		{ 
			int cl = ilabels[i][j];
			((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 0] = (color[cl])&255;
			((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 1] = (color[cl]>>8)&255;
			((uchar *)(img->imageData + i*img->widthStep))[j*img->nChannels + 2] = (color[cl]>>16)&255;
		}

	cvNamedWindow("MeanShift",CV_WINDOW_AUTOSIZE);
	cvShowImage("MeanShift",img);

	cvWaitKey();

	cvDestroyWindow("MeanShift");

	cvReleaseImage(&img);

	return 0;
}
