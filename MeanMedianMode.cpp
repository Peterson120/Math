#include <iostream>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
int arr[100000000];
std::unordered_map<int, int> m;
std::unordered_set<int> s;
int main() {
	std::ios_base::sync_with_stdio(0); std::cin.tie(NULL); std::cout.tie(NULL);
	int i = 0;
	while (std::cin >> arr[i]) {m[arr[i++]]++;}
	std::sort(arr, arr+i);
	long long total = 0;
	s.insert(0);
	for (int j = 0; j < i; j++) {
		total += arr[j];
		if (m[arr[j]] > m[*s.begin()]) {
			s.clear();
			s.insert(arr[j]);
		} else if (m[arr[j]] == m[*s.begin()]) s.insert(arr[j]);
	}
	std::cout << "Mean: " << total*1.0/i << "\nMedian: " << (i&1 ? arr[(i+1)>>1] : (arr[(i+1)>>1] + arr[(i-1)>>1])/2.0) << "\nMode: ";
	std::copy(s.begin(), s.end(), std::ostream_iterator<int>(std::cout, ", "));
	std::cout << "\b\b\b\b\n";
	return 0;
}
