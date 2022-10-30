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
typedef long double ld;
const char file_name[] = "testdata.txt";
std::unordered_map<ld, std::vector<ld>> map;
std::vector<ld> scatter_x, scatter_y;
std::vector<ld> xs, ys;
bool readData(ld &avgx, ld &avgy) {
	ld t, i = 0;
	std::ifstream fs(file_name, std::fstream::in);
	std::string line;
	while (1) {
		fs >> line;
		if (line[0] < '0' || line[0] > '9') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	t = std::stold(line);
	do {avgx += t; scatter_x.push_back(t); i++;} while (fs.get() != '\n' && fs >> t);
	avgx /= i;
	while (1) {
		fs >> line;
		if (line[0] < '0' || line[0] > '9') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	i = 0;
	t = std::stold(line);
	do {
		avgy += t;
		map[scatter_x[i++]].push_back(t);
		scatter_y.push_back(t);
	} while (fs >> t);
	avgy /= i;
	return scatter_x.size() == scatter_y.size();
}

int main() {
	std::cin.tie(NULL); std::cout.tie(NULL); fflush(stdout);
	ld avgx = 0, avgy = 0;
	if (!readData(avgx, avgy)) {std::cout << "Inequivalent # of Points\n"; return 1;}
	plt::scatter(scatter_x, scatter_y, 10.0, {{"c", "b"}});
	ld mTop = 0, mBottom = 0;
	for (auto it = map.begin(); it != map.end(); ++it) { // Linear Regression
		ld currX = it->x-avgx;
		for (ld i : it->y) {
			mTop += currX*(i-avgy);
			mBottom += currX*currX;
		}
	}
	ld m = mTop/mBottom, b = avgy - m*avgx;
	std::ofstream fs("out.txt", std::ios::app);
	fs << "y = " << m << (b > 0 ? "x + " : b == 0 ? "" : "x - ") << std::abs(b) << '\n';
	std::sort(scatter_x.begin(), scatter_x.end());
	std::sort(scatter_y.begin(), scatter_y.end());
	for (long long i = -scatter_x[0] * 8; i <= scatter_x[scatter_x.size()-1] * 8; i++) {
		xs.push_back(i);
		ys.push_back(m*i+b);
	}
	plt::named_plot("y = " + std::to_string(m) + (b > 0 ? "x + " : b == 0 ? "" : "x - ") + std::to_string(std::abs(b)), xs, ys);
	plt::ylim(scatter_x[0] - scatter_x[0] * 1.5, scatter_x[scatter_x.size()-1]*2);
	plt::xlim(scatter_y[0] - scatter_y[0] * 1.5, scatter_y[scatter_y.size()-1]*2);
	plt::grid(1);
	plt::legend();
	plt::show();
	return 0;
}
