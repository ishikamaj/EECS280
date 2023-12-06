// stats.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
  vector <vector<double>> summary;
  sort(v);
  double num = v[0];
  int counts = 0;
  for (int i = 0; i < count(v); i++) {
    if (v[i] == num) {
      counts++;
    }
    else {
      //makes individual vectors within large vector
      vector <double> repeats;
      repeats.push_back(num);
      repeats.push_back(counts);
      counts = 0;
      num = v[i];
      summary.push_back(repeats);
    }
  }
  return summary;
}

int count(vector<double> v) {
  return v.size();
}

double sum(vector<double> v) {
  double sum = 0;
  for (int i=0; i < count(v); i++) {
    sum += v[i];
  }
  return sum;
}

double mean(vector<double> v) {
  return sum(v)/count(v);
}

double median(vector<double> v) {
  int size = count(v);
  sort(v);
  if (size % 2 == 1) {
    return v[size/2];
  }
  else {
    return ((v[size/2] + v[size/2 - 1])/2);
  }
}

double mode(vector<double> v) {

sort(v);

double num = v[0];
double mode = v[0];
int counts = 1;
int record = 1;

for (int i = 1; i < count(v); i++)
{
  if (v[i] == num) {
    counts++;
  }
  else {
    //check if it's a new mode
    if (counts > record) {
      record = counts;
      mode = num;
    }
    //reset
    counts = 1;
    num = v[i];
  }
}

return mode;
}

double min(vector<double> v) {
  sort(v);
  return v[0];
}

double max(vector<double> v) {
  sort(v);
  return v[count(v) - 1];
}

double stdev(vector<double> v) {
  int sum = 0;
  double avg = mean(v);
  double term;
  for (int i = 0; i < count(v); i++) {
    term = pow((v[i] - avg), 2);
    sum += term;
  }

  return sqrt(sum/count(v));
}

double percentile(vector<double> v, double p) {
  double rank = p * (count(v)-1) + 1;
  int k = rank - 1;
  double d = rank - k;
  return v[k] + (d * (v[k+1] - v[k]));
}