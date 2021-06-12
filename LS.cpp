#include <iostream>
#include <thread>
#include <cmath>

using namespace std;
typedef unsigned int UI;

struct LS {
    int **pointer = nullptr;
    int order = 0;
    int orderBasic = 0;
};


void Delete(const struct LS LS, const UI *Mask = nullptr) {
    for (int p = 0; p < LS.order; p++) {
        delete[]LS.pointer[p];
    }
    delete[]LS.pointer;
    delete[]Mask;
}


void Print(const struct LS LS) {   //toDo заменить вывод на запись в файл
    for (int j = 0; j < LS.order; j++) {
        for (int i = 0; i < LS.order; i++)
            cout << LS.pointer[j][i] << " ";
        cout << endl;
    }
}


void test(struct LS LS, int g, int t) {
    for (int i = 0; i < LS.order; i++) {
        for (int j = 0; j < LS.order / 2; j++) {
            LS.pointer[i][g] = g;
        }
    }
    if (g % 2 != 0) {
        return;
    }
    int gB = g - (LS.order / int(pow(2, t + 2)));
    int gA = g + (LS.order / int(pow(2, t + 2)));
    thread A(test, LS, gA, t + 1);
    thread B(test, LS, gB, t + 1);
    A.join();
    B.join();
}


void MakeBasicLS(struct LS LS) {   //toDo
    LS.pointer = new int *[LS.order];
    for (int i = 0; i < LS.order; i++) {
        LS.pointer[i] = new int[LS.order];
        for (int j = 0; j < LS.order; j++) {
            LS.pointer[i][j] = 0;
        }
    }
}


void ShiftAlphabet(LS B) {  //toDo

}


void FillHalfLS(struct LS LS, const struct LS A, const struct LS B, char UorD) { //toDo

}


void Permutation(struct LS LS){ //toDo

}


void MakeLS(struct LS LS) {
    if (LS.order == LS.orderBasic) {
        MakeBasicLS(LS);
        return;
    }
    //step 1
    //step 1.a
    struct LS A;
    A.order = (LS.order >> 1);
    A.orderBasic = LS.orderBasic;
    thread generateA(MakeLS, A);
    //step 1.b
    struct LS B;
    B.order = (LS.order >> 1);
    B.orderBasic = LS.orderBasic;
    thread generateB(MakeLS, B);
    generateA.join();
    generateB.join();
    //step 2
    ShiftAlphabet(B);
    //step 4
    //step 4.1
    FillHalfLS(LS, A, B, 'u');
    //step 3
    //step 3.a
    thread permutationA(Permutation, A);
    //step 3.b
    thread permutationB(Permutation, B);
    permutationA.join();
    permutationB.join();
    //step 4
    //step 4.2
    FillHalfLS(LS, A, B, 'd');
    //step 5
    Permutation(LS);
}


int main() {
    srand(time(nullptr));
    LS LS{};

    cout << "Input square order, power of 2:" << endl;
    cin >> LS.order;
    LS.orderBasic = 8;
    if ((LS.order & (LS.order - 1)) != 0) {
        cout << "Incorrect data, set order to 1024" << endl;
        LS.order = 1024;
    }
    cout.flush();

    LS.pointer = new int *[LS.order];
    for (int i = 0; i < LS.order; i++) {
        LS.pointer[i] = new int[LS.order];
        for (int j = 0; j < LS.order; j++) {
            LS.pointer[i][j] = 0;
        }
    }
    //test(LS,(LS.order/2), 0);
    MakeLS(LS);
    Print(LS);
    Delete(LS);
    return 0;
}