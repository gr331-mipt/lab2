//
// Created by altair on 07.10.15.
//

#include <assert.h>
#include "Interpolation.h"
#include "types.h"
#include "../zadacha1var4.4/coefficient.h"
#include "Coefficient2.h"

void Interpolation::setPoint(const size_t index, const Point value) {
    if(index >= N)
        throw "Invalid Argument";
    data[index] = value;
}

void Interpolation::setPoint(size_t index, mydouble x, mydouble y) {
    assert(data != nullptr);
    if(index >= N)
        throw "invalid argument";
    data[index] = Point(x, y);
}

mydouble Interpolation::getNewtonF(size_t i1, size_t i2) const {
    assert(i1 < N);
    assert(i2 < N);
    assert(i1 <= i2);
    if(i1 == i2) {
        return data[i2].y;
    }
    if(i2 - i1 == 1) {
        return (data[i2].y - data[i1].y) / (data[i2].x - data[i1].x);
    }
    return (getNewtonF(i1 + 1, i2) - getNewtonF(i1, i2 - 1)) / (data[i2].x - data[i1].x);
}

void Interpolation::calcB() {
    newB(N);
    for (size_t i = 0; i < N; i++) {
        b[i] = getNewtonF(0, i);
    }
}

void Interpolation::newB(const size_t N) {
    if(b != nullptr) {
        delete[] b;
    }
    b = new mydouble[N];
}

mydouble Interpolation::getNewtonY(mydouble x) {
    if(b == nullptr) {
        calcB();
    }
    mydouble res = b[0];
    mydouble m = 1;
    for (size_t i = 1; i < N; i++) {
        m *= x - data[i - 1].x;
        res += b[i] * m;
    }
    return res;
}

mydouble Interpolation::getLaGrangeY(mydouble x) {
    mydouble res = 0;
    for (size_t i = 0; i < N; i++) {
        mydouble m = data[i].y;
        for (size_t j = 0; j < i; j++) {
            m *= (x - data[j].x) / (data[i].x - data[j].x);
        }
        for (size_t j = i + 1; j < N; j++) {
            m *= (x - data[j].x) / (data[i].x - data[j].x);
        }
        res += m;
    }
    return res;
}

Coefficient2 Interpolation::getNewtonPolynom() {
    if(b == nullptr) {
        calcB();
    }
    Coefficient2 ret(1);
    assert(N - 1 > 0);
    ret.setCoefficient(0, b[0]);
    Coefficient2 m(1);
    m.setCoefficient(0, 1);
    for (size_t i = 1; i < N; i++) {
        m = m * Coefficient2(-data[i - 1].x, (mydouble) 1);
        ret = ret + b[i] * m;
    }
    return ret;
}

Coefficient2 Interpolation::calcSpline(size_t i) {
    assert(i < N - 1);
    Coefficient2 a(4);
    Coefficient2 polynom = getNewtonPolynom();
    Coefficient2 dpolynom = polynom.getDerive2();
    a.setCoefficient(3,
                     (dpolynom.f(getXindex(i + 1)) * (getXindex(i + 1) - getXindex(i)) - 2 * (getYindex(i + 1) - getYindex(i)) + dpolynom.f(getXindex(i)) * (getXindex(i + 1) - getXindex(i))) /
                             (cubeValue(getXindex(i + 1) - getXindex(i)))
    );
    a.setCoefficient(2,
                     (- dpolynom.f(getXindex(i + 1)) * (getXindex(i + 1) - getXindex(i)) * (getXindex(i + 1) + 2 * getXindex(i)) + 3 * (getYindex(i + 1) - getYindex(i)) * (getXindex(i + 1) + getXindex(i))) /
                             (cubeValue(getXindex(i + 1) - getXindex(i)))
                     - (dpolynom.f(getXindex(i)) * (getXindex(i + 1) - getXindex(i)) * (getXindex(i) + 2 * getXindex(i + 1))) /
                                                    (cubeValue(getXindex(i + 1) - getXindex(i)))

    );
    a.setCoefficient(1,
                     (dpolynom.f(getXindex(i + 1)) * getXindex(i) * (2 * getXindex(i + 1) + getXindex(i)) * (getXindex(i + 1) - getXindex(i)) - 6 * (getYindex(i + 1) - getYindex(i)) * getXindex(i) * getXindex(i + 1)) /
                             (cubeValue(getXindex(i + 1) - getXindex(i)))
                     + (dpolynom.f(getXindex(i)) * getXindex(i + 1) * (getXindex(i + 1) + 2 * getXindex(i)) * (getXindex(i + 1) - getXindex(i))) /
                       (cubeValue(getXindex(i + 1) - getXindex(i)))
    );
    a.setCoefficient(0, (-dpolynom.f(getXindex(i + 1)) * getXindex(i) * getXindex(i) * getXindex(i + 1) * (getXindex(i + 1) - getXindex(i)) + getYindex(i + 1) * getXindex(i) * getXindex(i) * (3 * getXindex(i + 1) - getXindex(i))) /
                          (cubeValue(getXindex(i + 1) - getXindex(i)))
                        + (getYindex(i) * getXindex(i + 1) * getXindex(i + 1) * (getXindex(i + 1) - 3 * getXindex(i)) - dpolynom.f(getXindex(i)) * getXindex(i) * getXindex(i + 1) * getXindex(i + 1) * (getXindex(i + 1) - getXindex(i))) /
                          (cubeValue(getXindex(i + 1) - getXindex(i)))
    );
    return a;
}

mydouble Interpolation::getXindex(size_t index) const{
    assert(index < N);
    return data[index].x;
}

mydouble Interpolation::getYindex(size_t index) {
    assert(index < N);
    return data[index].y;
}

mydouble Interpolation::getSpline(mydouble x) {
    size_t index = findIndex(x);
    Coefficient2 a = calcSpline(index);
    return a.f(x);
}

size_t Interpolation::findIndex(mydouble x) const {
    if(IS_ZERO(getXindex(0) - x))
        return 0;
    for (size_t i = 0; i < N - 1; i++) {
        if(getXindex(i) < x && x <= getXindex(i + 1)) {
            return i;
        }
    }
    throw std::invalid_argument("invalix x");
}

void Interpolation::printSplines() {
    for(size_t i = 0; i < N - 1; i++) {
        cout << "#Spline " << i << endl << calcSpline(i) << endl;
    }
}
