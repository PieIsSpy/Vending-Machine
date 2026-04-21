// Library inclusions
#include <stdio.h>
#include <string.h>
#include "ANSI-color-codes.h"

// Display functions
void displayDivider(); // Status: Done
void displayDenominations(int *, double); // Status: Done
void displayItems(double *, int *, int *, double, double, int); // Status: Done
void displayOrders(int *, double *, double *, double); // Status: Done
void displayChange(int *, int *, double *, double *); // Status: Done
void displayWithdrawal(int *, int *); // Status: Done
void giveCashOutDenom(int *, int *); // Status: Done

// Computational Functions
void getDenomination(int , int , int *, double *); // Status: Done
int checkOrder(int *); // Status: Done
double countMoney(int *); // Status: Done
void giveDenominations(double, int *, int *); // Status: Done

// Feature functions
void acceptDenominations(int *, double *); // Status: Done
void getOrder(int *, int *, double *, int *, int *, double, double *); // Status: Done
void vendingFeatures(int *, double *, int *); // Status: Done

void maintenanceFeatures(int *, double *, int *); // Status: Done
void inventoryFeatures(int *, double *); // Status: Done
void changePrice(int *, double *); // Status: Done
void restockInventory(int *, double *); // Status: Done

void cashRegisterFeatures(int* ); // Status: Done
void cashOut(int *); // Status: Done
void denominationCashOut(int *); // Status: Done
void valueCashOut(int *); // Status: Done