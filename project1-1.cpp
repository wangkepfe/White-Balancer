#include <opencv2\opencv.hpp>
#include <stdint.h>
#include <algorithm>

using namespace cv;
using namespace std;

const int N = 19;
void writeDataToFile(float* x, float* y, int N, const string& name);

int main()
{
	// load images
	Mat img[N];
	int i, r, c;
	for (i = 0; i < N; i++)
	{
		string filename = "raw/img" + to_string(i + 1) + ".JPG";
		img[i] = imread(filename, CV_LOAD_IMAGE_COLOR);
	}

	// extract patches
	float vb[N] = { 0.0f }, vg[N] = { 0.0f }, vr[N] = { 0.0f };
	for (i = 0; i < N; i++)
	{
		for (r = 0; r < 20; r++)
		{
			for (c = 0; c < 20; c++)
			{
				const auto& p = img[i].at<Vec3b>(r + img[i].rows / 2 - 10, c + img[i].cols / 2 - 10);
				vb[i] += (float)p[0];
				vg[i] += (float)p[1];
				vr[i] += (float)p[2];
			}
		}
		vb[i] /= 400.0f;
		vg[i] /= 400.0f;
		vr[i] /= 400.0f;
	}

	float t[N] =
	{
		1/10.0,
		1/15.0,
		1/20.0,
		1/30.0,
		1/45.0,
		1/60.0,
		1/90.0,
		1/125.0,
		1/180.0,
		1/250.0,
		1/350.0,
		1/500.0,
		1/750.0,
		1/1000.0,
		1/1500.0,
		1/2088.0,
	    1/3000.0,
		1/4425.0,
		1/6667.0
	};

	writeDataToFile(t, vb, N, "originalBlue.txt");
	writeDataToFile(t, vg, N, "originalGreen.txt");
	writeDataToFile(t, vr, N, "originalRed.txt");

	waitKey();
}

void writeDataToFile(float* x, float* y, int N, const string& name)
{
	ofstream ofs(name);
	int i;
	for (i = 0; i < N; i++)
	{
		ofs << x[i] << " " << y[i];
		ofs << endl;
	}
	ofs.close();
}
