// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h 
//as needed.

TEST(Matrix_at_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  // 0 1 2
  // 3 4 5
  // 6 7 8

  int *function_ptr = Matrix_at(mat,2,2);

  ASSERT_TRUE(*function_ptr == 8);

  delete mat;
}

TEST(Matrix_print_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  // 0 1 2
  // 3 4 5
  // 6 7 8

  ostringstream expected;
  expected << "3 3\n"
           << "0 1 2 \n3 4 5 \n6 7 8 \n";

  ostringstream actual;

  Matrix_print(mat,actual);

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(Matrix_row_test) {
  Matrix *mat = new Matrix;

  Matrix_init(mat, 4, 3);
  const int value = 13;
  Matrix_fill(mat, value);

  const int *ptr = Matrix_at(mat,0,2);

  // { 13 13 13 13
  //   13 13 13 13
  //   13 13 13 13 }

  int row = Matrix_row(mat,ptr);
  ASSERT_EQUAL(row,0);

  delete mat;

  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat2,row,col) = row*width + col;
    }
  }
  // 0 1 2
  // 3 4 5
  // 6 7 8
  const int *ptr2 = Matrix_at(mat2,2,2);
  int row2 = Matrix_row(mat2,ptr2);

  ASSERT_EQUAL(row2, 2);

  delete mat2;
}

/*
Make a matrix of different values
1 2 3
1 2 3
1 2 3
*/
TEST(Matrix_column_of_min_value_in_row_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  *Matrix_at(mat,1,1) = 3;
  *Matrix_at(mat,1,2) = 3;
  // 0 1 2
  // 3 3 3
  // 6 7 8

  int col_of_min = Matrix_column_of_min_value_in_row(mat,0,0,3);
  int col_of_min2 = Matrix_column_of_min_value_in_row(mat,1,0,3);

  ASSERT_EQUAL(col_of_min,0);
  ASSERT_EQUAL(col_of_min2,0);

  delete mat;

  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 1, 1);

  Matrix_fill(mat2,3);
  int col_of_min3 = Matrix_column_of_min_value_in_row(mat2,0,0,1);
  ASSERT_EQUAL(col_of_min3, 0);

  delete mat2;
}

TEST(Matrix_column_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  const int* ptr = Matrix_at(mat,1,2);
  // 0 1 2
  // 3 4 5
  // 6 7 8

  int column = Matrix_column(mat,ptr);
  ASSERT_EQUAL(column,2);

  delete mat;
}


TEST(Matrix_fill_border_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  // 0 1 2
  // 3 4 5
  // 6 7 8

  Matrix_fill_border(mat,13);

  ASSERT_EQUAL(*Matrix_at(mat,0,0), 13);
  ASSERT_EQUAL(*Matrix_at(mat,0,1), 13);
  ASSERT_EQUAL(*Matrix_at(mat,0,2), 13);
  ASSERT_EQUAL(*Matrix_at(mat,1,0), 13);
  ASSERT_EQUAL(*Matrix_at(mat,1,2), 13);
  ASSERT_EQUAL(*Matrix_at(mat,2,0), 13);
  ASSERT_EQUAL(*Matrix_at(mat,2,1), 13);
  ASSERT_EQUAL(*Matrix_at(mat,2,2), 13);
  ASSERT_EQUAL(*Matrix_at(mat,1,1), 4);

  delete mat;

  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 4, 3);
  const int width2 = 4;
  const int height2 = 3;
  for(int row = 0; row < height2; ++row) {
    for(int col = 0; col < width2; ++col) {
      *Matrix_at(mat2,row,col) = row*width2 + col;
    }
  }
  // 0 1 2 3
  // 4 5 6 7
  // 8 9 10 11

  Matrix_fill_border(mat2,5);

  ASSERT_EQUAL(*Matrix_at(mat2,0,0), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,0,1), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,0,2), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,0,3), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,1,0), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,1,3), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,2,0), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,2,1), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,2,2), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,2,3), 5);

  ASSERT_EQUAL(*Matrix_at(mat2,1,1), 5);
  ASSERT_EQUAL(*Matrix_at(mat2,1,2), 6);

  delete mat2;

  Matrix *mat3 = new Matrix;
  Matrix_init(mat3, 1, 1);

  Matrix_fill_border(mat3,3);
  ASSERT_EQUAL(*Matrix_at(mat3,0,0), 3);

  delete mat3;
}

TEST(Matrix_max_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  *Matrix_at(mat,0,1) = 8;
  // 0 8 2
  // 3 4 5
  // 6 7 8

  int max_element = Matrix_max(mat);

  ASSERT_EQUAL(max_element, 8);

  delete mat;

  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 3, 3);

  Matrix_fill(mat2,0);
  int max2 = Matrix_max(mat2);
  ASSERT_EQUAL(max2,0);
  delete mat2;
}

TEST(Matrix_min_value_in_row_test) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  const int width = 3;
  const int height = 3;
  for(int row = 0; row < height; ++row) {
    for(int col = 0; col < width; ++col) {
      *Matrix_at(mat,row,col) = row*width + col;
    }
  }
  *Matrix_at(mat,1,2) = 1;
  *Matrix_at(mat,0,1) = 0;
  // 0 0 2
  // 3 4 1
  // 6 7 8

  int min_value = Matrix_min_value_in_row(mat,1,0,3);
  int min_value2 = Matrix_min_value_in_row(mat,0,0,3);

  ASSERT_EQUAL(min_value, 1);
  ASSERT_EQUAL(min_value2, 0);

  delete mat;

  Matrix *mat2 = new Matrix;
  Matrix_init(mat2, 1, 1);
  *Matrix_at(mat2,0,0) = 5;

  int min = Matrix_min_value_in_row(mat2,0,0,1);

  ASSERT_EQUAL(min,5);

  delete mat2;
 
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
