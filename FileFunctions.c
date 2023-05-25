/******************************************************************************
* Filename    : FileFunctions.c
* Author      : Education & Research Dept, Infosys Technologies Limited
* Date        : 24-Feb-2005
* Description : Contains the functions required for reading records from files.
*   Part of Programming Fundamentals file
* Modification Log:
*   24-Feb-2005: Nagendra: Modified for adherance to coding standards
*                and guidelines
******************************************************************************/

/* Include files */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Declaration of functions and constants used */
#include "FileFunctions.h"

/******************************************************************************
* Function: fnOpenFile
* Description: Opens a file specified by the parameter. Looks for the file
*		in the current working directory.
* Input Parameters:
* 	int iFile - The file to be opened. Can have values
*		DEP_FILE - Opens Department file (dept.txt)
*		EMP_FILE - Opens Employee file (emp.txt)
* Returns : Zero on success. 1 if an error occurs when opening a file
******************************************************************************/

int fnOpenFile ( int iFile )
{
	char acFileName[20];

	switch (iFile) {

		case DEP_FILE:
			strcpy (acFileName, "dept.txt");
			fpDept = fopen(acFileName, "r+");
			if (NULL == fpDept) {
				return 1;
			}
			break;

		case EMP_FILE:
			strcpy (acFileName, "emp.txt");
			fpEmp = fopen(acFileName, "r+");
			if (NULL == fpEmp) {
				return 1;
			}
			break;

        case TELE_FILE:
            strcpy (acFileName, "tele.txt");
			fpTele = fopen(acFileName, "r+");
			if (NULL == fpTele) {
				return 1;
			}
			break;

		default:
			return 1;
			break;
	}
	return 0;
}

/******************************************************************************
* Function: fnReadFile
* Description: Reads a record (one line) from the file into parameter acLine[]
* Input Parameters:
* 	char acLine[] - character array into which the record is read into
* 	int iFile - The file from which record has to be read from. Can have values
*		DEP_FILE - reads from Department file (dept.txt)
*		EMP_FILE - reads from Employee file (emp.txt)
*	int iPos - The record number to be read. Can have values
*		BEGIN - The first record. Resets cursor position and reads first record.
*		CURRENT - Current record. Increments the cursor position after reading.
* Returns : Zero on Success. 1 on error.
******************************************************************************/

int fnReadFile ( char acLine[], int iFile, int ipos)
{
	switch (iFile) {

		case DEP_FILE:
			if (ipos == BEGIN){
				if (fseek(fpDept, 0L, SEEK_SET)){
					return 1;
				}
			}
			if ( NULL == fgets (acLine, DEP_FILE , fpDept) ){
				return 1;
			}
			break;

		case EMP_FILE:
			if (ipos == BEGIN) {
				if (fseek(fpEmp, 0L, SEEK_SET)) {
					return 1;
				}
			}
			if ( NULL == fgets (acLine, EMP_RECLEN, fpEmp) ) {
				return 1;
			}
			break;

		default:
			return 1;
			break;
	}
	return 0;
}

/******************************************************************************
* Function: fnWriteFile
* Description: Adds a record (one line) from the array acLine[] into a file
*              specified by parameter iFile
* Input Parameters:
* 	char acLine[] - character array whose contents have to be written
* 	int iFile - The file into which record has to be added. Can have values
*		DEP_FILE - reads from Department file (dept.txt)
*		EMP_FILE - reads from Employee file (emp.txt)
******************************************************************************/

void fnWriteFile ( char acLine[], int iFile)
{

	switch (iFile)
	{
		case DEP_FILE:

			fseek(fpDept, 0L, SEEK_END);

			fprintf(fpDept, "%s\n", acLine);
			break;

		case EMP_FILE:

			fseek(fpEmp, 0L, SEEK_END);
			fprintf (fpEmp, "%s\n", acLine);
			break;
	}

}

/******************************************************************************
* Function: fnUpdateFile
* Description: Updates the record read by fiReadFile
* Input Parameters:
* 	char acLine[] - character array into which the record is read into
* 	int iFile - The file from which record has to be read from. Can have values
*		DEP_FILE - reads from Department file (dept.txt)
*		EMP_FILE - reads from Employee file (emp.txt)
* Returns:  Zero on success. 1 on error.
******************************************************************************/

int fnUpdateFile ( char acLine[], int iFile)
{
	long lRec_dept;
	long lRec_emp;
	lRec_dept = 16;
	lRec_emp = 45+2;
	switch (iFile)
	{
		case DEP_FILE:
			if (fseek(fpDept, -lRec_dept, SEEK_CUR)) {
				return 1;
			}
			fprintf (fpDept, "%s", acLine);
			fflush(fpDept);
			break;

		case EMP_FILE:
			if (fseek(fpEmp, -lRec_emp, SEEK_CUR)) {
				return 1;
			}
			fprintf (fpEmp, "%s", acLine);
			fflush(fpEmp);
			break;

		default:
			return 1;
			break;
	}

	return 0;
}

/******************************************************************************
* Function: fnCloseFile
* Description: Closes the file specified in the parameter.
* Input Parameters:
* 	int iFile - The file which has to be closed. Can have values
*		DEP_FILE - reads from Department file (dept.txt)
*		EMP_FILE - reads from Employee file (emp.txt)
* Returns: Zero on success. 1 on error
******************************************************************************/

int fnCloseFile ( int iFile)
{
	switch (iFile)
	{
		case DEP_FILE:
			if (fclose (fpDept)) {
				return 1;
			}
			break;

		case EMP_FILE:
			if (fclose (fpEmp)) {
				return 1;
			}
			break;

        case TELE_FILE:
            if (fclose (fpTele)) {
				return 1;
			}
			break;

		default:
			return 1;
			break;
	}

	return 0;
}

/******************************************************************************
* End of FileFunctions.c
******************************************************************************/
