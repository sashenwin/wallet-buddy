#include <stdio.h>
#include <conio.h>
#include <string.h>
#define max_yr 2021
#define min_yr 1900

char userfile[15];
char userfileIndex[20];

struct record
{
    int id;
    char type[10];
    char category[30];
    int day;
    int month;
    int year;
    double amount;
};

void menu1();
void menu2();
void addRecord();
void editRecord();
void deleteRecord();
void viewDailySummary();
void viewMonthlySummary();
void filterTransactions();
void filterbyCategory();
void filterbyAmount();
void personalSavings();
void displayAll();
void selectIncome(char category[30]);
void selectExpense(char category[30]);
void getDate(int * date, int * month, int *year);
void getMonth(int * month, int *year);
void printIncomeChart(double income [5]);
void printExpenseChart(double expense [7]);
double getTotal(double subtotal[], int arrSize);
double getTotalIncomes();
double getTotalExpenses();
void login();
void signUp();
void readIndex(int *recordID);
void saveIndex(int recordID);
int isLeap(int y);
int dateValid(int d, int m, int y);
int monthValid(int m, int y);
int yearValid(int y);
void getAmount(double * amount);


int main()
{
    menu1();
    return 0;
}

void menu1()
{
    int choice = 0;
    system("COLOR B0");

    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }
    printf("\n%c                 Welcome to Wallet Buddy!                %c\n",176, 176);
    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }

    printf("\n\n");

    printf("[1] - Existing User\n");
    printf("[2] - Register as a New User\n");
    printf("[3] - EXIT\n");

    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        login();
        break;
    case 2:
        signUp();
        break;
    case 3:
        printf("\nPress any key to exit...\n");
        getch();
        break;
    default:
        printf("\nInvalid Input!\n\n");
        printf("Press any key to retry...\n");
        getch();
        system("cls");
        menu1();
    }
}

void menu2()
{
    int choice = 0;
    double totIncome=0;
    double totExpense=0;
    double currentSavings = 0;
    do
    {
        totIncome = getTotalIncomes();
        totExpense = getTotalExpenses();
        currentSavings = (totIncome - totExpense);

        system("cls");
        for(int i=0 ; i<81 ; i++)
        {
            printf("%c", 176);
        }
        printf("\n%c                                   DASHBOARD                                   %c\n",176, 176);
        for(int i=0 ; i<81 ; i++)
        {
            printf("%c", 176);
        }
        printf("\n\n");

        system("COLOR F1");
        printf("[1] - Add Income/Expense");
        printf("                          ===============================\n");
        printf("[2] - Edit Income/Expense");
        printf("                         Total Incomes   : %10.2lfLKR\n", totIncome);
        printf("[3] - Delete Income/Expense");
        printf("                       Total Expenses  : %10.2lfLKR\n", totExpense);
        printf("[4] - View Daily Summary");
        printf("                          Current Savings : %10.2lfLKR\n", currentSavings);
        printf("[5] - View Monthly Summary");
        printf("                        ===============================\n");
        printf("[6] - Filter Transactions\n");
        printf("[7] - Personal Savings Overview\n");
        printf("[8] - View All Records\n");
        printf("[9] - Sign Out\n");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord();
            break;

        case 2:
            editRecord();
            break;

        case 3:
            deleteRecord();
            break;

        case 4:
            viewDailySummary();
            break;

        case 5:
            viewMonthlySummary();
            break;

        case 6:
            filterTransactions();
            break;

        case 7:
            personalSavings();
            break;

        case 8:
            displayAll();
            break;

        case 9:
            system("cls");
            menu1();
            getch();
            break;

        default:
            printf("\nInvalid Input!\n");
            printf("\nPress any key to go back to menu\n");
            getch();
            menu2();
            break;
        }

    }
    while (choice !=9);
}

void addRecord()
{
    system("COLOR 06");

    int recordID = 0;

    readIndex(&recordID);

    int choice;
    char tempCategory[30];


    system("cls");
    printf("                           <<<<Add Income/Expense>>>>\t\t\n\n\n");

    printf("[1] Income Record\n");
    printf("[2] Expense Record\n");

    printf("\n\nEnter your choice: ");

    scanf("%d", &choice);

    FILE *file;
    struct record t;
    switch (choice)
    {
    case 1:
        recordID++;

        file = fopen(userfile, "ab");
        t.id = recordID;
        strcpy(t.type,"Income");
        system("cls");
        printf("\t\t<<<<Add Income>>>>\t\t\n\n\n");

findDate1:
        getDate(&t.day, &t.month, &t.year);
        if (dateValid(t.day,t.month,t.year))
        {
            printf("\n");
            selectIncome(tempCategory);
            strcpy(t.category, tempCategory);
            printf("\n");
            getAmount(&t.amount);
            fwrite(&t,sizeof(t),1,file);
            fclose(file);
            printf("\nIncome record added successfully!");
        }
        else
        {
            printf("\nDate is not valid\n");
            printf("\nPress any key to re-enter a date...");
            getch();
            system ("cls");
            goto findDate1;
        }

        printf("\n\nPress any key to go back to menu...");
        saveIndex(recordID);
        getch();
        break;

    case 2:
        recordID++;

        file = fopen(userfile, "ab");
        t.id = recordID;
        strcpy(t.type,"Expense");
        system("cls");
        printf("\t\t<<<<Add Expense>>>>\t\t\n");

findDate2:
        printf("\n");
        getDate(&t.day, &t.month, &t.year);
        if (dateValid(t.day,t.month,t.year))
        {
            printf("\n");
            selectExpense(tempCategory);
            strcpy(t.category, tempCategory);
            printf("\n");
            getAmount(&t.amount);
            fwrite(&t,sizeof(t),1,file);
            fclose(file);
            printf("\nExpense record added successfully!");
        }
        else
        {
            printf("\nDate is not valid\n");
            printf("\nPress any key to re-enter a date...");
            getch();
            system ("cls");
            goto findDate2;
        }

        printf("\n\nPress any key to go back to menu...");
        saveIndex(recordID);
        getch();
        break;
    default:
        printf("\nInvalid Input!\n");
        printf("\nPress any key to retry...\n");
        getch();
        addRecord();
        break;
    }
}

void editRecord()
{
    system("COLOR 03");
    system("cls");

    int day = 0;
    int month = 0;
    int year = 0;
    int chooseid;
    int found = 0;
    int founD = 0;

    system("cls");

enterDate1:

    printf("                           <<<<Edit Income/Expense>>>>\t\t\n\n");

    getDate(&day, &month, &year);

    if (dateValid(day,month,year))
    {
        goto edit;

    }
    else
    {
        printf("Date is not valid\n");
        printf("\nPress any key to re-enter a date!");
        getch();
        system ("cls");
        goto enterDate1;
    }
edit:

    printf("\n\n--------------------------------------------------------------------------------------\n");
    printf("                              Records on %02d/%02d/%04d\n",day, month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    FILE *file, *file1;
    struct record t;
    file = fopen(userfile,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(day==t.day && month==t.month && year==t.year)
        {
            found = 1;
           printf(" %04d     ",t.id);
            printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }

    if(found==0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
        getch();
    }

    if(found==1)
    {

        file = fopen(userfile,"rb");
        file1 = fopen("temp.txt","wb");

        printf("\n\nEnter the transaction ID: ");
        scanf("%d",&chooseid);

        while(1)
        {
            fread(&t,sizeof(t),1,file);

            if(feof(file))
            {
                break;
            }
            if(t.id==chooseid && day==t.day && month==t.month && year==t.year)
            {
                founD = 1;
                system("cls");

                printf("--------------------------------------------------------------------------------------\n");
                printf(" %04d     ",t.id);
                printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
                printf("   %s   \t",t.type);
                printf("%-25s\t", t.category);
                printf("%10.2lf\n", t.amount);
                printf("--------------------------------------------------------------------------------------\n");
                getAmount(&t.amount);
                fwrite(&t,sizeof(t),1,file1);
                printf("\nRecord updated successfully!\n");
            }
            else
            {
                fwrite(&t,sizeof(t),1,file1);
            }
        }
        fclose(file);
        fclose(file1);

        if(founD==0)
        {
            printf("\nInvalid Transaction ID!\n\n");
            printf("Press any key to re-enter transaction ID: ");
            getch();
            system("cls");
            goto edit;
        }
        else
        {
            file = fopen(userfile,"wb");
            file1 = fopen("temp.txt","rb");

            while(1)
            {

                fread(&t,sizeof(t),1,file1);

                if(feof(file1))
                {
                    break;
                }
                fwrite(&t,sizeof(t),1,file);
            }
        }

        fclose(file);
        fclose(file1);



    }
    printf("\nPress any key to go back to menu...");
    getch();
}

void deleteRecord()
{
    system("COLOR 04");
    system("cls");
    int chooseid;
    int day = 0;
    int month = 0;
    int year = 0;
    int found =0;

enterDate2:

    printf("                           <<<<Delete Income/Expense>>>>\t\t\n\n");

    getDate(&day, &month, &year);

    if (dateValid(day,month,year))
    {
        goto deleteR;

    }
    else
    {
        printf("Date is not valid\n");
        printf("\nPress any key to re-enter a date!");
        getch();
        system ("cls");
        goto enterDate2;
    }

deleteR:

    printf("\n\n--------------------------------------------------------------------------------------\n");
    printf("                              Records on %02d/%02d/%04d\n",day, month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    FILE *file, *file1;
    struct record t;

    file = fopen(userfile,"rb");


    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(day==t.day && month==t.month && year==t.year)
        {
            found = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }

    file = fopen(userfile,"rb");
    file1 = fopen("temp.txt","wb");

    if(found==0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }

    if(found==1)
    {
        printf("\n\nEnter the transaction ID: ");
        scanf("%d",&chooseid);

        while(1)
        {
            fread(&t,sizeof(t),1,file);

            if(feof(file))
            {
                break;
            }
            if(t.id==chooseid && day==t.day && month==t.month && year==t.year)
            {
                found = 1;
                system("cls");

                printf("--------------------------------------------------------------------------------------\n");
                printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
                printf("   %s   \t",t.type);
                printf("%-25s\t", t.category);
                printf("%10.2lf\n", t.amount);
                printf("--------------------------------------------------------------------------------------\n");

                printf("\nRecord deleted successfully!\n");
            }
            else
            {
                fwrite(&t,sizeof(t),1,file1);
            }
        }
        fclose(file);
        fclose(file1);

        if(found==0)
        {
            printf("\nInvalid Transaction ID!\n\n");
            printf("Press any key to re-enter transaction ID: ");
            getch();
            system("cls");
            goto deleteR;

        }
        else
        {
            file = fopen(userfile,"wb");
            file1 = fopen("temp.txt","rb");

            while(1)
            {

                fread(&t,sizeof(t),1,file1);

                if(feof(file1))
                {
                    break;
                }
                fwrite(&t,sizeof(t),1,file);
            }
        }

        fclose(file);
        fclose(file1);
    }


    printf("\nPress any key to go back to menu...");
    getch();
}

void viewDailySummary()
{
    int day = 0;
    int month = 0;
    int year = 0;
    int foundi = 0;
    int founde = 0;
    int foundI = 0;
    int foundE = 0;
    double income[5];
    double expense[7];
    double totalI = 0;
    double totalE = 0;

    system("COLOR F5");
    int choice;
    system("cls");

enterDate3:

    printf("                           <<<<Daily Report>>>>\t\t\n\n");

    getDate(&day, &month, &year);

    if (dateValid(day,month,year))
    {
        goto dailyReport;

    }
    else
    {
        printf("Date is not valid\n");
        printf("\nPress any key to re-enter a date!");
        getch();
        system ("cls");
        goto enterDate3;
    }

dailyReport:

    printf("\n\n");

    FILE *file;
    struct record t;
    file = fopen(userfile,"rb");


    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.day==day && t.month==month && t.year==year && strcmp(t.type, "Income")==0)
        {
            foundi = 1;
            if(strcmp(t.category, "Salary")==0)
            {
                income[0]+=t.amount;
            }
            if(strcmp(t.category, "Dividends Income")==0)
            {
                income[1]+=t.amount;
            }
            if(strcmp(t.category, "Rent Income")==0)
            {
                income[2]+=t.amount;
            }
            if(strcmp(t.category, "Interest Income")==0)
            {
                income[3]+=t.amount;
            }
            if(strcmp(t.category, "Miscellaneous Income")==0)
            {
                income[4]+=t.amount;
            }
        }
    }
    if(foundi == 1)
    {
        printIncomeChart(income);
    }
    totalI = getTotal(income, 5);

    fclose(file);

    file = fopen(userfile,"rb");

    printf("--------------------------------------------------------------------------------------\n");
    printf("                         Daily Income Report for %02d/%02d/%04d\n", day, month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(t.day==day && t.month==month && t.year==year && strcmp(t.type, "Income")==0)
        {
            foundI = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }

    if(foundI == 0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }
    if(foundI == 1)
    {
        printf(" Total                                                                  %10.2lf        \n", totalI);
        printf("--------------------------------------------------------------------------------------\n");
    }
    printf("\n\n\n");


    fclose(file);
    file = fopen(userfile,"rb");

    printf("\n\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.day==day && t.month==month && t.year==year && strcmp(t.type, "Expense")==0)
        {
            founde = 1;
            if(strcmp(t.category, "Utility Expense")==0)
            {
                expense[0]+=t.amount;
            }
            if(strcmp(t.category, "Transportation Expense")==0)
            {
                expense[1]+=t.amount;
            }
            if(strcmp(t.category, "Food Expense")==0)
            {
                expense[2]+=t.amount;
            }
            if(strcmp(t.category, "Medical Expense")==0)
            {
                expense[3]+=t.amount;
            }
            if(strcmp(t.category, "Insurance Expense")==0)
            {
                expense[4]+=t.amount;
            }
            if(strcmp(t.category, "Entertainment Expense")==0)
            {
                expense[5]+=t.amount;
            }
            if(strcmp(t.category, "Miscellaneous Expense")==0)
            {
                expense[6]+=t.amount;
            }
        }
    }

    if(founde == 1)
    {
        printExpenseChart(expense);
    }
    totalE = getTotal(expense, 7);

    printf("--------------------------------------------------------------------------------------\n");
    printf("                        Daily Expense Report for %02d/%02d/%04d\n", day, month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    fclose(file);
    file = fopen(userfile,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(t.day==day && t.month==month && t.year==year && strcmp(t.type, "Expense")==0)
        {
            foundE = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }

    if(foundE == 0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }
    if(foundE == 1)
    {
        printf(" Total                                                                  %10.2lf        \n", totalE);
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(file);

    printf("\nPress any key to go back to menu...");
    getch();
}

void viewMonthlySummary()
{
    int month = 0;
    int year = 0;
    int foundi = 0;
    int founde = 0;
    int foundI = 0;
    int foundE = 0;
    double income[5];
    double expense[7];
    double totalI = 0;
    double totalE = 0;

    system("COLOR B0");
    int choice;
    system("cls");

enterDate4:

    printf("                           <<<<Monthly Report>>>>\t\t\n\n");

    getMonth(&month, &year);

    if (monthValid(month,year))
    {
        goto monthlyReport;

    }
    else
    {
        printf("\nMonth is not valid\n");
        printf("\nPress any key to re-enter a month!");
        getch();
        system ("cls");
        goto enterDate4;
    }

monthlyReport:
    printf("\n\n");

    FILE *file;
    struct record t;
    file = fopen(userfile,"rb");


    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.month==month && t.year==year && strcmp(t.type, "Income")==0)
        {
            foundi = 1;
            if(strcmp(t.category, "Salary")==0)
            {
                income[0]+=t.amount;
            }
            if(strcmp(t.category, "Dividends Income")==0)
            {
                income[1]+=t.amount;
            }
            if(strcmp(t.category, "Rent Income")==0)
            {
                income[2]+=t.amount;
            }
            if(strcmp(t.category, "Interest Income")==0)
            {
                income[3]+=t.amount;
            }
            if(strcmp(t.category, "Miscellaneous Income")==0)
            {
                income[4]+=t.amount;
            }
        }
    }
    if(foundi == 1)
    {
        printIncomeChart(income);
    }

    totalI = getTotal(income, 5);

    fclose(file);
    file = fopen(userfile,"rb");

    printf("--------------------------------------------------------------------------------------\n");
    printf("                         Monthly Income Report for %02d/%04d\n", month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(t.month==month && t.year==year && strcmp(t.type, "Income")==0)
        {
            foundI = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    if(foundI == 0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }
    if(foundI == 1)
    {
        printf(" Total                                                                  %10.2lf        \n", totalI);
        printf("--------------------------------------------------------------------------------------\n");
    }

    printf("\n\n\n");

    file = fopen(userfile,"rb");

    printf("\n\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.month==month && t.year==year && strcmp(t.type, "Expense")==0)
        {
            founde = 1;
            if(strcmp(t.category, "Utility Expense")==0)
            {
                expense[0]+=t.amount;
            }
            if(strcmp(t.category, "Transportation Expense")==0)
            {
                expense[1]+=t.amount;
            }
            if(strcmp(t.category, "Food Expense")==0)
            {
                expense[2]+=t.amount;
            }
            if(strcmp(t.category, "Medical Expense")==0)
            {
                expense[3]+=t.amount;
            }
            if(strcmp(t.category, "Insurance Expense")==0)
            {
                expense[4]+=t.amount;
            }
            if(strcmp(t.category, "Entertainment Expense")==0)
            {
                expense[5]+=t.amount;
            }
            if(strcmp(t.category, "Miscellaneous Expense")==0)
            {
                expense[6]+=t.amount;
            }
        }
    }
    if(founde == 1)
    {
        printExpenseChart(expense);
    }
    totalE = getTotal(expense, 7);

    fclose(file);
    file = fopen(userfile,"rb");

    printf("--------------------------------------------------------------------------------------\n");
    printf("                        Monthly Expense Report for %02d/%04d\n", month, year);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(t.month==month && t.year==year && strcmp(t.type, "Expense")==0)
        {
            foundE = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    if(foundE == 0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }
    if(foundE == 1)
    {
        printf(" Total                                                                  %10.2lf        \n", totalE);
        printf("--------------------------------------------------------------------------------------\n");
    }

    fclose(file);

    printf("\nPress any key to go back to menu: ");
    getch();
}

void filterTransactions()
{
    system("COLOR E1");
    int choice = 0;
    system("cls");
    printf("                           <<<<Filtered Summary>>>>\t\t\n\n");
    printf("[1] Filter by Category\n");
    printf("[2] Filter by Amount\n");

    printf("\nEnter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        filterbyCategory();
        break;
    case 2:
        filterbyAmount();
        break;
    default:
        printf("Invalid Choice!\n");
        printf("Press any key to retry: \n");
        getch();
        filterTransactions();
        break;
    }

}

void filterbyCategory()
{
    system("cls");
    char tempCategory[30];
    int choice = 0;
    int month = 0;
    int year = 0;
    int found = 0;

    printf("                            <<Filter by Category>>\t\t\n\n");

    printf("[1] Income Records\n");
    printf("[2] Expense Records\n");

    printf("\nEnter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        printf("\n\n");
        selectIncome(tempCategory);
        system("cls");
        break;
    case 2:
        printf("\n\n");
        selectExpense(tempCategory);
        system("cls");
        break;
    default:
        printf("Invalid Choice!\n");
        printf("Press any key to retry: \n");
        getch();
        filterbyCategory();
        break;
    }

enterMonth1i:

    getMonth(&month, &year);
    if (monthValid(month, year))
    {
        goto filterTi;
    }
    else
    {
        printf("\nMonth is not valid\n");
        printf("\nPress any key to re-enter a month!");
        getch();
        system ("cls");
        goto enterMonth1i;
    }

filterTi:

    printf("\n\n--------------------------------------------------------------------------------------\n");
    printf("                    Records for Month %02d/%04d in %s Category\n",month, year, tempCategory);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");


    FILE *file;
    struct record t;
    file = fopen(userfile,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(strcmp(t.category, tempCategory)==0 && t.month==month && t.year==year)
        {
            found =1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    fclose(file);

    if(found==0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }

    printf("\nPress any key to go back to menu: ");
    getch();
}

void filterbyAmount()
{
    system("cls");
    double minAmount = 0.0;
    double maxAmount = 0.0;
    char tempType[10];
    int choice = 0;
    int month = 0;
    int year = 0;
    int found = 0;

    printf("                            <<Filter by Amount>>\t\t\n\n");

    printf("[1] Income Records\n");
    printf("[2] Expense Records\n");

    printf("\nEnter your choice: ");

    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
        strcpy(tempType, "Income");
        break;
    case 2:
        strcpy(tempType, "Expense");
        break;
    default:
        printf("Invalid Choice!\n");
        printf("Press any key to retry: \n");
        getch();
        filterbyAmount();
        break;
    }
    system("cls");
enterMonth1ii:

    getMonth(&month, &year);
    if (monthValid(month, year))
    {
        goto filterTii;
    }
    else
    {
        printf("\nMonth is not valid\n");
        printf("\nPress any key to re-enter a month!");
        getch();
        system ("cls");
        goto enterMonth1ii;
    }

filterTii:

    printf("\nMinimum >>> ");
    getAmount(&minAmount);
enterMax:
    printf("\nMaximum >>> ");
    getAmount(&maxAmount);
    if(minAmount>=maxAmount)
    {
        printf("\nMinimum amount cannot be greater than Maximum amount!");
        printf("\n\nPress any key to re-enter maximum amount!\n\n");
        getch();
        goto enterMax;
    }

    system("cls");
    printf("\n\n--------------------------------------------------------------------------------------\n");
    printf("              Records for Month %02d/%04d in the range %.2lfLKR-%.2lfLKR\n", month, year, minAmount, maxAmount);
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");


    FILE *file;
    struct record t;
    file = fopen(userfile,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        if(strcmp(t.type, tempType)==0 && t.month==month && t.year==year && t.amount>=minAmount && t.amount<=maxAmount)
        {
            found = 1;
            printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
            printf("   %s   \t",t.type);
            printf("%-25s\t", t.category);
            printf("%10.2lf\n", t.amount);
            printf("--------------------------------------------------------------------------------------\n");
        }
    }
    fclose(file);

    if(found==0)
    {
        printf("                                 No Records Found!\n");
        printf("--------------------------------------------------------------------------------------\n");
    }

    printf("\nPress any key to go back to menu: ");
    getch();
}

void personalSavings()
{
    int year = 0;
    double income[12];
    double expense[12];
    double totalI = 0;
    double totalE = 0;
    system("cls");
    system("COLOR F4");
enterYear:

    printf("                           <<<<Overview of Personal Savings>>>>\t\t\n\n");

    printf("Please Enter an Year: ");
    scanf("%d", &year);

    if (yearValid(year))
    {
        goto personalSave;

    }
    else
    {
        printf("Year is not valid\n");
        printf("\nPress any key to re-enter an year...");
        getch();
        system ("cls");
        goto enterYear;
    }
personalSave:

    printf("\n\n");

    FILE *file;
    struct record t;

    file = fopen(userfile,"rb");
    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.year==year && strcmp(t.type, "Income")==0)
        {

            if(t.month == 1)
            {
                income[0]+=t.amount;
            }
            if(t.month == 2)
            {
                income[1]+=t.amount;
            }
            if(t.month == 3)
            {
                income[2]+=t.amount;
            }
            if(t.month == 4)
            {
                income[3]+=t.amount;
            }
            if(t.month == 5)
            {
                income[4]+=t.amount;
            }
            if(t.month == 6)
            {
                income[5]+=t.amount;
            }
            if(t.month == 7)
            {
                income[6]+=t.amount;
            }
            if(t.month == 8)
            {
                income[7]+=t.amount;
            }
            if(t.month == 9)
            {
                income[8]+=t.amount;
            }
            if(t.month == 10)
            {
                income[9]+=t.amount;
            }
            if(t.month == 11)
            {
                income[10]+=t.amount;
            }
            if(t.month == 12)
            {
                income[11]+=t.amount;
            }
        }
    }
    totalI = getTotal(income, 12);
    fclose(file);

    file = fopen(userfile,"rb");
    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(t.year==year && strcmp(t.type, "Expense")==0)
        {
            if(t.month == 1)
            {
                expense[0]+=t.amount;
            }
            if(t.month == 2)
            {
                expense[1]+=t.amount;
            }
            if(t.month == 3)
            {
                expense[2]+=t.amount;
            }
            if(t.month == 4)
            {
                expense[3]+=t.amount;
            }
            if(t.month == 5)
            {
                expense[4]+=t.amount;
            }
            if(t.month == 6)
            {
                expense[5]+=t.amount;
            }
            if(t.month == 7)
            {
                expense[6]+=t.amount;
            }
            if(t.month == 8)
            {
                expense[7]+=t.amount;
            }
            if(t.month == 9)
            {
                expense[8]+=t.amount;
            }
            if(t.month == 10)
            {
                expense[9]+=t.amount;
            }
            if(t.month == 11)
            {
                expense[10]+=t.amount;
            }
            if(t.month == 12)
            {
                expense[11]+=t.amount;
            }
        }
    }
    totalE = getTotal(expense, 12);
    fclose(file);

    printf("\n----------------------------------------------------------------------------------\n");
    printf("                   Overview of Personal Savings for the Year %04d\n", year);
    printf("----------------------------------------------------------------------------------\n");
    printf("     Month          Total Income             Total Expenses             Savings             \n");
    printf("----------------------------------------------------------------------------------\n");
    for(int i=0 ; i<12 ; i++)
    {
        printf("    %02d/%04d           %10.2f            %10.2f               %10.2f            \n", i+1, year, income[i], expense[i], income[i]-expense[i]);
        printf("----------------------------------------------------------------------------------\n");
    }
    printf("     Total            %10.2f            %10.2f               %10.2f           \n", totalI, totalE, totalI-totalE);
    printf("----------------------------------------------------------------------------------\n");

    printf("\n\nPress any key to go back to menu...");
    getch();
}

void displayAll()
{
    system("cls");
    system("COLOR F2");
    FILE *file;
    struct record t;

    file = fopen(userfile,"rb");

    printf("--------------------------------------------------------------------------------------\n");
    printf("                                    All Records\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("  ID         Date           Type               Category                     Amount\n");
    printf("--------------------------------------------------------------------------------------\n");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }
        printf(" %04d     ",t.id);
        printf("%02d/%02d/%04d\t", t.day, t.month, t.year);
        printf("   %s   \t",t.type);
        printf("%-25s\t", t.category);
        printf("%10.2lf\n", t.amount);
        printf("--------------------------------------------------------------------------------------\n");
    }
    fclose(file);

    printf("\nPress any key to go back to menu: ");
    getch();
}

double getTotalIncomes()
{
    double totalincome = 0;
    FILE *file;
    struct record t;

    file = fopen(userfile,"rb");


    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(strcmp(t.type, "Income")==0)
        {
            totalincome+=t.amount;
        }

    }
    fclose(file);

    return totalincome;
}

double getTotalExpenses()
{
    double totalexpense = 0;
    FILE *file;
    struct record t;

    file = fopen(userfile,"rb");

    while(1)
    {
        fread(&t,sizeof(t),1,file);

        if(feof(file))
        {
            break;
        }

        if(strcmp(t.type, "Expense")==0)
        {
            totalexpense+=t.amount;
        }
    }
    fclose(file);

    return totalexpense;
}

void selectIncome(char category[30])
{

    int categorY = 0;
getCategory:
    printf("[1] Salary\n");
    printf("[2] Dividends Income\n");
    printf("[3] Rent Income\n");
    printf("[4] Interest Income\n");
    printf("[5] Miscellaneous Income\n");
    printf("\nEnter your choice: ");

    scanf("%d", &categorY);

    switch (categorY)
    {

    case 1:
        strcpy(category, "Salary");
        break;

    case 2:
        strcpy(category, "Dividends Income");
        break;

    case 3:
        strcpy(category, "Rent Income");
        break;

    case 4:
        strcpy(category, "Interest Income");
        break;

    case 5:
        strcpy(category, "Miscellaneous Income");
        break;

    default:
        printf("Invalid Choice!");
        printf("\nPress any key to re-enter a choice...");
        getch();
        system ("cls");
        goto getCategory;
        break;
    }
}

void selectExpense(char category[30])
{
    int categorY = 0;
getCategory:
    printf("[1] Utility Expense\n");
    printf("[2] Transportation Expense\n");
    printf("[3] Food Expense\n");
    printf("[4] Medical Expense\n");
    printf("[5] Insurance Expense\n");
    printf("[6] Entertainment Expense\n");
    printf("[7] Miscellaneous Expense\n");
    printf("\nEnter your choice: ");

    scanf("%d", &categorY);

    switch (categorY)
    {

    case 1:
        strcpy(category, "Utility Expense");
        break;

    case 2:
        strcpy(category, "Transportation Expense");
        break;

    case 3:
        strcpy(category, "Food Expense");
        break;

    case 4:
        strcpy(category, "Medical Expense");
        break;

    case 5:
        strcpy(category, "Insurance Expense");
        break;

    case 6:
        strcpy(category, "Entertainment Expense");
        break;

    case 7:
        strcpy(category, "Miscellaneous Expense");
        break;

    default:
        printf("Invalid Choice!");
        printf("\nPress any key to re-enter a choice...");
        getch();
        system ("cls");
        goto getCategory;
        break;
    }
}

void getDate(int * date, int * month, int *year)
{

    printf("Date of transaction (DD/MM/YYYY): ");
    scanf("%d/%d/%d", date, month, year);
}

void getMonth(int * month, int * year)
{

    printf("Select Month (MM/YYYY): ");
    scanf("%d/%d", month, year);
}

void printIncomeChart(double income[5])
{

    double yaxis[12] = {1000, 2000, 4000, 6000, 8000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000};

    printf("           ^");
    for(int j=11 ; j>=0 ; j--)
    {
        printf("\n");
        printf("%10.0f-", yaxis[j]);
        printf("%c", 179);
        for(int i=0; i<5; i++)
        {
            printf(" \t");
            if(income[i]>=yaxis[j])
            {
                printf("%c", 219);
            }
            else
            {
                printf(" ");
            }
        }
    }

    printf("\n%10d-",0);
    printf("%c", 192);
    for(int i=0 ; i<40 ; i++)
    {
        printf("%c", 196);
    }
    printf(">");
    printf("\n               Sal     Divi    Rent     Int    Misc\n\n\n");

    printf("Total Salary               : %12.2lfLKR\n", income[0]);
    printf("Total Dividends Incomes    : %12.2lfLKR\n", income[1]);
    printf("Total Rent Incomes         : %12.2lfLKR\n", income[2]);
    printf("Total Interest Incomes     : %12.2lfLKR\n", income[3]);
    printf("Total Miscellaneous Incomes: %12.2lfLKR\n\n\n", income[4]);
    printf("\n");
}

void printExpenseChart(double expense[7])
{
    double yaxis[12] = {1000, 2000, 4000, 6000, 8000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000};

    printf("           ^");
    for(int j=11 ; j>=0 ; j--)
    {
        printf("\n");
        printf("%10.0f-", yaxis[j]);
        printf("%c", 179);
        for(int i=0; i<7; i++)
        {
            printf(" \t");
            if(expense[i]>=yaxis[j])
            {
                printf("%c", 219);
            }
            else
            {
                printf(" ");
            }
        }
    }

    printf("\n%10d-",0);
    printf("%c", 192);
    for(int i=0 ; i<60 ; i++)
    {
        printf("%c", 196);
    }
    printf(">");


    printf("\n               Util     Tran    Food     Med    Insu    Ent    Misc\n");

    printf("\n\n");
    printf("Total Utility Expense       : %10.2lfLKR\n", expense[0]);
    printf("Total Transportation Expense: %10.2lfLKR\n", expense[1]);
    printf("Total Food Expense          : %10.2lfLKR\n", expense[2]);
    printf("Total Medical Expense       : %10.2lfLKR\n", expense[3]);
    printf("Total Insurance Expense     : %10.2lfLKR\n", expense[4]);
    printf("Total Entertainment Expense : %10.2lfLKR\n", expense[5]);
    printf("Total Miscellaneous Expense : %10.2lfLKR\n\n\n", expense[6]);
}

double getTotal(double subtotal[], int arrSize)
{

    int total = 0;

    for(int i=0 ; i<arrSize ; i++)
    {
        total += subtotal[i];
    }
    return total;
}

void login()
{
    char username[15];
    char password[15];
    char tempUsername[15];
    char tempPassword[15];
    int found = 0;

    system("COLOR B0");
    system("cls");
    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }
    printf("\n%c                 Welcome to Wallet Buddy!                %c\n",176, 176);
    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }

    printf("\n\n");
    printf("Default username - user\nDefault password - abc@1234\n\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<<Login>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Username: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);
    FILE *fptr;
    fptr = fopen("userdetails.txt", "r");
    while(!feof(fptr))
    {
        fscanf(fptr, "%s %s\n", &tempUsername, &tempPassword);
        if((strcmp(tempUsername,username)==0 && strcmp(tempPassword,password)==0))
        {
            found = 1;
            printf("\nSuccessfully Logged in\n\n");
            printf("Press any key to enter the system");

            strcpy(userfile, tempUsername);
            strcat(userfile, ".txt");

            FILE *file1;
            file1 = fopen(userfile, "a");
            fclose(file1);

            strcpy(userfileIndex, tempUsername);
            strcat(userfileIndex, "Index");
            strcat(userfileIndex, ".txt");

            FILE *file2;
            file2 = fopen(userfileIndex, "a");

            fclose(file2);

            getch();
            menu2();
        }
    }
    if(found == 0)
    {
        printf("\nInvalid Credentials!\n\n");
        printf("Press any key to retry\n");
        getch();
        login();
    }
}

void signUp()
{
    char newUsername[15];
    char newPassword[15];
    char tempUsername[15];
    char tempPassword[15];
    int found = 0;

    system("COLOR B0");
    system("cls");
signIn:
    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }
    printf("\n%c                 Welcome to Wallet Buddy!                %c\n",176, 176);
    for(int i=0 ; i<59 ; i++)
    {
        printf("%c", 176);
    }

    printf("\n\n");
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<Sign Up>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
    printf("Enter Username: ");
    scanf("%s", &newUsername);
    FILE *fptr;
    fptr = fopen("userdetails.txt", "r");
    while(!feof(fptr))
    {
        fscanf(fptr, "%s %s\n", &tempUsername, &tempPassword);
        if(strcmp(tempUsername, newUsername)==0)
        {
            found = 1;
            printf("\nUsername already exists!");
            printf("\n\nPress any key to re-enter username...");
            getch();
            system("cls");
            goto signIn;
        }
    }
    fclose(fptr);
createPassword:
    printf("Enter Password: ");
    scanf("%s", &newPassword);
    if((strlen(newPassword))<6)
    {
        printf("\nPassword is too week!");
        printf("\n\nPlease enter a password with at least 6 characters");
        printf("\n\nPress any key to retry...\n\n");
        getch();
        goto createPassword;
    }
    fptr = fopen("userdetails.txt", "a");
    fprintf(fptr, "%s %s\n", newUsername, newPassword);
    fclose(fptr);
    printf("\nUser Registration Successful!\n\n");
    printf("Press any key to proceed to login...\n");
    getch();
    login();
}

void readIndex(int *recordID)
{
    FILE *fp;

    fp = fopen(userfileIndex,"r");
    fscanf(fp, "%d", recordID);
    fclose(fp);

}

void saveIndex(int recordID)
{
    FILE *fp;

    fp = fopen(userfileIndex,"w");
    fprintf(fp, "%d", recordID);
    fclose(fp);
}

int isLeap(int y)
{
    if((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
        return 1;
    else
        return 0;
}

int dateValid(int d, int m, int y)
{
    if(y < min_yr || y > max_yr)
        return 0;
    if(m < 1 || m > 12)
    {
        if( m == 02 )
        {
            if(isLeap(y))
            {
                if(d <= 29)
                    return 1;
                else
                    return 0;
            }
        }
        return 0;
    }


    if(d < 1 || d > 31)
        return 0;

    if ( m == 4 || m == 6 || m == 9 || m == 11 )
        if(d <= 30)
            return 1;
        else
            return 0;
    return 1;
}

int monthValid(int m, int y)
{
    if(y < min_yr || y > max_yr)
        return 0;
    if(m < 1 || m > 12)
        return 0;
}

int yearValid(int y)
{
    if(y < min_yr || y > max_yr)
        return 0;
}

void getAmount(double * amount)
{
enterAmount:
    printf("Please enter the transaction amount: ");
    scanf("%lf", amount);
    if(*amount <= 0.0)
    {
        printf("\nInvalid Amount!");
        printf("\n\nPress any key to re-enter amount...\n\n");
        getch();
        goto enterAmount;
    }

}
