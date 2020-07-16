#ifndef SAT_FNC_
#define SAT_FNC_

#include "LinkFnc.h"

class SatFnc : public LinkFnc
{

public:
    SatFnc(FPType freeFlow, FPType B, FPType capacity, FPType power);
    ~SatFnc();

    FPType evaluate(FPType linkFlow) const;
    FPType evaluateDerivative(FPType linkFlow) const;
    FPType evaluateSecondDerivative(FPType linkFlow) const;

    void print() const;

    virtual std::string toString() const
    {
        return "Saturn fnc";
    };

    LinkFnc *clone() const { return new SatFnc(*this); }

    FPType evaluateTimeAndDerivative(FPType linkFlow, FPType &der);

    virtual FncType getType();

    virtual FPType getCapacity();

private:
    const FPType freeFlow_;
    const FPType B_;
    const FPType capacity_;
    const FPType power_;
    // const FPType capacityDispersion_;
    // const FPType modelPeriod_;
};

#endif
