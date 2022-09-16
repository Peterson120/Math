#include "matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <numeric>
namespace plt = matplotlibcpp;
#define x first
#define y second
typedef std::pair<int, int> pii;
int main() {
	std::cin.tie(NULL); std::cout.tie(NULL); fflush(stdout);
	std::cout << "Format: x y\nTerminate with \\0\n";
	std::vector<long double> scatter_x, scatter_y;
	long double xP, yP; std::unordered_map<long double, std::vector<long double>> map;
	std::fstream f("testdata.txt");
	while (f >> xP >> yP) {
		map[xP].push_back(yP);
		scatter_x.push_back(xP);
		scatter_y.push_back(yP);
	}
	plt::scatter(scatter_x, scatter_y, 10.0, {{"c", "b"}});
	long double numPoints = 0, avgx = 0, avgy = 0;
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
	int n = 10000;
	std::vector<long double> xs(n), ys(n);
	for (int i = 0; i < n; i++) {
		xs[i] = i - 5000;
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
