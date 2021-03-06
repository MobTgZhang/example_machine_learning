#ifndef MATRIX_MAP_H
#define MATRIX_MAP_H
#include "matrix.h"
#include "vector.h"
#include<cstdlib>
#include<ctime>
#include<random>
namespace MathTool {
	Matrix<long> UniformRandom(Size size, long down, long up) {
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
	Matrix<double> UniformRandom(Size size, double down, double up) {
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
	Matrix<double> NormalRandom(Size size, double mean, double sigma) {
		Matrix<double> resultMat(size);
		std::default_random_engine engine((unsigned)time(NULL));
		std::normal_distribution<double> uniform(mean,sigma);
		for (unsigned int k = 0; k<size.RowLength; k++) {
			for (unsigned int j = 0; j<size.ColumnLength; j++) {
				double value = uniform(engine);
				resultMat.Set(value, k, j);
			}
		}
		return resultMat;
	}
	Vector<double> UniformRandom(unsigned int Length, double down, double up) {
		if (up >= down) {
			throw "The value of input is wrong!";
		}
		Vector<double> resultMat(Length);
		std::default_random_engine engine((unsigned)time(NULL));
		std::uniform_real_distribution<double> uniform(down, up);
		for (unsigned int k = 0; k<Length; k++) {
			double value = uniform(engine);
			resultMat.Set(value, k);
		}
		return resultMat;
	}
	void UniformRandom(long down, long up, Matrix<long>&resultMat) {
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
	void UniformRandom(double down, double up, Matrix<double>&resultMat) {
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
	void UniformRandom(double down, double up, Vector<double>&resultMat) {
		if (up <= down) {
			throw "The value of input is wrong!";
		}
		std::default_random_engine engine((unsigned)time(NULL));
		std::uniform_real_distribution<double> uniform(down, up);
		for (unsigned int k = 0; k<resultMat.GetLength(); k++) {
			double value = uniform(engine);
			resultMat.Set(value, k);
		}
	}

}
#endif //MATRIX_MAP_H!