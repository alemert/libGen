/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file : file.c                                                      */
/*                                                                            */
/* testing functions :                                       */
/*   - mkdirRecrusive                                        */
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
#include <libgen.h>
#include <sys/stat.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "tutl.h"

#if(0)
#include "var/cmdl/src/cmdln.h"
#endif

#include <genlib.h>
#include <limits.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( )
{
  int sysRc = NO_ERROR ;

  // -------------------------------------------------------
  // flush not existing file
  // -------------------------------------------------------
  doIntTest( "empty path"   , \
          0                 , \
          mkdirRecursive    , \
          NULL, 0           ) ;
#if(1)
  doIntTest( "existing path", \
          0                 , \
          mkdirRecursive    , \
          "/tmp", 0           ) ;
#endif
  int pid = getpid() ;
  char path[NAME_MAX] ;
  sprintf(path,"/tmp/%d",pid);
  

  doIntTest( "single path", \
          0                 , \
          mkdirRecursive    , \
          path, 755           ) ;

  sprintf(path,"/tmp/%d/%d",--pid,pid);

  doIntTest( "double path", \
          0                 , \
          mkdirRecursive    , \
          path, 755           ) ;
#if(0)
  // -------------------------------------------------------
  // flush no writing rights file
  // -------------------------------------------------------
  doIntTest( "no writing rights on file" , \
          13                             , \
          flushFile                      , \
          "test/cfg/no_writting.right"   ) ;

  // -------------------------------------------------------
  // flush no writing rights file
  // -------------------------------------------------------
  doIntTest( "open file for writing failed"  , \
          13                                 , \
          flushFile                          , \
          "test/cfg/no_writing.dir"          ) ;

  // -------------------------------------------------------
  // flush no writing rights file
  // -------------------------------------------------------
  doIntTest( "file flushed ok"      , \
          0                         , \
          flushFile                 , \
          "test/cfg/flushed.file"   ) ;
#endif

_door:
  return sysRc ;
}
