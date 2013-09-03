/*
 * Copyright (C) 2013 Otto Lu <llw33333@gmail.com>.
 *
 * Licensed under the WTFPL, Version 2.0 (the "License"); 
 * You may obtain a copy of the License at
 *
 *   http://www.wtfpl.net/about/
 *
 *         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *                   Version 2, December 2004 
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net> 
 *
 * Everyone is permitted to copy and distribute verbatim or modified 
 * copies of this license document, and changing it is allowed as long 
 * as the name is changed. 
 *
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#ifndef _COMPLEX_H_
#define _COMPLEX_H_
#pragma once

#include <iostream>
#include <cmath>

template<typename type>
class complex {

private:
	type _real;
	type _imag;

public:
	complex():_real(0), _imag(0) {}
	complex(type _real, type _imag):_real(_real), _imag(_imag) {}
	complex(const complex<type> &_comp) { 
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

	const complex<type>& operator ()(type _real, type _imag) {
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
	return complex<type>comp(-comp1.real(), -comp1.imag());
}

template<typename type>
complex<type> operator +(const complex<type> &comp1, const complex<type> &comp2) {
	return complex<type>(comp1.real() + comp2.real(), comp1.imag() + comp2.imag());
}

template<typename type>
complex<type> operator -(const complex<type> &comp1, const complex<type> &comp2) {
	return complex<type>(comp1.real() - comp2.real(), comp1.imag() - comp2.imag());
}

template<typename type>
complex<type> operator *(const complex<type> &comp1, const complex<type> &comp2) {
	type real = comp1.real() * comp2.real() - comp1.imag() * comp2.imag(),
		imag = 2 * comp1.real() * comp2.imag();
	return complex<type>(real, imag);
}

template<typename type>
complex<type> operator /(const complex<type> &comp1, const complex<type> &comp2) {
	type real = comp1.real() * comp2.real() + comp1.imag() * comp2.imag(),
		imag = comp1.imag() * comp2.real() - comp1.real() * comp2.imag(),
		divisor = comp2.real() * comp2.real() + comp2.imag() * comp2.imag();

	real /= divisor;
	imag /= divisor;

	return complex<type>(real, imag);
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

	//TODO:
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
	stream << comp.real() << '+' << comp.imag() << 'i';
	return stream;
}

template<typename type>
std::istream& operator >>(std::istream& stream, complex<type> &comp) {
	type real, imag;
	stream >> real >> imag;
	comp(real, imag);
	return stream;
}  

// NOT RECOMMENDED API
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
// end of NOT RECOMMENDED API

typedef complex<float> fcomplex;
typedef complex<double> dcomplex;

#endif