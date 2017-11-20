#include <opencv2\opencv.hpp>
#include <stdint.h>
#include "WhiteBalance.hpp"
#include <math.h>

using namespace cv;
using namespace std;

int main()
{
	// load images
	Mat img[5][5];
	int i, r, c, j, k, l;

	string filename;

	// without WB
	for (i = 0; i < 5; i++)
	{
		filename = "pic/cut/cloudy0" + to_string(i + 1) + ".jpg";
		img[0][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/sun0" + to_string(i + 1) + ".jpg";
		img[1][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/shadow0" + to_string(i + 1) + ".jpg";
		img[2][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/incande0" + to_string(i + 1) + ".jpg";
		img[3][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/fluore0" + to_string(i + 1) + ".jpg";
		img[4][i] = imread(filename, CV_LOAD_IMAGE_COLOR);
	}
		
	// automatic wb
	/*for (i = 0; i < 5; i++)
	{
		filename = "pic/cut/cloudyWB0" + to_string(i + 1) + ".jpg";
		img[0][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/sunWB0" + to_string(i + 1) + ".jpg";
		img[1][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/shadowWB0" + to_string(i + 1) + ".jpg";
		img[2][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/incandeWB0" + to_string(i + 1) + ".jpg";
		img[3][i] = imread(filename, CV_LOAD_IMAGE_COLOR);

		filename = "pic/cut/fluoreWB0" + to_string(i + 1) + ".jpg";
		img[4][i] = imread(filename, CV_LOAD_IMAGE_COLOR);
	}*/

	float data[5][5][4][3] = {0.0f};
	float g = 2;

	// each picture
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			// patches: four corners
			for (r = 0; r < 20; r++)
			{
				for (c = 0; c < 20; c++)
				{
					const auto& white = img[i][j].at<Vec3b>(r, c);
					data[i][j][0][0] += pow((float)white[0], g);
					data[i][j][0][1] += pow((float)white[1], g);
					data[i][j][0][2] += pow((float)white[2], g);

					const auto& blue = img[i][j].at<Vec3b>(r, img[i][j].cols - c - 1);
					data[i][j][1][0] += pow((float)blue[0], g);
					data[i][j][1][1] += pow((float)blue[1], g);
					data[i][j][1][2] += pow((float)blue[2], g);

					const auto& yellow = img[i][j].at<Vec3b>(img[i][j].rows - r - 1, c);
					data[i][j][2][0] += pow((float)yellow[0], g);
					data[i][j][2][1] += pow((float)yellow[1], g);
					data[i][j][2][2] += pow((float)yellow[2], g);
					
					const auto& red = img[i][j].at<Vec3b>(img[i][j].rows - r - 1, img[i][j].cols - c - 1);
					data[i][j][3][0] += pow((float)red[0], g);
					data[i][j][3][1] += pow((float)red[1], g);
					data[i][j][3][2] += pow((float)red[2], g);
				}
			}
			
			for (k = 0; k < 4; k++)
			{
				for (l = 0; l < 3; l++)
				{
					data[i][j][k][l] /= 400.0f;
				}
			}
		}
	}

	WhiteBalancer wbr(5, 5, 4);
	wbr.normalize(data);

	wbr.writeToFile(data, "original.txt");
	//wbr.writeToFile(data, "autoWhiteBalance.txt");

	//wbr.greyPatch(data, false, "greyPatch.txt");
	//wbr.greyWorld(data, false, "greyWorld.txt");
	//wbr.whiteWorld(data, false, "whiteWorld.txt");

	//wbr.greyPatch(data, true, "greyPatchSpecRemoved.txt");
	//wbr.greyWorld(data, true, "greyWorldSpecRemoved.txt");
	//wbr.whiteWorld(data, true, "whiteWorldSpecRemoved.txt");

	return 0;
}
