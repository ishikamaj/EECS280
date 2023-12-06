/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void test_summarize();
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

int main() {
  test_sum_small_data_set();
  test_summarize();
  test_count();
  test_sum();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();
  return 0;
}

void test_sum_small_data_set() {
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}
void test_summarize() {

}

void test_count() {
  cout << "test_count" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(2.4);
  aTEST.push_back(9.5);
  aTEST.push_back(3);
  assert(count(aTEST) == 4);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  assert(count(bTEST) == 2);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(387);
  cTEST.push_back(192);
  cTEST.push_back(83.2);
  cTEST.push_back(83.1);
  cTEST.push_back(19.3);
  cTEST.push_back(873.2);
  assert(count(cTEST) == 7);
}

void test_sum() {
  cout << "test_sum" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(2.4);
  aTEST.push_back(9.5);
  aTEST.push_back(3);
  assert(sum(aTEST) == 22.9);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  assert(sum(bTEST) == 354);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(387);
  cTEST.push_back(192);
  cTEST.push_back(83.2);
  cTEST.push_back(83.1);
  cTEST.push_back(19.3);
  cTEST.push_back(873.2);
  assert(sum(cTEST) == 1647.1);
}

void test_mean() {
  cout << "test_mean" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(2.4);
  aTEST.push_back(9.5);
  aTEST.push_back(3);
  assert(mean(aTEST) == 5.725);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  assert(mean(bTEST) == 177);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(387);
  cTEST.push_back(192);
  cTEST.push_back(83.2);
  cTEST.push_back(83.1);
  cTEST.push_back(19.3);
  cTEST.push_back(873.2);
  assert(mean(cTEST) == 235.3);
}

void test_median() {
  cout << "test_median" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(2.4);
  aTEST.push_back(9.5);
  aTEST.push_back(3);
  assert(median(aTEST) == 5.5);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  assert(median(bTEST) == 17);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(3.87);
  cTEST.push_back(19.2);
  cTEST.push_back(83.2);
  cTEST.push_back(83.1);
  cTEST.push_back(19.3);
  cTEST.push_back(8.2);
  assert(median(cTEST) == 19.2);
}

void test_mode() {
  cout << "test_mode" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(3);
  aTEST.push_back(9.2);
  aTEST.push_back(3);
  assert(mode(aTEST) == 3);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  bTEST.push_back(21);
  assert(mode(bTEST) == 21);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(83);
  cTEST.push_back(72);
  cTEST.push_back(8);
  assert(mode(cTEST) == 83);
}
  
void test_min() {
  cout << "test_min" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(3);
  aTEST.push_back(9.2);
  aTEST.push_back(3);
  assert(min(aTEST) == 3);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  bTEST.push_back(21);
  assert(min(bTEST) == 21);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(83);
  cTEST.push_back(72);
  cTEST.push_back(8);
  assert(min(cTEST) == 8);
}
  
void test_max() {
  cout << "test_max" << endl;
  vector <double> aTEST;
  aTEST.push_back(8);
  aTEST.push_back(3);
  aTEST.push_back(9.2);
  aTEST.push_back(3);
  assert(max(aTEST) == 9.2);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(276);
  bTEST.push_back(21);
  assert(max(bTEST) == 276);

  vector <double> cTEST;
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(9.3);
  cTEST.push_back(83);
  cTEST.push_back(83);
  cTEST.push_back(72);
  cTEST.push_back(99);
  assert(max(cTEST) == 99);
}

void test_stdev() {
  cout << "test_stdev" << endl;

  const double epsilon = 0.00001;
  cout.precision(numeric_limits<double>::max_digits10);

  vector <double> aTEST;
  aTEST.push_back(3);
  aTEST.push_back(12);
  aTEST.push_back(9);
  aTEST.push_back(4);
  aTEST.push_back(2);
  assert(abs(stdev(aTEST) - 3.847) < epsilon);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(81);
  bTEST.push_back(27);
  assert(abs(stdev(bTEST) - 24.779) < epsilon);

  vector <double> cTEST;
  cTEST.push_back(1);
  cTEST.push_back(3);
  cTEST.push_back(3);
  cTEST.push_back(3);
  cTEST.push_back(5);
  cTEST.push_back(2);
  cTEST.push_back(8);
  assert(abs(stdev(cTEST) - 2.128 ) < epsilon);
}

void test_percentile() {
  cout << "test_percentile" << endl;

  const double epsilon = 0.00001;
  cout.precision(numeric_limits<double>::max_digits10);

  vector <double> aTEST;
  aTEST.push_back(3);
  aTEST.push_back(12);
  aTEST.push_back(9);
  aTEST.push_back(4);
  aTEST.push_back(2);
  assert(abs(percentile(aTEST, 40) - 3.6) < epsilon);

  vector <double> bTEST;
  bTEST.push_back(78);
  bTEST.push_back(81);
  bTEST.push_back(27);
  assert(abs(percentile(bTEST, 35) - 62.7) < epsilon);

  vector <double> cTEST;
  cTEST.push_back(1);
  cTEST.push_back(3);
  cTEST.push_back(3);
  cTEST.push_back(3);
  cTEST.push_back(5);
  cTEST.push_back(2);
  cTEST.push_back(8);
  assert(abs(percentile(cTEST, 75) - 4) < epsilon);
}
