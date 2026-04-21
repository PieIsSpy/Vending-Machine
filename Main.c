/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole
or otherwise plagiarized the work of other students and/or persons.
***************************************************************************/

/*
Description: This program serves the customer a silog meal with the option to add as many add-ons as they like in one serving.

Last modified: 11/23/2024

Version: 1.1.1

Acknowledgements: 
	Borrowed Libraries:
		ASCII Colors:
			https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a

Changelogs:
    - Bugfix regarding giveDenominations() having floating point errors
    - Changed most floats into doubles
    - Pruned unused variables
    - Removed debug printfs in giveDenominations()
*/

#include "Functions.c"

int
main()
{
    // Machine Variables
    int aDenomCashier[] = {0, 20, 20, 20, 10, 10, 10, 5, 4, 5, 0, 0};
    double aItemPrices[] = {0, 9.50, 20.75, 12.00, 35.00, 22.50, 18.00, 15.00, 8.00};
    int aStock[9];

    // Standalone variables
    int i, nPassword, nMenu;

    // Iteration for initializing starting values
    for (i = 1; i <= 9; i++)
        aStock[i] = 20;

    // Main program flow
    do
    {
        // Display Menu
        displayDivider();
        printf("1. Silog Vending Feature\n");
        printf("2. Maintenance Feature\n");
        printf("3. Shutdown Machine\n");
        printf("Please input a feature: ");
        scanf("%d", &nMenu);

        if (nMenu == 1)
            vendingFeatures(aStock, aItemPrices, aDenomCashier);

        // maintenanceFeatures()
        else if (nMenu == 2)
        {
            printf("Please enter the password: ");
            scanf("%d", &nPassword);

            if (nPassword != 123456)
                printf(RED "ERROR: Incorrect password\n\n" reset);
            else
            {
                printf(GRN "Welcome, User!\n\n" reset);
                maintenanceFeatures(aStock, aItemPrices, aDenomCashier);
            }
        }

        // Shutdown Machine
        else if (nMenu == 3)
        {
            printf("Please enter the password: ");
            scanf("%d", &nPassword);

            if (nPassword != 123456)
                printf(RED "ERROR: Incorrect password\n\n" reset);
            else
                printf(GRN "Shutting down...\n\n" reset);
        }

        else
            printf(RED "ERROR: Invalid Input\n\n" reset);

    } while (nPassword != 123456 || nMenu != 3);

    return 0;
}