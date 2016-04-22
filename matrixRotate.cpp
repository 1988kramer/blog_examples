// Andrew Kramer
// 4/20/2016

// matrixRotate.cpp
// reads a matrix from a file, prints the original matrix, 
// and prints the matrix rotated 90 degrees anti-clockwise

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <pthread.h>
#include <vector>
using namespace std;

struct threadParams
{
  int row;
  int column;
  int n;
};

int **matrix;

// accepts a pointer to a square two dimensional array 
// and three ints, the starting row and column indices
// and the highest index in the matrix, NOT the size
void* rotateLeftHelper(void* start) 
{
  threadParams* startState = (threadParams*) start;
  int row = startState->row;
  int column = startState->column;
  int n = startState->n;
  int temp = matrix[row][column];
  for (int i = 0; i < 3; i++) 
  {
    int nextRow = column;
    int nextColumn = n - row;
    matrix[row][column] = matrix[nextRow][nextColumn];
    row = nextRow;
    column = nextColumn;
  }
  matrix[row][column] = temp;
}

// accepts a pointer to a square two dimensional array 
// and an int, the matrix size
void rotateLeft(int n) 
{
  int level = n - 1; // switch n from matrix size to highest index
  // calculate number of threads
  int numThreads = 0;
  for (int i = level; i >= 1; i -= 2) {
    numThreads += i;
  }
  pthread_t *threads;
  threads = new pthread_t[numThreads];
  int curThread = 0;
  for (int i = 0; i < n/2; i++) 
  {
    for (int j = i; j < level; j++) 
    {
      cout << "Creating thread " << curThread << "!" << endl;
      threadParams current;
      current.row = i;
      current.column = j;
      current.n = n - 1;
      pthread_create(&threads[curThread], NULL, 
		     &rotateLeftHelper, (void*) &current);
      curThread++;
    }
    level--;
  }
  // join all threads
  cout << "joining " << numThreads << " threads" << endl;
  for (int i = 0; i < numThreads; i++) 
  {
    pthread_join(threads[i], NULL);
    cout << "thread " << i << " joined" << endl;
  }
}

// accepts a string designating the name of a file
// reads the contents of the file into a 2 dimensional array
void readFile(string fileName, int &n)
{
  const char* name = fileName.c_str();
  ifstream input(name);
  if (!input) 
  {
    cerr << "file: " << fileName << " does not exist";
    exit(1);
  }
  string line;
  getline(input, line);
  istringstream iss(line);
  iss >> n;
  matrix = new int*[n];
  for (int i = 0; i < n; i++) 
  {
    matrix[i] = new int[n];
  }
  for (int i = 0; i < n; i++) 
  {
    getline(input, line);
    istringstream iss(line);
    for (int j = 0; j < n; j++) 
    {
      iss >> matrix[i][j];
    }
  }
}

void printMatrix(int n) 
{
  for (int i = 0; i < n; i++) 
    {
      cout << "{" << matrix[i][0];
      for (int j = 1; j < n; j++) 
	{
	  cout << ", " << matrix[i][j];
	}
      cout << "}" << endl;
    }
  cout << endl;
}

void deleteMatrix(int n) 
{
  for (int i = 0; i < n; i++)
    {
      delete[] matrix[i];
    }
  delete[] matrix;
}

int main(int argc, char* argv[]) 
{
  int n = 0;
  readFile(argv[1], n);
  printMatrix(n);
  rotateLeft(n);
  printMatrix(n);
  deleteMatrix(n);
  return 0;
}
