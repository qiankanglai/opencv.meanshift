#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"

#define DECLARE_TIMING(s)  int64 timeStart_##s; double timeDiff_##s; double timeTally_##s = 0; int countTally_##s = 0
#define START_TIMING(s)    timeStart_##s = cvGetTickCount()
#define STOP_TIMING(s) 	   timeDiff_##s = (double)(cvGetTickCount() - timeStart_##s); timeTally_##s += timeDiff_##s; countTally_##s++
#define GET_TIMING(s) 	   (double)(timeDiff_##s / (cvGetTickFrequency()*1000.0))
#define GET_AVERAGE_TIMING(s)   (double)(countTally_##s ? timeTally_##s/ ((double)countTally_##s * cvGetTickFrequency()*1000.0) : 0)
#define CLEAR_AVERAGE_TIMING(s) timeTally_##s = 0; countTally_##s = 0

#include <vector>
#include <stack>
#include <iostream>
#include <cmath>

using namespace cv;

// Distance used in Mean Shift
inline int color_distance( const IplImage* img, int x1, int y1, int x2, int y2 ) 
{
	int r = ((uchar *)(img->imageData + x1*img->widthStep))[y1*img->nChannels + 0]
	- ((uchar *)(img->imageData + x2*img->widthStep))[y2*img->nChannels + 0];
	int g = ((uchar *)(img->imageData + x1*img->widthStep))[y1*img->nChannels + 1]
	- ((uchar *)(img->imageData + x2*img->widthStep))[y2*img->nChannels + 1];
	int b = ((uchar *)(img->imageData + x1*img->widthStep))[y1*img->nChannels + 2]
	- ((uchar *)(img->imageData + x2*img->widthStep))[y2*img->nChannels + 2];
	return r*r+g*g+b*b;
}
inline float color_distance( const float* a, const float* b)
{
	float l = a[0]-b[0], u=a[1]-b[1], v=a[2]-b[2];
	return l*l+u*u+v*v;
}
inline float color_distance( const Vec3f& a, const Vec3f& b)
{
	float l = a.val[0]-b.val[0], u=a.val[1]-b.val[1], v=a.val[2]-b.val[2];
	return l*l+u*u+v*v;
}
inline int spatial_distance( const CvPoint& q, const CvPoint& p ) 
{
	int a = q.x-p.x, b=q.y-p.y;
	return a*a+b*b;
}
inline int getLabel( std::vector<int>& unionfind, int l ) 
{
	int r = unionfind[l];
	if(unionfind[r] == r)
		return r;
	else
	{
		unionfind[l] = getLabel(unionfind, unionfind[r]);
		return unionfind[l];
	}
}
inline int getLabel2( std::vector<int>& unionfind, int l ) 
{
	int r = unionfind[l];
	if(r<0)
		return r;
	else
	{
		unionfind[l] = getLabel2(unionfind, r);
		return unionfind[l];
	}
}

const int spatial_radius = 10;
const double color_radius = 6.5;
int MeanShift(const IplImage* img, int **labels);

// RAList from EDISON

class RAList {
	// This is cut from Mean Shift Analysis Library, Implemented by Chris M. Christoudias, Bogdan Georgescu
public:
	int		label;
	RAList	*next;
	RAList( void );
	~RAList( void );
	int Insert(RAList*);

private:
	///////current and previous pointer/////
	RAList	*cur, *prev;
	unsigned char exists;

};
