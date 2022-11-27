#pragma once
#include <vector>
#include<cstdint>
#include<fstream>
#include<iostream>

class matrix
{
	private:
		unsigned int rows, columns;
		//double** data;

	public:
		std::vector<std::vector<double>> data;

		matrix(unsigned int nrows, unsigned int ncolumns);
		
		unsigned int get_rows();
		unsigned int get_columns();
		double get_value(unsigned int row_position, unsigned int column_position);
		
		void set_rows(unsigned int new_nrows);
		void set_columns(unsigned int new_columns);
		void set_value(unsigned int row_position, unsigned int column_position, double value);
		
		void print_matrix();
		matrix copy_matrix();
		void transpose();
		static matrix sum_matrix(matrix& A, matrix& B);
		static matrix sub_matrix(matrix& A, matrix& B);
		static matrix mult_matrix(matrix& A, matrix& B);
		static std::vector<double> apply_matrix(matrix& A, std::vector<double>& v);

		static void print_vector(std::vector<double>& v);
		static double distance(std::vector<double>& v, std::vector<double>& u);
		static double norm(std::vector<double>& v);
		static double dotProduct(std::vector<double>& v, std::vector<double>& u);
		static std::vector<double> sub_vectors(std::vector<double>& v, std::vector<double>u);
		static std::vector<double> sum_vectors(std::vector<double>& v, std::vector<double>u);
		static std::vector<double> axpy(std::vector<double>& x, std::vector<double>& y, double a);
		static std::vector<double> proj_UV(std::vector<double> vectorV, std::vector<double> vectorU);
		static std::vector<double> sum_projections(unsigned int position, std::vector<std::vector<double>>& matrix);
		static matrix identityMatrix(unsigned int order);

		void gram_schmidt();
		void gram_schmidt_normal();
		static void printMatrixToFile(std::vector<std::pair<std::vector<double>, double>>& matrix, std::string fileName);





	};

