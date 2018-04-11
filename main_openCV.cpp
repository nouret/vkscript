#include "opencv2/opencv.hpp"
#include "opencv/cv.hpp"
#include "opencv/cv.h"
#include <queue>
#include <vector>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

vector<pair<int, int>> BFS(int x, int y);

Mat img;
int lost;
double tmp;
vector<vector<int>> F;

int main(int argc, const char** argv)
{
	img = imread("1.jpg", CV_LOAD_IMAGE_COLOR);
	int r = img.rows;
	int c = img.cols;
	F.resize(r);
	vector<pair<int, int>> Plus;
	vector<pair<int, int>> Minus;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			F[i].push_back(0);
		}
	}
	lost = r * c;
	int MaX;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int sum = (img.at<Vec3b>(i, j)[0] - 255) ^ 2 + (img.at<Vec3b>(i, j)[1] - 255) ^ 2 + (img.at<Vec3b>(i, j)[2] - 255) ^ 2;
			MaX = max(MaX, sum);
			printf("%d\n", MaX);
		}
	}
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			int sum = (img.at<Vec3b>(i, j)[0] - 255) ^ 2 + (img.at<Vec3b>(i, j)[1] - 255) ^ 2 + (img.at<Vec3b>(i, j)[2] - 255) ^ 2;
			if (sum < MaX / 3) // white
			{
				for (int k = 0; k < 3; ++k)
				{
					img.at<Vec3b>(i, j)[k] = 255;
				}
			}
			else // black
			{
				for (int k = 0; k < 3; ++k)
				{
					img.at<Vec3b>(i, j)[k] = 0;
				}
			}
			if ((min(i, r - i) / r + min(j, c - j) / c) < 1 / 3) // corners to white
			{
				for (int k = 0; k < 3; ++k)
				{
					img.at<Vec3b>(i, j)[k] = 255;
				}
			}
		}
	}

	/*for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (F[i][j] == 0)
			{

				vector<pair<int, int>> part = BFS(i, j);
				int partmax0 = part[0].first;
				int partmin0 = part[0].first;
				int partmax1 = part[0].second;
				int partmin1 = part[0].second;
				for (int l = 0; l < part.size(); ++l)
				{

				}
				int dy = max([elem[0] for elem in part]) - min([elem[0] for elem in part]);
				int dx = max([elem[1] for elem in part]) - min([elem[1] for elem in part]);
				int y = max([elem[0] for elem in part]) + min([elem[0] for elem in part]);
				int x = max([elem[1] for elem in part]) + min([elem[1] for elem in part]);
				if 2 * dx >= dy and dx < 2 * dy and 8 * (dx + dy) > len(part) and len(part) > 20:
	Plus += [(y // 2, x // 2)]
		for elem in part :
	img[elem[0]][elem[1]][0] = 0
		img[elem[0]][elem[1]][1] = 0
		img[elem[0]][elem[1]][2] = 255
		elif dx >= 2 * dy and 4 * (dx + dy) > len(part) and len(part) > 10:
	Minus += [(y // 2, x // 2)]
		for elem in part :
	img[elem[0]][elem[1]][0] = 255
		img[elem[0]][elem[1]][1] = 0
		img[elem[0]][elem[1]][2] = 0
		elif len(part) < 500 :
		for elem in part :
	img[elem[0]][elem[1]][0] = 0
		img[elem[0]][elem[1]][1] = 255
		img[elem[0]][elem[1]][2] = 0
		print("+:", len(Plus))
		print("-:", len(Minus))
		*/
	namedWindow("MYWINDOW", WINDOW_NORMAL);
	imshow("MYWINDOW", img);

	/*printf("[i] channels:  %d\n", image->nChannels);
	printf("[i] pixel depth: %d bits\n", image->depth);
	printf("[i] width:       %d pixels\n", image->width);
	printf("[i] height:      %d pixels\n", image->height);
	printf("[i] image size:  %d bytes\n", image->imageSize);
	printf("[i] width step:  %d bytes\n", image->widthStep);*/

	waitKey(0);

	return 0;
}




vector<pair<int, int>> BFS(int x, int y)
{
	vector<pair<int, int>> ans;
	F[x][y] = 1;
	queue<pair<int, int>> Q;
	pair<int, int> p;
	p.first = x;
	p.second = y;
	Q.push(p);
	while (!Q.empty()) {
		p = Q.front();
		lost -= 1;
		printf("%d \n", lost);
		ans.push_back(p);
		for (int dx = -4; dx <= 4; ++dx) {
			for (int dy = -4; dy <= 4; ++dx) {
				if ((dx != 0) || (dy != 0)) {
					int nx = x + dx;
					int ny = y + dy;
					pair<int, int> np(nx, ny);
					bool eq = true;
					for (int k = 0; k < 3; ++k) {
						if (img.at<Vec3b>(nx, ny)[k] != img.at<Vec3b>(x, y)[k])
						{
							bool eq = false;
						}
					}
					if ((0 <= nx) && (nx < img.cols) && ((0 <= ny) && (ny < img.rows)) && (eq) && (!F[nx][ny])) {
						Q.push((np));
						F[nx][ny] = 1;
					}
				}
			}
		}
	}
					return ans;
}