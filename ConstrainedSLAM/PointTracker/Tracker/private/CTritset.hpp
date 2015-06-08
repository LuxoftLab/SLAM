#ifndef CTRITSET_H
#define CTRITSET_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

class CTritset
{
private:
    class CTritref
    {
    private:
        int index;
        CTritset *parent;
    public:
        CTritref(CTritset *p, int idx);
        operator int() const;
        const CTritref& operator=(int v) const;
        const CTritref& operator=(const CTritref& v) const;
    };

    unsigned long long *data;
    int N;
    int sLBP_LENS;
    static int pow3[5];
public:
    CTritset(int sLBP_L);
    CTritset(const CTritset& t);
    ~CTritset();
    int get(int idx) const;
    bool set(int idx, int v);
    CTritref operator[](int idx);
    const CTritset& operator=(const CTritset& t);
    const std::string toString() const;
    friend bool operator== (const CTritset& t1, const CTritset& t2);
    friend bool operator< (const CTritset& t1, const CTritset& t2);
    friend std::ostream& operator << (std::ostream &output, const CTritset& t);
    friend std::istream& operator >> (std::istream &input, CTritset& t);
};

#endif
