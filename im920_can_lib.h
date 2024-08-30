#ifndef _IM920_CAN_LIB_H_
#define _IM920_CAN_LIB_H_

#include "mbed.h"

enum PS5{
    RIGHT,
    DOWN,
    UP,
    LEFT,
    UPRIGHT,
    DOWNRIGHT,
    UPLEFT,
    DOWNLEFT,
    SQUARE,
    CROSS,
    CIRCLE,
    TRIANGLE,
    L1,
    R1,
    SHARE,
    OPTIONS,
    L3,
    R3,
    PSBUTTON,
    TOUCHPAD,
    L2,
    R2,
    L2VALUE,
    R2VALUE,
    LSTICKX,
    LSTICKY,
    RSTICKX,
    RSTICKY,
    ALL_BUTTON
};

class can920
{
public:
    

    can920(CAN &can,int node);
    
    int get_data(int*,bool*,int*);
    void trans_data(int*,int);
    

private:
    CAN &_can;
    Timer _t;
    int calculate(int*,int*,bool*);

    int _input[8];
    int _data[8];
    int _pdata[8];
    int _node;
    int _node_input;
    int _val;
    int _origin[8];

};

#endif
