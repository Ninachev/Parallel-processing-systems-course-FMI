#include<iostream>
#include<chrono>
#include<fstream>
#include<ctime>
#include<thread>
#include<vector>
#include<mutex>

using namespace std;

std::mutex mandelLock;
double Thread_time[256];
int Matrix[3840*2][2160*2];

int imgW = 3840*2, imgH = 2160*2, maxN = 256;
double minR = -0.716, maxR = -0.7092, minI = 0.24445, maxI = 0.2487;

int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;
	double zr = 0.0, zi = 0.0;
	double temp;
	while (i < max_iterations && zr * zr + zi * zi < 4.0)
	{
		temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return i;
}

double mapToReal(int x, int imgW, double minR, double maxR)
{
	double range = maxR - minR;
	return x*(range / imgW) + minR;

}

double mapToImaginary(int y, int imgH, double minI, double maxI)
{
	double range = maxI - minI;
	return y*(range / imgH) + minI;
}


void paintMandelbrotForThread(int startX, int stepX, int g_spread, int granularity, int id)
{
	using namespace std::chrono;
	auto startT = std::chrono::high_resolution_clock::now();

	for (size_t j = startX; j < imgW; j += g_spread)
	{
		for (size_t y = 0; y < imgH; y++)
		{
			for (size_t x = j; x < j + stepX; x++)
			{
				double cr = mapToReal(x, imgW, minR, maxR);
				double ci = mapToImaginary(y, imgH, minI, maxI);

				Matrix[x][y] = findMandelbrot(cr, ci, maxN);
			}
		}
	}

	auto endT = std::chrono::high_resolution_clock::now();
	auto durationT = duration_cast<microseconds>(endT - startT);
	double time_elapsedT = double(durationT.count()) / 1000000;
	Thread_time[id] = time_elapsedT;
}

void paintMandelbrot(int threads, int granularity)
{
	std::vector<std::thread> threadVect;
	int g_spread = imgW / granularity;
	int step = g_spread / threads;
	int startX = 0;
	for (size_t i = 0; i < threads; i++)
	{
		

		threadVect.emplace_back(paintMandelbrotForThread, startX, step, g_spread, granularity, i);
		startX += g_spread / threads;

		
	}
	for (auto& t : threadVect)
	{
		t.join();
	}
}

int main()
{
	int n, g;
	cin >> n >> g;
	ofstream fout("Mimage.ppm");
	fout << "P3" << endl;
	fout << imgW << " " << imgH << endl;
	fout << "256" << endl;

	using namespace std::chrono;
	auto start = std::chrono::high_resolution_clock::now();
	auto start2 = std::chrono::high_resolution_clock::now();

	paintMandelbrot(n, g);

	auto end2 = std::chrono::high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(end2 - start2);
	double time_elapsed2 = double(duration2.count()) / 1000000;
	/*for (size_t y = 0; y < imgH; y++)
	{
		for (size_t x = 0; x < imgW; x++)
		{
			int r = ((int)(Matrix[x][y] * sinf(Matrix[x][y])) % 256);
			int g = ((Matrix[x][y] * 3) % 256);
			int b = (Matrix[x][y] % 256);

			fout << r << " " << g << " " << b << " ";
		}
		fout << endl;
	}*/
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	double time_elapsed = double(duration.count()) / 1000000;
	for (size_t i = 0; i < n; i++)
	{
		cout << "Thread " << i+1 << " worked " << Thread_time[i] << endl;
	}
	cout << endl << "MandelbrotX found in seconds: " << time_elapsed2 << endl;
	cout << endl << "Time elapsed in seconds: " << time_elapsed << endl;
	fout.close();
	cin >> minI;
}
