#include<stdio.h>
#include<stdlib.h>
#include "Lib.h"

int main(){
    int checked=0;
    while(checked==0){
        int choice = menu();
        switch(choice){
            case 1:
                addAcc();
                break;
            case 2:
                showListOfAcc();
                break;
            case 3:
                printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                printf("+       1. Dia chi       |       2. So dien thoai       +\n");
                printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                printf("Moi chon thong tin can thay doi: ");
                int choiceInfo;
                scanf("%d",&choiceInfo);
                updAcc(choiceInfo);
                showListOfAcc();
                break;
            case 4:
                sendMoneyToAcc();
                showListOfAcc();
                break;
            case 5:
                getMoneyFromAcc();
                showListOfAcc();
                break;
            case 6:
                printf("Dang tien hanh luu file...\n");
                writeFile();
                printf("Luu file thanh cong!!\n");
                break;
            case 7:
                printf("Dang tien hanh doc file...\n");
                int status = readFile();
                if(status==1){
                    printf("Doc file thanh cong!\n");
                    showListOfAcc();
                }
                break;
            case 8:
                checked=-1;
                break;
            default:
                printf("Lua chon menu khong hop le!\n");
                break;
        }
    }
    return 0;
}
