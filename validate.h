#include<stdio.h>
#include<stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX 50

typedef struct BankManagementSystem{
    char bankName[MAX];
    char ifsc[MAX];
    char accNumber[MAX];
    char accHolderName[MAX];
    int age;
    char gender;
    char dob[MAX];
    char address[MAX];
    char city[MAX];
    char accType[MAX];
    float balance;
    char panCard[MAX];
    char aadhar[MAX];
}bank;

static bank b[MAX];

// Display functions
void displayMainMenu();
void displayUpdateMenu();
void displaySearchMenu();
void displayAccountTypes();

// Validate functions
bool validateGender(char gender);
bool validateAge(int age);
bool validateDob(char *dob);
bool validatePanCard(char pan[]);
bool validateAadharNumber(char *aadhar);
bool validateStr(char *str);
bool validateAccountNumber(char *account);
bool validateAmount(float amount);
bool checkAccountExist(char *account);
bool checkWithdraw(char *accountNumber, float amount);

// Function for generating account number
char *generateAccountNumber(char name[]);

// Function for adding an account
void addAccount(char name[MAX], char gender, char dob[MAX], char address[MAX], char city[MAX], char pan[MAX], char aadhar[MAX], char accType[MAX]);

// Functions
void checkBalance(char *accountNumber);
void checkBalance(char *accountNumber);
void fundTransfer(char *senderAccNumb, char *receiverAccNumb, float amount);
int GetIndexByAccNumber(char *accountNumber);

// Search functions
void findAccountByAccountNumber(char *accountNumber);
void findAccountByName(char *name);
void findAccountByType(char *accType);

// Update functions
void updateAccountBalance(char *accountNumber, float amount);
void updateAccountHolderName(char *name,char *accountNumber);
void updateAddressAndCity(char *address,char *city, char *accountNumber);
void updateDob(char *dob, char *accountNumber);


// -------------------------------Initialization ----------------------------------------------------
void addTestUsers() {
    char names[10][MAX] = {"Harikrishna Giri Goswami", "Sneha Sharma", "Sneha Rani Patel", "Rohit Sharma", "Smita Sanjay Desai", "Rajeshwari Ramesh Iyer", "Amitabh Harivansh Bachchan", "Michael Clarke Duncan", "Dharmendra Kewal Krishan Deol", "Akshay HariOm Bhatia"};
    char genders[10] = {'M', 'F', 'F', 'M', 'F', 'M', 'M', 'M', 'M', 'M'};
    char dobs[10][MAX] = {"15-05-1990", "22-08-1985", "10-03-1995", "05-11-1982", "18-09-1978", "07-07-1992", "30-12-1980", "14-06-1998", "03-09-1987", "19-01-1993"};
    char addresses[10][MAX] = {"123 Main St", "456 Oak Ave", "789 Pine Blvd", "321 Elm Ln", "555 Maple Rd", "777 Cedar Dr", "888 Birch Ct", "999 Spruce Pl", "111 Willow Ln", "222 Aspen Rd"};
    char cities[10][MAX] = {"CityA", "CityB", "CityC", "CityD", "CityE", "CityF", "CityG", "CityH", "CityI", "CityJ"};
    char pans[10][10] = {"ABCPD1234E", "XYZQR5678F", "LMNOP1234G", "QRSTU5678H", "VWXYZ1234I", "ABCDK5678J", "EFGHI1234K", "LMNOJ5678L", "PQRST1234M", "UVWXY5678N"};
    char aadhars[10][12] = {"123456789012", "234567890123", "345678901234", "456789012345", "567890123456", "678901234567", "789012345678", "890123456789", "901234567890", "012345678901"};
    char accTypes[10][MAX] = {"Savings Account", "Savings Account", "Joint Account", "Savings Account", "Current Account", "Joint Account", "Savings Account", "Current Account", "Joint Account", "Savings Account"};

    for (int i = 0; i < 10; i++) {
        addAccount(names[i], genders[i], dobs[i], addresses[i], cities[i], "ABCPD1234E", "567890123456", accTypes[i]);
    }
}
// -------------------------------Input ----------------------------------------------------------------
int input(char str[MAX],int n){
    int ch,i=0;
    while((ch = getchar()) != '\n')
        if(i<n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}
int Stromginput(char str[MAX], int n) {
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (i < n - 1) {  
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    if (ch != '\n') {
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return i;
}

// -------------------------------Display--------------------------------- 
void displayMainMenu(){
    printf("\n**** Bank Management System ****\n");
    printf("1. Create Account\n");
    printf("2. Update Account Details\n");
    printf("3. Deposit\n");
    printf("4. Withdraw\n");
    printf("5. Funds Transfer\n");
    printf("6. Search details of account holder\n");
    printf("7. Balance Enquiry\n");
    printf("8. Exit\n");
}

void displayUpdateMenu(){
    printf("--- Update Menu ---\n");
    printf("1. Update name of account holder\n");
    printf("2. Update address of account holder\n");
    printf("3. Update DOB of account holder\n");
    printf("4. Back to Main menu\n");
}

void displaySearchMenu(){
    printf("--- Search Menu ---\n");
    printf("1. Search by account number\n");
    printf("2. Search by name\n");
    printf("3. Search by Type of Account\n");
    printf("4. Back to Main menu\n");
}

void displayAccountTypes(){\
    printf("1. Savings account\n");
    printf("2. Current account\n");
    printf("3. joint account\n");
}

// -------------------------------Validate--------------------------------- 
bool validateGender(char gender){
    // printf("(debug)--> Gender: %c\n",gender);
    if(toupper(gender)=='M' || toupper(gender)=='F'){
        return true;
    }
    printf("Please enter a valid gender: ");
    return false;
}

bool validateAge(int age){
    if(age<18){
        printf("Please enter a valid age: ");
        return false;
    }
    return true;
}

bool validateDob(char *dob) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int day = (dob[0] - '0') * 10 + (dob[1] - '0');
    int month = (dob[3] - '0') * 10 + (dob[4] - '0');
    int year = (dob[6] - '0') * 1000 + (dob[7] - '0') * 100 + (dob[8] - '0') * 10 + (dob[9] - '0');
    
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > (tm.tm_year + 1900)) {
        printf("Please enter a valid date in DD-MM-YYYY format: ");
        return false;
    }

    if (dob[2] != '-' && dob[5] != '-') {
        printf("Please enter a valid date in DD-MM-YYYY format: ");
        return false;
    }

    return true;
}

bool validatePanCard(char pan[]) {

    for(int i=0; i<5; i++){
        if(!isupper(pan[i])){
            printf("Please Enter a Valid Pan Card number: ");
            return false;
        }
    }
    for(int i=5; i<9;i++){
        if(!isdigit(pan[i])){
            printf("Please Enter a Valid Pan Card number: ");
            return false;
        }
    }
    if(!isupper(pan[9]) && strlen(pan)<=10){
        printf("Please Enter a Valid Pan Card number: ");
        return false;
    }
    
    return true;
}

bool validateAadharNumber(char *aadhar){
    for(int i=0; i<12; i++){
        if(!isdigit(aadhar[i])){
            printf("Please Enter a Valid Aadhar Number: ");
            return false;
        }
    }
    return true;
}
// later
bool validateStr(char str[MAX]){
    for(int i = 0; i < str[i]!='\0'; i++){
        if(!isalpha(str[i]) && !isspace(str[i])){ 
            printf("Please Enter a Valid String: ");
            return false;
        }
    }
    return true;
}


bool validateAccountNumber(char *account){
    for(int i=0; i<6; i++){
        if((i>=0 && i<3) && !isalpha(account[i])){
            printf("Please Enter a Valid Account Number: ");
            return false;
        }else if((i>=3) && !isdigit(account[i])){
            printf("Please Enter a Valid Account Number: ");
            return false;
        }
    }
    return true;
}

bool validateAmount(float amount){
    if(amount<=0){
        printf("Please enter a valid amount: ");
        return false;
    }
    return true;
}

bool checkAccountExist(char *account){
    if (validateAccountNumber(account)){
        for(int i=0; i<MAX; i++){
            if(strcmp(b[i].accNumber, account)==0){
                return true;
            }
        }
        printf("** Account does not exist **\n"); 
        printf("please Enter a valid account number: ");
        return false;
    }else{
        return false;
    }
    
}

bool checkWithdraw(char *accountNumber, float amount){
    for (int i = 0; i < MAX; i++) {
        if (strcmp(b[i].accNumber, accountNumber) == 0) {
            if(amount > b[i].balance) {
                printf("** Insufficient balance **\n");
                printf("Please enter a valid amount: ");
                return false;
            }
            break;
        }else if(strlen(b[i].accNumber)==0){
            printf("Account not found\n");
            break;
        }
    }
    return true;
}

// -------------------------------Function--------------------------------- 
char* generateAccountNumber(char name[]) {
    srand(time(NULL));
    char accountNum[MAX];
    int spaces = 0,i;
    accountNum[0] = toupper(name[0]);  
    accountNum[1] = '\0';

    for (i = 0; i < strlen(name); i++) {
        if (spaces > 1) break;
        if (isspace(name[i])) {
            char ch = name[i + 1];
            char str1[2] = {toupper(ch), '\0'};  
            char str2[2] = "";
            strcpy(str2, str1);
            strcat(accountNum, str2);
            spaces++;
        }
    }

    while ( spaces < 2 ) {
        char ch = name[spaces];
        char str1[2] = {toupper(ch), '\0'};  
        char str2[2] = "";
        strcpy(str2, str1);
        strcat(accountNum, str2);
        spaces++;
    }

    char random[MAX];
    sprintf(random, "%d", rand() % 900 + 100);

    return strcat(accountNum, random);
}

void addAccount(char name[MAX], char gender, char dob[MAX], char address[MAX], char city[MAX], char pan[MAX], char aadhar[MAX], char accType[MAX])
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if( strlen(b[MAX-1].accNumber)>0 ){
        printf("**** Account can't be created.(Reason Full) ****\n");
    }else{

        for(int i = 0; i < MAX; i++){
            if(strlen(b[i].accNumber)>0){
                continue;
            }else{
                strcpy(b[i].accHolderName, name);
                b[i].gender = gender;
                strcpy(b[i].dob, dob);
                strcpy(b[i].address, address);
                strcpy(b[i].city, city);
                strcpy(b[i].accType, accType);
                strcpy(b[i].panCard, pan);
                strcpy(b[i].aadhar, aadhar);

                int birthYear = (dob[6] - '0') * 1000 + (dob[7] - '0') * 100 + (dob[8] - '0') * 10 + (dob[9] - '0');
                b[i].age = tm.tm_year + 1900 - birthYear;

                strcpy(b[i].bankName, "Quack Bank of Ducks");
                strcpy(b[i].accNumber,generateAccountNumber(name));
                b[i].balance = 0;
                strcpy(b[i].ifsc, "QBOD00000581");

                printf("\n** Account created successfully **\n");
                printf("(Please keep this information Safely)\n");
                printf("- Account Number: %s\n", b[i].accNumber);
                printf("- Bank Name: %s\n", b[i].bankName);
                printf("- IFSC Number: %s\n", b[i].ifsc);
                printf("- Accout Type: %s\n",b[i].accType);
                break;
            }
        }
    }
}

void checkBalance(char *accountNumber){
  for (int i = 0; i < MAX; i++) {
        if (strcmp(b[i].accNumber, accountNumber) == 0) {
            printf("Account Balance  : %f\n", b[i].balance);
            break;
        }else if(strlen(b[i].accNumber)==0){
            printf("Account not found\n");
            break;
        }
    }  
}

void fundTransfer(char *senderAccNumb, char *receiverAccNumb, float amount){
    if(checkWithdraw(senderAccNumb,amount)){
        updateAccountBalance(senderAccNumb, -amount);
        updateAccountBalance(receiverAccNumb, amount);
    }
}

int GetIndexByAccNumber(char *accountNumber){
    for (int i = 0; i < MAX; i++) {
        if (strcmp(b[i].accNumber, accountNumber) == 0) {
            return i;
        }
    }
    return -1;
}

// -------------------------------Search Functions------------------------- 
void findAccountByAccountNumber(char *accountNumber) {

    for (int i = 0; i < MAX; i++) {
        if (strcmp(b[i].accNumber, accountNumber) == 0) {
            printf("\n** Account Details **\n");
            printf("Account Holder   : %s\n", b[i].accHolderName);
            printf("Account Number   : %s\n", b[i].accNumber);
            printf("Gender           : %c\n", b[i].gender);
            printf("Age              : %d\n", b[i].age);
            printf("Date of Birth    : %s\n", b[i].dob);
            printf("Address          : %s, %s\n", b[i].address, b[i].city);
            printf("Account Type     : %s\n", b[i].accType);
            printf("PAN Card         : %s\n", b[i].panCard);
            printf("Aadhar Number    : %s\n", b[i].aadhar);
            printf("Account Balance  : %f\n", b[i].balance);
            break;
        }
    }
}

void findAccountByName(char *name) {
    int count = 1;

    for (int i = 0; i < MAX; i++) {

        if (strstr(strupr(b[i].accHolderName), strupr(name)) != NULL) {
            printf("\nAccount : %d\n",count++);
            printf("\n** Account Details **\n");
            printf("Account Holder   : %s\n", b[i].accHolderName);
            printf("Account Number   : %s\n", b[i].accNumber);
            printf("Gender           : %c\n", b[i].gender);
            printf("Age              : %d\n", b[i].age);
            printf("Date of Birth    : %s\n", b[i].dob);
            printf("Address          : %s, %s\n", b[i].address, b[i].city);
            printf("Account Type     : %s\n", b[i].accType);
            printf("PAN Card         : %s\n", b[i].panCard);
            printf("Aadhar Number    : %s\n", b[i].aadhar);
            printf("Account Balance  : %f\n", b[i].balance);
        }else if(strlen(b[i].accNumber)==0){
            break;
        }
    }
    if(count == 1)
        printf("No Account Details");
}

void findAccountByType(char *accType) {
    int count = 1;
    printf("Account Type : %s\n", accType);
    for (int i = 0; i < MAX; i++) {

        if (strstr(strupr(b[i].accType), strupr(accType)) != NULL) {
            printf("\nAccount : %d\n",count++);
            printf("\n** Account Details **\n");
            printf("Account Holder   : %s\n", b[i].accHolderName);
            printf("Account Number   : %s\n", b[i].accNumber);
            printf("Gender           : %c\n", b[i].gender);
            printf("Age              : %d\n", b[i].age);
            printf("Date of Birth    : %s\n", b[i].dob);
            printf("Address          : %s, %s\n", b[i].address, b[i].city);
            printf("Account Type     : %s\n", b[i].accType);
            printf("PAN Card         : %s\n", b[i].panCard);
            printf("Aadhar Number    : %s\n", b[i].aadhar);
            printf("Account Balance  : %f\n", b[i].balance);
        }else if(strlen(b[i].accNumber)==0){
            break;
        }
    }
    if(count == 1)
        printf("No Account Details");
}

// -------------------------------Update Functions-------------------------
void updateAccountBalance(char *accountNumber, float amount) {
    for (int i = 0; i < MAX; i++) {
        if (strcmp(b[i].accNumber, accountNumber) == 0) {
            b[i].balance += amount;
            printf("\n** Account Updated **\n");
            printf("Account Number   : %s\n", b[i].accNumber);
            printf("Account Balance  : %f\n", b[i].balance);
            break;
        }else if(strlen(b[i].accNumber)==0){
            printf("Account not found\n");
            break;
        }
    }
}

void updateAccountHolderName(char *name, char *accountNumber){
    int index = GetIndexByAccNumber(accountNumber);
    if(index!=-1){
        strcpy(b[index].accHolderName, name);
        printf("\n** Account Updated **\n");
    }
}

void updateAddressAndCity(char *address,char *city, char *accountNumber){
    int index = GetIndexByAccNumber(accountNumber);
    if(index!=-1){
        strcpy(b[index].address, address);
        strcpy(b[index].city, city);
        printf("\n** Account Updated **\n");
    }
}

void updateDob(char *dob, char *accountNumber){
    int index = GetIndexByAccNumber(accountNumber);
    if(index!=-1){
        strcpy(b[index].dob, dob);
        printf("\n** Account Updated **\n");
    }
}

