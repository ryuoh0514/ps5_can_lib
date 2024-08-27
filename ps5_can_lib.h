#ifndef _PS5_CAN_LIB_H_
#define _PS5_CAN_LIB_H_

#include "mbed.h"

class PS5
{
public:
    enum{
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
        ALL_BUTTON
    };
    enum{
        L2VALUE,
        R2VALUE,
        LSTICKX,
        LSTICKY,
        RSTICKX,
        RSTICKY,
        ALL_ANALOG
    };

    PS5(CAN &can,int node);
    
    int get_data(bool*,int*,bool*);
    

private:

    CAN &_can;
    int calculate(int*,bool*,int*,bool*);

    int _input[8];
    int _data[8];
    int _pdata[8];
    int _node;
    int _node_input;
    int _val;
    int _origin[8];

};

#endif
