/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c                                                                  */
/*                                                                            */
/* testing functions :                                                        */
/*   - iniReader                                                              */
/*   - iniHandleOpenTag                                                       */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
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
#include <tutl.h>

#include <genlib.h>

/******************************************************************************/
/*   M A I N                                                                  */
/******************************************************************************/
int main( int argc, const char** argv )
{
  int sysRc = NO_ERROR ;

//sysRc = initLogging( "test/log/t_string_002.log", INF ) ;
//if( sysRc != 0 ) goto _door ;

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "full string"      , \
                 RC_IS_NULL         , \
                  findLastBlankStr  , \
                  "hello world"     ) ;

    checkMessage( TEST_OK_TXT, findLastBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "blank full string"      , \
                 RC_NOT_NULL         , \
                  findLastBlankStr  , \
                  "  hello world"     ) ;

    char* result = (char*) gRcVoidPointer ;
    printf( "%s\n", (result+1) );

    checkMessage( TEST_OK_TXT, findLastBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "empty string"      , 
                 RC_IS_NULL         , 
                  findLastBlankStr  , 
                  ""     ) ;

    checkMessage( TEST_OK_TXT, findLastBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "blank string"      , \
                 RC_IS_NULL         , \
                  findLastBlankStr  , \
                  "      "     ) ;

    checkMessage( TEST_OK_TXT, findLastBlankStr ) ;
  }
#endif

_door:
  return sysRc ;
}
