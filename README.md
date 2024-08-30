## main.cpp

    #include "mbed.h"
    #include "im920_can_lib.h"
    
    CAN can(PA_11,PA_12,1000000);
    can920 im920(can,1);//受信したいコントローラ側im920のノード番号

    int main()
    {
        int val;
        int data[PS5::ALL_BUTTON];//ディジタル・アナログすべてまとめた
        bool Stop_Signal;//遠隔非常停止の状態 true=停止 false=解除
        int jyusin[8];//モジュール間通信の受信データ格納
        int sousin[8];//モジュール間通信の送信データ
        while(1){
            val=im920.get_data(data,&Stop_Signal,jyusin);//コントローラのデータ、遠隔非常停止の状態確認、受信データ
            //val=im920.get_data(data,&Stop_Signal);//データの受信しない場合はこれでもいい
            im920.trans_data(sousin,4);//データを送信する。送信に使用するモジュールのノード番号指定
            if(val==1){
                if(data[PS5::CIRCLE]){}
                else{}
                if(data[PS5::LSTICKX]){}
                else{}
                //コントローラデータに変化があるとき入る
            }
            else if(val==-1){
                //コントローラが何も押されてないときに入る
            }
        }
    }
