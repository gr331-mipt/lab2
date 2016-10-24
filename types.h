//
// Created by altair on 07.10.15.
//

#ifndef ZADACHA2_TYPES_H
#define ZADACHA2_TYPES_H

typedef long double mydouble;

const mydouble eps = 1e-7;

inline bool IS_ZERO(mydouble x) {
    return (-eps < x && x < eps);
}

#endif //ZADACHA2_TYPES_H
