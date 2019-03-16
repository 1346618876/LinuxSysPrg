#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;


int main()
{
    char temp[20] = "asdfghjkl";
    cout << "temp is "<< temp << endl;
    const int sz = 3;
    int strsize = (int)strlen(temp);
    const int rear = strsize - 1; //末尾字母下标
//    cout << "strsize is: " <<strsize <<endl;
//    cout << "rear is: " <<rear <<endl;
    char * u = (char *)malloc(sz);
    for (int i = 0; i < sz; i++)
    {
        u[i] = temp[rear - sz + 1 + i];
    }
//    cout << "reversed u is: " << u <<endl;
    for (int i = rear - sz; i >= 0; i--)
    {
 //       cout << "reversed temp0 is: " << temp[rear - sz] <<endl;
        static int j = rear;
 //       cout << "reversed temp0 is: " << temp[j] <<endl;
        temp[j] = temp[i];
        j--;
    }
//    cout << "reversed temp1 is: " <<temp <<endl;
    for(int i = 0; i < sz; i++)
    {
        temp[i] = u[i];
    }

    cout << "reversed temp is: " <<temp <<endl;
    return 0;

}