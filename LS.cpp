#include <iostream>
#include <thread>
#include <cmath>

using namespace std;
typedef unsigned int UI;

struct LS{
    int ** pointer;
    int order;
    int orderBasic;
};


void Delete(const LS LS, const UI *Mask = nullptr)
{
    for(int p=0; p<LS.order; p++) {
        delete[]LS.pointer[p];
    }
    delete[]LS.pointer;
    delete[]Mask;
}


void Print(const LS LS) //заменить вывод на запись в файл
{
    for(int j=0;j<LS.order;j++){
        for(int i=0;i<LS.order;i++)
            cout<<LS.pointer[j][i]<<" ";
        cout<<endl;
    }
}


void test(LS LS, int g, int t)
{
    for(int i = 0; i < LS.order; i++) {
        for (int j = 0; j < LS.order / 2; j++) {
            LS.pointer[i][g] = g;
        }
    }
    if(g%2!=0){
        return;
    }
    int gB=g-(LS.order/int(pow(2,t+2)));
    int gA=g+(LS.order/int(pow(2,t+2)));
    thread A (test, LS, gA,t+1);
    thread B (test, LS, gB,t+1);
    A.join();
    B.join();
}


void Make_LS(LS LS)
{
    for(int i=0;i<LS.order;i++) {
        for(int j=0;j<LS.order;j++) {
            LS.pointer[i][j]=0;
        }
    }
    test(LS,(LS.order/2), 0);
}


int main()
{
    srand(time(nullptr));
    LS LS{};

    cout<<"Input square order, power of 2:"<<endl;
    cin>>LS.order;
    LS.orderBasic = 8;
    if((LS.order & (LS.order-1)) != 0) {
        cout<<"Incorrect data, set order to 1024"<<endl;
        LS.order = 1024;
    }
    cout.flush();

    LS.pointer = new int*[LS.order];
    for(int i=0;i<LS.order;i++) {
        LS.pointer[i]=new int[LS.order];
    }

    Make_LS(LS);
    Print(LS);
    Delete(LS);
    return 0;
}