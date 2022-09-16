#include "matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
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
	int x, y; std::unordered_map<int, std::vector<int>> map;
	std::cout << "Format: x y\nTerminate with \\0\n";
	while (std::cin >> x >> y) map[x].push_back(y);
	double avgx = 0, avgy = 0; int numPoints = 0;
	for (auto it = map.begin(); it != map.end(); ++it) {	// 1.5*IQR and average
		//std::sort(it->y.begin(), it->y.end());
		//double IQR = it->y[3*((it->y.size()-1)>>2)]-it->y[(it->y.size()-1)>>2]*1.5;
		for (int i : it->y) {
			//if (i < it->y[(it->y.size()-1)>>2]-IQR || i > it->y[3*((it->y.size()-1)>>2)]+IQR) continue;
			avgy += i;
			numPoints++;
		}
		avgx += it->x * numPoints;
	}
	avgx /= numPoints;
	avgy /= numPoints;
	double mTop = 0, mBottom = 0;
	bool firstPass = 1;
	for (auto it = map.begin(); it != map.end(); ++it) { // Linear Regression
		for (int i : it->y) {
			if (firstPass) {firstPass = 0; continue;}
			mTop += (it->x-avgx)*(i-avgy);
		}
		mBottom += (it->x-avgx)*(it->x-avgx);
	}
	double m = mTop/mBottom, b = avgy - m*avgx;
	std::cout << "y = " << m << (b > 0 ? "x + " : b == 0 ? "" : "x - ") << std::abs(b) << '\n';
	return 0;
}
