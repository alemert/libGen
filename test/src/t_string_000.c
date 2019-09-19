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

//char *cfgFile    ;

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
  // testing countWords
  // -------------------------------------------------------

  // -------------------------------------------------------
  startTestStep( "count words empty sring" ) ;

  if( countWords("",0) != 0 )
  {
    errTestStep( "count words empty sring" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words empty sring" ) ;

  // -------------------------------------------------------
  startTestStep( "count words buffer overflow" ) ;
  
  if( countWords("",-1) != -1 )
  {
    errTestStep( "count words buffer overflow" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words buffer overflow" ) ;

  // -------------------------------------------------------
  startTestStep( "count words one word" ) ;

  if( countWords("hello",sizeof("hello")) != 1 )
  {
    errTestStep( "count words one word" ) ;
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words one word" ) ;

  // -------------------------------------------------------
  startTestStep( "count words one word" ) ;
  
  if( countWords(" hello ",sizeof(" hello   ")) != 1 )
  {
    errTestStep( "count words one word" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words one word" ) ;

  // -------------------------------------------------------
  startTestStep( "count words buffer overflow" ) ;
  
  if( countWords(" hello ",(sizeof(" hello ")-1)) != -1 )
  {
    errTestStep( "count words buffer overflow" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words buffer overflow" ) ;

  // -------------------------------------------------------
  startTestStep( "count words two words" ) ;
  
  if( countWords("hello world",255) != 2 )
  {
    errTestStep( "count words two words" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words two words" ) ;

  // -------------------------------------------------------
  startTestStep( "count words multiple blanks" ) ;

  if( countWords("hello   world",255) != 2 )
  {
    errTestStep( "count words multiple blanks" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words multiple blanks" ) ;

  // -------------------------------------------------------
  startTestStep( "count words non pritible" ) ;
  
  if( countWords("hello  world",255) != -2 )
  {
    errTestStep( "count words non pritible" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "count words non pritible" ) ;

  // -------------------------------------------------------
  // testing getting words
  // -------------------------------------------------------
  char *word ;

  // -------------------------------------------------------
  startTestStep( "alloc word empty string" ) ;
  
  word = allocWord( "", 1 ) ;
  if( word != NULL )
  {
    errTestStep( "alloc word empty string" ) ;
    printf("err\n");
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "alloc word empty string" ) ;

  // -------------------------------------------------------
  startTestStep( "alloc word blank string" ) ;
  
  word = allocWord( "    ", 1 ) ;
  if( word != NULL )
  {
    errTestStep( "alloc word blank string" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "alloc word blank string" ) ;
 
  // -------------------------------------------------------
  startTestStep( "alloc word test one word" );
  
  word = allocWord( "hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word test one word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one word" );

  // -------------------------------------------------------
  startTestStep( "alloc word test one word" );
 
  word = allocWord( " hello", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word test one word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one word" );

  // -------------------------------------------------------
  startTestStep( "alloc word test one letter" );
  
  word = allocWord( "a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word test one letter" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word test one letter" );

  // -------------------------------------------------------
  startTestStep( "alloc word blank - one letter" );

  word = allocWord( " a", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word blank - one letter" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word blank - one letter" );

  // -------------------------------------------------------
  startTestStep( "alloc word one letter - blank" );

  word = allocWord( "a ", 1 ) ;
  if( memcmp("a",word,sizeof("a") ) != 0 )
  {
    errTestStep( "alloc word one letter - blank" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word one letter - blank" );

  // -------------------------------------------------------
  startTestStep( "alloc word first out of two word" );
  
  word = allocWord( "hello world", 1 ) ;
  if( memcmp("hello",word,sizeof("hello") ) != 0 )
  {
    errTestStep( "alloc word first out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word first out of two word" );

  // -------------------------------------------------------
  startTestStep( "alloc word secound out of two word" );
  
  word = allocWord( " hello world", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    errTestStep( "alloc word secound out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word secound out of two word" );

  // -------------------------------------------------------
  startTestStep( "alloc word secound out of two word" );
  
  word = allocWord( " hello   world  ", 2 ) ;
  if( memcmp("world",word,sizeof("world") ) != 0 )
  {
    errTestStep( "alloc word secound out of two word" );
    sysRc = 1 ;
    goto _door ;
  }
  free(word) ;

  okTestStep( "alloc word secound out of two word" );

  // -------------------------------------------------------
  // flash log line
  // -------------------------------------------------------
  char line[1024] ;

  // -------------------------------------------------------
  startTestStep( "flash log line ok case" ) ;

  #define LOG_STR_1 "2012-07-13 21:25:41  11038 00100 SYS starting t"
  #define LOG_CMP_1 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_1 , sizeof(LOG_STR_1) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 1 )
  {
    errTestStep( "flash log line ok case" ) ;
    goto _door ; 
  }
  if( memcmp(line, LOG_CMP_1, sizeof(LOG_CMP_1) ) != 0 )
  {
    errTestStep( "flash log line ok case" ) ;
    sysRc = 1 ;
    goto _door ; 
  }
  okTestStep( "flash log line ok case" ) ;

  // -------------------------------------------------------
  startTestStep( "flash log line err case" ) ;

  #define LOG_STR_2 "201a-07-13 21:25:41  11038 00100 SYS starting t"
  #define LOG_CMP_2 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_2 , sizeof(LOG_STR_2) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 0 )
  {
    errTestStep( "flash log line err case" ) ;
    goto _door ; 
  }
  sysRc = 0 ;
  if( memcmp(line, LOG_CMP_2, sizeof(LOG_CMP_2) ) == 0 )
  {
    errTestStep( "flash log line err case" ) ;
    sysRc = 1 ;
    goto _door ; 
  }
  okTestStep( "flash log line err case" ) ;

  // -------------------------------------------------------
  startTestStep( "flash log line ok case" ) ;

  #define LOG_STR_3 "2012-07-13 21:25:41      8 00100 SYS starting t"
  #define LOG_CMP_3 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_3 , sizeof(LOG_STR_3) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 1 )
  {
    errTestStep( "flash log line ok case" ) ;
    goto _door ;
  }
  if( memcmp(line, LOG_CMP_3, sizeof(LOG_CMP_3) ) != 0 )
  {
    errTestStep( "flash log line ok case" ) ;
    sysRc = 1 ;
    goto _door ;
  }

  okTestStep( "flash log line ok case" ) ;

  // -------------------------------------------------------
  startTestStep( "flash log line err case no pid" ) ;

  //                 2013-01-15 14:49:27  30178 00100 SYS starting t_ctl_000
  #define LOG_STR_4 "2012-07-13 21:25:41        00100 SYS starting t"
  #define LOG_CMP_4 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_4 , sizeof(LOG_STR_4) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 0 )
  {
    errTestStep( "flash log line err case" ) ;
    goto _door ;
  }
  sysRc = 0 ;

  if( memcmp(line, LOG_CMP_4, sizeof(LOG_CMP_4) ) != 0 )
  {
    errTestStep( "flash log line err case" ) ;
    sysRc = 1 ;
    goto _door ;
  }
  okTestStep( "flash log line err case no pid" ) ;

  // -------------------------------------------------------
  startTestStep( "flash log line err case no blank after pid" ) ;

  //                 2013-01-15 14:49:27  30178 00100 SYS starting t_ctl_000
  #define LOG_STR_5 "2019-07-13 21:25:41  11038x00100 SYS starting t"
  #define LOG_CMP_5 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_5 , sizeof(LOG_STR_5) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 0 )
  {
    errTestStep( "flash log line err case no blank after pid" ) ;
    goto _door ;
  }
  sysRc = 0 ;
  okTestStep( "flash log line err case no blank after pid" ) ;

  // -------------------------------------------------------
  startTestStep( "flash log line check log id" );

  //                 2013-01-15 14:49:27  30178 00100 SYS starting t_ctl_000
  #define LOG_STR_6 "2019-07-13 21:25:41  11038 00100 SYS starting t"
  #define LOG_CMP_6 "                           00100 SYS starting t"

  memcpy( line, LOG_STR_6 , sizeof(LOG_STR_6) ) ;
  sysRc = flashLogLineId(line) ;
  if( sysRc == 1 )
  {
    errTestStep( "flash log line check log id" );
    goto _door ;
  }
  okTestStep( "flash log line check log id" );

_door :
  return sysRc ;
}
