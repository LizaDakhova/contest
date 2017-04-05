#include <functional>
#include <iostream>
#include <cmath>

using namespace std;
using std::function;

template <typename F, typename G>
auto compose(F f, G g) {
	return [f, g](auto x) { return f(g(x)); };
}

template <typename F, typename G>
auto operator*(F f, G g) {
	return compose(f, g);
}

int main() {
	double x;
	function<int(int)> f = [](auto i) { return i + 1; };
	function<int(double)> g = [](auto i) { return i * 2; };
	function<int(int) > h = [](auto i) {return i / 2; };
	cout << (f * g * h) (4) << endl;
	system("pause");
	return 0;
}