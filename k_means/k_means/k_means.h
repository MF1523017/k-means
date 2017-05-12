#pragma once
#include<iostream>
#include<vector>
typedef int element_type;
class Vector
{
public:
	Vector() = default;
	Vector(std::istream& is);
	Vector(const Vector &rhs);
	Vector&operator=(const Vector &rhs);
	friend element_type operator*(const Vector &lhs, const Vector &rhs);
	friend Vector operator-(const Vector &lhs, const Vector &rhs);
	friend Vector operator+(const Vector &lhs, const Vector &rhs);
	friend Vector operator/(const Vector &lhs, const element_type div);
	friend std::ostream &operator<<(std::ostream &os, const Vector &rhs);
	element_type operator[](size_t index)const { return _vectors[index]; }
	double abs();
	element_type square();
	size_t size() const { return _vectors.size(); }
	void push_back(element_type e) { _vectors.push_back(e); }
private:
	std::vector<element_type> _vectors;
};

element_type operator*(const Vector &lhs, const Vector &rhs);
Vector operator-(const Vector &lhs, const Vector &rhs);
Vector operator+(const Vector &lhs, const Vector &rhs);
Vector operator/(const Vector &lhs, const element_type div);
std::ostream &operator<<(std::ostream &os, const Vector &rhs);


class Kmeans
{
public:
	Kmeans()=default;
	Kmeans(size_t k, std::istream &is);
	void kmeans();
	void print_result();
	std::vector<std::vector<Vector>> get_result();
	~Kmeans() { ; }
private:
	size_t _k;
	element_type _criterion;
	typedef std::vector<std::pair<Vector, int>> Data;
	Data _data;
	typedef std::vector<Vector> Center;
	Center _center;
	void _random_init();
	void _assign();
	void _update_center();
	element_type _criterion_funcion();
};