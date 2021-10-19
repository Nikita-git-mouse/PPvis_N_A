#include <iostream>
#include "library.h"

using namespace std;

int main()
{
    MySet A;
    A.setter("{1, 2, 3, 4, 5 ,10}");
    MySet B;
    B.setter("{2,4,7,8,10}");

    MySet C;
    C = A;
    C -= B;
    cout << " A = " << A.getter() << endl;
    cout << " B = " << B.getter() << endl;
    cout << " |A| = " << A.capacity() << endl;
    cout << " A is empty? = " << A.isEmpty() << endl;
    cout << " A + B = " << C.getter() << endl;
    cout << " A * B = " << (A * B).getter() << endl;
    cout << " A - B = " << (A - B).getter() << endl;
    cout << " B - A = " << (B - A).getter() << endl;
    cout << " P(A) = " << (A.boolean()).getter() << endl;
    system("pause");
    return 0;
}
