#include "mbed.h"
#include "ps5_can_lib.h"

PS5::PS5(CAN &can,int node)
    : _can(can)
{
    // _can.frequency(1000000);
    _can.mode(CAN::Normal);
    _node=node;  
    _origin[0]=0;
    _origin[1]=0;
    _origin[2]=128;
    _origin[3]=128;
    _origin[4]=128;
    _origin[5]=128;
    _origin[6]=0;
    _origin[7]=0;
    CANMessage msg_node;
    msg_node.id=0x10;
    msg_node.data[0]=0x10+_node;
    can.write(msg_node);
}

int PS5::get_data(bool *d,int *a,bool *stop_emer)
{
    CANMessage _msg;

    if(_can.read(_msg)){
        if(_msg.id==0x10+_node){
            // printf("node in!!!\r\n");
            for(int i=0;i<8;i++)_input[i]=(int)_msg.data[i];
            return calculate(_input,d,a,stop_emer);  
        }
    }
    return 0;
}

int PS5::calculate(int *msg_data,bool *d,int *a,bool *stop_emer){
    CANMessage _msg_stop;
    _msg_stop.id=0x01;
    _msg_stop.len=1;
    int sdec=0;
    for(int i=0;i<8;i++){
      if(_pdata[i]!=msg_data[i])sdec++;
      _pdata[i]=msg_data[i];
    }
    *stop_emer=(msg_data[7]&0xC0)>>6;
    _msg_stop.data[0]=*stop_emer;
    _can.write(_msg_stop);
    if(sdec>0){
        int _r2,_l2;
        _l2=msg_data[6]&0x7F;
        _r2=(msg_data[6]&0x80)>>7|(msg_data[7]&0x3F)<<1;
        
        d[RIGHT]    =msg_data[0]==0b0001?true:false;
        d[PS5::DOWN]=msg_data[0]==0b0010?true:false;
        d[UP]       =msg_data[0]==0b0011?true:false;
        d[LEFT]     =msg_data[0]==0b0100?true:false;
        d[UPRIGHT]  =msg_data[0]==0b0101?true:false;
        d[DOWNRIGHT]=msg_data[0]==0b0110?true:false;
        d[UPLEFT]   =msg_data[0]==0b0111?true:false;
        d[DOWNLEFT] =msg_data[0]&0b1000?true:false;
        d[SQUARE]   =msg_data[0]&0b00010000?true:false;
        d[CROSS]    =msg_data[0]&0b00100000?true:false;
        d[CIRCLE]   =msg_data[0]&0b01000000?true:false;
        d[TRIANGLE] =msg_data[0]&0b10000000?true:false;
        d[L1]       =msg_data[1]&0b0001?true:false;
        d[R1]       =msg_data[1]&0b0010?true:false;
        d[SHARE]    =msg_data[1]&0b0100?true:false; 
        d[OPTIONS]  =msg_data[1]&0b1000?true:false;
        d[L3]       =msg_data[1]&0b00010000?true:false;
        d[R3]       =msg_data[1]&0b00100000?true:false;
        d[PSBUTTON] =msg_data[1]&0b01000000?true:false;
        d[TOUCHPAD] =msg_data[1]&0b10000000?true:false;
        d[L2]       =_l2?true:false;
        d[R2]       =_r2?true:false;

        a[L2VALUE]=_l2;
        a[R2VALUE]=_r2;
        a[LSTICKX]=msg_data[2]-128;
        a[LSTICKY]=msg_data[3]-128;
        a[RSTICKX]=msg_data[4]-128;
        a[RSTICKY]=msg_data[5]-128;

        int j=0;
        msg_data[7]=(msg_data[7]<<2)&0xFF;
        printf("msg_data[7]:%d  ",msg_data[7]);
        for(int i=0;i<8;i++){
            // printf("%3x",msg_data[i]);
            if(_origin[i]==msg_data[i])j++;
        }
        // printf("\r\n");

        if(j==8)return -1;
        else return 1;
    }else{
        return 0;
    }
}
