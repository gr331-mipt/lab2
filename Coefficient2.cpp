//
// Created by altair on 08.10.15.
//

#include <assert.h>
#include <string.h>
#include "Coefficient2.h"


Coefficient2 Coefficient2::getDerive2() const {
    Coefficient2 ret(getLen() - 1);
    for (size_t i = 1; i < getLen(); ++i) {
        ret.setCoefficient(i - 1, getVal(i) * i);
    }
    return ret;
}

mydouble Coefficient2::f2(mydouble c) const {
    mydouble k = 1;
    mydouble res = 0;
    for (size_t i = 0; i < getLen(); res += getVal(i) * k, k*= c, i++);
    return res;
}

Coefficient2::Coefficient2(mydouble a1, mydouble a0) : Coefficient2(2) {
    setCoefficient(0, a1);
    setCoefficient(1, a0);
}

Coefficient2 operator*(mydouble a, const Coefficient2 &b) {
    Coefficient2 ret(b.getLen());
    for (size_t i = 0; i < b.getLen(); i++) {
        ret.setCoefficient(i, a * b.getVal(i));
    }
    return ret;
}

Coefficient2 operator*(const Coefficient2 &a, const Coefficient2 &b) {
    Coefficient2 ret(a.getLen() + b.getLen() - 1);
    for(size_t i = 0; i < a.getLen(); i++) {
        for(size_t j = 0; j < b.getLen(); j++) {
            ret.addCoefficient(i + j, a.getVal(i) * b.getVal(j));
        }
    }
    return ret;
}

Coefficient2 operator+(const Coefficient2 &a, const Coefficient2 &b) {
    size_t len = std::max(a.getLen(), b.getLen());
    Coefficient2 ret(len);
    for (size_t i = 0; i < len; ++i) {
        if(i < a.getLen()) {
            ret.addCoefficient(i,a.getVal(i));
        }
        if(i < b.getLen()) {
            ret.addCoefficient(i, b.getVal(i));
        }
    }
    return ret;
}

Coefficient2 Coefficient2::operator=(const Coefficient2 &a) {
    len = a.len;
    mydouble *val1 = new mydouble[len];
    memcpy(val1, a.val, len * sizeof(mydouble));
    delete[] val;
    val = val1;
    return *this;
}

bool Coefficient2::setCoefficient(size_t index, mydouble value) {
    if(index < this->len) {
        this->val[index] = value;
        return true;
    }
    return false;
}

Coefficient2 Coefficient2::getDerive() const {
    return getDerive2();
}

mydouble Coefficient2::f(mydouble c) const {
    return f2(c);
}

Coefficient2::Coefficient2(const Coefficient2 &c) : Coefficient2(c.len) {
    for(size_t i = 0; i < c.len; i++) {
        val[i] = c.getVal(i);
    }
}

void Coefficient2::addCoefficient(const size_t index, const mydouble value) {
    assert(index < len);
    this->val[index] += value;
}
