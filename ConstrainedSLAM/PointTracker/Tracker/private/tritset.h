#ifndef TRITSET_H
#define TRITSET_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

template <int _n> class tritset
{
private:
	class tritref
	{
	private:
		int index;
		tritset <_n> *parent;
	public:
		tritref(tritset <_n> *p, int idx);
		operator int() const;
		const tritref& operator=(int v) const;
		const tritref& operator=(const tritref& v) const;
	};

	unsigned long long *data;
	int N;
public:
	tritset();
	tritset(const tritset& t);
	~tritset();
	int get(int idx) const;
	bool set(int idx, int v);
	tritref operator[](int idx);
	const tritset <_n>& operator=(const tritset <_n>& t);
	const std::string toString() const;
	template <int _m> 
	friend bool operator== (const tritset<_m>& t1, const tritset<_m>& t2);
	template <int _m> 
	friend bool operator< (const tritset<_m>& t1, const tritset<_m>& t2);
	template <int _m> 
	friend std::ostream& operator << (std::ostream &output, const tritset<_m>& t);
	template <int _m> 
	friend std::istream& operator >> (std::istream &input, tritset<_m>& t);
};

#include "tritset.cpp"

#endif