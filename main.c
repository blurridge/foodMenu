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
} COMBOFOOD, *SLIST;

typedef struct mainFoodItem{
    char name[15];
    float price;
    struct mainFoodItem *next;
    struct comboFoodItem *comboFoodItem;
} MAINFOOD, *LIST;

int itemCount = 0;

void showMenu(LIST menu);
void addMainItem(LIST *menu);
void addComboItem(LIST *menu);
void takeOrder(float *totalBalance, LIST menu);
float getPrice(int choice, LIST menu);
void getRemBal(float *totalBalance);

int main(){

    LIST menu = NULL;
    MAINFOOD newMain;
    int choice, maxLogin = 0;
    while(choice != 3)
    {
        float totalBal = 0;
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
            if(menu != NULL)
            {
                takeOrder(&totalBal, menu);
                printf("Your total balance is: %.2f\n", totalBal);
                getRemBal(&totalBal);
                if(totalBal < 0)
                    printf("Thank you for your order! Your change is %.2f. See you soon!\n", totalBal*-1);
                else
                    printf("Thank you for your order! See you soon! \n");
            }
        }
        else if(choice == 2)
            addMainItem(&menu);
    }
    return 0;
}

void getRemBal(float *totalBalance){

    float cashPaid, tries = 0;
    while(tries <= 3 && *totalBalance > 0)
    {
        if(tries < 1)
            printf("Enter cash paid: ");
        else
            printf("Your remaining balance is PHP %.2f.\n Enter cash paid: ", *totalBalance);
        scanf("%f", &cashPaid);
        *totalBalance-=cashPaid;
        tries++;
    }
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

    char foodName[15], choice;
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
    do{
        printf("Would you like to add combo items? (y/n)");
        scanf(" %c", &choice);
        if(choice == 'y')
            addComboItem(&menu);
    }while(choice == 'y');
}

void addComboItem(LIST *menu){

    char itemChoice[15];
    MAINFOOD *current_item = menu;
    int flag = 0;
    showMenu(menu);
    printf("To which item would you like to add a combo item to?");
    scanf(" %[^\n]s", itemChoice);
    while(flag == 0 && current_item != NULL)
    {
        if(strcmp(*current_item->name, itemChoice) == 0)
            flag = 1;
        else
            current_item = current_item->next;
    }
    if(flag == 1)
    {
        char foodName[15];
        float price;
        int numItems, i;
        printf("How many combo items would you like to add to %s?", current_item->name);
        scanf("%d", &numItems);
        
    }
    else
        printf("There is no item with that name. Returning to main menu!");
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