#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class matrix {
private:
    int n;
    int* data;

public: 
    matrix(int size) {
        n = size;
        data = new int[n * n]();
    }

    matrix(const matrix &other) {
        n = other.n;
        data = new int[n * n];
        for (int i = 0; i < n * n; ++i)
            data[i] = other.data[i];
    }

    ~matrix() {
        delete[] data;
    }

    matrix operator+(const matrix &other) const {
        matrix matrixresult(n);
        for (int i = 0; i < n*n; i++) {
            matrixresult.data[i] = this->data[i] + other.data[i];
        }
        return matrixresult;
    }

    matrix operator*(const matrix &other) const {
        matrix matrixresult(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += this->data[i*n + k] * other.data[k*n + j];
                }
                matrixresult.data[i*n + j] = sum;
            }
        }
        return matrixresult;
    }

    void display() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(4) << data[i * n + j];
            }
            cout << '\n';
        }
    }

    bool filetomatrix(istream &is) {
        for (int i = 0; i < n * n; ++i) {
            if (!(is >> data[i])) return false;
        }
        return true;
    }

    long long diagonal_sum() const {
        long long main_sum = 0;
        long long secondary_sum = 0;
        for (int i = 0; i < n; i++) {
            main_sum += data[i * n + i];
            secondary_sum += data[i * n + (n - 1 - i)];
        }
        cout << "Main diagonal sum: " << main_sum << endl;
        cout << "Secondary diagonal sum: " << secondary_sum << endl;
        cout << "Total diagonal sum: " << (main_sum + secondary_sum) << endl;
        return main_sum + secondary_sum;
    }

    void swapmatrixrows(int r1, int r2) {
        if (r1 < 0 || r2 < 0 || r1 >= n || r2 >= n) {
            cerr << "Error: invalid row indices (" << r1 << "," << r2 << ")" << endl;
            return;
        }
        for (int j = 0; j < n; ++j) {
            swap(data[r1 * n + j], data[r2 * n + j]);
        }
    }

    void swapmatrixcols(int c1, int c2) {
        if (c1 < 0 || c2 < 0 || c1 >= n || c2 >= n) {
            cerr << "Error: invalid column indices (" << c1 << "," << c2 << ")" << endl;
            return;
        }
        for (int i = 0; i < n; ++i) {
            swap(data[i * n + c1], data[i * n + c2]);
        }
    }

    void update_matrix_element(int r, int c, int v) {
        if (r < 0 || c < 0 || r >= n || c >= n) {
            cerr << "Error: invalid element indices (" << r << "," << c << ")" << endl;
            return;
        }
        data[r * n + c] = v;
    }
};

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: could not open file " << filename << endl;
        return 1;
    }

    int N;
    infile >> N;
    
    matrix A(N), B(N);
    if (!A.filetomatrix(infile) || !B.filetomatrix(infile)) {
        cerr << "Error: not enough data in file" << endl;
        return 1;
    }

    cout << "\nMatrix A:\n"; A.display();
    cout << "\nMatrix B:\n"; B.display();

    matrix sum = A + B;
    cout << "\nA + B:\n"; sum.display();

    matrix product = A * B;
    cout << "\nA * B:\n"; product.display();

    cout << "\nDiagonal sum of A:\n";
    A.diagonal_sum();

    int row1 = 0, row2 = 1; // defaults
    string line;
    cout << "Enter two rows to swap (or type 'default' for 0 1): "<< endl;
    getline(cin >> ws, line);
    if (!line.empty()) {
        if (line != "default") {
            stringstream ss(line);
            ss >> row1 >> row2;
        }
    }
    matrix A_rowswapped = A; // copy
    A_rowswapped.swapmatrixrows(row1, row2);
    cout << "\nMatrix after row swap:\n";
    A_rowswapped.display();

    int col1 = 0, col2 = 1; // defaults
    string col_line;
    cout << "Enter two columns to swap (or type 'default' for 0 1): " << endl;
    getline(cin >> ws, col_line);
    if (!col_line.empty()) {
        if (col_line != "default") {
            stringstream ss(col_line);
            ss >> col1 >> col2;
        }
    }
    matrix A_colswapped = A; // copy
    A_colswapped.swapmatrixcols(col1, col2);
    cout << "\nMatrix after column swap:\n";
    A_colswapped.display();

    int element_row = 0, element_col = 0, element_value = 100; // defaults
    string element_line;
    cout << "Enter element row, column, value (or type 'default' for 0 0 100): " << endl;
    getline(cin >> ws, element_line);
    if (!element_line.empty()) {
        if (element_line != "default") {
            stringstream ss(element_line);
            ss >> element_row >> element_col >> element_value;
        }
    }
    matrix A_elementupdated = A;
    A_elementupdated.update_matrix_element(element_row, element_col, element_value);
    cout << "\nMatrix after element update:\n";
    A_elementupdated.display();

    return 0;
}
