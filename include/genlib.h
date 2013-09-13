/******************************************************************************/
/*                     G E N E R I C   U T I L I T I E S                      */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdio.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define NO_ERROR   0

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

// ---------------------------------------------------------
// strint.c
// ---------------------------------------------------------
#define checkFileRead(  fName ) checkFileRights( fName, R_OK ) ;
#define checkFileWrite( fName ) checkFileRights( fName, W_OK ) ;
#define checkFileExec(  fName ) checkFileRights( fName, X_OK ) ;
#define checkFileDir(   fName ) checkFileRights( fName, F_OK ) ;

// ---------------------------------------------------------
// general macros
// ---------------------------------------------------------
#define errmsg( str ) { errRc=errno ; perror( str ) ;  goto _door ; }

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

// ---------------------------------------------------------
// file.c
// ---------------------------------------------------------
int checkFileRights( const char* fName, int mode ) ;
long fileSize(       const char* fName           ) ;
int flushFile(       const char* fName           ) ;

// ---------------------------------------------------------
// string.c
// ---------------------------------------------------------
int countWords( const char* str, const int maxOffset ) ;
char* allocWord( const char* str, const int wordIndex ) ;
int flashLogLineId( char* line) ;
int flashLogLineSrc( char* line) ;
int diff( const char* file1, const char* file2 ) ;
int diffLog( const char* lFile, const char* cFile ) ;
int countChar( const char* mem, char c ) ;
char* findLastBlankStr( const char* str );
char* findLastNonBlankStr( const char* str );

// ---------------------------------------------------------
// fork.c
// ---------------------------------------------------------
int startChild( const char *prg, FILE *stdOutFp ,
                                 FILE *stdErrFp ,
                                 char **cmdLn   ) ;


