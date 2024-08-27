## main.cpp

    #include "mbed.h"
    #include "ps5_can_lib.h"
    
    CAN can(PA_11,PA_12,1000000);
    PS5 ps5(can,4); //第二引数はデータを受信したいコントローラとペアになってるim920slのノード番号
    
      
    int main(){
    
        int val;
        bool data[PS5::ALL_BUTTON];
        int analog[PS5::ALL_ANALOG]; 
        bool Stop_Signal; //緊急停止の状態を示す
        
        while (true) {
            val=ps5.get_data(data,analog,&Stop_Signal);
            if(val==1){
                if(data[PS5::CIRCLE])printf("circle\r\n");
                else printf("not circle\r\n");
                if(analog[PS5::R2VALUE])printf("r2value:%3d\r\n",analog[PS5::R2VALUE]);
                
                //ここにボタンに割り当てた動作を書く
                
            }
            else if(val==-1){
                //何もボタンが押されていないときに入ります
                printf("no push button\r\n");
            }
            if(Stop_Signal)printf("緊急停止中\r\n");
        }
    }
