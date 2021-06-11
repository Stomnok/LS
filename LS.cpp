#include<iostream>
#include<thread>

using namespace std;
typedef unsigned int UI;

struct LS{
    int ** pointer;
    int order;
    int orderBasic;
};


void Delete(LS LS, UI *Mask)
{
    for(int p=0; p<LS.order; p++) {
        delete[]LS.pointer[p];
    }
    delete[]LS.pointer;
    delete[]Mask;
    return;
}


void Print(LS LS) //заменить вывод на запись в файл
{
    for(int j=0;j<LS.order;j++){
        for(int i=0;i<LS.order;i++)
            cout<<LS.pointer[j][i]<<" ";
        cout<<endl;
    }
    return;
}


void test(LS LS, int g)
{
    if(g==2){
        for(int i=0;i<LS.order;i++) {
            for(int j=0;j<LS.order/2;j++) {
                LS.pointer[i][j]=2;
            }
        }
    } else {
       for(int i=0;i<LS.order;i++) {
            for(int j=LS.order/2;j<LS.order;j++) {
                LS.pointer[i][j]=3;
            }
        } 
    }
    return;
}


void Make_LS(LS LS)
{
    for(int i=0;i<LS.order;i++) {
        for(int j=0;j<LS.order;j++) {
            LS.pointer[i][j]=1;
        }
    }
    for(int i=0;i<LS.order;i++) {
        for(int j=0;j<LS.order;j++) {
            LS.pointer[i][5]=5;
        }
    }
    //thread A (test, LS, 2);
    //thread B (test, LS, 3);
    //A.join();
    //B.join();
    
    return;
}


int main()
{
    srand(time(NULL));
    LS LS;

    cout<<"Input square order, power of 2:"<<endl;
    cin>>LS.order;
    LS.orderBasic = 8;
    if(LS.order & (LS.order-1) != 0) {
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
    return 0;
}