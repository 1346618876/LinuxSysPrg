//#include "String.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class String
{
private:
    char *data; //对于定义的存储型数据，只能定义一个指针，然后动态内存分配了

public:
    String();
    String(const char *another);    //普通构造函数
    String(const String &p);    //拷贝构造函数
    ~String();  //对于存储型类，要定义好其析构函数
    String& operator=(const String &other);
    friend ostream & operator<<(ostream &os,const String &another);
    friend const String operator-(const String& p1, const String& p2);
    friend int fd();
    
};

String::String()
{
    cout << "默认构造函数" << endl;
}

String::String(const char * another)   //普通构造函数
{
    cout << "普通构造函数" << endl;
    data = (char *)malloc(strlen(another) + 1);
    strcpy(data,another);
}

String::String(const String &p) //拷贝构造函数
{
    cout << "拷贝构造函数" << endl;
    data = (char *)malloc(strlen(p.data + 1));
    strcpy(data, p.data);   //strlen传递指针
}

String::~String()
{   
    cout << "析构函数" << endl;
    if (data == NULL) {
        return;
    }
    else
    {
        delete[] data;
        data = NULL;
    }
}

//赋值运算符都需要先释放当前内存空间，再创建一片新的空间
String & String::operator =(const String &other)
{//赋值函数可能是在对象已经实例化之后才执行赋值操作，所以应该先进行判断是否与输入参数一样，不一样时要先进行析构
    cout << "赋值函数" << endl;
    if(this != &other)
    {
        delete [] data;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }
    return *this;   //直接返回本身
}



//注：友元函数在函数定义中不需要加作用域String::operator,否则会提示class "String" has no member "operator<<"，即证明类内friend声明不是该类定义的一部分
ostream & operator<<( ostream & os,const String & another)  //运算符重载   对象+参数1 == 对象.operator+();  参数1<<
{
    cout << "<<运算符重载" << endl;
    os << another.data << endl;
    return os;
}


//符合赋值运算符

const String operator-(const String& p1, const String& p2)
{
    cout << "-运算符重载" <<endl;
    static int repeatsum = 0;
    for(int i = 0; i<strlen(p2.data); i++)
    {
        for(int j = 0; j < strlen(p1.data); j++)
        {
            if(p2.data[i] == p1.data[j])
            {

                repeatsum++;
                for(int k=i+1; i < strlen(p1.data); i++)
                {
                    p1.data[k-1] = p1.data[k];   
                }
            }
        }
        
    }
    for(int i = 0; i < repeatsum; i++)
    {
        p1.data[strlen(p1.data) -1 -i] = 0;
    }
    cout << "af_del_str is : " << p1.data <<endl;
    return p1;
}



int main()
{
    String testa("abc");
    char a[] = "def";
    String testb(a);
    char b[] = "ghi";
    String testc = b;
    String testd("faqbrcu");
    String opjian = testd - testa;  // operator-
    cout << opjian;     // operator<<
}