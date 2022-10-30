#include <iostream>
#include <vector>
#include <algorithm>
int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(NULL);
	std::vector<double> v;
	double t;
	while (std::cin >> t) v.push_back(t);
	std::sort(v.begin(), v.end());
	for (auto &i : v) std::cout << i << ", ";
	putchar('\n');
	return 0;
}
