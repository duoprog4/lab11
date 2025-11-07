#include <fstream>
#include <iostream>
using namespace std;
class matrix {
private:
    int n;
    int* data;


public: 
    matrix(int size);
    matrix(const matrix &other);
    ~matrix();
    
    matrix operator+(const matrix &other) const {
        return matrixadd(this->data,other.data);        
    }
    matrix operator*(const matrix &other) {
        return matrixmultiply();
    }
    
    bool filetomatrix(istream &is);
    void print() const;
    long long diagonal_sum() const;
    void swapmatrixrows(int r1, int r2);
    void swapmatrixcols(int c1, int c2);
    void update_matrix_element(int r, int c, int v);

};

void swapmatrixrows(matrix m,int r1 = 0, int r2 = 1);
void swapmatrixcols(matrix m,int c1 = 0, int c2 = 1);
void update_matrix_element(matrix m, int r = 0, int c=0, int v=100);

int main() {
    string filename;
    cout << "Enter filename: " << endl;
    cin >> filename;
    ifstream infile(filename);
    int N;
    infile >> N;
    
    matrix A(N), B(N);
    A.filetomatrix(infile);
    B.filetomatrix(infile);

    matrix sum = A + B;
    matrix product = A * B;

    A.diagonal_sum();

    swapmatrixrows(A,0,1);
    int row1;
    int row2;
    cout << "Enter first swap row: " << endl;
    cin >> row1;
    cout << "Enter second swap row: " << endl;
    cin >> row2;
    swapmatrixrows(A,row1,row2);

    swapmatrixcols(A,0,1);
    int col1;
    int col2;
    cout << "Enter first swap column: " << endl;
    cin >> col1;
    cout << "Enter second swap column: " << endl;
    cin >> col2;
    swapmatrixcols(A,col1,col2);

    update_matrix_element(0,0,100);
    int element_row;
    int element_col;
    int element_value;
    cout << "Enter element row: " << endl;
    cin >> element_row;
    cout << "Enter element column: " << endl;
    cin >> element_col;
    cout << "Enter element value: " << endl;
    cin >> element_value;
    update_matrix_element(element_row,element_col,element_value);

    return 0;
}
