/*
Goals:
1. Create a linked list of possible combo food to be added to a meal along with a main food product.
2. Items can only be edited with successful password entry.
3. Should output order made, and total price of order.
4. Ask for cash paid, and check if money given is enough for a max of 3 tries.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct mainFoodItem{
    char name[30];
    float price;
    struct mainFoodItem *next, *prev;
} mainFood, *menu;

typedef struct comboFoodItem{
    char name[30];
    float price;
    struct comboFoodItem *next, *prev;
} comboFood;

void showMenu();

int main(){

    return 0;
}