#include <iostream>
#include "gerastr.hpp"

long long my_abs(long long x) {
	if (x < 0)
		return -x;
	return x;
}

long long capacity(long long x) {
	long long k = 1;
	while (x > 9) {
		k++;
		x /= 10;
	}
	return k;
}

str::str() : len(0) {
	buffer = new char[1];
	buffer[0] = '\0';
};

str::str(const char *arr) {
	len = 0;
	while (arr[len] != '\0')
		len++;

	buffer = new char[len + 1];
	for (size_t i = 0; arr[i] != '\0'; i++)
		buffer[i] = arr[i];
	buffer[len] = '\0';
};

str::str(const str &obj) : len(obj.len) {
	buffer = new char[len + 1];
	for (size_t i = 0; i < len; i++)
		buffer[i] = obj[i];
};

str::str(char ch) : len(1) {
	buffer = new char[2];
	buffer[0] = ch;
	buffer[1] = '\0';
};

str::str(long long num) : len(capacity(num)) {
	str result = "";
	result.add(num);
	copy(result);
};

str::str(int num) : len(capacity(static_cast<long long>(num))) {
	str result = "";
	result.add(static_cast<long long>(num));
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

str &str::operator=(long long num) {
	clear();
	add(num);
	return *this;
};

str &str::operator=(int num) {
	return operator=(static_cast<long long>(num));
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

str &str::operator+=(long long num) {
	add(num);
	return *this;
};

str &str::operator+=(int num) {
	return operator+=(static_cast<long long>(num));
};

str &str::operator*=(long long num) {
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

str str::operator+(long long num) const {
	str result = read(0, len);
	result.add(num);
	return result;
};

str str::operator+(int num) const {
	return operator+(static_cast<long long>(num));
};

str str::operator*(long long num) const {
	str result = "";
	for (size_t i = 0; i < num; i++)
		result += read(0, len);
	return result;
};

bool str::operator==(const str &obj) const {
	if (len != obj.len)
		return false;
	for (size_t i = 0; i < len; i++)
		if (buffer[i] != obj[i])
			return false;
	return true;
};

bool str::operator!=(const str &obj) const {
	return !(obj == *this);
};
bool str::operator>=(const str &obj) const {
	if (len >= obj.len)
		return true;
	else
		return false;
};
bool str::operator<=(const str &obj) const {
	if (len <= obj.len)
		return true;
	else
		return false;
};
bool str::operator>(const str &obj) const {
	if (len > obj.len)
		return true;
	else
		return false;
};
bool str::operator<(const str &obj) const {
	if (len < obj.len)
		return true;
	else
		return false;
};

str operator+(const char *left, const str &right) {
	return str(left) + right;
};

str operator+(char left, const str &right) {
	return str(left) + right;
};

std::ostream &operator<<(std::ostream &out, const str &obj) {
	out << '"' << obj.buffer << '"';
	return out;
};

std::istream &operator>>(std::istream &in, str &obj) {
	char *new_buffer = new char[1024];
	in.getline(new_buffer, 1024);
	if (obj.buffer != nullptr)
		delete[] obj.buffer;
	obj = new_buffer;
	delete[] new_buffer;
	return in;
};

/* Returns the character at the specified index in the buffer
Index "-1" points to the last element of the buffer
Index "-2" points to the second element from the end, etc. */
char str::operator[](long long index) const {
	if (index < 0)
		index = len - index;
	return buffer[index];
};

// Returns the char array of the current buffer
char *str::operator()() const {
	return buffer;
};

// Returns the size of the current buffer
const long long str::size() const {
	return len;
};

// Returns the index of the searched element in the buffer
size_t str::find_first(char ch) const {
	for (size_t i = 0; i < len; i++)
		if (buffer[i] == ch)
			return i;
	return '\0';
};

// Returns the index of the first element of the search string in the buffer
size_t str::find_first_string(str obj) const {
	for (size_t i = 0; i < len; i++)
		if (buffer[i] == obj[0])
			if (str(read(i, i + obj.len)) == obj)
				return i;
	return '\0';
};

// Checks if the character is in the buffer
bool str::contain(char ch) const {
	for (size_t i = 0; i < len; i++)
		if (buffer[i] == ch)
			return true;
	return false;
};

// Checks if the string is in the buffer
bool str::contain_string(str obj) const {
	for (size_t i = 0; i < len; i++)
		if (buffer[i] == obj[0])
			if (str(read(i, i + obj.len)) == obj)
				return true;
	return false;
}

// Returns a char array with the given bounds
char *str::read(long long left, long long right) const {
	if (left == right) {
		char *empty = new char[1];
		empty[0] = '\0';
		return empty;
	}

	long long length = my_abs(right - left);
	char *new_buffer = new char[length + 1];
	
	long long j = 0;
	if (left < right)
		for (long long i = left; j < length; i++)
			new_buffer[j++] = buffer[i];
	else
		for (long long i = left; j < length; i--)
			new_buffer[j++] = buffer[i];

	new_buffer[length] = '\0';
	return new_buffer;
};

// Removes the last element
void str::pop_back() {
	str result = read(0, len - 1);
	copy(result);
};

// Removes the first element
void str::pop_forward() {
	str result = read(1, len);
	copy(result);
};

// Removes some number of elements by index
void str::remove(long long index, long long amount) {
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

// Inverts a string at the given boundaries
void str::reverse(long long left, long long right) {
	if (right == -1)
		right = len - 1;
	str result = read(0, left);
	result += read(right, left - 1);
	result += read(right + 1, len);
	copy(result);
};

// You dont need to use it :)
void str::copy(const str &obj) {
	delete[] buffer;
	buffer = new char[obj.len + 1];
	for (size_t i = 0; obj[i] != '\0'; i++)
		buffer[i] = obj[i];
	buffer[obj.len] = '\0';
	len = obj.len;
};

// You dont need to use it :)
str str::copy_add(const str &obj) const {
	char *new_buffer = new char[len + obj.len + 1];
	for (size_t i = 0; i < len + obj.len; i++) {
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

// Insert elements before index
void str::insert(str obj, long long index) {
	str result = read(0, index);
	result += obj;
	result += read(index, len);
	copy(result);
};

// Number of characters in the buffer
long long str::count(char ch) const {
	long long cnt = 0;
	for (size_t i = 0; i < len; i++)
		if (buffer[i] == ch)
			cnt++;
	return cnt;
};

/* Method returning an array of objects of class str
Filled with strings separated by the ch character */
str *str::parse(char ch) const {
	const long long cnt = count(ch) + 1;
	str *result = new str[cnt];
	if (cnt == 1) {
		result[0] = str(read(0, len));
		return result;
	}
	long long left = 0, k = 0;
	for (long long i = 0; i < len; i++) {
		if (buffer[i] == ch) {
			result[k++] = str(read(left, i));
			left = i + 1;
		}
	}
	if (left < len)
		result[k] = str(read(left, len));
	return result;
};

// Returns the char array of the current object
char *str::to_char() const {
	return buffer;
};

// Returns the integer value of the current object
long long str::to_int() const {
	long long k = 1;
	long long result = 0;
	for (long long i = len - 1; i > 0; i--) {
		result += (buffer[i] - '0') * k;
		k *= 10;
	}
	if (buffer[0] != '-')
		result += (buffer[0] - '0') * k;
	else
		result *= -1;
	return result;
};

// Returns the floating point value of the current object
long double str::to_float() const {
	double k = 0.1;
	long double result = 0.0;
	str stat = read(0, find_first('.'));
	result += (long double)stat.to_int();
	stat = read(find_first('.') + 1, len);
	for (size_t i = 0; i < stat.size(); i++) {
		if (buffer[0] == '-')
			result -= (long double)(stat[i] - 48) * k;
		else
			result += (long double)(stat[i] - 48) * k;
		k *= 0.1;
	}
	return result;
};

// Translation into the 2th number system
str str::bin() const {
	return notation(2);
};

// Translation into the 8th number system
str str::oct() const {
	return notation(8);
};

// Translation into the 16th number system
str str::hex() const {
	return notation(16);
}

/* Translates string "integer" values in the 10th system
into various number systems up to and including the 16th
8,388,607 is the maximum number that an object of the class can accept */
str str::notation(long long k) const {
	const str alphabet = "0123456789ABCDEF";
	str result = "";
	long long num = my_abs(to_int()), old = num;
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

/* Converts a string value from various number systems to a 
string with an "integer" value in the 10th system */
str str::decimal(long long n) const {
	const str alphabet = "0123456789ABCDEF";
	str result = "";
	long long k = 1;
	long long sum = 0;
	for (long long i = len - 1; i > 0; i--) {
		sum += alphabet.find_first(buffer[i]) * k;
		k *= n;
	}
	if (buffer[0] == '-')
		result = '-' + str(sum);
	else
		result = (sum + (long long)alphabet.find_first(buffer[0]) * k);
	return result;
}

/* Adds an integer value to the buffer, converting each bit to a char
9,223,372,036,854,775,807 is the maximum value the method can accept */
void str::add(long long num) {
	str result = "";
	bool negative = false;
	if (num < 0)
		negative = true;
	num = my_abs(num);
	long long length = capacity(num);
	char ch;
	for (long long i = 1; i <= length; i++) {
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

unsigned long str::hash() const {
	unsigned long hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + buffer[i];
    }
    return hash;
};

// Clears the object buffer
void str::clear() {
	buffer = new char[1];
	buffer[0] = '\0';
};
