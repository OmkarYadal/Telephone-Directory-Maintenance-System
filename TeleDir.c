/******************************************************************************
* Filename    : TelDir.c
* Author      :
* Date        : 20-Sept-2022
* Description : Displays the main menu for telephone directory maintenace and
*		invokes the respective functions
******************************************************************************/

/* Include files */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

/* Declare constants and function prototypes */
#include "FileFunctions.h"
#include "DeptMaint.c"
#include "EmpMaint.c"
#include "TeleEnq.c"
#include "FileFunctions.c"

void clearscreen()
{
    int i;
    for(i=0; i<40; i++){
        printf("\n");
	}
}

/******************************************************************************
* Function: fnLogin
Description: check for valid User Id and calls fnMainMenu.
 If invalid employee id is entered for User Id, error message "Login Denied"
 is displayed and quits the application.
* Input Parameters: None
* Return : None
******************************************************************************/



void fnLogin()
{
	int iempid;
    clearscreen();
	printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tLOGIN SCREEN\n");
	printf("\t\t============\n");
    fnOpenFile(EMP_FILE);
    if(fgetc(fpEmp)==EOF)
    {
        fnCloseFile(EMP_FILE);
        printf("\n\n\tNo Employee registered");
        printf("\n\tPress any Key To continue .. \n");
        getch();
        fnMainMenu();
    }
	printf("\n\n\tEnter User ID : ");
	scanf("%d",&iempid);
	fnLoginValidate(iempid);
}

void fnLoginValidate(int acUserId)
{
    fnOpenFile(EMP_FILE);
    fseek(fpEmp,0L,SEEK_SET);
    while(fgetc(fpEmp)!=EOF){
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(acUserId==e.ecode){
            fnCloseFile(EMP_FILE);
            fnMainMenu();
        }
    }
    printf("\n\tEmployee does not exist");
    fnCloseFile(EMP_FILE);
    printf("\n\tPress any Key To continue .. \n");
    getch();
    fnLogin();
}

/******************************************************************************
* Function: fnDisplayMainMenu
* Description: Displays the main menu of telephone directory system. Then
*		waits for user's input using scanf function. Until the user types in
*		a selection, control will not be returned to the calling function.
* Input Parameters: None
* Returns: The user's choice
******************************************************************************/

int fnDisplayMainMenu()
{
	int ichoice;
	clearscreen();
	printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\t\tMAIN MENU\n");
	printf("\t\t\t=========\n");
	printf("\n\n\t\t1. Department Maintenance");
	printf("\n\t\t2. Employee Maintenance");
	printf("\n\t\t3. Telephone Directory Maintenance");
	printf("\n\t\t4. Telephone Enquiry Menu");
	printf("\n\t\t5. Exit");
	printf("\n\n\n\t\tEnter your choice :");
	scanf("%d",&ichoice);
	return ichoice;
}

/******************************************************************************
* Function: fnMainMenu
* Description: Calls fnDisplayMainMenu and waits for user's choice. Upon
*     user's selection, does appropriate action. If user chooses 'exit'
*     option, returns control back to the calling function.
* Input Parameters: None
* Returns : None
******************************************************************************/

void fnMainMenu ()
{
	int ichoice = fnDisplayMainMenu();
	switch(ichoice){
	    case 1: fnDepartmentMenu();
		        break;
	    case 2: fnEmpMenu();
		        break;
	    case 3: fnTeleDirMenu();
		        break;
	    case 4: fnTeleEnqMenu();
		        break;
	    case 5: printf("\n\t\tThank you for using our software :)\n\n\n");
		        exit(0);
		        break;
	    default:printf("\n\t\tChoice is Invalid. Re-Enter the choice.\n");
		        printf("\n\t\tPress any Key To continue ..");
		        getchar();
		        getch();
                clearscreen();
		        fnMainMenu();
	}
}

/******************************************************************************
* Function: fnDisplayDepartmentMenu
* Description: Displays the Department Maintenance menu. Waits for user's
*		input in keyboard using scanf. Returns control back to calling function
*		only after user has typed a choice.
* Input Parameters: None
* Returns: The user's choice.
******************************************************************************/

int fnDisplayDepartmentMenu()
{
	int ichoice;
	clearscreen();
	printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tDepartment Maintenance Menu\n");
	printf("\t\t===========================\n");
	printf("\n\n\t\t1. Add Department");
	printf("\n\t\t2. Print Department Detail");
	printf("\n\t\t3. Change Department name");
	printf("\n\t\t4. Goto Main Menu");
	printf("\n\n\n\t\tEnter your choice :");
	scanf("%d",&ichoice);
	return ichoice;
}

/******************************************************************************
* Function: fnDepartmentMenu
* Description: Handles the Department menu. Calls fnDisplayDepartmentMenu
*		function to display the menu. choice of user is handled by this
*		function.
* Input Parameters: None
* Returns: None
******************************************************************************/

void fnDepartmentMenu()
{
	int ichoice = fnDisplayDepartmentMenu();
	switch(ichoice){
	    case 1: fnDispAddNewDepartment();
                fnAddNewDepartment();
		        printf("\n\tPress any Key To continue\n");
                getch();
                fnDepartmentMenu();
                break;
	    case 2: fnPrintDept();
                printf("\n\tPress any Key To continue\n");
                getch();
                fnDepartmentMenu();
		        break;
        case 3: fnChangeDepName();
                printf("\n\tPress any Key To continue\n");
                getch();
                fnDepartmentMenu();
		        break;
	    case 4: fnMainMenu();
		        break;
	    default:printf("\n\tChoice is Invalid. Re-Enter the choice.");
		        getchar();
		        getch();
		        fnDepartmentMenu();
	}
}

/******************************************************************************
* Function: fnDisplayEmpMenu
* Description: Displays the Employee Maintenance menu. Waits for user's
*		input in keyboard using scanf. Returns control back to calling function
*		only after user has typed a choice.
* Input Parameters: None
* Returns: The user's choice.
******************************************************************************/

int fnDisplayEmpMenu()
{
	int ichoice;
	clearscreen();
	printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\n\t\tEmployee Maintenance Menu\n");
	printf("\t\t=========================\n");
	printf("\n\n\t\t1. Add Employee");
	printf("\n\t\t2. Print Employee Detail");
	printf("\n\t\t3. Change Employee name");
	printf("\n\t\t4. Change Employee Location");
	printf("\n\t\t5. Change Employee Department");
	printf("\n\t\t6. Goto Main Menu");
	printf("\n\n\n\t\tEnter your choice :");
	scanf("%d",&ichoice);
	return ichoice;
}

/******************************************************************************
* Function: fnEmpMenu
* Description: Handles the Employee Maintenance menu. Calls fnDisplayEmpMenu
*		function to display the menu. choice of user is handled by this
*		function.
* Input Parameters: None
* Returns: None
******************************************************************************/

void fnEmpMenu()
{
	int ichoice = fnDisplayEmpMenu();
	switch(ichoice){
	    case 1: fnDispAddNewEmp();
                fnAddNewEmp();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnEmpMenu();
		        break;
	    case 2: fnPrintEmp();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnEmpMenu();
		        break;
        case 3: fnChangeEmpName();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnEmpMenu();
		        break;
        case 4: fnChangeEmpLoc();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnEmpMenu();
		        break;
        case 5: fnChangeEmpDepartment();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnEmpMenu();
		        break;
	    case 6: fnMainMenu();
		        break;
	    default:printf("\n\tChoice is Invalid. Re-Enter the choice.");
                getchar();
		        getch();
		        fnEmpMenu();
	}
}

/******************************************************************************
* Function: fnDisplayTeleDirMenu
* Description: Displays the Telephone Directory Maintenance menu. Waits for user's
*		input in keyboard using scanf. Returns control back to calling function
*		only after user has typed a choice.
* Input Parameters: None
* Returns: The user's choice.
*******************************************************************************/

int fnDisplayTeleDirMenu()
{
	int ichoice;
	clearscreen();
	printf("\n\tTelephone Directory And Maintenance System\n");
	printf("\n\t==========================================\n");
	printf("\n\n");
    printf("\n\t  Telephone Directory Maintenance Menu\n");
	printf("\t  ====================================\n");
	printf("\n\n\t  1. Add Telephone Number");
	printf("\n\t  2. Goto Main Menu");
	printf("\n\n\t  Enter your choice :");
	scanf("%d",&ichoice);
	return ichoice;
}

/******************************************************************************
* Function: fnTeleDirMenu
* Description: Handles the Telephone Directory Maintenance menu. Calls
	fnDisplayTeleDirMenu function to display the menu. choice of user is
	handled by this	function.
* Input Parameters: None
* Returns: None
******************************************************************************/

void fnTeleDirMenu()
{
	int ichoice = fnDisplayTeleDirMenu();
	switch(ichoice){
	    case 1: fnDispAddTeleNum();
                fnAddTeleNum();
                printf("\n\tPress any Key To continue .. \n");
                getch();
                fnTeleDirMenu();
		        break;
    	case 2: fnMainMenu();
	    	    break;
	    default:printf("\n\tChoice is Invalid. Re-Enter the choice.");
                getchar();
                getch();
		    	clearscreen();
		    	fnTeleDirMenu();
    }
}

/******************************************************************************
* Function: fnDisplayTeleEnqMenu
* Description: Displays the Telephone Enquiry menu. Waits for user's
*		input in keyboard using scanf. Returns control back to calling function
*		only after user has typed a choice.
* Input Parameters: None
* Returns: The user's choice.
******************************************************************************/

int fnDisplayTeleEnqMenu()
{
	int ichoice;
	clearscreen();
	printf("\n\tTelephone Directory And Maintenance System\n");
	printf("\n\t==========================================\n");
	printf("\n\n");
	printf("\n\t\tTelephone Enquiry Menu\n");
	printf("\t\t======================\n");
	printf("\n\n\t\t1. Enquiry On Employee Name");
	printf("\n\t\t2. Enquiry On Telephone Number");
	printf("\n\t\t3. Goto Main Menu");
	printf("\n\n\t\tEnter your choice :");
	scanf("%d",&ichoice);
	return ichoice;
}

/******************************************************************************
* Function: fnTeleEnqMenu
* Description: Handles the Telephone Enquiry menu. Calls fnDisplayTeleEnqMenu
*		function to display the menu. choice of user is handled by this
*		function.
* Input Parameters: None
* Returns: None
******************************************************************************/

void fnTeleEnqMenu()
{
	int ichoice = fnDisplayTeleEnqMenu();
	switch(ichoice){
	    case 1: fnDispEnqByName();
                fnEnqByName();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnTeleEnqMenu();
	            break;
        case 2: fnDispEnqByTeleNum();
                fnEnqByTeleNum();
                printf("\n\t\tPress any Key To continue .. \n");
                getch();
                fnTeleEnqMenu();
		        break;
	    case 3: fnMainMenu();
	            break;
        default:printf("\n\tChoice is Invalid. Re-Enter the choice.");
                getchar();
		        getch();
			    fnTeleEnqMenu();
	}
}

/******************************************************************************
* Function: main
* Description: Entry point of program.
* Input Parameters: None
******************************************************************************/

int main (int argc, char** argv)
{
	/* calling fnLogin function to generate login screen*/
	fnLogin();

	/* Return a success code to Operating System */
	return 0;
}

/******************************************************************************
* End of TelDir.c
******************************************************************************/
