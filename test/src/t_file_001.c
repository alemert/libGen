/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file : file.c                                                      */
/*                                                                            */
/* testing functions :                                       */
/*   - flushFile                                                              */
/*   - fileSize                                                               */
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
#include "tutl.h"

#if(0)
#include "var/cmdl/src/cmdln.h"
#endif

#include "genlib.h"

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

  // -------------------------------------------------------
  // flush not existing file
  // -------------------------------------------------------
#if(1)
  doIntTest( "file does not exists"     , \
          22                            , \
          flushFile                    , \
          "test/cfg/not.exists"           ) ;

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

  // -------------------------------------------------------
  // get size of not existing file
  // -------------------------------------------------------
#if(1)
  doIntTest( "file not exists"    , \
          -2                      , \
          fileSize                , \
          "test/cfg/not.exists"   ) ;
#endif

  // -------------------------------------------------------
  // get size of not existing file
  // -------------------------------------------------------
#if(1)
  doIntTest( "empty file"         , \
           0                      , \
          fileSize                , \
          "test/cfg/flushed.file"   ) ;
#endif

  // -------------------------------------------------------
  // get size of some file
  // -------------------------------------------------------
#if(1)
  doIntTest( "some file"             , \
           5184                      , \
           fileSize                  , \
          "test/cfg/t_file_long.txt" ) ;
#endif


_door:
  return sysRc ;
}
