#include"k_means.h"
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<assert.h>
Vector::Vector(std::istream &is)
{
	element_type tmp;
	while(is >> tmp)
		_vectors.push_back(tmp);
}
Vector::Vector(const Vector &rhs)
{
	*this = rhs;
}
Vector& Vector::operator=(const Vector &rhs)
{
	if (this == &rhs)
		return *this;
	if (size() != rhs.size())
		_vectors.resize(rhs.size());
	for (size_t i = 0; i < rhs.size(); ++i)
		_vectors[i]=rhs[i];
	return *this;
}

element_type operator*(const Vector &lhs, const Vector &rhs)
{
	if (lhs.size() != rhs.size())
		return 0;
	element_type ret = 0;
	for (size_t i = 0; i < lhs.size(); ++i)
	{
		ret += lhs[i] * rhs[i];
	}
	return ret;
}
Vector operator-(const Vector &lhs, const Vector &rhs)
{
	Vector tmp;
	for (size_t i = 0; i < lhs.size(); ++i)
		tmp.push_back(lhs[i] - rhs[i]);
	return tmp;
}
Vector operator+(const Vector &lhs, const Vector &rhs)
{
	Vector tmp;
	for (size_t i = 0; i < lhs.size(); ++i)
		tmp.push_back(lhs[i] + rhs[i]);
	return tmp;
}
Vector operator/(const Vector &lhs, const element_type div)
{
	Vector tmp;
	for (size_t i = 0; i < lhs.size(); ++i)
		tmp.push_back(lhs[i]/div);
	return tmp;
}

std::ostream &operator<<(std::ostream &os, const Vector &rhs)
{
	for (size_t i = 0; i < rhs.size(); ++i)
		os << rhs[i] << " ";
	return os;
}

double  Vector::abs()
{
	return sqrt(square());
}
element_type Vector::square()
{
	element_type ret = 0;
	for (size_t i = 0; i < _vectors.size(); ++i)
		ret += _vectors[i] * _vectors[i];
	return ret;
}
Kmeans::Kmeans(size_t k, std::istream &is):_k(k), _criterion(INT_MAX)
{
	std::string tmp;
	size_t i= 0;
	while (std::getline(is, tmp))
	{
		if (tmp.empty())
			break;
		std::istringstream iss(tmp);
		_data.push_back(std::make_pair(Vector(iss), (++i) % k));
	}
	//assert(_k == 4);
	//assert(_data.size() == 13);//for test
	//for (int i = 0; i < 13; ++i)
		//assert(_data[i].first.size() == 3);
}
void Kmeans::_random_init()
{
	srand(static_cast<unsigned>(time(nullptr)));
	size_t data_size = _data.size();
	for (size_t i = 0; i < _k; ++i)
	{
		_center.push_back(_data[rand() % data_size].first);
		//assert(_center[i].size() == 3);
	}
	//assert(_center.size() == 4);
}

void Kmeans::_assign()
{
	for (size_t i = 0; i < _data.size(); ++i)
	{
		size_t min_index = 0;
		element_type dis = INT_MAX;
		for (size_t j = 0; j < _k; ++j)
		{
			element_type square = (_data[i].first - _center[j]).square();
			if (dis >square )
			{
				dis = square;
				min_index = j;
			}
		}
		_data[i].second = min_index;
	}
}

void Kmeans::_update_center()
{
	std::vector<int>_data_count(_k, 0);
	for (size_t i=0; i < _k; ++i)
		_center[i] =_center[i]- _center[i];
	for (size_t i = 0; i < _data.size(); ++i)
	{
		size_t index = _data[i].second;
		++_data_count[index];
		_center[index] = _center[index] + _data[i].first;
	}
	for (size_t i = 0; i < _k; ++i)
	{
		if (_data_count[i] == 0)
			continue;
		_center[i] = _center[i] / _data_count[i];
	}
}

element_type Kmeans::_criterion_funcion()
{
	element_type ret = 0;
	for (size_t i = 0; i < _data.size(); ++i)
	{
		int index = _data[i].second;
		ret += (_data[i].first - _center[index]).square();
	}
	return ret;
}



void Kmeans::kmeans()
{
	_random_init();
	int it= 0;
	while (true)
	{
		_assign();
		_update_center();
		element_type e = _criterion_funcion();
		if (e >= _criterion||it>10000)
			break;
		_criterion = e;
		++it;
	}
}

void Kmeans::print_result()
{
	for (size_t i = 0; i < _data.size(); ++i)
	{
		int index = _data[i].second;
		std::cout << _data[i].first << "'s center is " << _center[index] << std::endl;
	}
}