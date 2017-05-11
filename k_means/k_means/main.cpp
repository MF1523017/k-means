#include"k_means.h"
#include<assert.h>
#include<fstream>
using namespace std;

void testVector()
{
	cout << "test Vector unit" << endl;
	Vector v(cin);
	assert(v.size() == 2);
	assert(v[0] == 0);
	assert(v[1] == 0);
	v.push_back(3);
	assert(v.size() == 3);
	assert(v[2] == 3);
	assert(v.abs() - 3 < 0.00000001);
	assert(v.square()==9);
	cout << v << endl;
	Vector v1(v);
	v1 = v;
	v1 = v;
	cout << v1 << endl;
	cout << "v1 - v "<<v1 - v << endl;
	cout << "v1 + v "<<v1 + v << endl;
	cout << "v1 / 3 "<<v1 / 3 << endl;
	cout << "v1 * v "<<v1*v << endl;
}

void testKmeans()
{
	ifstream in("test.txt");
	Kmeans test(4, in);
	test.kmeans();
	test.print_result();
}

int main(int argc,char **argv)
{
	//testVector();
	testKmeans();
	return 0;
}