#include <iostream>
#include "gerastr.h"
using namespace std;
using ll = long long;

ll my_abs(ll x) {
	if (x < 0)
		return -x;
	return x;
}

ll capacity(ll x) {
	ll k = 1;
	while (x > 9) {
		k++;
		x /= 10;
	}
	return k;
}

str::str() : len(0) {};

str::str(const char *arr) {
	len = 0;
	while (arr[len] != '\0')
		len++;

	buffer = new char[len + 1];
	for (ll i = 0; arr[i] != '\0'; i++)
		buffer[i] = arr[i];
	buffer[len] = '\0';
};

str::str(const str &obj) : len(obj.len) {
	buffer = new char[len + 1];
	for (ll i = 0; i < len; i++)
		buffer[i] = obj[i];
};

str::str(char ch) : len(1) {
	buffer = new char[2];
	buffer[0] = ch;
	buffer[1] = '\0';
};

str::str(ll num) : len(capacity(num)) {
	str result = "";
	result.add(num);
	copy(result);
};

str::str(int num) : len(capacity(static_cast<ll>(num))) {
	str result = "";
	result.add(static_cast<ll>(num));
	copy(result);
};

str::~str() {
	delete[] buffer;
};

str &str::operator=(const str &obj) {
	if (this == &obj)
		return *this;
	len = obj.len;
	copy(obj);
	return *this;
};

str &str::operator=(const char *arr) {
	len = str(arr).len;
	copy(str(arr));
	return *this;
};

str &str::operator=(char ch) {
	len = str(ch).len;
	copy(str(ch));
	return *this;
};

str &str::operator=(ll num) {
	clear();
	add(num);
	return *this;
};

str &str::operator=(int num) {
	return operator=(static_cast<ll>(num));
};

str &str::operator+=(const str &obj) {
	str res = copy_add(obj);
	len = res.len;
	copy(res);
	return *this;
};

str &str::operator+=(const char *arr) {
	str res = copy_add(str(arr));
	len = res.len;
	copy(res);
	return *this;
};

str &str::operator+=(char ch) {
	str res = copy_add(str(ch));
	len = res.len;
	copy(res);
	return *this;
};

str &str::operator+=(ll num) {
	add(num);
	return *this;
};

str &str::operator+=(int num) {
	return operator+=(static_cast<ll>(num));
};

str &str::operator*=(ll num) {
	str result = str(read(0, len)) * num;
	copy(result);
	return *this;
};

str str::operator+(const str &obj) const {
	return copy_add(obj);
};

str str::operator+(const char *arr) const {
	return copy_add(str(arr));
};

str str::operator+(char ch) const {
	return copy_add(str(ch));
};

str str::operator+(ll num) const {
	str result = read(0, len);
	result.add(num);
	return result;
};

str str::operator+(int num) const {
	return operator+(static_cast<ll>(num));
};

str str::operator*(ll num) const {
	str result = "";
	for (ll i = 0; i < num; i++)
		result += read(0, len);
	return result;
};

bool str::operator==(const str &obj) const {
	if (len != obj.len)
		return false;
	for (ll i = 0; i < len; i++)
		if (buffer[i] != obj[i])
			return false;
	return true;
};

str operator+(const char *left, const str &right) {
	return str(left) + right;
};

str operator+(char left, const str &right) {
	return str(left) + right;
};

ostream &operator<<(ostream &out, const str &obj) {
	out << obj.buffer;
	return out;
};

istream &operator>>(istream &in, str &obj) {
	char *new_buffer = new char[1024];
	in.getline(new_buffer, 1024);
	if (obj.buffer != nullptr)
		delete[] obj.buffer;
	obj = new_buffer;
	delete[] new_buffer;
	return in;
};

/* Возвращает символ по указанному индексу в буфере 
Индекс "-1" указывает на последний элемент буфера 
Индекс "-2" на второй элемент с конца и т.д. */
char str::operator[](ll index) const {
	if (index < 0)
		index = len - index;
	return buffer[index];
};

// Возвращает массив char текущего буфера
char *str::operator()() const {
	return buffer;
};

// Возвращает размер текущего буфера
const ll str::size() const {
	return len;
};

// Возвращает индекс искомого элемента в буфере
ll str::find_first(char ch) const {
	for (ll i = 0; i < len; i++)
		if (buffer[i] == ch)
			return i;
	return '\0';
};

// Возвращает индекс первого элемента искомой строки в буфере
ll str::find_first_string(str obj) const {
	for (ll i = 0; i < len; i++)
		if (buffer[i] == obj[0])
			if (str(read(i, i + obj.len)) == obj)
				return i;
	return '\0';
};

// Проверяет содержится ли символ в буфере
bool str::contain(char ch) const {
	for (ll i = 0; i < len; i++)
		if (buffer[i] == ch)
			return true;
	return false;
};

// Проверяет содержится ли строка в буфере
bool str::contain_string(str obj) const {
	for (ll i = 0; i < len; i++)
		if (buffer[i] == obj[0])
			if (str(read(i, i + obj.len)) == obj)
				return true;
	return false;
}

// Возвращает массив char по заданным границам
char *str::read(ll left, ll right) const {
	if (left == right) {
		char *empty = new char[1];
		empty[0] = '\0';
		return empty;
	}

	ll length = my_abs(right - left);
	char *new_buffer = new char[length];
	
	ll j = 0;
	if (left < right)
		for (ll i = left; j < length; i++)
			new_buffer[j++] = buffer[i];
	else
		for (ll i = left; j < length; i--)
			new_buffer[j++] = buffer[i];

	new_buffer[length] = '\0';
	return new_buffer;
};

// Удаляет последний элемент
void str::pop_back() {
	str result = read(0, len - 1);
	copy(result);
};

// Удаляет первый элемент
void str::pop_forward() {
	str result = read(1, len);
	copy(result);
};

// Удаляет некоторое количество элементов по индексу
void str::remove(ll index, ll amount) {
	if (index == -1)
		index = len - 1;
	if (amount < 1)
		return;
	if (index == 0 && amount == len) {
		delete[] buffer;
		buffer = nullptr;
	}
	if (index == len - 1 && amount == 1) {
		pop_back();
		return;
	}
	if (index == 0 && amount == 1) {
		pop_forward();
		return;
	}
	if (amount > (len - index))
		amount = len - index;
	str result = read(0, index);
	result += read(index + amount, len);
	copy(result);
};

// Инвертирует строку по заданным границам
void str::reverse(ll left, ll right) {
	if (right == -1)
		right = len - 1;
	str result = read(0, left);
	result += read(right, left - 1);
	result += read(right + 1, len);
	copy(result);
};

void str::copy(const str &obj) {
	buffer = new char[obj.len];
	for (ll i = 0; obj[i] != '\0'; i++)
		buffer[i] = obj[i];
	buffer[obj.len] = '\0';
	len = obj.len;
};

str str::copy_add(const str &obj) const {
	char *new_buffer = new char[len + obj.len];
	for (ll i = 0; i < len + obj.len; i++) {
		if (i < len)
			new_buffer[i] = buffer[i];
		else
			new_buffer[i] = obj[i - len];
	}
	new_buffer[len + obj.len] = '\0';
	str result = new_buffer;
	delete[] new_buffer;
	return result;
};

// Вставка элементов перед индексом
void str::insert(str obj, ll index) {
	str result = read(0, index);
	result += obj;
	result += read(index, len);
	copy(result);
};

// Количество символов в буфере
ll str::count(char ch) const {
	ll cnt = 0;
	for (ll i = 0; i < len; i++)
		if (buffer[i] == ch)
			cnt++;
	return cnt;
};

/* Метод возвращающий массив из объектов класса str
Заполненный строками разделенными по символу ch */
str *str::parse(char ch) const {
	const ll cnt = count(ch) + 1;
	str *result = new str[cnt];
	if (cnt == 1) {
		result[0] = str(read(0, len));
		return result;
	}
	ll left = 0, k = 0;
	for (ll i = 0; i < len; i++) {
		if (buffer[i] == ch) {
			result[k++] = str(read(left, i));
			left = i + 1;
		}
	}
	if (left < len)
		result[k] = str(read(left, len));
	return result;
};

// Возвращает массив char текущего объекта
char *str::to_char() const {
	return buffer;
};

// Возвращает целочисленное значение текущего объекта
ll str::to_int() const {
	ll k = 1;
	ll result = 0;
	for (ll i = len - 1; i > 0; i--) {
		result += (buffer[i] - '0') * k;
		k *= 10;
	}
	if (buffer[0] != '-')
		result += (buffer[0] - '0') * k;
	else
		result *= -1;
	return result;
};

// Возвращает значение с плавающей точкой текущего объекта
long double str::to_float() const {
	double k = 0.1;
	long double result = 0.0;
	str stat = read(0, find_first('.'));
	result += (long double)stat.to_int();
	stat = read(find_first('.') + 1, len);
	for (ll i = 0; i < stat.size(); i++) {
		if (buffer[0] == '-')
			result -= (long double)(stat[i] - 48) * k;
		else
			result += (long double)(stat[i] - 48) * k;
		k *= 0.1;
	}
	return result;
};

// Перевод в 2-ую систему счисления
str str::bin() const {
	return notation(2);
};

// Перевод в 8-ую систему счисления
str str::oct() const {
	return notation(8);
};

// Перевод в 16-ую систему счисления
str str::hex() const {
	return notation(16);
}

/* Переводит строковые "целочисленные" значения в 10-ой системе 
в различные системы счислений до 16-ой включительно
8 388 607 - максимальное число которое способен принять объект класса */
str str::notation(ll k) const {
	const str alphabet = "0123456789ABCDEF";
	str result = "";
	ll num = my_abs(to_int()), old = num;
	while (num > 0) {
		result = alphabet[num % k] + result;
		num /= k;
	}
	if (buffer[0] == '-')
		result = '-' + result;
	if (old == 0)
		result += '0';
	return result;
};

/* Переводит строковое значение из различных систем 
счислений в строку с "целочисленным" значением в 10-ой системе */
str str::decimal(ll n) const {
	const str alphabet = "0123456789ABCDEF";
	str result = "";
	ll k = 1;
	ll sum = 0;
	for (ll i = len - 1; i > 0; i--) {
		sum += alphabet.find_first(buffer[i]) * k;
		k *= n;
	}
	if (buffer[0] == '-')
		result = '-' + str(sum);
	else
		result = (sum + alphabet.find_first(buffer[0]) * k);
	return result;
}

/* Добавляет целочисленное значение к буферу, конвертируя каждый разряд в char 
9 223 372 036 854 775 807 - максимальное значение, которое может принять метод */
void str::add(ll num) {
	str result = "";
	bool negative = false;
	if (num < 0)
		negative = true;
	num = my_abs(num);
	ll length = capacity(num);
	char ch;
	for (ll i = 1; i <= length; i++) {
		ch = (num % 10) + 48;
		result += ch;
		num /= 10;
	}
	result.reverse();
	if (negative)
		result = str(read(0, len)) + '-' + result;
	else
		result = str(read(0, len)) + result;
	copy(result);
};

// Очищает буфер объекта
void str::clear() {
	buffer = new char[1];
	buffer[0] = '\0';
};
