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
std::vector<ld> scatter_x, scatter_y, residual_x, residual_y;
std::vector<ld> xs, ys;
bool readData(ld &avgx, ld &avgy) {
	ld t, i = 0;
	std::ifstream fs(file_name, std::fstream::in);
	std::string line;
	while (1) {
		fs >> line;
		if ((line[0] < '0' || line[0] > '9') && line[0] != '-') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	t = std::stold(line);
	do {avgx += t; scatter_x.push_back(t); i++;} while (fs.get() != '\n' && fs >> t);
	avgx /= scatter_x.size();
	while (1) {
		fs >> line;
		if ((line[0] < '0' || line[0] > '9') && line[0] != '-') fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		else break;
	}
	i = 0;
	t = std::stold(line);
	do {
		avgy += t;
		map[scatter_x[i++]].push_back(t);
		scatter_y.push_back(t);
	} while (fs >> t);
	avgy /= scatter_y.size();
	return scatter_x.size() == scatter_y.size();
}

int main() {
	std::cin.tie(NULL); std::cout.tie(NULL);

	ld avgx = 0, avgy = 0;
	if (!readData(avgx, avgy)) {std::cout << "Inequivalent # of Points\n"; return 1;}
	plt::scatter(scatter_x, scatter_y, 10.0, {{"c", "r"}});

	ld sx = 0, sy = 0, sxy = 0;
	for (auto it = map.begin(); it != map.end(); it++) { // Linear Regression
		for (ld i : it->y) {
			ld currX = it->x - avgx;
			sx += currX * currX;
			ld currY = i - avgy;
			sy += currY * currY;
			sxy += currX * currY;
		}
	}

	ld m = sxy / sx, b = avgy - m * avgx;
	sxy = sxy / (scatter_x.size()-1);
	sx = sqrt(sx / (scatter_x.size()-1));
	sy = sqrt(sy / (scatter_y.size()-1));
	ld r = sxy / (sx * sy);

	std::ofstream fs("out.txt", std::ios::app);
	fs << "y = " << (m == 1 ? "" : std::to_string(m)) << (b > 0 ? "x + " + std::to_string(abs(b)) : b == 0 ? "x" : ("x - " + std::to_string(abs(b)))) << "\nStrength: " << r << '\n';
	std::cout << "Accuracy: " << r << '\n';

	std::sort(scatter_x.begin(), scatter_x.end());
	std::sort(scatter_y.begin(), scatter_y.end());
	for (long long i = -abs(scatter_x[0]) * 8; i <= abs(scatter_x[scatter_x.size()-1]) * 8; i++) {
		xs.push_back(i);
		ys.push_back(m*i+b);
	}

	plt::named_plot("y = " + (m == 1 ? "" : std::to_string(m)) + (b > 0 ? "x + " + std::to_string(abs(b)) : b == 0 ? "x" : ("x - " + std::to_string(abs(b)))), xs, ys);
	plt::xlim(scatter_x[0] - scatter_x[0] * 1.5, scatter_x[scatter_x.size()-1] + scatter_x[scatter_x.size()-1] * 1.5);
	plt::ylim(scatter_y[0] - scatter_y[0] * 1.5, scatter_y[scatter_y.size()-1] + scatter_y[scatter_y.size()-1] * 1.5);
	plt::grid(1);
	plt::legend();
	plt::show();

	for (auto it = map.begin(); it != map.end(); it++) { // Linear Regression
		ld yhat = 0;
		for (auto &i : map[it->x]) yhat += i;
		yhat /= map[it->x].size();
		residual_x.push_back(it->x);
		residual_y.push_back(yhat - (m * it->x + b));
	}

	plt::scatter(residual_x, residual_y, 10.0, {{"c", "g"}});
	plt::show();

	ld x;
	while (std::cin >> x) {
		ld yhat = 0;
		for (auto &i : map[x]) yhat += i;
		yhat /= map[x].size();
		std::cout << "y est: " << m * x + b << "\nResidual: " << yhat - (m * x + b) << '\n';
	}
	return 0;
}
