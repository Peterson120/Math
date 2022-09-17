#include "matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <numeric>
namespace plt = matplotlibcpp;
#define x first
#define y second
#define n 10000 // Number of Points to show
const char file_name[] = "testdata.txt";
std::unordered_map<long double, std::vector<long double>> map;
std::vector<long double> scatter_x, scatter_y;
std::vector<long double> xs(n), ys(n);
bool readData() {
	long double xP, yP;
	std::ifstream fs(file_name);
	std::string line;
	while (1) {
		fs >> line;
		if (line[0] < '0' || line[0] > '9') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	xP = std::stold(line);
	do {scatter_x.push_back(xP);} while (fs.get() != '\n' && fs >> xP);
	int i = 0;
	while (1) {
		fs >> line;
		if (line[0] < '0' || line[0] > '9') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	yP = std::stold(line);
	do {
		map[scatter_x[i++]].push_back(yP);
		scatter_y.push_back(yP);
	} while (fs >> yP);
	return scatter_x.size() == scatter_y.size();
}

void calcAverage(long double &avgx, long double &avgy) {
	long double numPoints = 0;
	for (auto it = map.begin(); it != map.end(); ++it) {	// 1.5*IQR and average
		//std::sort(it->y.begin(), it->y.end());
		//double IQR = it->y[3*((it->y.size()-1)>>2)]-it->y[(it->y.size()-1)>>2]*1.5;
		for (long double i : it->y) {
			//if (i < it->y[(it->y.size()-1)>>2]-IQR || i > it->y[3*((it->y.size()-1)>>2)]+IQR) continue;
			avgy += i;
			numPoints++;
		}
		avgx += it->x * it->y.size();
	}
	avgx /= numPoints;
	avgy /= numPoints;
}

int main() {
	std::cin.tie(NULL); std::cout.tie(NULL); fflush(stdout);
	if (!readData()) {std::cout << "Inequivalent # of Points\n"; return 1;}
	plt::scatter(scatter_x, scatter_y, 10.0, {{"c", "b"}});
	long double avgx = 0, avgy = 0;
	calcAverage(avgx, avgy);
	long double mTop = 0, mBottom = 0;
	for (auto it = map.begin(); it != map.end(); ++it) { // Linear Regression
		long double currX = it->x-avgx;
		for (long double i : it->y) {
			mTop += currX*(i-avgy);
			mBottom += currX*currX;
		}
	}
	long double m = mTop/mBottom, b = avgy - m*avgx;
	std::cout << "y = " << m << (b > 0 ? "x + " : b == 0 ? "" : "x - ") << std::abs(b) << '\n';
	for (int i = 0; i < n; i++) {
		xs[i] = i - (n >> 1);
		ys[i] = m*xs[i]+b;
	}
	plt::named_plot("y = " + std::to_string(m) + (b > 0 ? "x + " : b == 0 ? "" : "x - ") + std::to_string(std::abs(b)), xs, ys);
	plt::ylim(0, 100);
	plt::xlim(0, 100);
	plt::grid(1);
	plt::legend();
	plt::show();
	return 0;
}
