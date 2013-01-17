/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*    - strings.c                                                    */
/*                                                                            */
/* testing functions :                                                        */
/*    - diff( )                                 */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// std
// ---------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <errno.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "main.h"
#include "tutl.h"
#include "genlib.h"

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  // -------------------------------------------------------
  // diff two empty files
  // -------------------------------------------------------
  startTestStep( "testing diff empty" ) ;
  sysRc = diff( "test/cfg/empty.1.txt", "test/cfg/empty.2.txt" ) ;
  if( sysRc != 0 )
  {
    errTestStep( "testing diff empty" ) ;
    goto _door ;
  }
  okTestStep( "testing diff empty" ) ;

  // -------------------------------------------------------
  // first file not exist
  // -------------------------------------------------------
  startTestStep( "testing diff no file 1" ) ;
  sysRc = diff( "not_exist", "test/cfg/empty.2.txt" ) ;
  if( sysRc == 0 )
  {
    errTestStep( "testing diff no file 1" ) ;
    goto _door ;
  }
  okTestStep( "testing diff no file 1" ) ;
  sysRc = 0 ;

  // -------------------------------------------------------
  // 2nd file not exist
  // -------------------------------------------------------
  startTestStep( "testing diff no file 2" ) ;
  sysRc = diff( "test/cfg/empty.1.txt", "not_exist" ) ;
  if( sysRc == 0 )
  {
    errTestStep( "testing diff no file 2" ) ;
    goto _door ;
  }
  okTestStep( "testing diff no file 2" ) ;
  sysRc = 0 ;

  // -------------------------------------------------------
  // diff two equal files
  // -------------------------------------------------------
  startTestStep( "testing diff ok " ) ;
  sysRc = diff( "test/cfg/ok.1.txt", "test/cfg/ok.2.txt" ) ;
  if( sysRc != 0 )
  {
    errTestStep( "testing diff ok " ) ;
    goto _door ;
  }
  okTestStep( "testing diff ok " ) ;
  sysRc = 0 ;

  // -------------------------------------------------------
  // diff two equal files
  // -------------------------------------------------------
  startTestStep( "testing diff on diffrent files" ) ;
  sysRc = diff( "test/cfg/nok.1.txt", "test/cfg/nok.2.txt" ) ;
  if( sysRc != 1 )
  {
    errTestStep( "testing diff on diffrent files" ) ;
    goto _door ;
  }
  okTestStep( "testing diff on diffrent files" ) ;
  sysRc = 0 ;

_door:
  return sysRc ;
}
