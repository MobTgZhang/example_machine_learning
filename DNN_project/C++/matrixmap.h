#ifndef MATRIX_MAP_H
#define MATRIX_MAP_H
#include "matrix.h"
#include<cstdlib>
#include<ctime>
#include<random>
namespace MathTool {
	Matrix<long> Random(Size size, long down, long up) {
		if (up >= down) {
			throw "The value of input is wrong!";
		}
		Matrix<long> resultMat(size);
		srand((unsigned)time(NULL));
		for (unsigned int k = 0; k<size.RowLength; k++) {
			for (unsigned int j = 0; j<size.ColumnLength; j++) {
				long value = down + rand() % (up - down);
				resultMat.Set(value, k, j);
			}
		}
		return resultMat;
	}
	Matrix<double> Random(Size size, double down, double up) {
		if (up >= down) {
			throw "The value of input is wrong!";
		}
		Matrix<double> resultMat(size);
		std::default_random_engine engine((unsigned)time(NULL));
		std::uniform_real_distribution<double> uniform(down, up);
		for (unsigned int k = 0; k<size.RowLength; k++) {
			for (unsigned int j = 0; j<size.ColumnLength; j++) {
				double value = uniform(engine);
				resultMat.Set(value, k, j);
			}
		}
		return resultMat;
	}
	void Random(long down, long up, Matrix<long>&resultMat) {
		if (up >= down) {
			throw "The value of input is wrong!";
		}
		srand((unsigned)time(NULL));
		for (unsigned int k = 0; k<resultMat.GetRowLength(); k++) {
			for (unsigned int j = 0; j<resultMat.GetColumnLength(); j++) {
				long value = down + rand() % (up - down);
				resultMat.Set(value, k, j);
			}
		}
	}
	void Random(double down, double up, Matrix<double>&resultMat) {
		if (up <= down) {
			throw "The value of input is wrong!";
		}
		std::default_random_engine engine((unsigned)time(NULL));
		std::uniform_real_distribution<double> uniform(down, up);
		for (unsigned int k = 0; k<resultMat.GetRowLength(); k++) {
			for (unsigned int j = 0; j<resultMat.GetColumnLength(); j++) {
				double value = uniform(engine);
				resultMat.Set(value, k, j);
			}
		}
	}
}
#endif //MATRIX_MAP_H!