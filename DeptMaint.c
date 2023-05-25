/******************************************************************************
* Filename    : DeptMaint.c
* Author      : Education & Research Dept, Infosys Technologies Limited
* Date        : 11-Mar-2009
* Description : Contains the functions required for the department
*		maintenance.
*******************************************************************************/

/* Include files */
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>

#include "FileFunctions.h"

struct dept{
    int dcode;
    char dname[16];

}d;

struct tele{
    int tcode;
    int tnum;
}t;

struct emp1{
    int ecode;
    char ename[26];
    int edep;
    char edepname[16];
    char eloc[6];
    int etele;
}e1;

/* Stores the Code of the next department that may be added */
int giDeptCode=1000;
int iFlag=1;
int iFlag2;
int Flag4=1;

/******************************************************************************
* Function: fnPrintDept
* Description: Prints all the department codes and names that exist in the
*		file dept.txt
* Input Parameters: None
******************************************************************************/

void fnPrintDept ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tDepartment Details\n");
	printf("\t\t==================\n\n");
	fnOpenFile(DEP_FILE);
	if(fgetc(fpDept) == EOF) {
        printf("\n\tThere are no Departments available\n\n");
        return;
	}
    printf("\t\t_____________________");
    printf("\n\t\tDept code   Dept name");
    printf("\n\t\t_____________________");
    fseek(fpDept,0L,SEEK_SET);

    while(fgetc(fpDept)!=EOF){
        fscanf(fpDept,"%4d   %15s",&d.dcode,&d.dname);
        printf("\n\t\t%-4d        %-15s\n",d.dcode,d.dname);
    }
    fnCloseFile(DEP_FILE);
}

/******************************************************************************
* Function: fnDispAddNewDepartment
* Description: This prints the menu headline for Adding a Department
* Input Parameters: None
******************************************************************************/

void fnDispAddNewDepartment()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tAdd a Department\n");
	printf("\t\t================\n\n");
}

/******************************************************************************
* Function: fnAddNewDepartment
* Description: Allows user to visually add a new department into the system
* Input Parameters: None
******************************************************************************/

void fnAddNewDepartment ()
{
    char s1[50];
    int len;
    fnOpenFile(DEP_FILE);
    printf("\tEnter Department name\t: ");
    scanf("%s",&s1);
    len = strlen(s1);
    if(len > 15) {
        printf("\n\tThe length of the name exceeds the limit\n");
        goto depEnd;
    }

    if(fgetc(fpDept)==EOF)
    {
        d.dcode=giDeptCode;
    }
    else{
        fseek(fpDept,0L,SEEK_SET);
        while(fgetc(fpDept)!=EOF){
            fscanf(fpDept,"%d   %s",&d.dcode,&d.dname);
            if(!strcmpi(d.dname,s1)){
                printf("\nEntered Department Name already exist.");
                iFlag=0;
                break;
            }
        }
        d.dcode++;
    }
    if(iFlag){
        strcpy(d.dname,s1);

        printf("\tDepartment Code\t\t: %d",d.dcode);
        fprintf(fpDept,"\n%4d  %15s",d.dcode,d.dname);
        fnOpenFile(TELE_FILE);
        fseek(fpTele,0L,SEEK_END);
        t.tcode=d.dcode;
        t.tnum=0;
        fprintf(fpTele,"\n%d  %3d",t.tcode,t.tnum);
        fnCloseFile(TELE_FILE);
    }
    iFlag=1;
    depEnd: fnCloseFile(DEP_FILE);
}

/******************************************************************************
* Function: fnChangeDepName
* Description: Allows user to visually change the name of any Department
        present in the system and also accordingly the details of the
        Employees also changes
* Input Parameters: None
******************************************************************************/

void fnChangeDepName ()
{
    clearscreen();
    printf("\n\tTelephone Directory Maintenance System\n");
	printf("\t======================================\n");
	printf("\n\n");
	printf("\t\tChange Department Name\n");
	printf("\t\t======================\n\n");

    fnOpenFile(DEP_FILE);
    if(fgetc(fpDept) == EOF) {
        printf("\n\tThere are no Departments available\n");
        return;
    }
    int depNum;
    fseek(fpDept,0L,SEEK_SET);
    printf("\tEnter the Department number : ");
    scanf("%d",&depNum);
    while(fgetc(fpDept) != EOF) {
        fscanf(fpDept,"%d   %s",&d.dcode,&d.dname);
        if(d.dcode == depNum) {
            Flag4 = 0;
            break;
        }
    }
    int len;
    char newName[50];
    if(!Flag4) {
        printf("\n\tThe current name of the Department is : %s\n",d.dname);
        printf("\n\tEnter the new name for the Department : ");
        scanf("%s",newName);

        len = strlen(newName);
        if(len > 15) {
            printf("\n\tThe length of the name exceeds the limit\n");
            Flag4 = 1;
            fnCloseFile(DEP_FILE);
            return;
        }
        fseek(fpDept,-15,SEEK_CUR);
        fprintf(fpDept,"%15s",newName);
    }
    else {
        printf("\n\tThe department does not exist\n");
    }
    Flag4 = 1;
    fnCloseFile(DEP_FILE);

    fnOpenFile(EMP_FILE);

    while(fgetc(fpEmp) != EOF) {
        fscanf(fpEmp,"%d   %s   %d  %s  %s  %d",&e1.ecode,&e1.ename,&e1.edep,&e1.edepname,&e1.eloc,&e1.etele);
        if(depNum == e1.edep) {
            fseek(fpEmp,-31,SEEK_CUR);
            fprintf(fpEmp,"%15s",newName);
            fseek(fpEmp,16,SEEK_CUR);
        }
    }
    fnCloseFile(EMP_FILE);
}

/******************************************************************************
* End of DeptMaint.c
******************************************************************************/
