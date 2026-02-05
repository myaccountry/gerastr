#pragma once
#include <iostream>

long long my_abs(long long x);

class str {
	long long len = 0;
	char *buffer = new char[1];
public:
	// Operator overloading
		// Internal:
			str();
			str(const char *arr);
			str(const str &obj);
			str(char ch);
			str(long long num);
			str(int num);
			~str();
			str &operator=(const str &obj);
			str &operator=(const char *arr);
			str &operator=(char ch);
			str &operator=(int num);
			str &operator=(long long num);
			str &operator+=(const str &obj);
			str &operator+=(const char *arr);
			str &operator+=(char ch);
			str &operator+=(long long num);
			str &operator+=(int num);
			str &operator*=(long long num);
			str operator+(const str &obj) const;
			str operator+(const char *arr) const;
			str operator+(char ch) const;
			str operator+(long long num) const;
			str operator+(int num) const;
			str operator*(long long num) const;
			bool operator==(const str &obj) const;
			bool operator!=(const str &obj) const;
			bool operator>=(const str &obj) const;
			bool operator<=(const str &obj) const;
			bool operator>(const str &obj) const;
			bool operator<(const str &obj) const;
			char operator[](long long index) const;
			char *operator()() const;
		// External:
			friend str operator+(const char *left, const str &right);
			friend str operator+(char left, const str &right);
			friend std::ostream &operator<<(std::ostream &out, const str &obj);
			friend std::istream &operator>>(std::istream &in, str &obj);
	// Class str methods
		long long size() const;
		size_t find_first(char ch) const;
		size_t find_first_string(str obj) const;
		bool contain(char ch) const;
		bool contain_string(str obj) const;
		char *read(long long left, long long right) const;
		void pop_back();
		void pop_forward();
		void remove(long long index, long long amount = 1);
		void reverse(long long left = 0, long long right = -1);
		void copy(const str &obj);
		str copy_add(const str &obj) const;
		void insert(str obj, long long index);
		long long count(char ch) const;
		str *parse(char ch) const;
		char *to_char() const;
		long long to_int() const;
		long double to_float() const;
		str bin() const;
		str oct() const;
		str hex() const;
		str notation(long long k = 2) const;
		str decimal(long long n) const;
		void add(long long num);
		unsigned long hash() const;
		void clear();
};
