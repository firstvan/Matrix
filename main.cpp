#include "HEADER/Matrix.h"

int main(){
try{

	int tomb[6]={1,2,4,5,6,8};

	Matrix<int> a(2, 3, tomb);
	Matrix<int> b(a);
	std::cout << a;
	std::cout <<"--------------b----------------"<<std::endl;
	std::cout << b;

	Matrix<int> c;

	c = a;

	std::cout << "-------------c----------------"<< std::endl;
	std::cout << c;

	std::cout << a+b;
	c += b;
	std::cout << c;
	
	c -= b;
	std::cout << c;
	/*int tomb2[4]={1,2,3,4};
	
	Matrix<int> d(2,2,tomb2);

	std::cout << d+c;*/

	Matrix<int> e(3,2,tomb);
	std::cout << e;
	std::cout << a*e;

	

	int tomb1[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};

	Matrix<int> egyseg(4,4, tomb1);
	std::cout << egyseg;
	std::cout << egyseg.det() << std::endl;

	int tomb2[9] = {1,2,2,4,7,8,3,1,1};

	Matrix<int> f(3,3, tomb2);
	std::cout << f;
	std::cout << f.det() << std::endl;
	std::cout << f;


	std::cout << f.trans() << std::endl;

	std::cout << std::endl;

	std::cout << a;
	std::cout << a.trans();


	std::cout << f.inverse();
	//Matrix<double> g(3,3,tomb2);
	//std::cout << g*g.inverse();

 	} catch(myexception e){
 		std::cout << e.what()<< std::endl	;
 	}


	return 0;
}