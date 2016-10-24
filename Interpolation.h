//
// Created by altair on 07.10.15.
//

#ifndef ZADACHA2_INTERPOLATION_H
#define ZADACHA2_INTERPOLATION_H


#include <string.h>
#include "types.h"
#include "Point.h"
#include "Coefficient2.h"
#include <iostream>

using std::cout;
using std::endl;

class Interpolation {
    Point *data;
    size_t N;

    mydouble *b;

    void newB(const size_t N);

    inline mydouble cubeValue(mydouble x) {
        return x * x * x;
    }

    mydouble getXindex(size_t index) const;
    mydouble getYindex(size_t index);

public:
    Interpolation(const size_t N): N(N){
        data = new Point[N];
        b = nullptr;
    }

    Interpolation(const Interpolation &interpolation) {
        N = interpolation.N;
        data = new Point[N];
        memcpy(data, interpolation.data, sizeof(Point) * N);
        if(interpolation.b != nullptr) {
            b = new mydouble[N];
            memcpy(b, interpolation.b, N * sizeof(mydouble));
        } else {
            b = nullptr;
        }
    }

    ~Interpolation() {
        delete[] data;
        if(b != nullptr) {
            delete[] b;
        }
    }

    void setPoint(size_t index, Point value);

    void setPoint(size_t index, mydouble x, mydouble y);

    void dump() {
        cout << "#Dump" << endl;
        cout << "N=" << N << endl;
        for (size_t i = 0; i < N; i++) {
            cout << "data[" << i << "]=(" << data[i].x << ", " << data[i].y << ")" << endl;
        }
        cout << "#END DUMP" << endl;
    }

    mydouble getNewtonF(const size_t i1 , const size_t i2) const;

    void calcB();

    mydouble getNewtonY(mydouble x);

    Coefficient2 getNewtonPolynom();

    mydouble getLaGrangeY(mydouble Y);

    size_t findIndex(mydouble x) const;

    mydouble getSpline(mydouble x);

    Coefficient2 calcSpline(size_t i);

    void printSplines();

};


#endif //ZADACHA2_INTERPOLATION_H
