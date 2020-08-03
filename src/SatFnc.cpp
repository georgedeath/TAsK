#include "SatFnc.h"

#include <math.h>
#include <stdio.h>

#include <cassert>
#include <iomanip>
#include <iostream>

SatFnc::SatFnc(FPType freeFlow,
               FPType B,
               FPType capacity,
               FPType power,
               FPType capdisp,
               FPType toll) : freeFlow_(freeFlow),
                              B_(B),
                              capacity_(capacity),
                              power_(power),
                              capdisp_(capdisp),
                              toll_(toll){};

SatFnc::~SatFnc(){

};

FPType SatFnc::evaluate(FPType linkFlow) const {
    if (toll_ == 1e7) {
        return INFINITY;
    }
    // same for both
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
        return freeFlow_ + toll_;

    // BPR
    if (linkFlow <= capacity_) {
        if (B_ == 0.0) {
            return freeFlow_ + toll_;
        }
        return freeFlow_ * (1 + B_ * pow(linkFlow / capacity_, power_)) + toll_;
    }

    // saturn
    // 0.5 * 3600 = 1800  -- 3600 is the modelperiod for everything
    return freeFlow_ * (1 + B_) + 1800.0 * (linkFlow - capacity_) / capdisp_ + toll_;
};

FPType SatFnc::evaluateDerivative(FPType linkFlow) const {
    if (toll_ == 1e7) {
        return 0.0;
    }
    // same for both
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7)
        return 0.0;

    // BPR
    if (linkFlow <= capacity_) {
        if (B_ == 0.0) {
            return 0.0;
        }
        return freeFlow_ * B_ * power_ * pow(linkFlow / capacity_, power_ - 1) / capacity_;
    }

    // saturn: deriv -> m / (2 * capacity dispersion)
    return 1800.0 / capdisp_;
};

void SatFnc::print() const {
    std::cout << "sat " << std::endl;
    std::cout << "freeFlow = " << freeFlow_ << " B = " << B_ << " capacity = " << capacity_ << " power_ = " << power_ << std::endl;
};

FPType SatFnc::evaluateSecondDerivative(FPType linkFlow) const {
    // not used anywhere
    return 1800.0 / capdisp_;
};

FPType SatFnc::evaluateTimeAndDerivative(FPType linkFlow, FPType &der) {
    if (toll_ == 1e7) {
        der = 0.0;
        return INFINITY;
    }

    // same for both
    if (capacity_ == 0 || linkFlow == 0.0 || capacity_ == 1e7) {
        der = 0.0;
        return freeFlow_ + toll_;
    }

    // BPR
    if (linkFlow <= capacity_) {
        if (B_ == 0.0) {
            der = 0.0;
            return freeFlow_ + toll_;
        }
        A_ = freeFlow_ * B_ * pow(linkFlow / capacity_, power_ - 1) / capacity_;
        der = power_ * A_;
        return freeFlow_ + A_ * linkFlow + toll_;
    }

    der = 1800.0 / capdisp_;
    return freeFlow_ * (1 + B_) + 1800.0 * (linkFlow - capacity_) / capdisp_ + toll_;
};

FPType SatFnc::getCapacity() {
    return capacity_;
};

FncType SatFnc::getType() {
    return SATFNC;
};
