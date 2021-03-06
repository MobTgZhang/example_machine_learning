#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include<sstream>
#include<string>
#include"vector.h"
struct Size{
	unsigned int RowLength;
	unsigned int ColumnLength;
	Size(unsigned int r,unsigned int c){
		this->RowLength = r;
		this->ColumnLength = c;
	}
	Size(Size&size){
		this->RowLength = size.RowLength;
		this->ColumnLength = size.ColumnLength;
	}
	Size() {}
};
template<typename DataType>
class Matrix {
private:
	Size mat_size;
	DataType** InnerMat;
public:
	//构造函数
	Matrix(Matrix<DataType>&mat);
	Matrix(unsigned int RowLength, unsigned int ColumnLength);
	Matrix(Size& size);
	//获取矩阵的大小
	unsigned int GetRowLength() { return this->mat_size.RowLength; }
	unsigned int GetColumnLength() { return this->mat_size.ColumnLength; }
	Size size(){return this->mat_size;}
	//表示矩阵逐个元素相乘
	Matrix<DataType> mul(Matrix<DataType>& mat);
	Matrix<DataType> mul(DataType value);
	//获取矩阵中的某一个元素
	DataType Get(unsigned int rowindex,unsigned int columninex);
	//设置矩阵中的某一个元素
	void Set(DataType value,unsigned int rowindex,unsigned int columninex);
	//表示矩阵逐个元素相加
	Matrix<DataType> add(Matrix<DataType>& mat);
	Matrix<DataType> add(DataType value);
	//表示矩阵中逐个元素相减
	Matrix<DataType> sub(Matrix<DataType>& mat);
	Matrix<DataType> sub(DataType value);
	//表示矩阵中逐个元素相除
	Matrix<DataType> div(Matrix<DataType>& mat);
	Matrix<DataType> div(DataType value);
	//Matrix对Vector广播处理
	Matrix<DataType> add(Vector<DataType>& mat);
	Matrix<DataType> sub(Vector<DataType>& mat);
	//重载运算符
	Matrix<DataType> operator +(Matrix<DataType>& mat) { return this->add(mat); }
	Matrix<DataType> operator +(DataType value) { return this->add(value); }
	Matrix<DataType> operator -(Matrix<DataType>& mat) { return this->sub(mat); }
	Matrix<DataType> operator -(DataType value) { return this->sub(value); }
	Matrix<DataType> operator *(Matrix<DataType>& mat) { return this->mul(mat); }
	Matrix<DataType> operator *(DataType value) { return this->mul(value); }
	Matrix<DataType> operator /(Matrix<DataType>& mat) { return this->div(mat); }
	Matrix<DataType> operator /(DataType value) { return this->div(value); }
	//重载运算符中的广播
	Matrix<DataType> operator +(Vector<DataType>& mat) { return this->add(mat); }
	Matrix<DataType> operator -(Vector<DataType>& mat) { return this->sub(mat); }
	//将矩阵中的元素转化为字符串形式
	std::string toString();
	//析构函数
	~Matrix();
};
//构造函数的实现
template<typename DataType>
Matrix<DataType>::Matrix(unsigned int RowLength, unsigned int ColumnLength) {
	this->mat_size = Size(RowLength,ColumnLength);
	this->mat_size.RowLength = RowLength;
	this->mat_size.ColumnLength = ColumnLength;
	this->InnerMat = new DataType*[RowLength];
	for (unsigned int k = 0; k < RowLength; k++) {
		this->InnerMat[k] = new DataType[ColumnLength];
	}
}
template<typename DataType>
Matrix<DataType>::Matrix(Size& size){
	this->mat_size = Size(size);
	this->InnerMat = new DataType*[size.RowLength];
	for (unsigned int k = 0; k <  size.RowLength; k++) {
		this->InnerMat[k] = new DataType[size.ColumnLength];
	}
}
template<typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>&mat) {
	this->mat_size = Size(mat.size());
	this->InnerMat = new DataType*[mat.GetRowLength()];
	for (unsigned int k = 0; k < mat.GetRowLength(); k++) {
		this->InnerMat[k] = new DataType[mat.GetColumnLength()];
	}
	for (unsigned int k = 0; k < mat.GetRowLength(); k++) {
		for (unsigned int j = 0; j < mat.GetColumnLength(); j++) {
			this->InnerMat[k][j] = mat.Get(k, j);
		}
	}
}
//析构函数的实现
template<typename DataType>
Matrix<DataType>::~Matrix() {
	for (unsigned int k = 0; k < this->mat_size.RowLength; k++) {
		delete[] this->InnerMat[k];
	}
	delete[] this->InnerMat;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::add(Matrix<DataType>& mat) {
	if (mat.GetRowLength() != this->mat_size.RowLength && mat.GetColumnLength() != this->mat_size.ColumnLength) {
		throw "The size of two matrix don't match!";
	}
	Matrix<DataType> Result(mat.size());
	for(unsigned int k=0;k<this->mat_size.RowLength;k++){
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]+mat.Get(k,j),k,j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::add(DataType value) {
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for (unsigned int k = 0; k < this->mat_size.RowLength; k++) {
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]+value,k,j); 
		}
	}
	return Rsult;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::sub(Matrix<DataType>& mat) {
	if (mat.GetRowLength() != this->mat_size.RowLength && mat.GetColumnLength() != this->mat_size.ColumnLength) {
		throw "The size of two matrix don't match!";
	}
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for(unsigned int k=0;k<this->mat_size.RowLength;k++){
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]-mat.Get(k,j),k,j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::sub(DataType value) {
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for (unsigned int k = 0; k < this->mat_size.RowLength; k++) {
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]-value,k,j); 
		}
	}
	return Rsult;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::div(Matrix<DataType>& mat) {
	if (mat.GetRowLength() != this->mat_size.RowLength && mat.GetColumnLength() != this->mat_size.ColumnLength) {
		throw "The size of two matrix don't match!";
	}
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for(unsigned int k=0;k<this->mat_size.RowLength;k++){
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]/mat.Get(k,j),k,j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::div(DataType value) {
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for (unsigned int k = 0; k < this->mat_size.RowLength; k++) {
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]/value,k,j); 
		}
	}
	return Rsult;
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::mul(Matrix<DataType>& mat) {
	if (mat.GetRowLength() != this->mat_size.RowLength && mat.GetColumnLength() != this->mat_size.ColumnLength) {
		throw "The size of two matrix don't match!";
	}
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for(unsigned int k=0;k<this->mat_size.RowLength;k++){
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]*mat.Get(k,j),k,j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::mul(DataType value) {
	Matrix<DataType> Result(this->mat_size.RowLength,this->mat_size.ColumnLength);
	for (unsigned int k = 0; k < this->mat_size.RowLength; k++) {
		for(unsigned int j=0;j<this->mat_size.ColumnLength;j++){
			Result.Set(this->InnerMat[k][j]*value,k,j); 
		}
	}
	return Rsult;
}
//Matrix对Vector广播处理
template<typename DataType>
Matrix<DataType> Matrix<DataType>::add(Vector<DataType>& mat) {
	if (this->GetColumnLength() != mat.GetLength()) {
		throw "The size don't match!";
	}
	Matrix<DataType> Result(this->mat_size);
	for (unsigned int k = 0; k<this->mat_size.RowLength; k++) {
		for (unsigned int j = 0; j<this->mat_size.ColumnLength; j++) {
			Result.Set(this->InnerMat[k][j] + mat.Get(j), k, j);
		}
	}
	return Result;
}
template<typename DataType>
Matrix<DataType> Matrix<DataType>::sub(Vector<DataType>& mat) {
	if (this->GetColumnLength() != mat.GetLength()) {
		throw "The size don't match!";
	}
	Matrix<DataType> Result(this->mat_size);
	for (unsigned int k = 0; k<this->mat_size.RowLength; k++) {
		for (unsigned int j = 0; j<this->mat_size.ColumnLength; j++) {
			Result.Set(this->InnerMat[k][j] - mat.Get(j), k, j);
		}
	}
	return Result;
}
//将矩阵中的元素转化为字符串形式
template<typename DataType>
std::string Matrix<DataType>::toString(){
	unsigned int RowLength=this->mat_size.RowLength;
	unsigned int ColumnLength = this->mat_size.ColumnLength;
	std::stringstream tmp_stream;
	tmp_stream.precision(4);  //由于未用定点格式，这里设置的是保留4位有效数字
	std::string str_size;
	tmp_stream << "Size:[" << RowLength << "," << ColumnLength << "]";
	tmp_stream >> str_size;
	str_size = str_size + "\n";
	//注意用完s_stream要清除字符流
	tmp_stream.clear();
	std::string str_mat = "";
	for(unsigned int k=0;k<RowLength;k++){
		for(unsigned int j=0;j<ColumnLength;j++){
			tmp_stream << this->InnerMat[k][j];
			std::string line;
			tmp_stream >> line;
			str_mat = str_mat + line + "\t";
			tmp_stream.clear();
		}
		str_mat = str_mat + "\n";
	}
	return str_mat + str_size;
}
//获取矩阵中的某一个元素
template<typename DataType>
DataType Matrix<DataType>::Get(unsigned int rowindex, unsigned int columninex) {
	return this->InnerMat[rowindex][columninex];
}
//设置矩阵中的某一个元素
template<typename DataType>
void Matrix<DataType>::Set(DataType value, unsigned int rowindex, unsigned int columninex) {
	this->InnerMat[rowindex][columninex] = value;
}
#endif
