#include <iostream>
#include "interpolTask.h"

using namespace std;

int main() {
    interpolTask task;
    cout.precision(9);
    task.readData();
    mydouble i = 0;
    cin >> i;
    Coefficient2 c = task.getInterpolation()->getNewtonPolynom();
    cout << "#Polynom:" << endl;
    cout << c << endl;
    cout << "#Splines:" << endl;
    task.getInterpolation()->printSplines();
    cout << "#Values in point " << i << ":" << endl;
    cout << "#Polynom:" << endl << c.f(i) << endl;
    cout << "#Newton:" << endl << task.getInterpolation()->getNewtonY(i) << endl;
    cout << "#LaGrange:" << endl <<  task.getInterpolation()->getLaGrangeY(i) << endl;
    cout << "#Spline:" << endl;
    cout << task.getInterpolation()->getSpline(i) << endl;
    cout << "#dPol:" << endl;
    cout << c.getDerive2().f(i) << endl;
    cout << "#dSpline:" << endl;
    cout << task.getInterpolation()->calcSpline(task.getInterpolation()->findIndex(i)).getDerive2().f(i) << endl;
    return 0;
}