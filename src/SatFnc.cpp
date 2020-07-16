#include "SatFnc.h"

#include <cassert>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>

SatFnc::SatFnc(FPType freeFlow, FPType B, FPType capacity, FPType power) : freeFlow_(freeFlow),
                                                                           B_(B), capacity_(capacity), power_(power){};

SatFnc::~SatFnc(){

};

FPType SatFnc::evaluate(FPType linkFlow) const
{
    if (capacity_ == 0 || power_ == 0.0 || linkFlow == 0.0)
        return freeFlow_;

    // use BPR cost func here
    if (linkFlow <= capacity_)
        return freeFlow_ * (1 + B_ * pow(linkFlow / capacity_, power_));

    FPType capcost = freeFlow_ * (1 + B_);
    // 0.5 * 3600 = 1800  -- 3600 is the modelperiod for everything
    FPType penalty = 1800.0 * (linkFlow - capacity_) / capacity_;
    return capcost + penalty;
};

FPType SatFnc::evaluateDerivative(FPType linkFlow) const
{
    if (capacity_ == 0 || power_ - 1e-16 < 2 || linkFlow == 0.0)
        return 0.0;
    if (linkFlow <= capacity_)
        // bpr first derivative
        return freeFlow_ * B_ * power_ * pow(linkFlow / capacity_, power_ - 1) / capacity_;
    // else the saturn deriv: m / (2 * capacity dispersion)
    return 1800.0 / capacity_;
};

void SatFnc::print() const
{
    std::cout << "sat " << std::endl;
    std::cout << "freeFlow = " << freeFlow_ << " B = " << B_ << " capacity = " << capacity_ << " power_ = " << power_ << std::endl;
};

FPType SatFnc::evaluateSecondDerivative(FPType linkFlow) const
{
    // not used anywhere
    return 0.0;
};

FPType SatFnc::evaluateTimeAndDerivative(FPType linkFlow, FPType &der)
{
    der = evaluateDerivative(linkFlow);
    return evaluate(linkFlow);
};

FPType SatFnc::getCapacity()
{
    return capacity_;
};

FncType SatFnc::getType()
{
    return SATFNC;
};
