#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iomanip>
#include <iostream>
#include <exception>


class myexception: public std::exception{
	const char* fail;
public:
	myexception(const char* a) throw() : fail(a){}

	virtual const char * what () const throw ()
  	{
   		 return fail;
  	}

  	virtual ~myexception() throw(){}
};


template<typename T>
class Matrix{
	int _cols;
	int _rows;
	std::vector<T> _matrix;
public:

/* Constructors */
	Matrix();						//empty matrix
	Matrix(int, int);				//zero matrix
	Matrix(int, int, const T*);		//initialized with array
	Matrix(int, int, std::vector<T>&); //initialized with vector
	Matrix(int row, int col, const std::initializer_list<T>& values);
	Matrix(const Matrix&);			//copy ctor
	Matrix& operator=(const Matrix&);	//assigment operator*/
	~Matrix(){}						//destructor

/* Getters */
	int getColls() const;
	int getRows() const;
	T element(int) const;
	std::vector<T> getMatrix() const;



/* Operators */
	void operator()(int, T);
	Matrix operator+(const Matrix&);
	Matrix operator+=(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator-=(const Matrix&);
	Matrix operator*(const Matrix&);
//	Matrix operator/(const Matrix&);
//	Matrix operator/=(const Matrix&);

/* Actions */
	double det();
	Matrix trans();
	Matrix<double> inverse();
	bool square();



};

template<typename T>
Matrix<T>::Matrix() : _cols(0), _rows(0), _matrix()
{
}

template<typename T>
Matrix<T>::Matrix(int rows, int cols) : _cols(cols), _rows(rows) {
	for(int i = 0; i < cols * rows; i++)
		_matrix.push_back(0);
} 

template<typename T>
Matrix<T>::Matrix(int rows, int cols, const T* a) : _cols(cols), _rows(rows){
	for(int i = 0; i< cols * rows; i++){
		_matrix.push_back(a[i]);
	}
}

template<typename T>
Matrix<T>::Matrix(int rows, int cols, std::vector<T>& matrix): _rows(rows), _cols(cols), _matrix(matrix)
{}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) : _rows(rhs.getRows()), _cols(rhs.getColls()), _matrix(rhs._matrix)
{}

template<typename T>
Matrix<T>::Matrix(int row, int col, const std::initializer_list<T>& values) : _rows(row), _cols(col), _matrix(values)
{}


template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs){
	if(this != &rhs)
	{
		_matrix = rhs._matrix;
		_rows = rhs.getRows();
		_cols = rhs.getColls();
	}
	
	return *this;

}

template<typename T>
void Matrix<T>::operator()(int i, T value){
	_matrix[i] = value;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs){
	

	if(_rows == rhs.getRows() && _cols == rhs.getColls() )
	{
		Matrix<T> temp(this->getRows(), this->getColls(), _matrix);
		for (int i = 0; i < _rows * _cols; i++)
			temp._matrix[i] += rhs.element(i);
		return temp;
	}
	else 
		throw myexception("Matrices does not equal!");
	

}

template<typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T>& rhs){
	if(_rows == rhs.getRows() && _cols == rhs.getColls() )
	{
		for (int i = 0; i < _rows * _cols; i++)
			this->_matrix[i] += rhs.element(i);
	}
	else 
		throw myexception("Matrices does not equal!");
	
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs){
	
	Matrix<T> temp(this->getRows(), this->getColls(), this->getMatrix());
	if(_rows == rhs.getRows() && _cols == rhs.getColls() )
	{
		for (int i = 0; i < _rows * _cols; i++)
			temp._matrix[i] -= rhs.element(i);
	}
	else 
		throw myexception("Matrices does not equal!");
	
	return temp;

}

template<typename T>
Matrix<T> Matrix<T>::operator-=(const Matrix<T>& rhs){
	if(_rows == rhs.getRows() && _cols == rhs.getColls() )
	{
		for (int i = 0; i < _rows * _cols; i++)
			this->_matrix[i] -= rhs.element(i);
	}
	else 
		throw myexception("Matrices does not equal!");
	
	return *this;

}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& rhs){
 if(_cols != rhs.getRows())
 {
 	throw myexception("Matrices does not multiplied");
 }
 else 
 {
 	T temp[this->getRows() * rhs.getColls()];
 	for(int i = 0;i < this->getRows(); i++)
 		for(int j = 0;j < rhs.getColls(); j++)
 			{	
 				T tempRow[this->getColls()];
 				for(int k = 0; k < this->getColls(); k++)
 				{
 					int number = i * (this->getColls()) + k;
 					tempRow[k] = this->_matrix[number];
 				//	std::cout << tempRow[k] << ' ';	
 				}
 				
 				//std::cout << std::endl;

 				T tempColls[rhs.getRows()];
 				for(int k = 0; k < rhs.getRows(); k++)
 				{
 					int number = k * rhs.getColls() + j;
 					tempColls[k] = rhs._matrix[number];
 				//	std::cout << tempColls[k] << ' ';
 				}
 				//std::cout << std::endl;

 				T result = 0;
 				//T temp1[this->getColls()]
 				for(int k = 0; k < this->getColls(); k++)
 				{
 					result += tempColls[k] * tempRow[k];
 				}
 				//std::cout << result<< '\n';
 				temp[i * rhs.getColls() + j] = result;
 				
 			}
 	return Matrix<T>(this->getRows(), rhs.getColls(), temp); 
 }

}


template<typename T>
int Matrix<T>::getColls() const{
	return _cols;
}

template<typename T>
int Matrix<T>::getRows() const{
	return _rows;
}

template<typename T>
T Matrix<T>::element(int i) const{
	return _matrix[i];
}

template<typename T>
std::vector<T> Matrix<T>::getMatrix() const{
	return _matrix;
}

template <typename T>
std::ostream& operator<<(std::ostream& os,const Matrix<T>& va)
{
	int maxlength = std::to_string(va.element(0)).length();
	for(int i = 1; i < va.getColls()*va.getRows();i++)
	{
		if(maxlength < std::to_string(va.element(i)).length());
			maxlength = std::to_string(va.element(i)).length();
	}
	

	for (int i = 0; i < va.getRows() ; i++)
	{
		os << "|";
		for(int j = 0; j < va.getColls();j++)
		{
			
			os << std::setw(maxlength) << va.element(i * va.getColls() + j);
			if(j != va.getColls()-1)
				std::cout << " ";
			
				
		}
			os << "|" << std::endl;
	}

	os << std::endl;
		
	return os;
}

template<typename T>
double Matrix<T>::det(){

	int colls, rows;
	colls = this->getColls();
	rows = this->getRows();

	if(colls != rows)
		throw myexception("Matrix does not square matrix");
	else
	{
		double result = 1;
		double c;
		T A[rows][colls];
		int dim = rows;
		int k = 0;
		for(int i = 0; i < rows; i++)
			for(int j = 0; j < colls; j++)
			{
				A[i][j] = this->element(k);
				k++;
			}

		for(int i = 0; i < dim; i++)
			for(int j = 0; j < dim; j++)
			{
				if(j>i)
				{
					c = (double)A[j][i]/(double)A[i][i];
					for(k = 0; k < dim; k++)
					{
						A[j][k] = A[j][k]-c*A[i][k];
					}
				}
			}

		/*for(int i = 0; i < dim; i++)
		{
			for(int j = 0; j < dim; j++)
				std::cout << A[i][j] << ", "; 
			std::cout<< std::endl;
		}*/


		// Sum the diagonal
		for(int i = 0; i < dim; i++)
			result *= A[i][i];

		return result;
	}
}
	
template<typename T>
Matrix<T> Matrix<T>::trans(){

	Matrix<T> tempMatrix(this->getColls(),this->getRows());

	for(int n = 0; n < this->getRows() * this->getColls(); ++n)
	{
		int i = n / this->getRows();
		int j = n % this->getRows();
		tempMatrix._matrix[n] = this->_matrix[this->getColls() * j + i];
	}

	return tempMatrix;
}

template<typename T>
Matrix<double> Matrix<T>::inverse(){
	if((!this->square()) || this->det() == 0 )
		throw myexception("This matrix has no inverse");

	Matrix<double> tempMatrix(this->getRows(),this->getColls());
	double E[this->getRows()][this->getColls()];
	for(int i = 0; i < this->getRows(); i++)
		for(int j = 0; j < this->getColls(); j++)
		{
			if(i == j)
				E[i][j] = 1;
			else
				E[i][j] = 0;
			
		}



	double c;
	T A[this->getRows()][this->getColls()];
	int dim = this->getRows();
	int k = 0;
	for(int i = 0; i < this->getRows(); i++)
		for(int j = 0; j < this->getColls(); j++)
		{
			A[i][j] = this->element(k);
			k++;
		}
	
	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
		{
			if(j>i)
			{
				c = (double)A[j][i]/(double)A[i][i];
				for(k = 0; k < dim; k++)
				{
					A[j][k] = A[j][k]-c*A[i][k];
					E[j][k] = E[j][k]-c*E[i][k];
				}
			}
		}

	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
		{
			if(j<i)
			{
				c = (double)A[j][i]/(double)A[i][i];
				for(k = 0; k < dim; k++)
				{
					A[j][k] = A[j][k]-c*A[i][k];
					E[j][k] = E[j][k]-c*E[i][k];
				}
			}
		}


	for(int i = 0; i < dim; i++)
		for(int j = 0; j < dim; j++)
		{
			if(i == j)
			{
				E[i][j] = E[i][j]/A[i][j];
				A[i][j] = A[i][j]/A[i][j];
			}
		}
	for(int i = 0; i < dim; i++)
	{
		for(int j = 0; j < dim; j++)
			std::cout << A[i][j] << ", "; 
		std::cout<< std::endl;
	}

	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColls(); j++)
		{
			std::cout << E[i][j] << ", ";
		}
		
		std::cout << std::endl;
	}

	k = 0;
	for(int i = 0; i < this->getRows(); i++)
	{
		for(int j = 0; j < this->getColls(); j++)
		{
			tempMatrix(k, E[i][j]);
			k++;
		}
	}


	return tempMatrix;
}

template<typename T>
bool Matrix<T>::square(){
	return this->getColls() == this->getRows() ? true : false; 
}

#endif
