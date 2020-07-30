#include "BprFnc.h"

#include <cassert>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>

BprFnc::BprFnc(FPType freeFlow, FPType B, FPType capacity, FPType power, FPType toll) : freeFlow_(freeFlow), B_(B), capacity_(capacity), power_(power), toll_(toll){};

BprFnc::~BprFnc(){

};

FPType BprFnc::evaluate(FPType linkFlow) const
{
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
        return freeFlow_ + toll_;
    return freeFlow_ * (1 + B_ * pow(linkFlow / capacity_, power_)) + toll_;
};

FPType BprFnc::evaluateDerivative(FPType linkFlow) const
{
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
        return 0.0;
    return freeFlow_ * B_ * power_ * pow(linkFlow / capacity_, power_ - 1) / capacity_;
};

void BprFnc::print() const
{
    std::cout << "bpr " << std::endl;
    std::cout << "freeFlow = " << freeFlow_ << " B = " << B_ << " capacity = " << capacity_ << " power_ = " << power_ << std::endl;
};

FPType BprFnc::evaluateSecondDerivative(FPType linkFlow) const
{
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
        return 0.0;
    return freeFlow_ * B_ * power_ / pow(capacity_, power_) * (power_ - 1) * pow(linkFlow, power_ - 2);
};

FPType BprFnc::evaluateTimeAndDerivative(FPType linkFlow, FPType &der)
{
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
    {
        der = 0.0;
        return freeFlow_ + toll_;
    }
    FPType A = freeFlow_ * B_ * pow(linkFlow / capacity_, power_ - 1) / capacity_;
    der = power_ * A;
    return freeFlow_ + A * linkFlow + toll_;
};

FPType BprFnc::getCapacity()
{
    return capacity_;
};

FncType BprFnc::getType()
{
    return BPRFNC;
};
