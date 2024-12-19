## main.cpp

    #include "mbed.h"
    #include "im920_can_lib.h"
    
    CAN can(PA_11,PA_12,1000000);
    can920 ps5(can,2);
    
    // main() runs in its own thread in the OS
    int main()
    {
        int val;
        int data[PS5::ALL_BUTTON];
        bool Stop_Signal;
        int jyusin[8];
        int sousin[8];
        for(int j=0;j<8;j++){
            sousin[j]=j*17;
        }
        ps5.setup(30);
        while(1){
            val=ps5.get_data(data,&Stop_Signal,jyusin);
            // val=ps5.get_data(data,&Stop_Signal);
            ps5.trans_data(sousin,2);
    
            if(val==1){
                // printf("button\r\n");
                if(data[PS5::LSTICKX])printf("%3d\r\n",data[PS5::LSTICKX]);
                if(data[PS5::RSTICKX])printf("%3d\r\n",data[PS5::RSTICKX]);
            }
            else if(val==-1){
                printf("nothing\r\n");
            }
        }
    }
