/******************************************************************************/
/*                      S T R I N G   U T I L I T I E S                       */
/*                                                                            */
/*   functions:                                                               */
/*      - countWords                                                          */
/*      - allocWord                                                           */
/*      - flashLogLineId                                                      */
/*      - flashLogLineSrc                                                     */
/*      - diff                                                                */
/*      - diffLog                                                             */
/*      - countChar                                                           */
/*      - findLastBlankStr                  */
/*      - findLastNonBlankStr              */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "genlib.h" 

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define DUMP_CMNT    "| "

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   F U N C T I O N S                                                        */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* count words                                                                */
/*                                                                            */
/* description:                                                               */
/*   count whithe space terminated words in a string                          */
/*   if maxOffset == 0 -> no checking of buffer overflow                      */
/*                                                                            */
/* return code:                                                               */
/*   >=0 : amount of words                                                    */
/*   -1  : buffer overflow                                                    */
/*   -2  : no printible char                                                  */
/*                                                                            */
/******************************************************************************/
int countWords( const char* str, const int maxOffset )
{
  int cnt=0;
  char *p ;

  // -------------------------------------------------------
  // initial test of the first byte
  // -------------------------------------------------------
  if( maxOffset < 0 )  //
  {                    // if max string length to short
    cnt = -1   ;       //   handle error
    goto _door ;       //
  }                    //
                       //
  if( *str == '\0' )   // no. of words = 0
  {                    // for empty string
    goto _door ;       //
  }                    //
                       //
  if( !isprint(*str) ) // return error (rc=-1)
  {                    // if byte not printible
    cnt = -2   ;       //
    goto _door ;       //
  }                    //
                       //
  if( !isspace(*str) ) // if first byte is not space
  {                    // there has to be at least one word
    cnt++ ;            //
  }                    //

  // -------------------------------------------------------
  // go through whole string
  // -------------------------------------------------------
  p=(char*)(str+1);
  while( *p!='\0' )
  {                                  //
    if( maxOffset > 0 )              // if buffer overflow chek on
    {                                //
      if( (p-str+2) > maxOffset )    // check buffer overflow
      {                              //  handle erro (rc=-1)
        cnt = -1   ;                 //
        goto _door ;                 //
      }                              //
    }                                //
                                     //
    if( *p == '\0' ) break ;         //  end of string -> return
                                     //
    if( !isprint(*p) )               // if byte not printible
    {                                // return error (rc=-1)
      cnt = -2   ;                   //
      goto _door ;                   //
    }                                //
                                     //
    if( !isspace( *p     ) &&        // if this byte is a non-space
         isspace( *(p-1) )  )        //   and byte prior this one is a space
    {                                // then this is a start of new word
      cnt++ ;                        //
    }                                //
    p++ ;                            // move to next byte
  }                                  //

_door:
  return cnt ;
}

/******************************************************************************/
/* allocate word                                                              */
/*                                                                            */
/*   find word (nr of word == wordIndex )                                     */
/*   allocate space for word                                                  */
/*   copy word in allocated memory                                            */
/*   return pointer to the word                                               */
/*                                                                            */
/******************************************************************************/
char* allocWord( const char* str, const int wordIndex )
{
  char *word = NULL ;
  char *wordBegin ;
  char *wordEnd   ;

  int wordCnt = 0 ;
  int wordSize ;

  // -------------------------------------------------------
  // initial test of the first byte
  // -------------------------------------------------------
  if( *str == '\0' )               // no. of words = 0
  {                                // for empty string
    goto _door ;                   //
  }                                //
                                   //
  if( !isprint(*str) )             // return error (rc=-1)
  {                                // if byte not printible
    word = NULL ;                  //
    goto _door ;                   //
  }                                //
                                   //
  if( !isspace(*str) )             // if first byte is not space
  {                                // there has to be at least one word
    wordCnt++ ;                    //
  }                                //
                                   //
  wordBegin = (char*) str ;        //
                                   //
  // -------------------------------------------------------
  // find the begin of word nr. wordIndex
  // -------------------------------------------------------
  while(1)                            //
  {                                   //
    if( wordCnt == wordIndex )        // break if th n-th word has been found
    {                                 //
      break ;                         //
    }                                 //
                                      //
    wordBegin++ ;                     // move to next byte
                                      //
    if( wordBegin == '\0' )           // no word has been found, return NULL
    {                                 //
      word = NULL ;                   //
      goto _door  ;                   //
    }                                 //
                                      //
    if( !isprint( *wordBegin ) )      // byte is not printible, return NULL
    {                                 //
      word = NULL ;                   //
      goto _door  ;                   //
    }                                 //
                                      //
    if( !isspace( *wordBegin    ) &&  // this byte is non-space
         isspace( *(wordBegin-1))  )  //  byte prior this one is a space
    {                                 //  -> begin of new word
      wordCnt++ ;                     //   -> incr word counter
    }                                 //
  }                                   //
                                      //
  // -------------------------------------------------------
  // find the end of word nr. wordIndex
  // -------------------------------------------------------
  wordEnd = wordBegin + 1 ;           // start searching for the end of the word
                                      //
  while(1)                            //
  {                                   //
    if( *wordEnd == '\0' )            // the end of str has been reached
    {                                 //
      break ;                         //
    }                                 //
                                      //
    if( !isprint(*wordEnd) )          // non printible char -> return NULL
    {                                 //
      word = NULL ;                   //
      goto _door  ;                   //
    }                                 //
                                      //
    if(  isspace( *wordEnd    ) &&    // this byte is a space
        !isspace( *(wordEnd-1))  )    //  byte prior this one is a non-space
    {                                 //  -> end of the word
      break ;                         //
    }                                 //
                                      //
    wordEnd++ ;                       // move to next byte
  }                                   //
                                      //
  // -------------------------------------------------------
  // alloc and copy the word
  // -------------------------------------------------------
  wordSize = (wordEnd - wordBegin ) ;
  word    = (char*) malloc( (wordSize+1) * sizeof(char) ) ;
  memcpy( word, wordBegin, wordSize ) ;
  word[wordSize] = '\0' ;

_door :
  return word ;
}

/******************************************************************************/
/* flash log file line id                                                     */
/*                                                                            */
/*  0         1         2         3                                           */
/*  0123456789 123456789 123456789 123456789 123456789 123456789              */
/* "2013-01-15 14:49:27  30178 00100 SYS starting t_ctl_000                   */
/*                                                                            */
/* description:                                                               */
/*    flash log line with id                                                  */
/******************************************************************************/
int flashLogLineId( char* line) 
{
  int sysRc = 1 ;
  int i ;
  
  for(i=0;i<4;i++)                           // YYYY
  {                                          //
    if(  !isdigit( line[i] ) ) goto _door ;  //
    line[i] = ' ' ;                          //
  }                                          //
  if( line[4] != '-' )  goto _door ;         // '-'
  line[4] = ' ' ;                            //
                                             //
  for(i=5;i<7;i++)                           // MM
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
  if( line[7] != '-' )  goto _door ;         // '-'
  line[7] = ' ' ;                            //
                                             //
  for(i=8;i<10;i++)                          // DD
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
  if( line[10] != ' ' )  goto _door ;        // blank
                                             //
  for(i=11;i<13;i++)                         // hh
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
  if( line[13] != ':' )  goto _door ;        // :
  line[13] = ' ' ;                           //
                                             //
  for(i=14;i<16;i++)                         // mm
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
  if( line[16] != ':' )  goto _door ;        // :
  line[16] = ' ' ;                           //
                                             //
  for(i=17;i<19;i++)                         // ss
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
                                             //
  for(i=19;i<25;i++)                         // blanks
  {                                          //
    if( line[i] == ' ' ) continue ;          //
    break ;                                  //
  }                                          //
                                             //
  for(;i<26;i++)                             // pid
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
                                             //
  if( line[26] != ' ' )  goto _door ;        // blank
                                             //
  #if(0)                                     // all fourther chars have to 
  for(;i<32;i++)                             //   be equal
  {                                          //
    if( !isdigit( line[i] ) ) goto _door ;   //
    line[i] = ' ' ;                          //
  }                                          //
  #endif                                     //
                                             //
  sysRc = 0 ;                                //
                                             //
  _door :

  return sysRc ;
}

/******************************************************************************/
/* flash log file line source                                                 */
/*                                                                            */
/* description:                                                               */
/*   check for a log file matching /^\s{37}func() in src/name.t (line \d+)$/  */
/* return code:                                                               */
/*   0 = type match                                                           */
/*   1 = none matching                                                        */
/******************************************************************************/
int flashLogLineSrc( char* line) 
{
  int sysRc = 1 ;
  int i ;
  int loop ;

  for( i=0; i<37; i++ )                    // check for blanks at start 
  {                                        //   of the line
    if( line[i] != ' ' ) goto _door ;      //
  }                                        //
                                           //
  loop = 1 ;                               //
  while( loop )                            // check for the function name
  {                                        //
    switch( line[i] )                      //
    {                                      //
      case '('  :                          // a function name ends with ()
      {                                    //
        loop = 0 ;                         //
        i++ ;                              //
        break ;                            //
      }                                    //
      case ' '  : goto _door ;             // chars not possible in a func name
      case '\n' : goto _door ;             //
      case '\0' : goto _door ;             //
      default :                            //
      {                                    //
        i++ ;                              //
        continue ;                         //
      }                                    //
    }                                      //
  }                                        //
                                           //
  if( line[i] != ')' ) goto _door ; i++ ;  // end of function name
  if( line[i] != ' ' ) goto _door ; i++ ;  // " in src/"
  if( line[i] != 'i' ) goto _door ; i++ ;  //
  if( line[i] != 'n' ) goto _door ; i++ ;  //
  if( line[i] != ' ' ) goto _door ; i++ ;  //
  if( line[i] != 's' ) goto _door ; i++ ;  //
  if( line[i] != 'r' ) goto _door ; i++ ;  //
  if( line[i] != 'c' ) goto _door ; i++ ;  //
  if( line[i] != '/' ) goto _door ; i++ ;  //
                                           //
  loop = 1 ;                               //
  while( loop )                            // check for the 
  {                                        //  base source file name
    switch( line[i] )                      //
    {                                      //
      case ' '  :                          // a function name ends with ()
      {                                    //
        i++ ;                              //
        loop = 0 ;                         //
        break ;                            //
      }                                    //
      case '('  : goto _door ;             // chars not possible in a file name
      case ')'  : goto _door ;             // 
      case '\n' : goto _door ;             //
      case '\0' : goto _door ;             //
      default :                            //
      {                                    //
        i++ ;                              //
        continue ;                         //
      }                                    //
    }                                      //
  }                                        //
                                           //
  if( line[i] != '(' ) goto _door ; i++ ;  // "(line: "
  if( line[i] != 'l' ) goto _door ; i++ ;  // 
  if( line[i] != 'i' ) goto _door ; i++ ;  // 
  if( line[i] != 'n' ) goto _door ; i++ ;  // 
  if( line[i] != 'e' ) goto _door ; i++ ;  // 
  if( line[i] != ':' ) goto _door ; i++ ;  // 
  if( line[i] != ' ' ) goto _door ; i++ ;  // 
                                           //
  if( !isdigit(line[i]) ) goto _door ;     //
  line[i] = ' ' ;                          //
  i++ ;                                    //
                                           //
  while( isdigit( line[i] ) )              //
  {                                        //
    line[i] = ' ' ;                        //
    i++ ;                                  //
  }                                        //
                                           //
  if( line[i] != ')' ) goto _door ;        // "(line: "
                                           //
  sysRc = 0 ;

  _door :

  return sysRc ;
}


/******************************************************************************/
/*   diff files                                                               */
/******************************************************************************/
int diff( const char* file1, const char* file2 )
{
  int errRc = NO_ERROR ;              // buffer for errno
                                      //
  FILE *fp1 = NULL ;                         // 1st file pointer
  FILE *fp2 = NULL ;                         // 2nd file pointer
                                      //
  char buff1[1024] ;                  // read buffer for the 1st file
  char buff2[1024] ;                  // read buffer for the 2nd file
                                      //
  char* rc1 ;                         // return code for calls on 1st file
  char* rc2 ;                         // return code for calls on 2nd file
                                      //
  fp1 = fopen( file1, "r" ) ;         // 
  if( fp1 == NULL ) errmsg( file1 ) ; //
                                      //
  fp2 = fopen( file2, "r" ) ;         //
  if( fp2 == NULL ) errmsg( file2 ) ; //
                                      //
  while( 1 )                          //
  {                                   //
    rc1 = fgets(buff1,1024,fp1) ;     // read 1k from 1st file
    rc2 = fgets(buff2,1024,fp2) ;     // read 1k from 1st file
                                      //
    if( rc1 == NULL ) break ;         // eof 1st file
    if( rc2 == NULL ) break ;         // eof 2nd file
                                      //
    if( strcmp( (const char*) buff1, (const char*)  buff2 ) != 0 )
    {                                 // compare both buffer
      errRc = 1  ;                    // if diffrent 
      goto _door ;                    // return error 1 => files diffrent
    }                                 //
  }                                   //
                                      //
  if( !feof( fp1 ) )                  // if eof(fp2) but not eof(fp1)
  {                                   //   return erro 2 => diffrent length 
    errRc = 2  ;                      //                      of files
    goto _door ;                      //
  }                                   //
                                      //
  if( !feof( fp2 ) )                  // if eof(fp2) but not eof(fp1)
  {                                   //   return erro 2 => diffrent length
    errRc = 2  ;                      //                      of files
    goto _door ;                      //
  }                                   //
                                      //
_door :
  if( fp1 != NULL ) fclose( fp1 ) ;
  if( fp2 != NULL ) fclose( fp2 ) ;

  return errRc ;
}

/******************************************************************************/
/*   diff log files                                                           */
/******************************************************************************/
int diffLog( const char* lFile, const char* cFile )
{
  int errRc = NO_ERROR ;                  // buffer for errno
                                          //
  FILE *lFP ;                             // log file pointer
  FILE *cFP ;                             // compaire file pointer
                                          //
  char lBuff[1024] ;                      // read buffer for the log file
  char cBuff[1024] ;                      // read buffer for the compaire file
                                          //
  char* lRC ;                             // return code for calls on log file
  char* cRC ;                             // return code for calls on cmp file
                                          //
  int lTypeId ;                           // line type log file (log or normal)
  int cTypeId ;                           // line type cmp file (log or normal)
                                          //
  int lTypeSrc ;                          // line type log file (log or normal)
  int cTypeSrc ;                          // line type cmp file (log or normal)
                                          //
  lFP = fopen( lFile, "r" ) ;             // 
  if( lFP == NULL ) errmsg( lFile ) ;     //
                                          //
  cFP = fopen( cFile, "r" ) ;             //
  if( cFP == NULL ) errmsg( cFile ) ;     //
                                          //
  while( 1 )                              //
  {                                       //
    lRC = fgets(lBuff,1024,lFP) ;         // read up to 1k from log file
    cRC = fgets(cBuff,1024,cFP) ;         // read up to 1k from cmp file
                                          //
    if( lRC == NULL ) break ;             // eof log file
    if( cRC == NULL ) break ;             // eof cmp file
                                          //
    lTypeId = flashLogLineId( lBuff ) ;   // adjust log file format to spaces, 
    cTypeId = flashLogLineId( cBuff ) ;   //  get the type of file 
                                          //  (log file or not)
    lTypeSrc = flashLogLineSrc( lBuff ) ; // adjust log file format to spaces, 
    cTypeSrc = flashLogLineSrc( cBuff ) ; //  get the type of file 
                                          //  (log file or not)
    if( memcmp( lBuff, DUMP_CMNT ,        //
                strlen(DUMP_CMNT)) == 0 &&// check if it is a dump 
        memcmp( cBuff, DUMP_CMNT ,        //  if so go back to the start of the
                strlen(DUMP_CMNT)) == 0  )//  loop
    {                                     //
      continue ;                          //
    }                                     //
                                          //
    if( lTypeId  != cTypeId  &&           // compare the type of line in log and
        lTypeSrc != cTypeSrc  )           //   compaire file, if not same 
    {                                     //
      errRc = 3  ;                        //   return error
      goto _door ;                        //
    }                                     //
                                          //
    if( strcmp( (const char*) lBuff,      //
                (const char*) cBuff )     //
        != 0 )                            //
    {                                     // compare both buffer
      errRc = 1  ;                        // if diffrent 
      goto _door ;                        // return error 1 => files diffrent
    }                                     //
  }                                       //
                                          //
  if( !feof( lFP ) )                      // if eof(fp2) but not eof(fp1)
  {                                       //   return erro 2 => diffrent length 
    errRc = 2  ;                          //                      of files
    goto _door ;                          //
  }                                       //
                                          //
  if( !feof( cFP ) )                      // if eof(fp2) but not eof(fp1)
  {                                       //   return erro 2 => diffrent length
    errRc = 2  ;                          //                      of files
    goto _door ;                          //
  }                                       //
                                          //
_door :
  if( cFP != NULL ) fclose( cFP ) ;
  if( lFP != NULL ) fclose( lFP ) ;

  return errRc ;
}

/******************************************************************************/
/* count char                                                                 */
/*                                                                            */
/*   count char c in string mem                              */
/******************************************************************************/
int countChar( const char* mem, char c )
{
  char *p  = (char*) mem ;
  int  cnt = 0   ;

  while( *p != '\0' )
  {
    if( *p == c ) cnt++ ;
    p++ ;
  }

  return cnt ;
}

/******************************************************************************/
/* find last blank in string                                                  */
/*                                                                            */
/*   ignore all leading blanks in string,                                     */
/*   return pointer to the last non-blank.                                    */
/*   if first char is non-blank, return NULL                                  */
/******************************************************************************/
char* findLastBlankStr( const char* str )
{
  char *p = (char*) str ;

  if( ( *str != ' '  && *str != '\t' ) ||
      *str == '\0'  )
  {
    p = NULL;
    goto _door;
  }

  while( 1 )
  {
    p++;
    switch( *p )
    {
      case ' '  :
      case '\t' :
      {
        continue ;
      }
      case '\0' : 
      {
        p = NULL;
        goto _door;
      }
      default   : 
      {
        p--;
        goto _door;
      }
    }
  }

  _door:
  return p;  
}

/******************************************************************************/
/* find last non-blank in string                                              */
/*                                                                            */
/*   find the end of the string, go backwards to the last non-blank.          */
/*   if strinng empty return NULL                                             */
/*   if last char is non-blank return NULL, this functionality is needed      */
/*    by libXym                                                               */
/******************************************************************************/
char* findLastNonBlankStr( const char* str )
{
  char *p = (char*) str ;
  
  if( p  == NULL ||             // check for initial values
      *p == '\0'  )             // return NULL for empty string
  {                             //
    p = NULL;                   //
    goto _door;                 //
  }                             //
                                //
  while( *p != '\0' )           // goto to the end of the string
  {                             //
    p++ ;                       //
  }                             //
                                //
  p--;                          //
  switch( *p )                  // check if the last char of the string 
  {                             //
    case ' ' : break ;          //  is a blank
    case '\t': break ;          //
    default  :                  //
    {                           //
      p = NULL;                 // if not return NULL
      goto _door;               //
    }                           //
  }                             //
                                //
  while( p != str )             // go backwards until start of string
  {                             //
    switch( *p )                //
    {                           //
      case ' ' :                //
      case '\t':                //
      {                         //
        p--;                    //
        break;                  //
      }                         //
      default :                 // no-blank found
      {                         //
        goto _door;             //
      }                         //
    }                           //
  }                             //
                                //
  if( p == str )                // complete string is non-blank 
  {                             //
    p = NULL;                   //
    goto _door;                 //
  }                             //
                                //
  _door:
  return p;
}
