#include "WhiteBalance.hpp"
#include <math.h>
#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

void WhiteBalancer::greyPatch(float data[5][5][4][3], bool removeSpecular, const std::string& filename)
{
	int i, j, k, l;
	if (removeSpecular)
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			float min[3] = { 10e9, 10e9, 10e9 };
			for (l = 0; l < 3; l++)
			{
				for (j = 0; j < vp; j++)
				{
					if (data[i][j][0][l] < min[l])
					{
						min[l] = data[i][j][0][l];
					}
				}
			}

			gb = min[1] / min[0];
			gr = min[1] / min[2];

			for (k = 0; k < sq; k++)
			{
				data[i][0][k][0] *= gb;
				data[i][0][k][2] *= gr;
			}

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					for (l = 0; l < 3; l++)
					{
						data[i][j][k][l] = data[i][0][k][l];
					}
				}
			}
		}
	}
	else
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			float ave[3] = { 0.0f };

			for (j = 0; j < vp; j++)
			{
				for (l = 0; l < 3; l++)
				{
					ave[l] += data[i][j][0][l];
				}
			}

			gb = ave[1] / ave[0];
			gr = ave[1] / ave[2];

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					data[i][j][k][0] *= gb;
					data[i][j][k][2] *= gr;
				}
			}
		}
	}
	writeToFile(data, filename);
}

void WhiteBalancer::greyWorld(float data[5][5][4][3], bool removeSpecular, const std::string& filename)
{
	int i, j, k, l;
	if (removeSpecular)
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			float min[4][3];
			float ave[3] = { 0.0f };
			for (k = 0; k < sq; k++)
			{
				for (l = 0; l < 3; l++)
				{
					min[k][l] = 10e9;
				}
			}

			for (l = 0; l < 3; l++)
			{
				for (k = 0; k < sq; k++)
				{
					for (j = 0; j < vp; j++)
					{
						if (data[i][j][k][l] < min[k][l])
						{
							min[k][l] = data[i][j][0][l];
						}
					}
				}
			}
			
			for (l = 0; l < 3; l++)
			{
				for (k = 0; k < sq; k++)
				{
					ave[l] += min[k][l];
				}
			}

			gb = ave[1] / ave[0];
			gr = ave[1] / ave[2];

			for (k = 0; k < sq; k++)
			{
				data[i][0][k][0] *= gb;
				data[i][0][k][2] *= gr;
			}

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					for (l = 0; l < 3; l++)
					{
						data[i][j][k][l] = data[i][0][k][l];
					}
				}
			}
		}
	}
	else
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			float ave[3] = { 0.0f };

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					for (l = 0; l < 3; l++)
					{
						ave[l] += data[i][j][k][l];
					}

				}
			}

			gb = ave[1] / ave[0];
			gr = ave[1] / ave[2];

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					data[i][j][k][0] *= gb;
					data[i][j][k][2] *= gr;
				}
			}
		}
	}

	writeToFile(data, filename);
}

void WhiteBalancer::whiteWorld(float data[5][5][4][3], bool removeSpecular, const std::string& filename)
{
	int i, j, k, l;
	if (removeSpecular)
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			float min[4][3];

			int maxk = 0;
			float maxVal = 0.0f;

			for (k = 0; k < sq; k++)
			{
				for (l = 0; l < 3; l++)
				{
					min[k][l] = 10e9;
				}
			}

			for (l = 0; l < 3; l++)
			{
				for (k = 0; k < sq; k++)
				{
					for (j = 0; j < vp; j++)
					{
						if (data[i][j][k][l] < min[k][l])
						{
							min[k][l] = data[i][j][0][l];
						}
					}
				}
			}

			for (k = 0; k < sq; k++)
			{
				float sum = min[k][0] + min[k][1] + min[k][2];
				if (sum > maxVal)
				{
					maxVal = sum;
					maxk = k;
				}
			}

			gb = min[maxk][1] / min[maxk][0];
			gr = min[maxk][1] / min[maxk][2];

			for (k = 0; k < sq; k++)
			{
				data[i][0][k][0] *= gb;
				data[i][0][k][2] *= gr;
			}

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					for (l = 0; l < 3; l++)
					{
						data[i][j][k][l] = data[i][0][k][l];
					}
				}
			}
		}
	}
	else
	{
		for (i = 0; i < ill; i++)
		{
			float gb, gr;
			int maxj = 0;
			int maxk = 3;
			float maxVal = 0.0f;

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					float sum = data[i][j][k][0] + data[i][j][k][1] + data[i][j][k][2];
					if (sum > maxVal)
					{
						maxVal = sum;
						maxj = j;
						maxk = k;
					}
				}
			}

			gb = data[i][maxj][maxk][1] / data[i][maxj][maxk][0];
			gr = data[i][maxj][maxk][1] / data[i][maxj][maxk][2];

			for (j = 0; j < vp; j++)
			{
				for (k = 0; k < sq; k++)
				{
					data[i][j][k][0] *= gb;
					data[i][j][k][2] *= gr;
				}
			}
		}
	}

	writeToFile(data, filename);
}

void WhiteBalancer::linearize(float data[5][5][4][3], float g)
{
	int i, j, k, l;
	for (i = 0; i < ill; i++)
		for (j = 0; j < vp; j++)
			for (k = 0; k < sq; k++)
				for (l = 0; l < 3; l++)
					data[i][j][k][l] = pow(data[i][j][k][l], g);
}

void WhiteBalancer::normalize(float data[5][5][4][3])
{
	// x = R / (R + G + B)
	// y = G / (R + G + B)

	int i, j, k, l;
	for (i = 0; i < ill; i++)
	{
		for (j = 0; j < vp; j++)
		{
			for (k = 0; k < sq; k++)
			{
				float sum = data[i][j][k][0] + data[i][j][k][1] + data[i][j][k][2];
				data[i][j][k][0] = data[i][j][k][2] / sum;
				data[i][j][k][1] = data[i][j][k][1] / sum;
			}
		}
	}
}

void WhiteBalancer::writeToFile(float data[5][5][4][3], const std::string & filename)
{
	int i, j, k, l;

	ofstream ofs(filename);
	ofs << setprecision(5);

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			for (k = 0; k < 4; k++)
			{
				for (l = 0; l < 2; l++)
				{
					ofs << data[i][j][k][l] << " ";
				}
				ofs << "   ";
			}
			ofs << endl;
		}
		ofs << endl;
	}
	ofs.close();
}
