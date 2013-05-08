#include <iostream>
#include <cassert>
#include "complex.hpp"

using namespace std;

int main() {

	fcomplex fc1(1.0f, 1.0f), fc2(2.0f, 2.0f), fc3(3.0f, 3.0f), fc4(1.0f, 1.0f), fc5;

	// test 0: ==
	assert(fc1 == fc4);
	cout<<"test 0 done."<<endl;

	// test 1: =
	fc3 = fc2;
	assert(fc2 == fc3);
	cout<<"test 1 done."<<endl;

	// test 2: () ¸³Öµ
	fc3(1.0f, 1.0f);
	assert(fc1 == fc3);
	cout<<"test 2 done."<<endl;

	// test 3: () È¡Ä£
	assert(fc2() == (float) sqrt(2 * (2.0f) * (2.0f)));
	cout<<"test 3 done."<<endl;

	// test 4: +
	fc4 = fc1 + fc2;
	fc3(3.0f, 3.0f);
	assert(fc3 == fc4);
	cout<<"test 4 done."<<endl;

	// test 5: -
	fc4 = fc1 - fc2;
	fc3(-1.0f, -1.0f);
	assert(fc4 == fc3);
	cout<<"test 5 done."<<endl;

	// test 6: +=
	fc4 = fc1;
	fc4 += fc2;
	assert(fc4 == (fc1 + fc2));
	cout<<"test 6 done."<<endl;

	// test 7: -=
	fc4 = fc1;
	fc4 -= fc2;
	assert(fc4 == (fc1 - fc2));
	cout<<"test 7 done."<<endl;

	// test 8: *=
	fc4 = fc1;
	fc4 *= fc2;
	assert(fc4 == (fc1 * fc2));
	cout<<"test 8 done."<<endl;

	// test 9: /=
	fc4 = fc1;
	fc4 /= fc2;
	assert(fc4 == (fc1 / fc2));
	cout<<"test 9 done."<<endl;

	// test 10: >>
	cin>>fc5;

	// test 11: <<
	cout<<fc5<<endl;

	return 0;
}