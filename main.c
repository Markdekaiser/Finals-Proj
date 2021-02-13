#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//For printing of Time in the Receipt
#include <time.h>
//For asserting
#include <assert.h>
//For the sleep function
#include <unistd.h>

//Globally Declared since it will be used by many functions
char cashierName[50];

// Lists of Coffee names
char* coffeeDatabase[20] = {
        "Iced Coffee",
        "Cafe Mocha",
        "Latte Machiato",
        "Glace",
        "Breve",
        "Espresso",
        "Latte",
        "Mocha",
        "Americano",
        "Cappucino",
        "Melya",
        "Cafe Miel",
        "Zoro",
        "Cubano",
        "Frappe",
        "Mazagran",
        "Palazzo",
        "Marocchino",
        "Guillermo",
        "Ristreto"
};

//Lists of coffee Prices
int coffeePrices[20]={
        30,
        35,
        35,
        35,
        35,
        40,
        40,
        40,
        40,
        40,
        50,
        50,
        50,
        50,
        50,
        30,
        40,
        50,
        35,
        45
};

//Lists of order quantities
int ordQuant[20] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
};

// PROMPT ENTER CASHIER NAME ON STARTUP
void cashierCheck(){
    system("cls");
    printf("\n\n\n");
    printf("\n");
    printf("\tEnter Cashier Name: ");
    scanf("%[^\n]%*c", &cashierName);
    printf("\n");
    printf("\n\n\n");
}


// START UP
void startUp(){
    printf("--------------------------------------------------------\n");
    printf("\n\n\n");
    printf("\tPOS(Point of Sale System) for Coffee Shop");
    printf("\n");
    printf("\tCoded and Designed by Mark Thaddeus Manuel");
    printf("\n");
    printf("\tBS Computer Science 1A");
    printf("\n\n\n");
    printf("--------------------------------------------------------\n");
    sleep(3);
    cashierCheck();
}

// RECEIPT
void receipt(int totalAmount,int payment, float change, char* customerName[], float tax){
    FILE *fp;

    //Creates a custom file name with a specific directory and it in "directory" var
    char* directory[50];
    sprintf(directory[0],".\\receipts\\%s.txt",customerName);

    //Use the custom directory to create a new file
    fp = fopen(directory[0], "w");

    fprintf(fp, "\tA CAFE SHOP\n");
    fprintf(fp, "\tVATREGIN #534-345-567-234\n");
    fprintf(fp, "\tOlongapo City Sports Complex,\n\tGordon College,Philippine,\n\tLungsod ng Olongapo, Zambales\n");
    fprintf(fp, "\n");

    //using the time library to create a time stamp
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));

    fprintf(fp,"\t%s\n", s);
    fprintf(fp, "\n");
    fprintf(fp, "\tCUSTOMER: %s\n", customerName);
    fprintf(fp, "\tCASHIER: %s\n", cashierName);
    fprintf(fp,"--------------------------------------------------------\n");
    fprintf(fp,"\n");
    fprintf(fp,"\tProduct\t\tPrice\t# of\t Amount\n");
    fprintf(fp,"\tName\t\t\tCups\t\n");
    fprintf(fp,"\n");

    //Loops the quantity array and print only if the quantity is not equal to zero
    for(int i = 0; i < 20; i++){
        if(ordQuant[i] != 0){
            int quan = ordQuant[i], presyo = coffeePrices[i];
            int Amount =  quan * presyo;
            //Measures string length so that only specific number of \t to be used
            if(strlen(coffeeDatabase[i]) >= 8 ){
                //\t used for  clean output
                fprintf(fp,"\t%s\t%d\t%d\t%d pesos\n", coffeeDatabase[i],coffeePrices[i],ordQuant[i],Amount);
            }else{
                //\t used for  clean output
                fprintf(fp,"\t%s\t\t%d\t%d\t%d pesos\n",coffeeDatabase[i], coffeePrices[i], ordQuant[i],Amount);
            }

        }
    }
    fprintf(fp,"--------------------------------------------------------\n");
    fprintf(fp, "\n");
    fprintf(fp, "\tAmount: %d pesos\n", totalAmount);
    fprintf(fp,"\tVAT: %.2f pesos\n", tax);
    fprintf(fp,"\tTotal Amount: %.2f\n", (float)totalAmount + tax);
    fprintf(fp, "\tPayment: %d pesos\n", payment);
    fprintf(fp, "\tChange: %.2f pesos\n", change);

    //closing file
    fclose(fp);
    system("cls");
    printf("\nRECEIPT DONE PRINTING. CHECK RECEIPT FOLDER WITH CUSTOMER_NAME.TXT");
    getch();
}


// EDIT CASHIER NAME
void editCashierName(){
    system("cls");
    printf("\n\n\n");
    printf("\n");
    printf("\tCurrent Cashier Name: %s\n", cashierName);
    printf("\n");
    printf("\tEnter New Cashier Name: ");
    scanf("%[^\n]%*c", &cashierName);
    printf("\n");
    printf("\n\n\n");
}


// ENTER ORDER
void enterOrder(){
    char customerName[50];
    int totalAmount = 0,payment = 0;
    float change = 0;

    //Resets Order
    for(int i = 0; i <20; i++){
        ordQuant[i] = 0;
    }

    //Prompts for Customer Name
    char cn;
    while(cn != 'y'){
        system("cls");
        printf("\n\n\n");
        printf("\tEnter Name of Customer: ");
        scanf("%[^\n]%*c", &customerName);
        printf("\tConfirm Name? y/n: ");
        scanf("%c", &cn);
        if (cn != 'y' || 'n'){
                scanf("%*[^\n]");
                scanf("%*c");
        }
    }
    printf("\n\n");

    char terminator;
    while(terminator != 'y'){
        system("cls");
        printf("\tCustomer: %s\n", customerName);
        printf("--------------------------------------------------------\n");
        printf("\n\n");
        printf("\tProduct\tProduct\t\tPrice\tQuantity\n");
        printf("\tNumber\tName\n");
        printf("\n");
        //Displays all Products
        for(int i = 0; i< 20; i++){
            //Measures string length so that only specific number of \t to be used
            if(strlen(coffeeDatabase[i]) >= 8 ){
                printf("\t%d\t%s\t%d\t%d\n", i+1 ,coffeeDatabase[i], coffeePrices[i],ordQuant[i]);
            }else{
                printf("\t%d\t%s\t\t%d\t%d\n",i+1 ,coffeeDatabase[i], coffeePrices[i],ordQuant[i]);
            }

        }


        printf("\n\n\n");
        printf("--------------------------------------------------------\n");
        int amount = 0, prodNum = 0, prodQuan = 0;
        printf("(Enter 0 to end ordering)");
        printf("Enter Product Number: ");
        scanf("%d", &prodNum);

        //Product number checker
        if(prodNum == 0){
            break;
        }else if(prodNum !=0){
            printf("Enter Product Quantity: ");
            scanf("%d", &prodQuan);
            ordQuant[prodNum - 1] = prodQuan;
        }


    }

    system("cls");
    printf("\tCUSTOMER: %s\n", customerName);
    printf("--------------------------------------------------------\n");
    printf("\n");
    printf("\tProduct\t\tPrice\t# of\t Amount\n");
    printf("\tName\t\t\tCups\t\n");
    printf("\n");

    //Processes and Calculations
    float tax = 0;
    for(int i = 0; i < 20; i++){
        if(ordQuant[i] != 0){
            int quan = ordQuant[i], presyo = coffeePrices[i];
            int Amount =  quan * presyo;
            totalAmount = totalAmount + Amount;
            float totalNumOfCups = totalNumOfCups + ordQuant[i];
            tax = 1.12 * totalNumOfCups;

            if(strlen(coffeeDatabase[i]) >= 8 ){
                printf("\t%s\t%d\t%d\t%d pesos\n", coffeeDatabase[i],coffeePrices[i],ordQuant[i],Amount);
            }else{
                printf("\t%s\t\t%d\t%d\t%d pesos\n",coffeeDatabase[i], coffeePrices[i], ordQuant[i],Amount);
            }

        }
    }
    printf("\n");
    printf("--------------------------------------------------------\n");
    printf("\tAmount: %d\n", totalAmount);
    printf("\tVAT: %.2f pesos\n", tax);
    printf("\tTotal Amount: %.2f\n", (float)totalAmount + tax);
    printf("\tEnter payment: ");
    scanf("%d", &payment);
    change = payment - ((float)totalAmount + tax);
    printf("\tCustomer Change: %.2f", change);

    printf("\n");
    printf("\nPress any key to print receipt");
    getch();

    //Calls receipt function to pass all needed datas
    receipt(totalAmount,payment,change, customerName, tax);



}


// MAIN FUNCTION
int main(){
    //Prompts Start Up
    startUp();

    //Main Menu
    char ch = '9';
    do{
        system("cls");
        printf("\n");
        printf("\tPOS(Point of Sale System) for Coffee Shop\n");
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("\n");
        printf("\t1. Edit Cashier Name\n");
        printf("\t2. Enter Order\n");
        printf("\t3. Exit\n");
        printf("\n");
        printf("--------------------------------------------------------\n");
        printf("Input: ");
        scanf("%c",&ch);

        //Resets input if not valid
        if (ch != '1' || '2' || '3'){
                scanf("%*[^\n]");
                scanf("%*c");
        }


        switch(ch){
            case '1':
                editCashierName();
                break;
            case '2':
                enterOrder();
                break;
            case '3':
                break;
        }
    }while(ch != '3');

    return 0;
}
