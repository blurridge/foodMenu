/*
Goals:
1. Create a linked list of possible combo food to be added to a meal along with a main food product.
2. Items can only be edited with successful password entry.
3. Should output order made, and total price of order.
4. Ask for cash paid, and check if money given is enough for a max of 3 tries.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct comboFoodItem{
    char name[15];
    float price;
    struct comboFoodItem *next;
} COMBOFOOD;

typedef struct mainFoodItem{
    char name[15];
    float price;
    struct mainFoodItem *next;
    struct comboFoodItem *comboFoodItem;
} MAINFOOD, *LIST;

int itemCount = 0;

void showMenu(LIST menu);
void addMainItem(LIST *menu);
void takeOrder(float *totalBalance, LIST menu);
float getPrice(int choice, LIST menu);
void getRemBal(float *totalBalance, float cashPaid);

int main(){

    LIST menu = NULL;
    MAINFOOD newMain;
    int choice, maxLogin = 0;
    float totalBal = 0;
    while(choice != 3)
    {
        printf("Welcome to McDonald's!\n");
        printf("Are you a customer or a manager?\n");
        printf("1. Order\n");
        printf("2. Manager's Access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while(choice > 2 || choice < 1)
        {
            printf("You have entered an invalid choice. Please try again.\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            maxLogin++;
            if(maxLogin == 3)
            {
                printf("You have entered the wrong choice too many times. Bye!");
                exit(0);
            }
        }
        if(choice == 1)
        {
            showMenu(menu);
            takeOrder(&totalBal, menu);
            printf("Your total balance is: %.2f\n", totalBal);
        }
        else if(choice == 2)
            addMainItem(&menu);
    }
    return 0;
}

void getRemBal(float *totalBalance, float cashPaid){

    
}

void showMenu(LIST menu){

    printf("Welcome to McDonald's!\n");
    printf("We hope you're having a great day.\n");
    printf("What would you like to order?\n");
    if(menu == NULL)
        printf("Sorry our machines are broken. Try again next time. Bye!");
    else
    {
        int i = 1;
        for(; menu != NULL; menu = menu->next, i++)
            printf("%d. %-15s%.2f\n", i, menu->name, menu->price);
        printf("%d. STOP ORDERING\n", i);
    }
}

void addMainItem(LIST *menu){

    char foodName[15];
    float price;
    int numItems, i;
    printf("Good day, manager!\n");
    printf("How many items would you like to add? ");
    scanf("%d", &numItems);
    for(i = 1; i <= numItems; i++)
    {
        MAINFOOD *newMain = malloc(sizeof(MAINFOOD));
        printf("Name of the new item #%d: ", i);
        scanf(" %[^\n]s", foodName);
        printf("Price of %s: ", foodName);
        scanf("%f", &price);
        strcpy(newMain->name, foodName);
        newMain->price = price;
        newMain->next = *menu;
        *menu = newMain;
        itemCount++;
    }
}

void takeOrder(float *totalBal, LIST menu){
    int choice, exitCode = itemCount+1;
    float bal;
    while(choice != exitCode)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice != exitCode)
            (*totalBal)+=getPrice(choice, menu);
    }
}

float getPrice(int choice, LIST menu){

    MAINFOOD *currItem = menu;
    int currPos = 1;
    while(currPos != choice)
    {
        currItem = currItem->next;
        currPos++;
    }
    printf("Added %s to order!\n\n", currItem->name);
    return currItem->price;
}