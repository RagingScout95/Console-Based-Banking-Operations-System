#include<stdio.h>
#include "validate.h"

int main(){
    
    // addTestUsers();
    char name[MAX];
    char gender;
    char dateOfBirth[MAX];
    char address[MAX];
    char city[MAX];
    char pan[MAX];
    char aadhar[MAX];
    char accType[MAX];
    char accountNumber[MAX];
    char receiverAccountNumber[MAX];
    float amount;
    
    for(;;){
        displayMainMenu(); 

        int choice;
        printf("Option ");
        scanf("%d", &choice);
        printf("\n");
        getchar();
        switch(choice){
            case 1:

                printf("Enter full name: ");
                do{
                    Stromginput(name,MAX);
                } while (!validateStr(name));
                
                printf("Enter gender (M/F): ");
                do {
                    gender = toupper(getchar());
                    getchar(); 
                } while (!validateGender(gender));

                printf("Enter date of birth (DD-MM-YYYY): ");
                do {
                    input(dateOfBirth, MAX);
                } while (!validateDob(dateOfBirth));

                printf("Enter address: ");
                do{
                    Stromginput(address,MAX);
                } while (!validateStr(address));

                printf("Enter city: ");
                do{
                    Stromginput(city,MAX);
                } while (!validateStr(city));

                printf("Enter PAN card number: ");
                do{
                    input(pan,10);
                } while (!validatePanCard(pan));
                

                printf("Enter Aadhar card number: ");
                do{
                    input(aadhar,12);
                } while (!validateAadharNumber(aadhar));

                printf("Choose account type: \n");
                displayAccountTypes();
                bool valid = false;

                do{
                    printf("Option: ");
                    scanf("%d", &choice);
                    getchar();
                    switch(choice) {
                    case 1:
                        strcpy(accType, "Savings Account");
                        valid = true;
                        break;
                    case 2:
                        strcat(accType, "Current Account");
                        valid = true;
                        break;
                    case 3:
                        strcpy(accType, "Joint Account");
                        valid = true;
                        break;
                    default: 
                        printf("Invalid choice\n");
                        break;
                    }
                    
                } while (!valid);
                   
                addAccount(name, gender, dateOfBirth, address, city, pan, aadhar, accType);
                break;
            case 2:
            // remaining
                displayUpdateMenu();
                valid = false;

                do{
                    printf("Option: ");
                    scanf("%d", &choice);
                    getchar();
                    switch(choice) {
                        case 1:
                            printf("Enter account number : ");
                            do{
                                input(accountNumber,MAX);
                            } while (!checkAccountExist(accountNumber));

                            printf("Enter full name: ");
                            do{
                                Stromginput(name,MAX);
                            } while (!validateStr(name));

                            updateAccountHolderName(name,accountNumber);

                            valid = true;
                            break;
                        case 2:
                            printf("Enter account number : ");
                            do{
                                input(accountNumber,MAX);
                            } while (!checkAccountExist(accountNumber));

                            printf("Enter address: ");
                            do{
                                Stromginput(address,MAX);
                            } while (!validateStr(address));

                            printf("Enter city: ");
                            do{
                                Stromginput(city,MAX);
                            } while (!validateStr(city));

                            updateAddressAndCity(address, city ,accountNumber);
                            valid = true;
                            break;
                        case 3:
                            printf("Enter account number : ");
                            do{
                                input(accountNumber,MAX);
                            } while (!checkAccountExist(accountNumber));

                            printf("Enter date of birth (DD-MM-YYYY): ");
                            do {
                                input(dateOfBirth, MAX);
                            } while (!validateDob(dateOfBirth));

                            updateDob(dateOfBirth ,accountNumber);
                            valid = true;
                            break;
                        case 4:
                            valid = true;
                            break;
                        default: 
                            printf("Invalid choice\n");
                            break;
                    }
                    
                } while (!valid);

                break;
            case 3:
                printf("Enter account number : ");
                do{
                    input(accountNumber,MAX);
                } while (!checkAccountExist(accountNumber));

                printf("Enter amount: ");
                do{
                    scanf("%f", &amount);
                    getchar();
                } while (!validateAmount(amount));
                
                updateAccountBalance(accountNumber ,amount);
                break;
            case 4:
                printf("Enter account number : ");
                do{
                    input(accountNumber,MAX);
                } while (!checkAccountExist(accountNumber));

                printf("Enter amount : ");
                do{
                    scanf("%f", &amount);
                    getchar();
                } while (!validateAmount(amount) || !checkWithdraw(accountNumber,amount));

                updateAccountBalance(accountNumber, -amount);
                break;
            case 5:
                printf("Enter Senders account number : ");
                do{
                    input(accountNumber,MAX);
                } while (!checkAccountExist(accountNumber));

                printf("Enter Receiver account number : ");
                do{
                    input(receiverAccountNumber,MAX);
                } while (!checkAccountExist(receiverAccountNumber));

                printf("Enter amount : ");
                do{
                    scanf("%f", &amount);
                    getchar();
                } while (!validateAmount(amount) || !checkWithdraw(accountNumber,amount));

                fundTransfer(accountNumber,receiverAccountNumber,amount);

                break;
            case 6:
                displaySearchMenu();
                valid = false;

                do{
                    printf("Option: ");
                    scanf("%d", &choice);
                    getchar();
                    switch(choice) {
                        case 1:
                            printf("Enter Account Number: ");
                            do{
                                input(accountNumber,6);
                            } while (!validateAccountNumber(accountNumber));

                            findAccountByAccountNumber(accountNumber);
                            
                            valid = true;
                            break;
                        case 2:
                            printf("Enter full name: ");
                            do{
                                Stromginput(name,MAX);
                            } while (!validateStr(name));

                            findAccountByName(name);
                            valid = true;
                            break;
                        case 3:
                            printf("\nChoose account type: \n");
                            displayAccountTypes();
                            do{
                                printf("Option: ");
                                scanf("%d", &choice);
                                getchar();
                                switch (choice){
                                    case 1:
                                        findAccountByType("SAVINGS");
                                        valid = true;
                                        break;
                                    case 2:
                                        findAccountByType("CURRENT");
                                        valid = true;
                                        break;
                                    case 3:
                                        findAccountByType("JOINT");
                                        valid = true;
                                        break;
                                    default:
                                        printf("Invalid choice\n");
                                        break;
                                }
                            } while(!valid);
                            break;
                        case 4:
                            valid = true;
                            break;
                        default: 
                            printf("Invalid choice\n");
                            break;
                    }
                    
                } while (!valid);

                break;
            case 7:
                printf("Enter account number: ");
                do{
                    input(accountNumber,6);
                } while (!validateAccountNumber(accountNumber));
                checkBalance(accountNumber);
                break;
            case 8:
                printf("Exiting...");
                printf("Come back again!! :)\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
        printf("\n");
    }
    
    return 0;
}