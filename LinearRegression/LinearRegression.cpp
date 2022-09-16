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
	std::vector<int> scatter_x, scatter_y;
	while (std::cin >> x >> y) {
		map[x].push_back(y);
		scatter_x.push_back(x);
		scatter_y.push_back(y);
	}
	plt::scatter(scatter_x, scatter_y, 10.0, {{"c", "b"}});
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
	double m = 0;
	bool firstPass = 1;
	for (auto it = map.begin(); it != map.end(); ++it) { // Linear Regression
		for (int i : it->y) {
			if (firstPass) {firstPass = 0; continue;}
			m += (avgy-i)/(avgx-it->x);
		}
	}
	double b = avgy - m*avgx;
	std::cout << "y = " << m << (b > 0 ? "x + " : b == 0 ? "" : "x - ") << std::abs(b) << '\n';
	int n = 100;
	std::vector<double> xs(n), ys(n);
	for (int i = 0; i < n; i++) {
		xs[i] = i;
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
