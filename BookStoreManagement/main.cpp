#include <iostream>
#include<string.h>
#define MAX 100
using namespace std;

struct Account{
	int ID;
	char userName[31];
	char passWord[31];
};
 
struct User{
	int ID;
	char name[31];
	char address[50];
	char phone[11];
	int account_ID;
};

Account accounts[MAX];
int nAccounts=0;

User users[MAX];
int nUsers=0;

bool checkUserNameExist(char username[]){
	for(int i=0;i<nAccounts;i++){
		if(strcmp(accounts[i].userName,username)==0){
			return false;
		}
	}
	return true;
}

void registerAccount(Account &account, int id=0){
	if(id<=0){
		account.ID = nAccounts+1;
	}
	else{
		account.ID = id;
	}
	re_enter:
	cout<<"\tEnter username: ";
	cin>>account.userName;
	if(checkUserNameExist(account.userName)==false){
		goto re_enter;
	}
	cout<<"\tEnter password: ";
	cin>>account.passWord;
}

bool loginSystem(char username[], char password[]){
	for(int i=0;i<nAccounts;i++){
		if(strcmp(accounts[i].userName,username)==0){
			if(strcmp(accounts[i].passWord,password)==0){
				return true;
			}
			else{
				return false;
			}
		}
	}
}

bool checkAccountIDExist(int id){
	for(int i=0;i<nAccounts;i++){
		if(accounts[i].ID==id){
			return true;
		}
	}
	return false;
}

void insertAccount(Account account){
	accounts[nAccounts++]=account;
}

void insertUser(User user){
	users[nUsers++] = user;
}

void registerUser(User &user){
	user.ID = nUsers+1;
	cout<<"\tEnter your name: ";
	cin.getline(user.name,sizeof(user.name));
	cout<<"\tEnter your address: ";
	cin.getline(user.address,sizeof(user.address));
	cout<<"\tEnter your phone: ";
	cin>>user.phone;
	
	re_enter:
	cout<<"\tEnter account ID: ";
	cin>>user.account_ID;
	
	if(checkAccountIDExist(user.account_ID)==false){
		Account account;
		registerAccount(account,user.account_ID);
		insertAccount(account);
	}
	else{
		cout<<"ID's account has already exist!";
		goto re_enter;
	}
	insertUser(user);
	cin.ignore();
}

int getAccountID(char username[]){
	for(int i=0;i<nAccounts;i++){
		if(strcmp(accounts[i].userName,username)==0){
			return accounts[i].ID;
		}
	}
}

char* getNameOfUser(char username[]){
	for(int i=0;i<nUsers;i++){
		if(users[i].account_ID==getAccountID(username)){
			return users[i].name;
		}
	}
}

void menuStartSystem(){
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	cout<<"|        1.Login       |        2. Register         |        3. Exit       |\n";
	cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
}

int main(){
	int choice;
	char userName[31], passWord[31];
	bool check=true;
	
	while(check==true){
		cout<<endl;
		menuStartSystem();
		cout<<"Enter your choice: ";
		cin>>choice;
		cin.ignore();
		
		switch(choice){
			case 1:
				cout<<"++++++++++++++++++++++LOGIN SYSTEM+++++++++++++++++++"<<endl;
				cout<<"Enter username: ";
				cin>>userName;
				cout<<"Enter password: ";
				cin>>passWord;
				if(loginSystem(userName,passWord)==true){
					cout<<"Hello, "<<getNameOfUser(userName)<<endl;
				}
				else{
					cout<<"Login failure!"<<endl;
				}
				break;
			case 2:
				cout<<"++++++++++++++++++++++REGISTER ACCOUNT++++++++++++++++"<<endl;
				User user;
				registerUser(user);
				cout<<"Registering successfully!"<<endl;
				break;
			case 3:
				check=false;
				break;
			default:
				cout<<"Invalid menu!"<<endl;
				break;
		}
	}
	return 0;
}
