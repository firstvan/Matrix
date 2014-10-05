/* Usage: give the dim(1 number)
 * give the matrix elements
 */
#include <iostream>


int main(int argc, char ** argv){
    
    int dim;
    
    std::cin >> dim;

    double matrix[dim][dim];
    
    for(int i = 0; i< dim; i++)
        for(int j = 0; j < dim; j++)
            std::cin >> matrix[i][j];
    
    
    //LU felbontás
    
    for(int k = 0; k < dim - 1; k++)
        for(int i = k+1; i < dim; i++) {
                matrix[i][k] = matrix[i][k] / (double)matrix[k][k]; 

                for(int j = k + 1; j < dim; j++)
                    matrix[i][j] = matrix[i][j] - (matrix[i][k]*matrix[k][j]);
            } 
    
    //LU mátrix kiiratása
    
    std::cout << std::endl;

    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
            std::cout << matrix[i][j] << ' '; 
    
        std::cout << std::endl;
    }


    return 0;
    }
