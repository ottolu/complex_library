#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>
#include <cmath>

template<typename type>
class complex {

private:
	type _real;
	type _imag;

public:
	complex():_real(), _imag() {}
	complex(type _real, type _imag):_real(_real), _imag(_imag) {}
	complex(complex<type> &_comp) { 
		this->_real = _comp.real();
		this->_imag = _comp.imag();
	}

	type real() const { return this->_real; }
	void real(type _real) { this->_real = _real; }
	type imag() const { return this->_imag; }
	void imag(type _imag) { this->_imag = _imag; }
	type val() const { 
		return std::sqrt(std::pow(this->_real, 2) + std::pow(this->_imag, 2)); 
	}

	type operator ()() const {
		return this->val();
	}

	complex<type>& operator ()(type _real, type _imag) {
		this->_real = _real;
		this->_imag = _imag;
		return *this;
	}

	complex<type>& operator =(const complex<type> &comp1) {
		this->_real = comp1.real();
		this->_imag = comp1.imag();
		return *this;
	}

	complex<type>& operator +=(const complex<type> &comp1) {
		this->_real += comp1.real();
		this->_imag += comp1.imag();
		return *this;
	}

	complex<type>& operator -=(const complex<type> &comp1) {
		this->_real -= comp1.real();
		this->_imag -= comp1.imag();
		return *this;
	}

	complex<type>& operator *=(const complex<type> &comp2) {
		type real = this->_real;
		this->_real = this->_real * comp2.real() - this->_imag * comp2.imag();
		this->_imag = 2 * real * comp2.imag();
		return *this;
	}

	complex<type>& operator /=(const complex<type> &comp2) {
		type divisor = comp2.real() * comp2.real() + comp2.imag() * comp2.imag(),
			real = this->_real;

		this->_real = this->_real * comp2.real() + this->_imag * comp2.imag();
		this->_imag = this->_imag * comp2.real() - real * comp2.imag();

		this->_real /= divisor;
		this->_imag /= divisor;

		return *this;
	}

	template<typename type>
	friend std::ostream& operator <<(std::ostream&, const complex<type>&);

	template<typename type>
	friend std::istream& operator >>(std::istream&, complex<type>&);
};

template<typename type>
complex<type> operator -(const complex<type> &comp1) {
	complex<type> comp;
	return comp(-comp1.real(), -comp1.imag());
}

template<typename type>
complex<type> operator +(const complex<type> &comp1, const complex<type> &comp2) {
	complex<type> comp;
	return comp(comp1.real() + comp2.real(), comp1.imag() + comp2.imag());
}

template<typename type>
complex<type> operator -(const complex<type> &comp1, const complex<type> &comp2) {
	complex<type> comp;
	return comp(comp1.real() - comp2.real(), comp1.imag() - comp2.imag());
}

template<typename type>
complex<type> operator *(const complex<type> &comp1, const complex<type> &comp2) {
	complex<type> comp;
	type real = comp1.real() * comp2.real() - comp1.imag() * comp2.imag(),
		imag = 2 * comp1.real() * comp2.imag();
	return comp(real, imag);
}

template<typename type>
complex<type> operator /(const complex<type> &comp1, const complex<type> &comp2) {
	complex<type> comp;
	type real = comp1.real() * comp2.real() + comp1.imag() * comp2.imag(),
		imag = comp1.imag() * comp2.real() - comp1.real() * comp2.imag(),
		divisor = comp2.real() * comp2.real() + comp2.imag() * comp2.imag();

	real /= divisor;
	imag /= divisor;

	return comp(real, imag);
}

namespace std
{
	template<typename type>
	complex<type> pow(complex<type> &comp, int times) {
		for (int i = 1; i < times; ++i) {
			comp = comp * comp;
		}
		return comp;
	}

	//暂不提供
	//template<typename type>
	//complex<type> sqrt(complex<type> &comp) {

	//}
}

template<typename type>
bool operator ==(const complex<type> &comp1, const complex<type> &comp2) {
	return comp1.real() == comp2.real() && comp1.imag() == comp2.imag();
}

template<typename type>
bool operator !=(const complex<type> &comp1, const complex<type> &comp2) {
	return !(comp1.real() == comp2.real() && comp1.imag() == comp2.imag());
}

template<typename type>
std::ostream& operator <<(std::ostream& stream, const complex<type> &comp) {
	stream<<comp.real()<<'+'<<comp.imag()<<'i';
	return stream;
}

template<typename type>
std::istream& operator >>(std::istream& stream, complex<type> &comp) {
	type real, imag;
	stream>>real>>imag;
	comp(real, imag);
	return stream;
}  

//危险的API
template<typename type>
bool operator <(type val, const complex<type> &comp) {
	return val < comp.val();
}

template<typename type>
bool operator >(type val, const complex<type> &comp) {
	return val > comp.val();
}

template<typename type>
bool operator <(const complex<type> &comp, type val) {
	return comp.val() < val;
}

template<typename type>
bool operator >(const complex<type> &comp, type val) {
	return comp.val() > val;
}

template<typename type>
bool operator <(const complex<type> &comp1, const complex<type> &comp2) {
	return comp1.val() < comp2.val();
}

template<typename type>
bool operator >(const complex<type> &comp1, const complex<type> &comp2) {
	return comp1.val() > comp2.val();
}

typedef complex<float> fcomplex;
typedef complex<double> dcomplex;

#endif