/******************************************************************************
* Filename    : FileFunctions.h
* Author      : Education & Research Dept, Infosys Technologies Limited
* Date        : 24-Feb-2005
* Description : Declaration of functions and constants required to use the
*               functions defined in FileFunctions.c
* Modification Log:
******************************************************************************/

/* Pre-defined constants */

/* Constants to choose Dept file or Employee file */
#define DEP_FILE 1
#define EMP_FILE 2
#define TELE_FILE 3

/* Constants to define position in file */
#define BEGIN 0
#define CURRENT 1

/* Length of records */
#define EMP_RECLEN 50
#define DEPT_RECLEN 50

FILE *fpDept;
FILE *fpEmp;
FILE *fpTele;

/* Function declarations */

int fnOpenFile ( int iFile );
int fnReadFile ( char acLine[], int iFile, int ipos);
void fnWriteFile ( char acLine[], int iFile);
int fnUpdateFile ( char acLine[], int iFile);
int fnCloseFile ( int iFile);

/* Forward declaration of functions defined in DeptMaint.c */
int fnInitializeDeptCode();
void fnAddNewDepartment();
void fnPrintDept();
void fnDispAddNewDepartment();
void fnChangeDepName();
/* Forward declaration of functions defined in EmpMaint.c */
int fnInitializeEmpCode();
void fnAddNewEmp();
void fnPrintEmp();
void fnAddTeleNum();
void fnDispAddNewEmp();
void fnDispAddTeleNum();
void fnChangeEmpName();
void fnChangeEmpLoc();
void fnChangeEmpDepartment();
int fnIncrementDepTele(int);
/* Forward declaration of functions defined in TeleEnq.c */
void fnEnqByTeleNum();
void fnEnqByName();
void fnDispEnqByName();

/*Function prototype*/
void fnMainMenu ();
void fnDepartmentMenu();
void fnEmpMenu();
void fnTeleEnqMenu();
void fnTeleDirMenu();
void fnLogin();
void fnLoginValidate(int acUserId);
void clearscreen();

/******************************************************************************
* End of FileFunctions.h
******************************************************************************/
