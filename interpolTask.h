//
// Created by altair on 02.10.15.
//

#ifndef ZADACHA2_INTERPOLTASK_H
#define ZADACHA2_INTERPOLTASK_H


#include <stddef.h>
#include <iostream>
#include <assert.h>
#include "Point.h"
#include "Interpolation.h"

using namespace std;

class interpolTask {
    Interpolation *interpolation;

public:


    interpolTask(Interpolation *interpolation = nullptr) {
        if(interpolation != nullptr) {
            this->interpolation = new Interpolation(*interpolation);
        } else {
            this->interpolation = nullptr;
        }
    }


    virtual ~interpolTask() {
        delete interpolation;
    }

    void readData() {
        size_t N;
        cin >> N;
        if(interpolation != nullptr) {
            delete interpolation;
        }
        interpolation = new Interpolation(N);
        mydouble x, y;
        for(size_t i = 0; i < N; i++) {
            cin >> x >> y;
            interpolation->setPoint(i, x, y);
        }
    }


    Interpolation *getInterpolation() const {
        assert(interpolation != nullptr);
        return interpolation;
    }
};


#endif //ZADACHA2_INTERPOLTASK_H
