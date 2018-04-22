#include "String.h"
#include <string.h>
#include <utility> // 包含swap函数的头文件，在Linux下需要我们自己声明这个头文件
#include <assert.h>
#include <unordered_map>

/*****************************Member Function*****************************/
String::String(const char* str)//这里不用设置缺省参数，头文件中已经设置过了
	:_size(strlen(str))
	, _capacity(15)
{
	if (_size > _capacity)
		_capacity = _size;
	_str = new char[_capacity + 1];//每次申请_capacity+1个空间，+1是为了来放'\0'
	strcpy(_str, str);
}

String::String(const String& str)
	:_size(str._size)
	, _capacity(15)
{
	if (_size > _capacity)
		_capacity = _size;

	_str = new char[_capacity + 1];
	String tmp(str._str);
	swap(_str, tmp._str);            //其定义在utility中
									 //_str = old._str               //记住这里不能这么赋值，出了这个作用域以后，
									 //old对象所属的那个空间就直接析构了
									 //这样_str等于指向了一块已经释放了的内存，再在析构的时候释放_str就会出错，蠢了蠢了
}

String& String::operator=(const String& str) {
	if (this != &str) {
		if (_capacity < str._size) {
            _capacity = str._size;
            _Expand();
		}
		String tmp(str._str);
		swap(_str, tmp._str);
		_size = str._size;
	}

	return *this;
}

String::~String() {
	if (_str) {
		delete[] _str;
		_str = NULL;
		_capacity = _size = 0;
	}
}

/**************************Capacity************************************/
size_t String::Size() {
	return _size;
}

size_t String::Capacity() {
	return _capacity;
}

size_t String::Length(){
    return _size;
}

//调整字符串大小(影响size)
//1.如果n比size小，字符串缩减到n的大小的长度
//  后面的那部分就不要了
//2.如果n比size大
//  a)如果c没有传，那么后面多的那部分就都是'\0'
//  b)如果c传了，那么后面多的那部分就是字符c
void String::Resize(size_t n,char c){
    if(n <= _size){
        while(n < _size){
            Pop_Back();
        }
        return;
    }

    if(n > _capacity){
        _capacity = n;
        _Expand();
    }

    while(_size < n){
        Push_Back(c);
    }
}

//调整容量大小，不对字符串作任何改变(影响capacity)
//如果n大于当前的字符串容量
//则该函数重新分配一块空间给字符串
//但是重新分配的空间的大小并不就是reserve后面括号中的值的大小
//具体分配的空间的大小还是按照设计的分配空间的方式分配的
//在我设计的这个string类中就是按*2分配的
//但在实际的string类中是按每次大小+16分配的
//为容器预留足够的空间，避免不必要的重复分配
//如果n小于当前的capacity，那么capacity并无变化
void String::Reserve(size_t n){
    if(n <= _capacity){
        return;
    }

    _capacity *= 2;
    while(_capacity < n){
        _capacity *= 2;
    }

    _Expand();
}

//将_str设为空字符串
//注意不是设为空指针
void String::Clear(){
    _str[0] = '\0';
    _size = 0;
}

bool String::Empty(){
    if(_size == 0)
        return true;
    return false;
}

/*****************************Element access*******************************/
char& String::Front(){
    assert(_size > 0);
    return _str[0];
}

const char& String::Front() const {
    assert(_size > 0);
    cout << "const Front" << endl;
    const char& ret = _str[0];
    return ret;
}

char& String::Back(){
    assert(_size > 0);
    return _str[_size - 1];
}

const char& String::Back() const{
    assert(_size > 0);
    cout << "const Back" << endl;
    const char& ret = _str[_size - 1];
    return ret;
}

//如果pos的位置刚好等于size
//那么会返回一个'\0'的引用
char& String::operator[](size_t pos){
    assert(pos <= _size);
    return _str[pos];
}

/**********************************Modifies********************************/
void String::Swap(String& str) {
	swap(_str, str._str);
	swap(_size, str._size);
	swap(_capacity, str._capacity);
}

void String::Push_Back(char c) {
	if (_size >= _capacity) {
		_capacity *= 2;
        _Expand();
	}
	_str[_size] = c;
	_str[_size + 1] = '\0';
	_size += 1;
}

//从pos位置开始向后删除count个字符
//允许pos = _size，这样的情况什么都不做
//pos不传默认给0.即从最开始开始删
//count默认给-1，即size_t能表示的最大值
//如果pos+count的值要比_size大了
//那么就默认为删除pos后之后的所以字符
void String::Erase(size_t pos,size_t count){
    assert(pos <= _size);
    if(count > _size || pos + count >= _size){
        //这样的情况都是删除pos之后的所有字符
        _str[pos] = '\0';
        _size -= (_size - pos);
        return;
    }

    //剩下的情况就都是pos + count加起来没有超过_size的
    for(size_t i = pos + count; i <= _size ; ++i){
        _str[pos] = _str[i];
        pos++;
    }
    _size -= count;
}

//注意原来_str[_size]的位置就是'\0'
void String::Pop_Back(){
    assert(_size > 0);
    _str[_size - 1] = '\0';
    --_size;
} 

//注意这里的insert的往pos的后面插入
//给了一个下标pos,那么我就要在pos+1这个位置插入一个字符
void String::Insert(size_t pos, char ch){
    //注意不能想下面这样写，因为_size的类型是size_t
   // if(pos > _size - 1){
   //     return;
   // }
    if(pos > _size || pos + 1 > _size){
        cout << "invalid pos !!" << endl;
        return;
    }

    if(_size == _capacity){
        _capacity *= 2;
        _Expand();
    }

    if(_size == 0){
        Push_Back(ch);
        return;
    }
    //_str[_size]的位置是'\0'
    for(size_t i = _size;i > pos ; --i){
        _str[i + 1] = _str[i];
    }

    _str[pos + 1] = ch;
    _size += 1;
} 

String& String::operator+=(const String& str) {
	if (_size + str._size >  _capacity) {
		//这就需要重新申请空间
		size_t max = _capacity;
		if (str._size > max) {
			max = str._size;
		}
		_capacity = max * 2;
        _Expand();
	}
	_size += str._size;
	//没进入if说明就不用重新申请空间
	strcat(_str, str._str);
	return *this;
}

String& String::operator+=(const char* str) {
	if (_size + strlen(str) > _capacity) {
		//这就需要重新申请空间
		size_t max = _capacity;
		if (strlen(str) > max) {
			max = strlen(str);
		}
		_capacity = max * 2;
        _Expand();
	}

	_size += strlen(str);
	//没进入if说明就不用重新申请空间
	strcat(_str, str);
	return *this;
}

String& String::operator+=(char c) {
	Push_Back(c);
	return *this;
}

/*****************************String operations**********************/
char* String::C_Str(){
    return _str;
}

size_t String::Find(char c,size_t pos) const{
    if(pos < _size){
        for(size_t i = pos; i< _size;++i){
            if(_str[i] == c)
                return i;
        }
    }

    return -1;
}

size_t String::Find(const char* c,size_t pos)const {
    if(pos < _size){
        size_t len = strlen(c);
        //len如果是0表示空字符串
        //直接返回pos的位置
        if(len == 0){
            return pos;
        }
        //pos + len的长度_size之内才可能存在
        if(pos + len <= _size){
            char* tmp = _str;
            tmp += pos;
            //从pos位置开始进行strstr
            char * ret = strstr(tmp,c);
            if(ret){
                //返回 ret到_str的偏移量
                return ret-_str;
            }
        }
    }
    return -1;
}

//从pos位置开始，向后找len个长度作为子串
//pos缺省为0，len缺省为-1
//即len如果不传，表示取pos后的所有内容
//pos可以为_size，那么返回的String就是空字符串
String String::Substr(size_t pos,size_t len)const{
    assert(pos <=_size);
    if(len >= _size || pos + len >= _size ){
        //把pos后面的所有内容全部返回
        String ret(_str + pos);
        return ret;
    }else{
        char* tmp = _str + pos;
        tmp[len] = '\0';
        String ret(tmp);
        return ret;
    }

}
/************************string类的一些友元函数**********************/
ostream& operator<<(ostream& os, const String& str) {
	os << str._str << endl;
	return os;
}

String operator+(const String& str1, const String& str2) {
	String ret(str1);
	ret += str2;
    cout << "ret" << &ret << endl;
	return ret;
}

/******************私有的扩容函数，很多需要扩容的函数中都要用到******/
void String::_Expand(){
    char* tmp = _str;
    _str = new char[_capacity + 1];
    strcpy(_str,tmp);
    delete[] tmp;
}
