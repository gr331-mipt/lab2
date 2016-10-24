//
// Created by altair on 08.10.15.
//

#ifndef ZADACHA2_COEFFICIENT2_H
#define ZADACHA2_COEFFICIENT2_H

#include "types.h"
#include <iostream>
#include <stddef.h>
#include <stdexcept>

class Coefficient2 {

    size_t len;
    mydouble *val;
public:
    Coefficient2(size_t len = 1) : len(len) {
        val = new mydouble[len];
        memset(val, 0, len * sizeof(mydouble));
    }


    Coefficient2(const Coefficient2 &c);

    ~Coefficient2() {
        delete[] this->val;
        len = 0;
    }


    bool setCoefficient(size_t index, mydouble value);

    friend std::ostream &operator<<(std::ostream &o, const Coefficient2 &c) {
        std::streamsize prec = o.precision();
        o.precision(7);
        for (size_t i = 0; i < c.len; i++) {
            o << "a" << i << "= " << c.val[i] << std::endl;
        }
        o.precision(prec);
        return o;
    }

    size_t getLen() const {
        return len;
    }


    mydouble getVal(size_t index) const {
        if(index >= len)
            throw std::invalid_argument("invalid index");
        return val[index];
    }

    Coefficient2 getDerive() const;

    void addCoefficient(const size_t index, const mydouble value);

    mydouble f(mydouble c) const;
    Coefficient2(mydouble a1, mydouble a0);
    Coefficient2 getDerive2() const;

    friend Coefficient2 operator*(mydouble a, const Coefficient2 &b);

    Coefficient2 operator=(const Coefficient2 &a);

    friend Coefficient2 operator*(const Coefficient2 &a, const Coefficient2 &b);

    friend Coefficient2 operator+(const Coefficient2 &a, const Coefficient2 &b);

    mydouble f2(mydouble c) const;
};


#endif //ZADACHA2_COEFFICIENT2_H
