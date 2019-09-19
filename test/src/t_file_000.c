/******************************************************************************/
/*  test util                                                                 */
/*                                                                            */
/*  test: t000                                                                */
/*                                                                            */
/*  tests:                                                                    */
/*    - testing command line                                                  */
/*    - testing check file rights                                             */
/******************************************************************************/

/******************************************************************************/
/*  includes                                                                  */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own
// ---------------------------------------------------------
#include "main.h"
#include "tutl.h"
#include "genlib.h"



/******************************************************************************/
/*  defines                                                                   */
/******************************************************************************/
#define NO_FILE "/do/not/exists"


/******************************************************************************/
/*  main                                                                      */
/******************************************************************************/
int main(int argc, const char** argv )
{
#if(0)
  int rc ;
  int i ;

  tTstCfg cfg ;
#endif

  int sysRc = NO_ERROR ;

  // -------------------------------------------------------  
  // command line tests
  // -------------------------------------------------------  

#if(0)
  startTestStep( "commandLine" ) ;

  char *stdOutFile ;
  char *stdErrFile ;
  char *doneFile   ;

  sysRc = cmdLineHandler( argc, argv, &cfgFile, 
                                      &stdOutFile, 
                                      &stdErrFile, 
                                      &doneFile ) ;

  printf("config file:\t%s\n", cfgFile    );
  printf("stdout file:\t%s\n", stdOutFile );
  printf("stderr file:\t%s\n", stdErrFile );
  printf("done file:\t%s\n"  , doneFile   );

  if( sysRc != NO_ERROR ) 
  {
    errTestStep( "commandLine" ) ;
    goto _door ;
  }

  okTestStep( "commandLine" ) ;
#endif

  // -------------------------------------------------------  
  // check for not existing file
  // -------------------------------------------------------  

  startTestStep( "check file rights" ) ;

  sysRc = checkFileRights( "/do/not/exists", R_OK ) ;  
  if( sysRc != ENOENT )
  {
    errTestStep( "check file rights" ) ;
    goto _door ; 
  }
  else
  {
    sysRc = 0 ;
  }

  okTestStep( "check file rights" ) ;

  startTestStep( "check file rights" ) ;

  sysRc = checkFileRights( argv[0], R_OK|X_OK ) ;  
  if( sysRc != NO_ERROR )
  {
    errTestStep( "checking exec rights failed" );
    goto _door ;
  }

  okTestStep( "check file rights" ) ;

_door :
  return sysRc ;
}
