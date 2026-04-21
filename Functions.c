/*
	Functions.c table of content:
	
	1. Display Functions
		- For displaying purposes only
    2. Computational Functions
		- For changing values of variables according to pre-conditions
	3. Feature Functions
		- Groups the functions and flow of a feature to keep the Main.c clean
*/

#include "Library.h"



/*
    Function type: Display Function
    displayDivider() displays a divider between operations
*/
void
displayDivider()
{
    int i;

    for (i = 1; i <= 125; i++)
        printf("=");

    printf("\n");
}



/*
	Function type: Display Function
	displayDenominations() displays how many denominations are currently inputed by the user
    
	@param aDenomUser - refers to the group of denominations currently present
	@param dMoney - refers to the current total money of the user
*/
void
displayDenominations(int aDenomUser[], double dMoney)
{
    // Counter Variables
    int i;

    // Denomination values (0 is a buffer)
    int aDenominations[] = {0, 5, 10, 25, 1, 5, 10, 20, 50, 100, 200, 500};

    // String variable
    char strValue[6] = "";

    displayDivider();

    // List denominations
    for (i = 1; i <= 11; i++)
    {
        if (i < 4)
            strcpy(strValue, "Cents");
        else if (i == 4)
            strcpy(strValue, "Peso");
        else
            strcpy(strValue, "Pesos");
        
        printf("%d.] %d %s: %5d\t\t\t", i, aDenominations[i], strValue, aDenomUser[i]);

        if (i % 3 == 0)
            printf("\n\n");
    }
    printf("\n\n");
    printf("Current money: %.2lf Pesos\n", dMoney);
}



/*
	Function type: Display Function
	displayItems() shows the available items, its price and current stock when called in vendingFeatures()

	@param aItemPrices - group of variables that stores the current price of items
	@param aStock - group of variables that stores the current available stock of items
	@param aOrder - group of variables that stores how many orders the user inputted
    @param dMoney - how much money does the user have
    @param dTotalPrice - how much money does the whole order cost
    @param nMode - toggles if order will 

    Pre-condition: There are no invalid values inside the arrays of the parameter
*/
void
displayItems(double aItemPrices[], int aStock[], int aOrder[], double dMoney, double dTotalPrice, int nMode)
{
    int nLine, nItemLine, nStockLine, nOrderLine, nItemCount = 1, nStockCount = 1, nOrderCount = 1;

    // String variable ("" is a buffer)
    char aItems[9][11] = {"", "Hotdog", "Longganisa", "Bacon", "Sausage", "Tapa", "Tocino", "Rice", "Egg"};
    
    displayDivider();

    // List all from left to right, top to bottom
    for (nLine = 1; nLine <= 3; nLine++)
    {
        // List all items per line
        for (nItemLine = 1; nItemLine <= 3; nItemLine++)
        {
            if (nItemCount <= 8)
            {
                printf("%d. ] %-10s: %6.2f Pesos", nItemCount, aItems[nItemCount], aItemPrices[nItemCount]);
                printf("\t\t\t");
                nItemCount++;
            }
        }
        printf("\n");

        // list all stocks per line
        for (nStockLine = 1; nStockLine <= 3; nStockLine++)
        {
            if (nStockCount <= 8)
            {
                printf("Stock: %d", aStock[nStockCount]);
                printf("\t\t\t\t\t");
                nStockCount++;
            }
        }
        printf("\n");

        // list all orders per line (if called from vending feature)
        if (nMode == 1)
        {
            for (nOrderLine = 1; nOrderLine <= 3; nOrderLine++)
            {
                if (nOrderCount <= 8)
                {
                    printf("Order: %d", aOrder[nOrderCount]);
                    printf("\t\t\t\t\t");
                    nOrderCount++;
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    if (nMode == 1)
    {
        displayDivider();
        printf("Current Money: %.2lf Pesos\n", dMoney);
        printf("Total Price: %.2lf Pesos\n", dTotalPrice);
    }
}



/*
	Function type: Display Function
	displayDivider() displays the user's orders

	@param aOrder - group of variables that stores how many orders the user inputted
    @param aItemPrices - group of variables that stores the current price of items
    @param dTotalPrice - how much money does the whole order cost 
    @param dMoney - how much money does the user have

    Pre-condition: aOrder's items are greater than 0 or 1(For rice and egg)
*/
void
displayOrders(int aOrder[], double aItemPrices[], double *dTotalPrice, double dMoney)
{
    // variable declarations
    int i, a = 1;
    char aItems[9][11] = {"", "Hotdog", "Longganisa", "Bacon", "Sausage", "Tapa", "Tocino", "Rice", "Egg"};

    for (i = 1; i < 9; i++)
    {
        if (aOrder[i] > 0)
        {
            printf("%d.] %s: %d orders\n", a, aItems[i], aOrder[i]);
            printf("Price: %.2lf\n\n", aItemPrices[i] * aOrder[i]);
            a++;
        }
    }
    printf("Current Money: %.2lf Pesos\n", dMoney);
    printf("Total Price: %.2lf Pesos\n\n", *dTotalPrice);
}



/*
    Function type: Computational Function

    getDenomination() gets the number of denominations that the user inputted and multiplies it to its respective value, after which
    is added to the current money of the user

    @param nSelection - the selected denomination of the user
    @param nMultiplier - how many denominations are there
    @param aDenomUser - group of denominations currently present
    @param dMoney - How much money does the user intend to input

    Pre-condition: The given nSelection & nMultiplier is a non-negative int
*/
void
getDenomination(int nSelection, int nMultiplier, int aDenomUser[], double *dMoney) //check1
{
    // variable declaration (0.0 in aValue is a buffer)
    double aValue[] = {0.0, 0.05, 0.10, 0.25, 1.00, 5.00, 10.00, 20.00, 50.00, 100.00, 200.00, 500.00};
    int i;
    
    aDenomUser[nSelection] += nMultiplier;
    
    // set money to 0 for recount (it will add to the pre-existing value of dMoney if not done)
    *dMoney = 0;
    
    // recount everything
    for (i = 1; i < 12; i++)
        *dMoney += aValue[i] * aDenomUser[i];
}



/*
    Function type: Computational Function

    checkOrder() checks if the user has ordered atleast one item other than the given rice and egg

    @param aOrder - group of variables that contains all ordered items of the user

    @return returns 0 if the user did not order other items than the given rice and egg, 1 otherwise
*/
int
checkOrder(int aOrder[])
{
    // var declaration
    int i, nChecker;

    // checks if there is atleast one order other than the default rice and egg
    for (i = 1; i <= 8; i++)
    {
        // check until there is an order
        if ((aOrder[i] > 0 && i < 7) || (aOrder[i] > 1 && i > 6))
            nChecker = 1;
    }

    // decision maker
    if (nChecker == 1) // if they did order
        return 1;
    else // if not
        return 0;
}



/*
    Function type: Computational Function

    countMoney() counts the current available denominations that is inputted by the parameter

    @param aDenominations - refers to the group of variables that stores how many denominations are presented in the functions

    @return returns the counted money from the given denominations

    Pre-condition: The given variables of aDenominations are non-negative ints

    @return dMoney returns the computed money based on the given denominations
*/
double
countMoney(int aDenominations[])
{
    // Value array (starting 0 is a buffer)
    double aValue[] = {0.0, 0.05, 0.10, 0.25, 1.00, 5.00, 10.00, 20.00, 50.00, 100.00, 200.00, 500.00};

    // Counter
    int i;

    // money variable
    double dMoney = 0;

    for (i = 1; i <= 11; i++)
        dMoney += aValue[i] * aDenominations[i];

    return dMoney;
}



/*
    Function type: Display Function

    displayChange() displays the denominations of the change

    Functions used:
    giveDenominations()

    @param aDenomUser - group of denominations currently present from the user
    @param aDenomCashier - group of denominations currently present in the machine
    @param dMoney - how much money does the user have
    @param dTotalPrice - how much money does the whole order cost

    Pre-condition: The given variables of aDenomUser and aDenomCashier are non-negative ints and dMoney >= dTotalPrice
*/
void
displayChange(int aDenomUser[], int aDenomCashier[], double *dMoney, double *dTotalPrice)
{
	// variable declarations
    int aDenominations[] = {0, 5, 10, 25, 1, 5, 10, 20, 50, 100, 200, 500};
    double fChange;
    int i, j = 1;
    char strValue[6] = "";
	
	fChange = *dMoney - *dTotalPrice;
	giveDenominations(fChange, aDenomUser, aDenomCashier);
	
    printf("Denominations given:\n");

    // display denominations
    for (i = 1; i <= 11; i++)
    {
        if (i < 4)
            strcpy(strValue, "Cents");
        else if (i == 4)
            strcpy(strValue, "Peso");
        else
            strcpy(strValue, "Pesos");

        if (aDenomUser[i] > 0)
        {
            printf("%d.] %d %s: %d\n", j, aDenominations[i], strValue, aDenomUser[i]);
            j++;
        }
    }
}



/*
    Function type: Display Function

    displayWithdrawal() displays the current denominations of the machine and its withdrawed money

    @param aDenomCashier - current denominations inside the machine
    @param aDenomUser - denominations that the owner would like to withdraw

    Pre-conditions: Ints of arrays are non-negative

    Note: this function is similar to displayDenominations(), but cannot be reused due to the function being catered towards vendingFeatures() more
*/
void 
displayWithdrawal(int aDenomCashier[], int aDenomUser[])
{
    int nLine, nRow1, nRow2, nDenom = 1, nWidthdraw = 1;

    // Denomination values (0 is a buffer)
    int aDenominations[] = {0, 5, 10, 25, 1, 5, 10, 20, 50, 100, 200, 500};

    // string variable
    char strValue[6] = "";

    displayDivider();

    // list denominations
    for (nLine = 1; nLine <= 4; nLine++)
    {
        // display denominations
        for (nRow1 = 1; nRow1 <= 3; nRow1++)
        {
            if (nDenom <= 11)
            {
                if (nDenom < 4)
                    strcpy(strValue, "Cents");
                else if (nDenom == 4)
                    strcpy(strValue, "Peso");
                else
                    strcpy(strValue, "Pesos");

                printf("%d.] %d %-10s: %2d\t\t\t", nDenom, aDenominations[nDenom], strValue, aDenomCashier[nDenom]);

                nDenom++;
            }
        }
        printf("\n");

        // display how many widthdrawals
        for (nRow2 = 1; nRow2 <= 3; nRow2++)
        {
            if (nWidthdraw <= 11)
            {
                printf("Withdraw: %d\t\t\t\t", aDenomUser[nWidthdraw]);
                nWidthdraw++;
            }
        }
        printf("\n\n");
    }
    printf("Current cash out: %.2lf\n\n", countMoney(aDenomUser));
}



/*
    Function type: Display Function
    
    giveCashOutDenom() displays the denominations the owner wants to withdraw, and subtracts it to the current denominations in the machine
    
    @param aDenomCashier - current denominations of the machine
    @param aDenomUser - denomination of the owner that are withdrawed

    Pre-conditions: both arrays contains non-negative ints

    Note: this function is similar to displayChange(), but cannot be reused due to the function being catered towards vendingFeatures() more
*/
void
giveCashOutDenom(int aDenomCashier[], int aDenomUser[])
{
    int i, j = 1;

    int aDenominations[] = {0, 5, 10, 25, 1, 5, 10, 20, 50, 100, 200, 500};
    char strValue[6] = "";

    printf("Withdrawed denominations:\n\n");

    // display denominations
    for (i = 1; i <= 11; i++)
    {
        if (i < 4)
            strcpy(strValue, "Cents");
        else if (i == 4)
            strcpy(strValue, "Peso");
        else
            strcpy(strValue, "Pesos");

        if (aDenomUser[i] > 0)
        {
            printf("%d.] %d %s: %d\n", j, aDenominations[i], strValue, aDenomUser[i]);
            j++;
        }
    }
    printf("\n");

    printf("Withdrawed cash: %.2lf\n", countMoney(aDenomUser));

    for (i = 1; i <= 11; i++)
        aDenomCashier[i] -= aDenomUser[i];
}



/*
    Function type: Computational Function

    giveDenominations() gives the user the smallest amounts of denomination of a given money value

    @param dMoney - current money of user
    @param aDenomUser - current denominations of the user
    @param aDenomCashier -  current denominations of the machine

    Pre-condition: dMoney is non-negative and is greater than 0.05; arrays are non negative integers
*/
void
giveDenominations(double dMoney, int aDenomUser[], int aDenomCashier[])
{
	// var declaration
	int aPesos[] = {1, 5, 10, 20, 50, 100, 200, 500};
    int aCents[] = {5, 10, 25};
    int i, j = 11, nWhole, nDecimal, nMoney;

    // turn dMoney into int
    nMoney = dMoney * 100;

    // get whole number and decimals as integers to prevent floating point errors
    nWhole = nMoney / 100;
    nDecimal = nMoney % 100;

    // give denominations first
    for (i = 1; i <= 11; i++)
    {
        aDenomCashier[i] += aDenomUser[i];
        aDenomUser[i] = 0;
    }

    // check for whole number pesos
    for (i = 7; i >= 0; i--)
    {
        while (nWhole >= aPesos[i] && aDenomCashier[j] > 0)
        {
            nWhole -= aPesos[i];
            aDenomUser[j]++;
            aDenomCashier[j]--;
        }
        j--;
    }

    for (i = 2; i >= 0; i--)
    {
        while (nDecimal >= aCents[i] && aDenomCashier[j] > 0)
        {
            nDecimal -= aCents[i];
            aDenomUser[j]++;
            aDenomCashier[j]--;
        }
        j--;
    }
}



/*
	Function type: Feature Function
	acceptDenominations() accepts denominations from the user

	Functions used:
	displayDenominations()
	getDenomination()

    @param aDenomUser - group of denominations currently present
    @param dMoney - How much money does the user intend to input

    Pre-condition: aDenomUser's ints are non-negative ints and dMoney is a non-negative double
*/
void
acceptDenominations(int aDenomUser[], double *dMoney)
{
    // variable declaration
    int nSelection, nMultiplier;

    do
    {
        displayDenominations(aDenomUser, *dMoney);
        printf("Type 0 if done\n\n");
        printf("Please enter a denomination: ");
		scanf("%d", &nSelection);

        if (nSelection > 0 && nSelection < 12)
        {
            printf("Please enter the amount of the denomination: ");
            scanf("%d", &nMultiplier);

            if (nMultiplier > -1)
                getDenomination(nSelection, nMultiplier, aDenomUser, dMoney);
            else if (nMultiplier != 0)
                printf(RED "ERROR: Invalid Input\n\n" reset);
        }
        else if (nSelection != 0)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nSelection != 0);
}



/*
    Function type: Feature Function

    getOrder() gets orders from the user, and asks for more money if the current user money is not enough

    Functions used:
    displayItems()
    acceptDenominations()
    checkOrder()

    @param aOrder - group of variables that stores how many orders the user inputted
    @param aStock - group of variables that stores the current available stock of items
    @param aItemPrices - group of variables that stores the current price of items
	@param aDenomUser - group of denominations currently present
    @param aDenomCashier - group of denominations currently present in the machine
    @param dMoney - how much money does the user have
    @param dTotalPrice - how much money does the whole order cost 

    Pre-condition: All parameters are non-negative variables.
*/
void
getOrder(int aOrder[], int aStock[], double aItemPrices[], int aDenomUser[], int aDenomCashier[], double dMoney, double *dTotalPrice)
{
    int nSelection, nDecision, nCancel, nConfirm = -1, i;

    do
    {
        displayItems(aItemPrices, aStock, aOrder, dMoney, *dTotalPrice, 1);
        printf("Type 0 if done\n\n");
        printf("Please enter an add-on you would like to choose: ");
        scanf("%d", &nSelection);

        // if within range
        if (nSelection > 0 && nSelection < 9)
        {
            aOrder[nSelection]++;
            *dTotalPrice += aItemPrices[nSelection];

            // if out of stock
            if (aOrder[nSelection] > aStock[nSelection])
            {
                printf(RED "ERROR: Out of Stock! Sorry!\n" reset);
                aOrder[nSelection]--;
                *dTotalPrice -= aItemPrices[nSelection];
            }

            // if not enough money
            else if (dMoney < *dTotalPrice)
            {
                do
                {
                    printf(RED "The given money is insufficient. " reset);
                    printf("Would you like to add more money to the machine?\n");
                    printf("Press 1 to add more denominations\n");
                    printf("Press 0 to cancel the last item\n");
                    scanf("%d", &nDecision);
                    
                    if (nDecision == 1)
                        acceptDenominations(aDenomUser, &dMoney);
                    else if (nDecision == 0)
                    {
                        *dTotalPrice -= aItemPrices[nSelection];
                        aOrder[nSelection]--;
                    }
                    else
                        printf(RED "ERROR: Invalid Input\n\n" reset);
                    
                } while (dMoney < *dTotalPrice && nDecision != 0);
            }
        }

        // if user did not order anything
        else if (checkOrder(aOrder) != 1 && nSelection == 0)
        {
            do
            {
                printf("No orders detected other than the basic silog\n");
                printf("Would you like to cancel the order?\n");
                printf("Press 1 to continue the order\n");
                printf("Press 0 to cancel the order\n");
                scanf("%d", &nCancel);

                if (nCancel == 0)
                {
					printf("Order canceled.\n");
					
					for (i = 1; i < 9; i++)
                        aOrder[0] = 0;

                    *dTotalPrice = 0;
					
					displayChange(aDenomUser, aDenomCashier, &dMoney, dTotalPrice);
				}

                else if (nCancel != 1)
                    printf(RED "ERROR: Invalid Input\n\n" reset);
            } while (nCancel != 0 && nCancel != 1);
        }

        // if user has ordered already
        else if (checkOrder(aOrder) == 1 && nSelection == 0)
        {
            do
            {
                displayDivider();
                printf("Current orders:\n");
                displayOrders(aOrder, aItemPrices, dTotalPrice, dMoney);
                printf("Confirm order?\n");
                printf("Press 0 to cancel the order\n");
                printf("Press 1 to confirm the order\n");
                printf("Press 2 to continue ordering\n");
                scanf("%d", &nConfirm);

                if (nConfirm == 0)
                {
                    displayDivider();
                    printf("\nOrder canceled.\n\n");
                    for (i = 1; i < 9; i++)
                        aOrder[0] = 0;

                    *dTotalPrice = 0;

                    displayChange(aDenomUser, aDenomCashier, &dMoney, dTotalPrice);
                }
                else if (nConfirm == 1)
                {
                    displayDivider();

                    printf("\nRecipt:\n\n");

                    displayOrders(aOrder, aItemPrices, dTotalPrice, dMoney);

                    printf("Money: %.2lf\n", dMoney);
                    printf("Price: %.2lf\n", *dTotalPrice);
                    printf("Change: %.2lf\n\n", dMoney - *dTotalPrice);

                    displayChange(aDenomUser, aDenomCashier, &dMoney, dTotalPrice);

                    printf("\nGiven change: %.2lf\n", countMoney(aDenomUser));

                    printf(GRN "\nPlease get your silog in the tray bin\n" reset);
                    printf("Thank you for ordering!\n");
					
					for (i = 1; i <= 8; i++)
						aStock[i] -= aOrder[i];
                }
                else if (nConfirm != 2)
                    printf(RED "ERROR: Invalid Input\n\n" reset);
            } while (nConfirm != 2 && nConfirm != 1 && nConfirm != 0);
        }
        else if (nSelection != 0)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nConfirm != 1 && nConfirm != 0 && nCancel != 0);
}



/*
    Function type: Feature function

    vendingFeatures() compiles all functions that would be used to complete 1 order

    Functions used:
    displayItems()
    acceptDenominations()
    getOrder()

    @param aStock - how many items are currently in stock inside the machine
    @param aItemPrices - how much does the items cost
    @param aDenomCashier - current available denominations inside the machine

    Pre-condition: ALL parameters are non-negative
*/
void
vendingFeatures(int aStock[], double aItemPrices[], int aDenomCashier[])
{
    // array declarations
    int aDenomUser[12];
    int aOrder[9];

    // variable declarations
    int nDecision, i;
    double dMoney = 0, dTotalPrice = 0;

    // array initializer
    for (i = 1; i <= 11; i++)
        aDenomUser[i] = 0;

    for (i = 1; i <= 8; i++)
        aOrder[i] = 0;

    // atleast one rice and one egg
    aOrder[7] = 1;
    dTotalPrice += aItemPrices[7];

    aOrder[8] = 1;
    dTotalPrice += aItemPrices[8];

    displayItems(aItemPrices, aStock, aOrder, dMoney, dTotalPrice, 0);
    // accept starting money
    do
    {
        acceptDenominations(aDenomUser, &dMoney);

        // if user did not order anything
        if (dMoney == 0)
        {
            do 
            {
                printf("No denominations placed, would you like to cancel the order?\n");
                printf("Press 1 to continue the order\n");
                printf("Press 0 to cancel the order\n");
                scanf("%d", &nDecision);

                if (nDecision == 0)
                    printf("Order canceled.\n");
                else if (nDecision != 1)
                    printf(RED "ERROR: Invalid Input\n\n" reset);
            } while (nDecision != 0 && nDecision != 1);
        }
    } while (nDecision != 0 && dMoney <= 0);

    // Main vending loop
    if (dMoney > 0)
        getOrder(aOrder, aStock, aItemPrices, aDenomUser, aDenomCashier, dMoney, &dTotalPrice);
}



/*
    Function type: Feature Function

    maintenanceFeatures() lets the owner access other feature functions such as inventory and cash register

    @param aStock - how many items are in stock
    @param aItemPrices - how much do the items cost
    @param aDenomCashier - how many denominations are in the machine
	
	Functions used:
	inventoryFeatures()
	cashRegisterFeatures()
	displayDivider()

    Pre-conditions: values of arrays are non-negative, aItemPrices are positive doubles except for the buffer value of index 0
*/
void
maintenanceFeatures(int aStock[], double aItemPrices[], int aDenomCashier[])
{
    int nMenu;

    do
    {
        displayDivider();

        printf("1. Inventory Features\n");
        printf("2. Cash Register Features\n");
        printf("3. Main Menu\n");
        
        printf("Please input a feature: ");
        scanf("%d", &nMenu);

        if (nMenu == 1)
            inventoryFeatures(aStock, aItemPrices);
        else if (nMenu == 2)
            cashRegisterFeatures(aDenomCashier);
        else if (nMenu != 3)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nMenu != 3);
}



/* 
	Function type: Feature functions
	
	inventoryFeatures() lets the owner restock the items and modify its prices
	
	@param aStock - how many items are in stock
    @param aItemPrices - how much do the items cost
	
	Functions used:
	displayItems()
	changePrice()
	restockInventory()
	displayDivider()

    Pre-conditions: aStock values are non-negative ints and aItemPrices are positive doubles
*/
void
inventoryFeatures(int aStock[], double aItemPrices[])
{
    int nMenu, i;

    // buffer variables
    int aOrder[9];
    double dMoney = 0, dTotalPrice = 0;
	
	// prevent garbage values
	for (i = 1; i <= 8; i++)
		aOrder[i] = 0;

    do
    {
        displayDivider();

        printf("1. View Inventory\n");
        printf("2. Modify Price\n");
        printf("3. Restock Inventory\n");
        printf("4. Back to Maintenance Features\n");
        
        printf("Please input a feature: ");
        scanf("%d", &nMenu);

        if (nMenu == 1)
            displayItems(aItemPrices, aStock, aOrder, dMoney, dTotalPrice, 0);
        else if (nMenu == 2)
            changePrice(aStock, aItemPrices);
        else if (nMenu == 3)
            restockInventory(aStock, aItemPrices);
        else if (nMenu != 4)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nMenu != 4);
}



/*
	Function type: Feature functions
	
	changePrice() overrides the current prices that are assigned to the items
	
	@param aStock - how many items are in stock
    @param aItemPrices - how much do the items cost

    Pre-conditions: aStock values are non-negative ints and aItemPrices are positive doubles
*/
void
changePrice(int aStock[], double aItemPrices[])
{
    double aDefaultPrices[] = {0, 9.50, 20.75, 12.00, 35.00, 22.50, 18.00, 15.00, 8.00};

    int nSelection, i;
    double dMoney;

    // buffer variables
    double buffer1 = 0, buffer2 = 0;
    int aOrder[9];
	
	// prevent garbage values
	for (i = 1; i <= 8; i++)
		aOrder[i] = 0;
    
    do
    {
        displayItems(aItemPrices, aStock, aOrder, buffer1, buffer2, 0);
        printf("Type 0 if done\n");
        printf("Type -1 to reset to default prices\n\n");
        printf("Please select the item to change price: ");
        scanf("%d", &nSelection);
        
        // if within range
        if (nSelection >= 1 && nSelection <= 8)
        {
			printf("Setting the price to 0 will cancel the price change\n");
            printf("New Price: ");
            scanf("%lf", &dMoney);

            // check if its non negative
            if (dMoney > 0)
                aItemPrices[nSelection] = dMoney;
			else if (dMoney == 0)
				printf("Price was set to 0. Price change canceled.\n");
            else
                printf(RED "ERROR: Invalid Input\n\n" reset);
        }

        // reset prices
        else if (nSelection == -1)
        {
            for (i = 1; i <= 8; i++)
                aItemPrices[i] = aDefaultPrices[i];

            printf(GRN "Item prices resetted\n" reset);
        }

        // invalid input
        else if (nSelection != 0)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while(nSelection != 0);
}



/*
	Function type: Feature functions
	
	restockInventory() adds stocks to the current number of items
	
	@param aStock - how many items are in stock
    @param aItemPrices - how much do the items cost

    Pre-conditions: aStock values are non-negative ints and aItemPrices are positive doubles
*/
void
restockInventory(int aStock[], double aItemPrices[])
{
    int nSelection, nRestock;

    // buffer variables
    double buffer1 = 0, buffer2 = 0;
    int aOrder[9], i;
	
	// prevent garbage values
	for (i = 1; i <= 8; i++)
		aOrder[i] = 0;

    do
    {
        displayItems(aItemPrices, aStock, aOrder, buffer1, buffer2, 0);
        printf("Type 0 if done\n\n");
        printf("Please select the item to restock: ");
        scanf("%d", &nSelection);
        
        if (nSelection >= 1 && nSelection <= 8)
        {
            printf("How many servings are restocked: ");
            scanf("%d", &nRestock);

            if (nRestock >= 0)
                aStock[nSelection] += nRestock;
            else
                printf(RED "ERROR: Invalid Input\n\n" reset);
        }
        else if (nSelection != 0)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while(nSelection != 0);
}



/*
	Function type: Feature functions
	
	cashRegisterFeatures() lets the owner restock the machine's denomination or cash out denominations
	
	@param aDenomCashier - how many denominations are in the machine
	
	Functions used:
	displayDenominations()
	acceptDenominations()
	cashOut()
	displayDivider()

    Pre-conditions: Ints of aDenomCashier are non-negative
*/
void
cashRegisterFeatures(int aDenomCashier[])
{
    int nMenu;
    double dMoney;

    do
    {
        dMoney = countMoney(aDenomCashier);
        displayDivider();
        printf("1. View Cash Register\n");
        printf("2. Restock Cash Register\n");
        printf("3. Cash Out\n");
        printf("4. Back to Maintenance Features\n");

        printf("Please input a feature: ");
        scanf("%d", &nMenu);

        if (nMenu == 1)
            displayDenominations(aDenomCashier, countMoney(aDenomCashier));
        else if (nMenu == 2)
            acceptDenominations(aDenomCashier, &dMoney);
        else if (nMenu == 3)
            cashOut(aDenomCashier);
        else if (nMenu != 4)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nMenu != 4);
}



/*
	Function type: Feature function
	
	cashOut() lets the owner withdraw the denominations in the machine
	
	@param aDenomCashier - how many denominations are in the machine
	
	Functions used:
	displayDenominations()
	acceptDenominations()
	cashOut()
	displayDivider()

    Pre-conditions: Ints of aDenomCashier are non-negative
*/
void
cashOut(int aDenomCashier[])
{
    int nMode;

    displayDivider();
    do
    {
        printf("1. Cash out by Denominations\n");
        printf("2. Cash out by Quantity\n");
        printf("3. Cancel\n");
        printf("Please pick the mode of withdrawal: ");
        scanf("%d", &nMode);
        if (nMode == 1)
            denominationCashOut(aDenomCashier);
        else if (nMode == 2)
            valueCashOut(aDenomCashier);
        else if (nMode != 3)
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nMode != 1 && nMode != 2 && nMode != 3);
}



/*
    Function Type: Feature Function

    denominationCashOut() asks the owner which denominations would they like to withdraw, provided that it has enough denominations

    @param aDenomCashier - current denominations inside the machine

    Pre-condition: aDenomCashier values are non-negative ints

    Note: this function is similar to acceptDenominations(), but cannot be reused due to the function being catered towards vendingFeatures() more
*/
void
denominationCashOut(int aDenomCashier[])
{
    int i, nSelection = 1, nMultiplier;
    int aDenomUser[12];

    for (i = 0; i <= 11; i++)
        aDenomUser[i] = 0;

    do
    {
        displayWithdrawal(aDenomCashier, aDenomUser);
        printf("Type 0 if done\n");
        printf("Type -1 to cancel\n\n");
        printf("Please enter a denomination: ");
		scanf("%d", &nSelection);

        if (nSelection >= 1 && nSelection <= 11)
        {
            printf("Please enter the amount of the denomination: ");
            scanf("%d", &nMultiplier);

            // check if non-negative
            if (nMultiplier >= 0)
            {
                aDenomUser[nSelection] += nMultiplier;
                
                // check if stock is enough
                if (aDenomUser[nSelection] > aDenomCashier[nSelection])
                {
                    printf(RED "ERROR: Not enough denominations\n\n" reset);
                    aDenomUser[nSelection] -= nMultiplier;
                }
            }
            else
                printf(RED "ERROR: Invalid Input\n\n" reset);
        }
        else if (nSelection == 0)
            if (countMoney(aDenomUser) > 0)
                giveCashOutDenom(aDenomCashier, aDenomUser);
            else
                printf("No denominations inputted. Cash out canceled.\n");
        else if (nSelection == -1)
            printf("Cash out canceled.\n");
        else
            printf(RED "ERROR: Invalid Input\n\n" reset);
    } while (nSelection != 0 && nSelection != -1);
}



/*
	Function type: Feature functions
	
	valueCashOut() lets the owner withdraw the denominations in the machine
	
	@param aDenomCashier - how many denominations are in the machine
	
	Functions used:
	displayDenominations()
	acceptDenominations()

    Pre-conditions: Ints of aDenomCashier are non-negative
*/
void
valueCashOut(int aDenomCashier[])
{
    // var declaration
    int aDenomCashOut[12];
    int i;
    double dMoney, dCount;

    // buffer varaibles (only sole purpose is to fill in required parameters)
    double fBuffer = 0;

    // initialize aDenomCashOut
    for (i = 1; i <= 11; i++)
        aDenomCashOut[i] = 0;

    // ask input
    displayDenominations(aDenomCashier, countMoney(aDenomCashier));
    printf("Type 0 if to cancel\n\n");
    printf("Please enter a value to withdraw: ");
    scanf("%lf", &dMoney);

    if (dMoney >= 0.05)
    {
        if (dMoney <= countMoney(aDenomCashier))
        {
            displayDivider();
            displayChange(aDenomCashOut, aDenomCashier, &dMoney, &fBuffer);
            dCount = countMoney(aDenomCashOut);
            printf("\nTotal withdrawal: %.2lf\n", dCount);
            if (dMoney != dCount)
            {
                printf(RED "Warning: " reset);
                printf("Unable to dispense exact stated amount.\n");
            }
        }
        else
            printf(RED "ERROR: Not enough money\n\n" reset);
    }
    else if (dMoney == 0)
        printf("Value of 0 was inputted. Cash out canceled.\n");
    else if (dMoney < 0)
        printf(RED "ERROR: Invalid Input\n\n" reset);
    else
        printf(RED "ERROR: Not dispensable by denominations\n\n" reset);
}