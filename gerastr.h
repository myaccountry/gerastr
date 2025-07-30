#include <iostream>
using namespace std;
using ll = long long;

ll my_abs(ll x);

class str {
	ll len = 0;
	char *buffer = nullptr;
public:
	// Перегрузка операторов
		// Внутренних:
			str();
			str(const char *arr);
			str(const str &obj);
			str(char ch);
			str(ll num);
			str(int num);
			~str();
			str &operator=(const str &obj);
			str &operator=(const char *arr);
			str &operator=(char ch);
			str &operator=(int num);
			str &operator=(ll num);
			str &operator+=(const str &obj);
			str &operator+=(const char *arr);
			str &operator+=(char ch);
			str &operator+=(ll num);
			str &operator+=(int num);
			str &operator*=(ll num);
			str operator+(const str &obj) const;
			str operator+(const char *arr) const;
			str operator+(char ch) const;
			str operator+(ll num) const;
			str operator+(int num) const;
			str operator*(ll num) const;
			bool operator==(const str &obj) const;
			bool operator!=(const str &obj) const;
			bool operator>=(const str &obj) const;
			bool operator<=(const str &obj) const;
			bool operator>(const str &obj) const;
			bool operator<(const str &obj) const;
			char operator[](ll index) const;
			char *operator()() const;
		// Внешних:
			friend str operator+(const char *left, const str &right);
			friend str operator+(char left, const str &right);
			friend ostream &operator<<(ostream &out, const str &obj);
			friend istream &operator>>(istream &in, str &obj);
	// Методы класса
		const ll size() const;
		ll find_first(char ch) const;
		ll find_first_string(str obj) const;
		bool contain(char ch) const;
		bool contain_string(str obj) const;
		char *read(ll left, ll right) const;
		void pop_back();
		void pop_forward();
		void remove(ll index, ll amount = 1);
		void reverse(ll left = 0, ll right = -1);
		void copy(const str &obj);
		str copy_add(const str &obj) const;
		void insert(str obj, ll index);
		ll count(char ch) const;
		str *parse(char ch) const;
		char *to_char() const;
		ll to_int() const;
		long double to_float() const;
		str bin() const;
		str oct() const;
		str hex() const;
		str notation(ll k = 2) const;
		str decimal(ll n) const;
		void add(ll num);
		void clear();
};
