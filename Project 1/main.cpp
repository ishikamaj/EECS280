// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
using namespace std;

int main() {
  cout << "enter a filename\n";
	string filename;
	cin >> filename;
	cout << "enter a column name\n";
	string col;
	cin >> col;
	cout << "reading column " + col + " from " + filename + "\n";

	vector <double> data = extract_column(filename, col);
	sort(data);

	cout << "Summary (value: frequency)" << endl;
	vector <vector<double>> summary;
	summary = summarize(data);
	for (int i = 0; i < summary.size(); i++)
	{
		cout << summary[i][0] << ": " << summary[i][1] << endl;
	}
  cout << endl;
	cout << "count = " << count(data) << endl;
	cout << "sum = " << sum(data) << endl;
	cout << "mean = " << mean(data) << endl;
	cout << "stdev = " << stdev(data) << endl;
	cout << "median = " << median(data) << endl;
	cout << "mode = " << mode(data) << endl;
	cout << "min = " << min(data) << endl;
	cout << "max = " << max(data) << endl;
	cout << "  0th percentile = " << percentile(data, 0) << endl;
	cout << " 25th percentile = " << percentile(data, .25) << endl;
	cout << " 50th percentile = " << percentile(data, .50) << endl;
	cout << " 75th percentile = " << percentile(data, .75) << endl;
	cout << "100th percentile = " << percentile(data, 1.0) << endl;

}