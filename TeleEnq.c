/******************************************************************************
* Filename    : TeleEnq.c
* Author      : Education & Research Tele, Infosys Technologies Limited
* Date        : 11-Mar-2009
* Description : Contains the functions required for the Telephone enquiry
*		maintenance.
*******************************************************************************/

/* Include files */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

#include "FileFunctions.h"

int iFlag3=1;

/******************************************************************************
* Function: fnDispEnqByName
* Description: This prints the menu headline for Telephone Number Enquiry
        by Name
* Input Parameters: None
******************************************************************************/

void fnDispEnqByName()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t   Telephone Number Enquiry by Name\n");
	printf("\t   ================================\n\n");
}

/******************************************************************************
* Function: fnEnqByName
* Description: It allows the user to view the details of any Employee present
        in the system by their name
* Input Parameters: None
******************************************************************************/

void  fnEnqByName()
{
    char tname[50];
    printf("\n\tEnter Employee name: ");
    scanf("%s",tname);
    fnOpenFile(EMP_FILE);
    if(fgetc(fpEmp) == EOF) {
        printf("\n\tThere are no Employees available\n\n");
        return;
    }
    printf("\n\t__________________________________________________________________");
    printf("\n\tName                        Location   DeptName          TelNumber\n");
    printf("\t__________________________________________________________________\n");
    fseek(fpEmp,0L,SEEK_SET);

    while(getc(fpEmp)!=EOF){
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(!strcmpi(e.ename,tname)){
            if(e.etele != 0) {
                printf("\n\t%-25s   %-5s      %-15s   %-7d\n",e.ename,e.eloc,e.edepname,e.etele);
                iFlag3=0;
            }
            else {
                printf("\n\t%-25s   %-5s      %-15s   Not Assigned\n",e.ename,e.eloc,e.edepname);
                iFlag3=0;
            }
        }
    }
    if(iFlag3){
        printf("\n\tEmployee name does not exist\n");
    }
    iFlag3=1;
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnDispEnqByTeleNum
* Description: This prints the menu headline for Telephone Number Enquiry
* Input Parameters: None
******************************************************************************/

void fnDispEnqByTeleNum(){
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tTelephone Number Enquiry\n");
	printf("\t\t========================\n\n\n");
}

/******************************************************************************
* Function: fnEnqByName
* Description: It allows the user to view the details of any Employee present
        in the system by their Telephone number
* Input Parameters: None
******************************************************************************/

void  fnEnqByTeleNum()
{
    int tnum;
    printf("\tEnter Telephone number: ");
    scanf("%d",&tnum);
    fnOpenFile(EMP_FILE);
    while(getc(fpEmp)!=EOF){
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(e.etele==tnum){
            printf("\n\tEmployee Name     :     %s\n",e.ename);
            printf("\n\tLocation          :     %s\n",e.eloc);
            printf("\n\tDepartment Name   :     %s\n",e.edepname);
            iFlag3=0;
            break;
        }
    }
    if(iFlag3){
        printf("\n\tTelephone number does not exist\n");
    }
    iFlag3=1;
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* End of TeleEnq.c
******************************************************************************/
