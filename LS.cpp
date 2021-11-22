#include <iostream>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

class LatinSquare {
public:
    int **pointer;
    int order;
    int orderBasic;

    LatinSquare();

    LatinSquare(int order, int orderBasic);

    ~LatinSquare();

    void Allocate();

    void Print() const;

    void PrintFile(string filename) const;

    void MakeBasicLS() const;

    void ShiftAlphabet() const;

    void FillHalfLS(LatinSquare *A, LatinSquare *B, char UorD) const;

};

LatinSquare::LatinSquare() {
    order = 0;
    orderBasic = 0;
    pointer = nullptr;
}

LatinSquare::LatinSquare(int _order, int _orderBasic) {
    order = _order;
    orderBasic = _orderBasic;
    pointer = nullptr;
}

LatinSquare::~LatinSquare() {
    for (int p = 0; p < order; p++) {
        delete[]pointer[p];
    }
    delete[]pointer;
}

void LatinSquare::Allocate() {
    pointer = new int *[order];
    for (int i = 0; i < order; i++) {
        pointer[i] = new int[order];
        for (int j = 0; j < order; j++) {
            pointer[i][j] = 0;
        }
    }
}

void LatinSquare::PrintFile(string filename) const {
    ofstream fileOut;
    fileOut.open(filename, ios::out);
    int ord = order;
    int width = 0;
    while (ord > 0) {
        ord /= 10;
        width += 1;
    }
    for (int j = 0; j < order; j++) {
        for (int i = 0; i < order; i++) {
            fileOut.width(width);
            fileOut << pointer[j][i] << " ";
        }
        fileOut << "\n";
    }
    fileOut.close();
}

void LatinSquare::Print() const {
    int width = 0;
    int ord = order;
    while (ord > 0) {
        ord /= 10;
        width += 1;
    }
    for (int j = 0; j < order; j++) {
        for (int i = 0; i < order; i++) {
            cout.width(width);
            cout << pointer[j][i] << " ";
        }
        cout << endl;
    }
    cout.flush();
}

void LatinSquare::MakeBasicLS() const {
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            pointer[i][j] = (i + j) % order;
        }
    }

}

void LatinSquare::ShiftAlphabet() const {
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            pointer[i][j] += order;
        }
    }
}

void LatinSquare::FillHalfLS(LatinSquare *A, LatinSquare *B, char UorD) const {
    int shift = 0;
    if (UorD == 'd') {
        shift = A->order;
    }
    for (int i = 0; i < A->order; i++) {
        for (int j = 0; j < A->order; j++) {
            pointer[i + shift][j] = A->pointer[i][j];
        }
        for (int j = 0; j < A->order; j++) {
            pointer[i + shift][j + A->order] = B->pointer[i][j];
        }
    }
}

void Permutation(LatinSquare *LS, bool flag) { //вывернутый алгоритм тасования Фишера — Йетса
    int randRow;
    int randColumn;
    int *tempRow;
    int tempElemFromColumn;
    //row permutation
    for (int row = 1; row < LS->order; row++) {
        randRow = rand() % row;
        tempRow = LS->pointer[row];
        LS->pointer[row] = LS->pointer[randRow];
        LS->pointer[randRow] = tempRow;
    }
    //column permutation
    for (int column = 1; column < LS->order; column++) {
        randColumn = rand() % column;
        for (int row = 0; row < LS->order; row++) {
            tempElemFromColumn = LS->pointer[row][randColumn];
            LS->pointer[row][randColumn] = LS->pointer[row][column];
            LS->pointer[row][column] = tempElemFromColumn;
        }
    }

    int *newAlphabetString;
    newAlphabetString = new int[LS->order];
    int tempLetter;
    if (flag) {
        for (int i = 0; i < LS->order; i++) {
            newAlphabetString[i] = i + (LS->order);
        }
        for (int i = 1; i < LS->order; i++) {
            int randLetter = rand() % i;
            tempLetter = newAlphabetString[i];
            newAlphabetString[i] = newAlphabetString[randLetter];
            newAlphabetString[randLetter] = tempLetter;
        }

        for (int column = 0; column < LS->order; column++) {
            for (int row = 0; row < LS->order; row++) {
                int value = LS->pointer[row][column] - LS->order;
                LS->pointer[row][column] = newAlphabetString[value];
            }
        }
    } else {
        for (int i = 0; i < LS->order; i++) {
            newAlphabetString[i] = i;
        }
        for (int i = 1; i < LS->order; i++) {
            int randLetter = rand() % i;
            tempLetter = newAlphabetString[i];
            newAlphabetString[i] = newAlphabetString[randLetter];
            newAlphabetString[randLetter] = tempLetter;
        }

        for (int column = 0; column < LS->order; column++) {
            for (int row = 0; row < LS->order; row++) {
                int value = LS->pointer[row][column];
                LS->pointer[row][column] = newAlphabetString[value];
            }
        }
    }

}

void MakeLS(LatinSquare *LS) {
    if (LS->order == LS->orderBasic) {
        LS->Allocate();
        LS->MakeBasicLS();
        Permutation(LS, 0);
        return;
    }
    //step 1
    //step 1.a
    LatinSquare A(LS->order >> 1, LS->orderBasic);
    thread generateA(MakeLS, &A);
    //step 1.b
    LatinSquare B(LS->order >> 1, LS->orderBasic);
    thread generateB(MakeLS, &B);
    generateA.join();
    generateB.join();
    //step 2
    B.ShiftAlphabet();
    //step 4
    //step 4.1
    LS->Allocate();
    LS->FillHalfLS(&A, &B, 'u');
    //step 3
    //step 3.a
    thread permutationA(Permutation, &A, 0);
    //step 3.b
    thread permutationB(Permutation, &B, 1);
    permutationA.join();
    permutationB.join();
    //step 4
    //step 4.2
    LS->FillHalfLS(&B, &A, 'd');
    //step 5
    Permutation(LS, 0);
}

int main(int argc, char **argv) { //first arg is power of 2, second is output filename
    srand(time(nullptr));
    int order, orderBasic;
    order = atoi(argv[1]); //argv[0] is name of program
    order = 1 << order;
    orderBasic = 8;
    if (order < orderBasic) {
        return 0;
    }
    //cout.flush();
    LatinSquare LS(order, orderBasic);
    unsigned int start_time = clock();
    MakeLS(&LS);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout << "Time is: " << search_time << endl;
    //LS.Print();
    string filename;
    filename = argv[2];
    LS.PrintFile(filename);
    cout << "Done!" << endl;
    cout.flush();
    return 0;
}
