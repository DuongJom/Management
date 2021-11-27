#include<stdio.h>
#include<string.h>
#include "Lib.h"
#define MAX 100
#define file "ACCOUNT.BIN"

Account acc[MAX];
int n=0;

Account registerAcc(){
	Account account;
	re_enter:
    printf("Nhap so tai khoan: ");
    scanf("%d",&account.accountID);
    fflush(stdin);
    if(checkExist(account.accountID)!=-1){
        printf("So tai khoan nay da ton tai. Vui long nhap so tai khoan khac!");
        goto re_enter;
    }
    printf("Nhap ten khach hang: ");
    gets(account.customerName);
    fflush(stdin);
    printf("Nhap dia chi khach hang: ");
    gets(account.address);
    fflush(stdin);
    printf("Nhap so dien thoai: ");
    gets(account.phone);
    fflush(stdin);
    account.balance=0;
    return account;
}

void addAcc(){
    Account account = registerAcc();
    acc[n++]= account;
}

void showListOfAcc(){
    int i;
    printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|%-10s|%-25s|%-25s|%-11s|%-15s|\n","Account number","Name's customer","Address","Phone","Balance");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    for(i=0;i<n;i++){
        printf("|%-14d|%-25s|%-25s|%11s|%15.2f|\n",acc[i].accountID, acc[i].customerName,acc[i].address,acc[i].phone,acc[i].balance);
    }
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int checkExist(int accountID){
    int i;
    for(i=0;i<n;i++){
        if(acc[i].accountID==accountID){
            return i;
        }
    }
    return -1;
}

void updAcc(int choice){
    int id;
    re_enter:
    printf("Nhap so tai khoan can cap nhat thong tin: ");
    scanf("%d",&id);
    fflush(stdin);
    int index = checkExist(id);
    if(index!=-1){
        //choice==1: update address's customer
        //choice==2: update phone's customer
        if(choice==1){
            printf("Nhap dia chi moi: ");
            char newAddress[31];
            gets(newAddress);
            strcpy(acc[index].address,newAddress);
        }else if(choice==2){
            printf("Nhap so dien thoai moi: ");
            char newPhone[11];
            gets(newPhone);
            strcpy(acc[index].phone,newPhone);
        }
        else{
            printf("Lua chon khong hop le!");
        }
    }
    else{
        printf("Tai khoan khong ton tai!!\n");
        printf("Ban co muon nhap lai?(Y/n)\n>> ");
        char c;
        scanf("%c",&c);
        if(c=='Y'||c=='y'){
            goto re_enter;
        }
        else{
            return;
        }
    }
}

void sendMoneyToAcc(){
    int id;
    double sendMoney;
    re_enter:
    printf("Nhap so tai khoan: ");
    scanf("%d",&id);
    fflush(stdin);
    int index = checkExist(id);
    if(index!=-1){
        printf("Nhap so tien can gui: ");
        scanf("%lf",&sendMoney);
        acc[index].balance+=sendMoney;
    }
    else{
        printf("So tai khoan khong ton tai!! Ban co muon nhap lai?(Y/n)\n>> ");
        char c;
        scanf("%c",&c);
        if(c=='Y'|| c=='y'){
            goto re_enter;
        }
        else{
            return;
        }
    }
}

void getMoneyFromAcc(){
    int id;
    double getMoney;
    re_enter:
    printf("Nhap so tai khoan: ");
    scanf("%d",&id);
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+  1. 50.000    |   2. 100.000    |   3. 200.000    |\n");
    printf("+  4. 500.000   |   5. 1.000.000  |   6. 2.000.000  |\n");
    printf("+  7. 3.000.000 |   8. So khac    |                 |\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("Luu y: \n\tSo tien giao dich toi thieu la 50.000VND/giao dich;\n\tSo tien giao dich toi da la 30.000.000VND/giao dich\n");
    printf("Moi chon so tien can rut: ");
    int choiceMoney;
    scanf("%d",&choiceMoney);
    int index = checkExist(id);
    if(index!=1){
        switch(choiceMoney){
            case 1:
                getMoney=50000;
                break;
            case 2:
                getMoney=100000;
                break;
            case 3:
                getMoney=200000;
                break;
            case 4:
                getMoney=500000;
                break;
            case 5:
                getMoney=1000000;
                break;
            case 6:
                getMoney=2000000;
                break;
            case 7:
                getMoney=3000000;
                break;
            case 8:
                do{
                    printf("Nhap so tien can rut: ");
                    scanf("%lf",&getMoney);
                    if(getMoney<50000||getMoney>30000000){
                        printf("So tien rut khong le(50.000<=x<=30.000.000)!\n");
                    }
                }while(getMoney<50000||getMoney>30000000);

                break;
            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
        if(getMoney>acc[index].balance){
            printf("So du khong du de rut!! Ban vui long chon so tien khac!!");
        }
        else{
            acc[index].balance-=getMoney;
        }
    }
    else{
        printf("So tai khoan khong ton tai!! Ban co muon nhap lai?(Y/n)\n>> ");
        char c;
        scanf("%c",&c);
        if(c=='Y'|| c=='y'){
            goto re_enter;
        }
        else{
            return;
        }
    }
}

void writeFile(){
	FILE* f = fopen(file,"wb");
	fwrite(&n,sizeof(n),1,f);
	for(int i=0;i<n;i++){
		fwrite(&acc[i],sizeof(Account),1,f);
	}
	fclose(f);
}

int readFile()
{
	FILE* f = fopen(file,"rb");
	if(f==NULL){
		printf("Khong the doc file!!");
		return 0;
	}
	fread(&n,sizeof(n),1,f);
	for(int i=0;i<n;i++){
		fread(&acc[i],sizeof(Account),1,f);
	}
	fclose(f);
	return 1;
}

int menu(){
    printf("\n++++++++++++++QUAN LY TAI KHOAN+++++++++++++++++\n");
    printf("+             1. Them tai khoan moi            +\n");
    printf("+             2. Danh sach tai khoan           +\n");
    printf("+             3. Sua thong tin tai khoan       +\n");
    printf("+             4. Goi tien vao tai khoan        +\n");
    printf("+             5. Rut tien tu tai khoan         +\n");
    printf("+             6. Luu file                      +\n");
    printf("+             7. Doc file                      +\n");
    printf("+             8. Thoat                         +\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("===> Moi chon menu: ");
    int choice;
    scanf("%d",&choice);
    return choice;
}

