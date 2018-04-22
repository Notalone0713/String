#include "String.h"
#include <string>

void Print(String& s) {
	cout << s << " " << s.Size() << " " << s.Capacity() << " " << endl;
    cout << (void*)s.C_Str() << endl;
}

void Print(string& s) {
	cout << s << " " << s.size() << " " << s.capacity() << " " << endl;
    cout << (void*)s.c_str() << endl;
}

//测试构造函数，拷贝构造函数，以及赋值运算符重载
void Test1() {
	String s1;
	String s2("hello");
	Print(s2);
	String s3("worldworldworldworld");
	Print(s3);
	String s4(s2);
	Print(s4);
	s3 = s2;
	Print(s3);
}

//测试+=运算符
void Test2() {
	String s1("hello");
	Print(s1);
	String s2(" world");
	s1 += s2;
	Print(s1);
	s1 += " hi";
	Print(s1);
	s1 += '!';
	Print(s1);
	s1 += '?';
	Print(s1);


	string s3("hello");
	Print(s3);
	string s4(" world");
	s3 += s4;
	Print(s3);
	s3 += " hi";
	Print(s3);
	s3 += '!';
	Print(s3);
	s3 += '?';
	Print(s3);
}

//测试+运算符
//有一点问题，Linux跑起来和Windows下跑起来结果不一样
//因为VS下s5=s1+s2+s3+s4这一句是通过拷贝了一个临时对象传给s5
//并调用了拷贝构造函数
//而Linux下这个编译器进行了优化，执行了这一句的时候并没有发生拷贝
//而是发生了RVO(return value optimize,返回值优化)
//是通过转移语义直接将临时对象给了s5
//可以通过打印返回值的地址和s5的地址看到两者的地址是一样的
//可以在编译的时候设置-fno-elide-constructors 选项来让编译器不进行优化
void Test3() {
	String s1("Hello");
	String s2(" world");
	String s3("!");
	String s4(" My name is pigff!");
	String s5 = s1 + s2 + s3 + s4;
    cout << "s5:" <<  &s5 << endl;
	String s6;
	s6 = s1 + s2 + s3 + s4;
    cout << "s6" << &s6 << endl;
	Print(s5);
	Print(s6);

    string s11("Hello");
	string s22(" world");
	string s33("!");
	string s44(" My name is pigff!");
	string s55 = s11 + s22 + s33 + s44;
	string s66;
	s66 = s11 + s22 + s33 + s44;
	Print(s55);
	Print(s66);
}

//测试Front和Back以及Pop_Back
void Test4(){
    String s1("hello world!");
    Print(s1);
    s1.Back() = '!';
    Print(s1);
    s1.Front() = 's';
    Print(s1);

    const String s2("pigff");
    const char& front = s2.Front();
    const char& back = s2.Back();
    
    cout << front << " " << back << endl;
    s1.Pop_Back();
    Print(s1);
}

//测试insert
void Test5(){
    String s1;
    String s2("hello");
    String s3("sfhhsadhksaljdasd");

    //s1.Insert(1,'c');
    //s1.Insert(0,'c');
    //s2.Insert(0,'h');
    //s2.Insert(5,'o');
    s3.Insert(-1,'!');
    Print(s3);
}

//测试Resize
void Test6(){
    String s1("hello");
    //s1.Resize(4);
    //s1.Resize(6);
    s1.Resize(20,'!');
    Print(s1);
}

//测试Reserve
void Test7(){
    String s1("hello");
    Print(s1);
    s1.Reserve(6);
    Print(s1);
    s1.Reserve(20);
    Print(s1);
}

//测试clear和empty
void Test8(){
    String s1("hello");
	cout << (void*)s1.C_Str() << endl;
	cout << s1.Empty() << endl;
	s1.Clear();
	cout << (void*)s1.C_Str() << endl;
	cout << s1.Empty() << endl;
}

//测试operator[]
void Test9(){
    String s1("hello");
    for(size_t i = 0 ; i <=s1.Size();++i){
        cout << s1[i] << " ";
    }
    cout << "!" << endl;
}

//测试Swap
void Test10(){
    String s1("hello");
    String s2("My name is pigff!!!");
    Print(s1);
    Print(s2);
    s1.Swap(s2);
    Print(s1);
    Print(s2);
}

//测试Erase
void Test11(){
    String s1("hello");
    //s1.Erase();
    //s1.Erase(1);
    //s1.Erase(6);
    //s1.Erase(2,7);
    //s1.Erase(2,3);
    //s1.Erase(2,2);
    s1.Erase(1,2);
    Print(s1);
}

//测试Find
void Test12(){
    String s1("hellhello");
   // cout << s1.Find('h') << endl;
   // cout << s1.Find('h',2) << endl;
   // cout << s1.Find('h',10) << endl;
   // cout << s1.Find('c') << endl;
   // cout << s1.Find('o',3) << endl;
   
    cout << s1.Find("hello") << endl;
    cout << s1.Find("hello",5) << endl;
    cout << s1.Find("dasf") << endl;
    cout << s1.Find("fasdgadgadfads") << endl;

}

//测试Substr
void Test13(){
    String s1("hello");
    cout << s1.Substr() << endl;
    cout << s1.Substr(1) << endl;
    cout << s1.Substr(1,6) << endl;
    cout << s1.Substr(1,3) << endl;
    cout << s1.Substr(6) << endl;
}


int main() {
	//Test1();    
	//Test2();
	//Test3();
    //Test4();
	//Test5();
    //Test6();
    //Test7();
    //Test8();
    //Test9();
    //Test10();
    //Test11();
    //Test12();
    Test13();
    return 0;
}

