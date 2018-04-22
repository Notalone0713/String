#pragma once

#include <iostream>
using namespace std;

class String{
    friend ostream& operator<<(ostream& os ,const String& str);
    friend String operator+(const String& str1,const String& str2);
public:
    //Member Function
    String(const char* str = "");
    String(const String& str);
    ~String();
    String& operator=(const String& str);

    //Capacity
    size_t Size();
    size_t Capacity();
    size_t Length();//本质上与size没有区别，一开始只有Length，为了和STL一致引入了size
    void Resize(size_t n,char c = '\0');
    void Reserve(size_t n = 0);
    void Clear();//删除字符串但是空间还是没释放的
    bool Empty();

    //Element access
    char& Front();
    const char& Front() const;
    char& Back();
    const char& Back() const;
    char& operator[](size_t pos);

    //Modifiers
    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);
    void Push_Back(char c);
    void Swap(String& str);
    void Pop_Back(); 
    void Insert(size_t pos, char ch); 
    void Insert(size_t pos, const char* str); 
    void Erase(size_t pos = 0, size_t count = -1); 

    //String operations
    char* C_Str();
    size_t Find(char ch,size_t pos = 0) const; 
    size_t Find(const char* str,size_t pos = 0) const; 
    String Substr(size_t pos = 0,size_t len = -1)const;

private:
    char* _str;
    size_t _size;
    size_t _capacity;

    //扩容函数
    void _Expand();
};

