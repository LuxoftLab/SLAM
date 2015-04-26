#include "PointTracker/Tracker/private/CTritset.hpp"

CTritset::CTritref::CTritref(CTritset *p, int idx)
    : parent(p), index(idx) {}

CTritset::CTritref::operator int() const
{
    return parent->get(index);
}


const CTritset::CTritref& CTritset::CTritref::operator=(int v) const
{
    parent->set(index, v);
    return *this;
}


const CTritset::CTritref& CTritset::CTritref
        ::operator=(const CTritset::CTritref& v) const
{
    parent->set(index, v);
    return *this;
}


CTritset::CTritset(int sLBP_L)
    : sLBP_LENS(sLBP_L)
{
    N = sLBP_LENS / 32;
    if (sLBP_LENS % 32)
        N++;
    data = new unsigned long long[N];
    for (int i = 0; i < N; i++)
        data[i] = 0;
}

CTritset::CTritset(const CTritset& t)
{
    N = t.N;
    data = new unsigned long long[N];
    for (int i = 0; i < N; i++)
        data[i] = t.data[i];
}

CTritset::~CTritset()
{
    delete[] data;
}


const CTritset& CTritset::operator=(const CTritset& t)
{
    delete[] data;
    this->N = t.N;
    data = new unsigned long long[this->N];
    for (int i = 0; i < this->N; i++)
        this->data[i] = t.data[i];
    return *this;
}

int CTritset::get(int idx) const
{
    idx = sLBP_LENS - idx - 1;
    if (idx > sLBP_LENS-1 || idx < 0)
        return -1;
    int block = idx / 32;
    idx %= 32;
    return 3 & (data[block] >> (64 - (idx + 1) * 2));
}

bool CTritset::set(int idx, int v)
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



CTritset::CTritref CTritset::operator[](int idx)
{
    return CTritref(this, idx);
}

const std::string CTritset::toString() const
{
    std::string s;
    s.reserve(sLBP_LENS);
    for (int i = sLBP_LENS - 1; i >= 0; i--)
        s += (get(i) + '0');
    return s;
}

bool operator== (const CTritset& t1, const CTritset& t2)
{
    if(t1.N != t2.N)
        return false;
    for (int i = 0; i < t1.N; i++)
    {
        if (t1.data[i] != t2.data[i])
            return false;
    }
    return true;
}


bool operator< (const CTritset& t1, const CTritset& t2)
{
    if(t1.N != t2.N)
        return t1.N < t2.N;
    for (int i = 0; i < t1.N; i++)
    {
        if (t1.data[i] < t2.data[i])
            return true;
        else if (t1.data[i] > t2.data[i])
            return false;
    }
    return false;
}


std::ostream& operator<< (std::ostream &output, const CTritset& t)
{
    output << t.toString();
    return output;
}


std::istream& operator>> (std::istream &input, CTritset & t)
{
    std::string s;
    input >> s;
    int l = s.length();
    for (int i = l - 1; i >= 0; i--)
        t.set(l - i - 1, s[i] - '0');
    return input;
}
