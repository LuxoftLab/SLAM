#include "tritset.h"

template <int _n> 
tritset <_n>::tritref::tritref(tritset <_n> *p, int idx)
	: parent(p), index(idx) {}

template <int _n> 
tritset <_n>::tritref::operator int() const
{
	return parent->get(index);
}


template <int _n> 
typename const tritset <_n>::tritref& tritset<_n>::tritref
									::operator=(int v) const
{
	parent->set(index, v);
	return *this;
}


template <int _n> 
typename const tritset <_n>::tritref& tritset<_n>::tritref
		::operator=(typename const tritset<_n>::tritref& v) const
{
	parent->set(index, v);
	return *this;
}


template <int _n> 
tritset <_n>::tritset()
{
	N = _n / 32;
	if (_n % 32)
		N++;
	data = new unsigned long long[N];
	for (int i = 0; i < N; i++)
		data[i] = 0;
}

template <int _n> 
tritset <_n>::tritset(const tritset <_n>& t)
{
	N = t.N;
	data = new unsigned long long[N];
	for (int i = 0; i < N; i++)
		data[i] = t.data[i];
}

template <int _n> 
tritset <_n>::~tritset()
{
	delete[] data;
}

template <int _n> 
const tritset <_n>& tritset <_n>::operator=(const tritset <_n>& t) const
{
	delete[] data;
	this->N = t.N;
	data = new unsigned long long[this->N];
	for (int i = 0; i < this->N; i++)
		this->data[i] = t.data[i];
	return *this;
}

template <int _n> 
int tritset <_n>::get(int idx) const
{
	idx = _n - idx - 1;
	if (idx > _n-1 || idx < 0)
		return -1;
	int block = idx / 32;
	idx %= 32;
	return 3 & (data[block] >> (64 - (idx + 1) * 2));
}

template <int _n> 
bool tritset <_n>::set(int idx, int v)
{
	idx = _n - idx - 1;
	if (idx > _n - 1 || idx < 0 || v < 0 || v > 2)
		return false;
	int block = idx / 32;
	idx %= 32;
	data[block] &= ULLONG_MAX - (1ull << (64 - idx * 2 - 1))
				    - (1ull << (64 - idx * 2 - 2));
	data[block] |= ((1ull * v) << (64 - (idx + 1) * 2));
	return true;
}



template <int _n> 
typename tritset<_n>::tritref tritset <_n>::operator[](int idx)
{
	return tritref(this, idx);
}

template <int _n> 
const std::string tritset<_n>::toString() const
{
	std::string s;
	s.reserve(_n);
	for (int i = _n - 1; i >= 0; i--)
		s += (get(i) + '0');
	return s;
}

template <int _n> 
bool operator== (const tritset <_n>& t1, const tritset <_n>& t2)
{
	for (int i = 0; i < t1.N; i++)
	{
		if (t1.data[i] != t2.data[i])
			return false;
	}
	return true;
}

template <int _n> 
bool operator< (const tritset <_n>& t1, const tritset <_n>& t2)
{

	for (int i = 0; i < t1.N; i++)
	{
		if (t1.data[i] < t2.data[i])
			return true;
		else if (t1.data[i] > t2.data[i])
			return false;
	}
	return false;
}

template <int _n> 
std::ostream& operator<< (std::ostream &output, const tritset<_n>& t)
{
	output << t.toString();
	return output;
}

template <int _n> 
std::istream& operator>> (std::istream &input, tritset <_n>& t)
{
	std::string s;
	input >> s;
	int l = s.length();
	for (int i = l - 1; i >= 0; i--)
		t.set(l - i - 1, s[i] - '0');
	return input;
}