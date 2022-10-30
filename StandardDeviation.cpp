#include <iostream>
#include <cmath>
#include <vector>
int main() {
	std::vector<double> v;
	std::cout << "Sample(s) or Population(p)?\n";
	double t, mean = 0; char c = getchar();
	while (std::cin >> t) {v.push_back(t); mean += t;}
	mean /= v.size();
	double s = 0;
	for (auto &i : v) s += (i - mean) * (i - mean);
	s /= c == 'P' || c == 'p' ? v.size() : v.size() - 1;
	std::cout << "n = " << v.size() << "\nMean = " << mean << "\nStandard Deviation = " << sqrt(s) << "\nVariance = " << s << '\n';
	return 0;
}
