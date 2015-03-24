#ifndef TRITSET_H
#define TRITSET_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include "PointTracker/Tracker/CSteinTracker.hpp"

template <int sLBP_LENS> class CTritset
{
private:
    class CTritref
    {
    private:
        int index;
        CTritset <sLBP_LENS> *parent;
    public:
        CTritref(CTritset <sLBP_LENS> *p, int idx);
        operator int() const;
        const CTritref& operator=(int v) const;
        const CTritref& operator=(const CTritref& v) const;
    };

    unsigned long long *data;
    int N;
public:
    CTritset();
    CTritset(const CTritset& t);
    ~CTritset();
    int get(int idx) const;
    bool set(int idx, int v);
    class Test {};
    CTritref operator[](int idx);
    const CTritset <sLBP_LENS>& operator=(const CTritset <sLBP_LENS>& t);
    const std::string toString() const;
    template <int _m>
    friend bool operator== (const CTritset<_m>& t1, const CTritset<_m>& t2);
    template <int _m>
    friend bool operator< (const CTritset<_m>& t1, const CTritset<_m>& t2);
    template <int _m>
    friend std::ostream& operator << (std::ostream &output, const CTritset<_m>& t);
    template <int _m>
    friend std::istream& operator >> (std::istream &input, CTritset<_m>& t);
};


template <int sLBP_LENS>
CTritset <sLBP_LENS>::CTritref::CTritref(CTritset <sLBP_LENS> *p, int idx)
    : parent(p), index(idx) {}

template <int sLBP_LENS>
CTritset <sLBP_LENS>::CTritref::operator int() const
{
    return parent->get(index);
}


template <int _m>
const typename CTritset <_m>::CTritref& CTritset<_m>::CTritref::operator=(int v) const
{
    parent->set(index, v);
    return *this;
}


template <int _m>
const typename CTritset <_m>::CTritref& CTritset<_m>::CTritref
        ::operator=(const typename CTritset<_m>::CTritref& v) const
{
    parent->set(index, v);
    return *this;
}


template <int sLBP_LENS>
CTritset <sLBP_LENS>::CTritset()
{
    N = sLBP_LENS / 32;
    if (sLBP_LENS % 32)
        N++;
    data = new unsigned long long[N];
    for (int i = 0; i < N; i++)
        data[i] = 0;
}

template <int sLBP_LENS>
CTritset <sLBP_LENS>::CTritset(const CTritset <sLBP_LENS>& t)
{
    N = t.N;
    data = new unsigned long long[N];
    for (int i = 0; i < N; i++)
        data[i] = t.data[i];
}

template <int sLBP_LENS>
CTritset <sLBP_LENS>::~CTritset()
{
    delete[] data;
}

template <int sLBP_LENS>
const CTritset <sLBP_LENS>& CTritset <sLBP_LENS>::operator=(const CTritset <sLBP_LENS>& t)
{
    delete[] data;
    this->N = t.N;
    data = new unsigned long long[this->N];
    for (int i = 0; i < this->N; i++)
        this->data[i] = t.data[i];
    return *this;
}

template <int sLBP_LENS>
int CTritset <sLBP_LENS>::get(int idx) const
{
    idx = sLBP_LENS - idx - 1;
    if (idx > sLBP_LENS-1 || idx < 0)
        return -1;
    int block = idx / 32;
    idx %= 32;
    return 3 & (data[block] >> (64 - (idx + 1) * 2));
}

template <int sLBP_LENS>
bool CTritset <sLBP_LENS>::set(int idx, int v)
{
    idx = sLBP_LENS - idx - 1;
    if (idx > sLBP_LENS - 1 || idx < 0 || v < 0 || v > 2)
        return false;
    int block = idx / 32;
    idx %= 32;
    data[block] &= ULLONG_MAX - (1ull << (64 - idx * 2 - 1))
                    - (1ull << (64 - idx * 2 - 2));
    data[block] |= ((1ull * v) << (64 - (idx + 1) * 2));
    return true;
}



template <int sLBP_LENS>
typename CTritset<sLBP_LENS>::CTritref CTritset <sLBP_LENS>::operator[](int idx)
{
    return CTritref(this, idx);
}

template <int sLBP_LENS>
const std::string CTritset<sLBP_LENS>::toString() const
{
    std::string s;
    s.reserve(sLBP_LENS);
    for (int i = sLBP_LENS - 1; i >= 0; i--)
        s += (get(i) + '0');
    return s;
}

template <int _m>
bool operator== (const CTritset <_m>& t1, const CTritset <_m>& t2)
{
    for (int i = 0; i < t1.N; i++)
    {
        if (t1.data[i] != t2.data[i])
            return false;
    }
    return true;
}

template <int _m>
bool operator< (const CTritset <_m>& t1, const CTritset <_m>& t2)
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

template <int _m>
std::ostream& operator<< (std::ostream &output, const CTritset<_m>& t)
{
    output << t.toString();
    return output;
}

template <int _m>
std::istream& operator>> (std::istream &input, CTritset <_m>& t)
{
    std::string s;
    input >> s;
    int l = s.length();
    for (int i = l - 1; i >= 0; i--)
        t.set(l - i - 1, s[i] - '0');
    return input;
}


#endif
