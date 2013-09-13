/******************************************************************************/
/* test c source template                                                     */
/*                                                                            */
/* testing file :                                                             */
/*  reader.c                                                                  */
/*                                                                            */
/* testing functions :                                                        */
/*   - findLastNonBlankStr                                                    */
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
    doPointTest( "full string"         , \
                 RC_IS_NULL            , \
                  findLastNonBlankStr  , \
                  "hello world"        ) ;

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "full string blank"      , \
                 RC_IS_NULL         , \
                  findLastNonBlankStr  , \
                  "  hello world"     ) ;

//  char* result = (char*) gRcVoidPointer ;
//  printf( "%s\n", (result+1) );

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "empty string"      , 
                 RC_IS_NULL         , 
                  findLastNonBlankStr  , 
                  ""     ) ;

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "blank string"      , \
                 RC_IS_NULL         , \
                  findLastNonBlankStr  , \
                  "      "     ) ;

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "blank char"      , \
                 RC_IS_NULL         , \
                  findLastNonBlankStr  , \
                  " "     ) ;

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "hello world"      , \
                 RC_NOT_NULL         , \
                  findLastNonBlankStr  , \
                  " hello world "     ) ;

    char* result = (char*) gRcVoidPointer ;
    printf( ">%s<\n", (result) );

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

  // -------------------------------------------------------
  // no file found
  // -------------------------------------------------------
  #if(1)
  {
    doPointTest( "hello world"      , \
                 RC_NOT_NULL         , \
                  findLastNonBlankStr  , \
                  " hello world      "     ) ;

    char* result = (char*) gRcVoidPointer ;
    printf( ">%s<\n", (result) );

    checkMessage( TEST_OK_TXT, findLastNonBlankStr ) ;
  }
#endif

_door:
  return sysRc ;
}
