#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
	float x;
	cin >> x;
	float y;
	cin >> y;
	float R = pow(x + y, 3 * sin(x));
	float S = sqrt(fabs(x)) / log(y);
	cout << R << " " << S << endl;
	float C = max(R, S);
	cout << C << endl;
	system("pause");
}
