/******************************************************************************
* Filename    : EmpMaint.c
* Author      : Education & Research Emp, Infosys Technologies Limited
* Date        : 11-Mar-2009
* Description : Contains the functions required for the Employee
*		maintenance.
*******************************************************************************/


/* Include files */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

#include "FileFunctions.h"

/* Stores the Code of the next Employee that may be added */
int giEmpCode=1000;

int iFlag1=1;
int iFlag2=1;
int iFlag4=1;

struct emp{
    int ecode;
    char ename[26];
    int edep;
    char edepname[16];
    char eloc[6];
    int etele;
}e;

struct dept1{
    int dcode;
    char dname[16];

}d1;

/******************************************************************************
* Function: fnDispAddNewEmp
* Description: This prints the menu headline for Adding an Employee
* Input Parameters: None
******************************************************************************/

void fnDispAddNewEmp ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tAdd an Employee\n");
	printf("\t\t================\n\n");
}

/******************************************************************************
* Function: fnAddNewEmp
* Description: Adds a new Employee entry into the Emp file
*		The Emp file should've been opened in the program already!
* Input Parameters: None
* Returns: Zero on success. 1 if Emp name exists already.
******************************************************************************/

void fnAddNewEmp ()
{
    char s1[50];
    int len;
    fnOpenFile(EMP_FILE);
    printf("\n\tEnter Employee Name: ");
    scanf("%s",&s1);
    len = strlen(s1);
    if(len > 25) {
        printf("\n\tThe length of the name exceeds the limit\n");
        fnCloseFile(EMP_FILE);
        return;
    }

    if(fgetc(fpEmp)==EOF)
    {
        e.ecode=giEmpCode;
    }
    else{
        fseek(fpEmp,0L,SEEK_SET);
        while(fgetc(fpEmp)!=EOF){
            fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        }
        e.ecode++;
    }
    printf("\n\tEmployee Id: %d",e.ecode);
    printf("\n\n\t\tDepartment Details\n");
    printf("\t\t_________________________");
    printf("\n\t\tDept code   Dept name");
    printf("\n\t\t_________________________");
    fnOpenFile(DEP_FILE);

    while(fgetc(fpDept)!=EOF){
        fscanf(fpDept,"%d   %s",&d.dcode,&d.dname);
        printf("\n\t\t%-4d        %-15s\n",d.dcode,d.dname);
    }
    fnCloseFile(DEP_FILE);
    printf("\n\tEnter Department Code: ");
    scanf("%d",&e.edep);
    fnOpenFile(DEP_FILE);
    fseek(fpDept,0L,SEEK_SET);
        while(fgetc(fpDept)!=EOF){
            fscanf(fpDept,"%d   %s",&d.dcode,&d.dname);
            if(d.dcode==e.edep){
                    strcpy(e.edepname,d.dname);
                    printf("\n\tDepartment Name: %s",e.edepname);
                    iFlag1=0;
                    break;
            }
        }
        if(iFlag1){
            printf("\n\t\tDepartment does not exist\n");
            fnEmpMenu();
        }
    iFlag1=1;
    printf("\n\n\tEnter Location : ");
    scanf("%s",e.eloc);
    len = strlen(e.eloc);
    if(len > 5) {
        printf("\n\tThe length of location exceeds the limit\n");
        return;
    }

    strcpy(e.ename,s1);
    fseek(fpEmp,0L,SEEK_END);
    e.etele=0;
    fprintf(fpEmp,"\n%d  %25s  %d  %15s  %5s        %d",e.ecode,e.ename,e.edep,e.edepname,e.eloc,e.etele);
    fnCloseFile(DEP_FILE);

    fnCloseFile(EMP_FILE);
}
/******************************************************************************
* Function: fnPrintEmp
* Description: Prints all the Employee codes and names that exist in the
*		file Emp.txt
* Input Parameters: None
******************************************************************************/

void fnPrintEmp ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tEmployee Details\n");
	printf("\t\t================\n\n");
	fnOpenFile(EMP_FILE);
	if(fgetc(fpEmp) == EOF) {
        printf("\n\tThere are no Employees available\n\n");
        fnCloseFile(EMP_FILE);
        return;
	}
    printf("\t________________________________________________________________________________");
    printf("\n\tEmp    Emp                         Dept   Dept              Location   Telephone");
    printf("\n\tcode   name                        code   name                          Number \n");
    printf("\t________________________________________________________________________________\n");
    fseek(fpEmp,0L,SEEK_SET);

    while(fgetc(fpEmp)!=EOF){
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(!e.etele)
            printf("\n\t%d   %-25s   %d   %-15s   %-5s         -\n",e.ecode,e.ename,e.edep,e.edepname,e.eloc);
        else
            printf("\n\t%d   %-25s   %d   %-15s   %-5s      %d\n",e.ecode,e.ename,e.edep,e.edepname,e.eloc,e.etele);
    }
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnDispAddTeleNum
* Description: This prints the menu headline for Adding Telephone number
* Input Parameters: None
******************************************************************************/

void fnDispAddTeleNum()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tAdd Telephone number\n");
	printf("\t\t====================\n\n");
}

/******************************************************************************
* Function: fnAddTeleNum
* Description: Adds a Telephone number to an Employee already present in the
        system. The Emp file should've been opened in the program already!
* Input Parameters: None
******************************************************************************/

void fnAddTeleNum ()
{
    int id;
    printf("\n\tEnter Employee Id :");
    scanf("%d",&id);
    fnOpenFile(EMP_FILE);
    fseek(fpEmp,0L,SEEK_SET);
        while(fgetc(fpEmp)!=EOF){
            fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
            if(e.ecode==id&&e.etele==0){
                    iFlag2=0;
                    break;
            }
            else if(e.ecode==id&&e.etele!=0){
                printf("\n\tTelephone number already assigned\n");
                break;
            }
        }
        if(!iFlag2){
            fnOpenFile(TELE_FILE);
            fseek(fpTele,0L,SEEK_SET);
            while(fgetc(fpTele)!=EOF){
                fscanf(fpTele,"%d     %d",&t.tcode,&t.tnum);
                if(e.edep==t.tcode){
                    t.tnum++;
                    e.etele=e.edep*1000+t.tnum;

                    fseek(fpTele,-3,SEEK_CUR);
                    fprintf(fpTele,"%3d",t.tnum);
                    fseek(fpEmp,-7,SEEK_CUR);
                    fprintf(fpEmp,"%d",e.etele);
                    break;
                }
            }
            fnCloseFile(TELE_FILE);
        }
        else if(e.ecode!=id){
            printf("\n\tEmployee does not exist\n");
            printf("\n\tPress any Key To continue .. \n");
            getch();
            fnCloseFile(EMP_FILE);
            fnTeleDirMenu();
        }
        iFlag2=1;
        printf("\n\tLocation                   : %s",e.eloc);
        printf("\n\n\tDepartment code            : %d",e.edep);
        printf("\n\n\tTelephone Number Allocated : %d\n",e.etele);
        fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnChangeEmpName
* Description: Allows user to visually change the name of any Employee
        present in the system
* Input Parameters: None
******************************************************************************/

void fnChangeEmpName ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tChange Employee Name\n");
	printf("\t\t====================\n\n");

    fnOpenFile(EMP_FILE);
    if(fgetc(fpEmp) == EOF) {
        printf("\n\tThere are no Employees available\n");
        return;
    }
    int empId;
    fseek(fpEmp,0L,SEEK_SET);
    printf("\tEnter the Employee Id : ");
    scanf("%d",&empId);
    while(fgetc(fpEmp) != EOF) {
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(e.ecode == empId) {
            iFlag4 = 0;
            break;
        }
    }
    int len;
    char newName[50];
    if(!iFlag4) {
        printf("\n\tThe current name of the Employee is : %s\n",e.ename);
        printf("\n\tEnter the new name for the Employee : ");
        scanf("%s",newName);

        len = strlen(newName);
        if(len > 25) {
            printf("\n\tThe length of the name exceeds the limit\n");
            iFlag4 = 1;
            fnCloseFile(EMP_FILE);
            return;
        }
        fseek(fpEmp,-64,SEEK_CUR);
        fprintf(fpEmp,"%25s",newName);
    }
    else {
        printf("\n\tThe Employee does not exist\n");
    }
    iFlag4 = 1;
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnChangeEmpLoc
* Description: Allows user to visually change the location of any Employee
        present in the system
* Input Parameters: None
******************************************************************************/

void fnChangeEmpLoc ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tChange Employee Location\n");
	printf("\t\t========================\n\n");

    fnOpenFile(EMP_FILE);
    if(fgetc(fpEmp) == EOF) {
        printf("\n\tThere are no Employees available\n");
        return;
    }
    int empId;
    fseek(fpEmp,0L,SEEK_SET);
    printf("\tEnter the Employee Id : ");
    scanf("%d",&empId);
    while(fgetc(fpEmp) != EOF) {
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(e.ecode == empId) {
            iFlag4 = 0;
            break;
        }
    }
    int len;
    char newLoc[50];
    if(!iFlag4) {
        printf("\n\tThe current location of the Employee is : %s\n",e.eloc);
        printf("\n\tEnter the new location for the Employee : ");
        scanf("%s",newLoc);

        len = strlen(newLoc);
        if(len > 5) {
            printf("\n\tThe length of the name exceeds the limit\n");
            iFlag4 = 1;
            fnCloseFile(EMP_FILE);
            return;
        }
        fseek(fpEmp,-14,SEEK_CUR);
        fprintf(fpEmp,"%5s",newLoc);
    }
    else {
        printf("\n\tThe Employee does not exist\n");
    }
    iFlag4 = 1;
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnChangeEmpDepartment
* Description: Allows user to visually change the Department of any Employee
        present in the system and also their Telephone number changes
        accordingly
* Input Parameters: None
******************************************************************************/

void fnChangeEmpDepartment ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tChange Employee Department\n");
	printf("\t\t==========================\n\n");

    fnOpenFile(EMP_FILE);
    if(fgetc(fpEmp) == EOF) {
        printf("\n\tThere are no Employees available\n");
        return;
    }
    int empId;
    fseek(fpEmp,0L,SEEK_SET);
    printf("\tEnter the Employee Id : ");
    scanf("%d",&empId);

    while(fgetc(fpEmp) != EOF) {
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e.ecode,&e.ename,&e.edep,&e.edepname,&e.eloc,&e.etele);
        if(e.ecode == empId) {
            iFlag4 = 0;
            break;
        }
    }
    int newDep,newTele,teleNum;
    if(!iFlag4) {
        printf("\n\tThe current Department of the Employee is : %s\n",e.edepname);
        fnOpenFile(DEP_FILE);

        printf("\n\tThe available departments are as follows\n");
        printf("\n\t\t_____________________");
        printf("\n\t\tDept code   Dept name");
        printf("\n\t\t_____________________");
        while(fgetc(fpDept)!=EOF){
            fscanf(fpDept,"%d   %s",&d1.dcode,&d1.dname);
            if(d1.dcode != e.edep)
                printf("\n\t\t%-4d        %-15s\n",d1.dcode,d1.dname);
        }
        fnCloseFile(DEP_FILE);

        printf("\n\tEnter the new Department Id for the Employee : ");
        scanf("%d",&newDep);

        fnOpenFile(DEP_FILE);

        while(fgetc(fpDept)!=EOF){
            fscanf(fpDept,"%d   %s",&d1.dcode,&d1.dname);
            if(newDep==d1.dcode){
                printf("\n\tDepartment Name: %s",d1.dname);

                fseek(fpEmp,-37,SEEK_CUR);
                fprintf(fpEmp,"%4d  %15s",newDep,d1.dname);
                iFlag1=0;
                break;
            }
        }
        if(iFlag1){
            printf("\n\n\tDepartment does not exist\n");
            return;
        }
        iFlag1=1;

        if(e.etele != 0) {
            teleNum = fnIncrementDepTele(newDep);
            newTele = (newDep*1000)+teleNum;
            fseek(fpEmp,9,SEEK_CUR);

            fprintf(fpEmp,"%7d",newTele);
        }
    }
    else {
        printf("\n\n\tThe Employee does not exist\n");
    }
    iFlag4 = 1;
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* Function: fnIncrementDepTele
* Description: It updates the tele.txt file for new Telephone number added
* Input Parameters: newDep - New Department code for the Employee assigned
******************************************************************************/

int fnIncrementDepTele (int newDep)
{
    fnOpenFile(TELE_FILE);
    while(fgetc(fpTele) != EOF) {
        fscanf(fpTele,"%d   %d",&t.tcode,&t.tnum);
        if(t.tcode == newDep) {
            break;
        }
    }
    fseek(fpTele,-3,SEEK_CUR);
    fprintf(fpTele,"%3d",++t.tnum);
    fnCloseFile(TELE_FILE);
    return t.tnum;
}

/******************************************************************************
* End of EmpMaint.c
******************************************************************************/
