#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

typedef struct
{
    int accountID;
    char customerName[31];
    char address[31];
    char phone[11];
    double balance;
} Account;

Account registerAcc();
void addAcc();
void showListOfAcc();
int checkExist(int accountID);
void updAcc(int choice);
int menu();
void sendMoneyToAcc();
void getMoneyFromAcc();
void writeFile();
int readFile();
#endif // LIB_H_INCLUDED
