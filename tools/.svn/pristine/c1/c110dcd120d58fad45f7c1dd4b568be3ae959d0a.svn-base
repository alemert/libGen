#!/usr/bin/perl

use strict ;

my $cfgFile ;
my $cFile ;
my $hFile ;
my $fileType ;
my @library  ;

my $majorHelpFormat = "  ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<~~
" ;
my $minorHelpFormat1 = "   -@,--@<<<<<<<<<<<<<<<:-:";
my $minorHelpFormat2 = "                        ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<~~
" ;

################################################################################
# globals
################################################################################
my $cmd_long_name_length = 16 ;
#my $cmd_help_length = 124 ;

my $cond_opr_or    = '|' ;
my $cond_opr_and   = '&' ;
my $cond_opr_xor   = '^' ;
my $cond_opr_nor   = 'o' ;
my $cond_opr_nand  = 'a' ;
my $cond_opr_nxor  = 'x' ;
my $cond_opr_if    = 'i' ;
my $cond_opr_gt    = '>' ;
my $cond_opr_lt    = '<' ;
my $cond_opr_eq    = '=' ;

my $macroArgcStr   = 'argc' ;
my $macroArgcId    = 1    ;

################################################################################
# command line
################################################################################
my $majorFlag ;
my $historyFlag ;
my $help ;

while( defined $ARGV[0] )
{    
                                   #
  if( $ARGV[0] =~ s/^-(\w)$/$1/ )  #
  {                                #
    $majorFlag = $ARGV[0] ;        #
    $historyFlag = $majorFlag ;    #
    shift @ARGV ;                  #
    next ;                         #
  }                                #
                                   #
  if( $majorFlag eq 't' )          # type ( c or h )
  {                                #
    $fileType = $ARGV[0] ;         #
    $majorFlag = '' ;              #
    shift @ARGV ;                  #
    next ;                         #
  }                                #
                                   #
  if( $majorFlag eq 'c' )          # c output file
  {                                #
    $cFile = $ARGV[0] ;            #
    $majorFlag = '' ;              #
    shift @ARGV ;                  #
    next ;                         #
  }                                #
                                   #
  if( $majorFlag eq 'h' )          # h output file
  {                                #
    $hFile = $ARGV[0] ;            #
    $majorFlag = '' ;              #
    shift @ARGV ;                  #
    next ;                         #
  }                                #
                                   #
  if( $majorFlag eq 'i' )          # cfg input file
  {                                #
    $cfgFile = $ARGV[0] ;          #
    $majorFlag = '' ;              #
    shift @ARGV ;                  #
    next ;                         #
  }                                #
                                   #
  if( $majorFlag eq 'l' )          #
  {                                #
    next unless defined $ARGV[0] ; #
    foreach my $library ( @ARGV )  #
    {                              #
      last if $ARGV[0] =~ /^-/ ;   #
      shift @ARGV ;            #
      push @library, $library ;    #
    }                              #
    next ;                    #
  }                                #
                                   #
  die "unknow flag -$historyFlag " ;
}

die &usage() unless defined $cfgFile ;
die &usage() unless defined $cFile   ;
die &usage() unless defined $hFile   ;
die &usage() unless defined $fileType ;

$fileType eq 'c' ||
$fileType eq 'h' || &usage()  ;

################################################################################
# functions
################################################################################
sub usage
{
  print "clo.pl -t c|h -c source.c -h source.h -i config.ini [-l libraries]"
}

sub readCfg
{
  my $cfgFile = $_[0] ;

  my %cfg ;

  open CFG, $cfgFile  ;

  my $section ;
  my $longName ;
  my $condCnt = 0 ;
 
  foreach my $line (<CFG>)
  {
    chomp $line ;
    next if $line =~ /^\s*#/ ;
    next if $line =~ /^\s*$/ ;
    if( $line =~ /^\s*(\S+)\s*:\s*$/ )
    {
      $section = $1 ;
      $section eq 'attribute' ||
      $section eq 'condition' ||
      $section eq 'help'      ||
      $section eq 'program'   ||
      die "usage" ;
      next ;
    }

    # ------------------------------------------------------
    # section attribute
    # ------------------------------------------------------
    if( $section eq 'attribute' ) 
    {
      $line =~ /^\s*(\S+)\s*=\s*(.+)$/ || 
        die "unknown format $line in section $section" ;
      my $key = $1 ;
      my $value = $2 ;
         $value =~ s/\s*$// ;
  
      die "unknown format $line" if $key   =~ /^\s*$/ ;
      die "unknown format $line" if $value =~ /^\s*$/ ;

      $longName = $value if $key eq 'long' ;

      if( $longName eq 'help'     ||
          $longName eq 'version'  ||
          $longName eq 'revision' ) 
      {
      # print "$longName is a key word, please change $cfgFile\n" ;
        die "$longName is a key word, please change $cfgFile\n" ;
      }

      $cfg{attr}{$longName}{$key}=$value ;
      next ;
    }

    # ------------------------------------------------------
    # section condition (incl macros
    # ------------------------------------------------------
    if( $section eq 'condition' ) 
    {
      $line =~ /^\s*(\$?\w+)\s+([!\w]+)\s+(\w+)\s*$/ ||
        die "unknown format $line in section $section" ;

      my $operator = $2 ;
      my $attr1    = $1 ;
      my $attr2    = $3 ;

      if(    $operator eq 'and'  ) { $operator = $cond_opr_and  ; }
      elsif( $operator eq 'or'   ) { $operator = $cond_opr_or   ; }
      elsif( $operator eq 'xor'  ) { $operator = $cond_opr_xor  ; }
      elsif( $operator eq '!and' ) { $operator = $cond_opr_nand ; }
      elsif( $operator eq '!or'  ) { $operator = $cond_opr_nor  ; }
      elsif( $operator eq '!xor' ) { $operator = $cond_opr_nxor ; }
      elsif( $operator eq 'if'   ) { $operator = $cond_opr_if   ; }
      elsif( $operator eq 'gt'   ) { $operator = $cond_opr_gt   ; }
      elsif( $operator eq 'lt'   ) { $operator = $cond_opr_lt   ; }
      elsif( $operator eq 'eq'   ) { $operator = $cond_opr_eq   ; }
      else { die "operator: $operator not valid" ;    }

      # ----------------------------------------------------
      # handle macros
      # ----------------------------------------------------
      if( $attr1 =~ s/^\$// )      # macros: attr1 starts with '$'
      {
        $cfg{macro}{$attr1}{opr}   = $operator;
        $cfg{macro}{$attr1}{value} = $attr2   ;
        next;
      }

      # ----------------------------------------------------
      # handle conditions
      # ----------------------------------------------------
      exists $cfg{attr}{$attr1}{short} || 
        die "condition $line points to unknown attribute $attr1" ;

      exists $cfg{attr}{$attr2}{short} || 
        die "condition $line points to unknown attribute $attr2" ;

      $cfg{cond}{$condCnt}{attr1} = $cfg{attr}{$attr1}{short} ;
      $cfg{cond}{$condCnt}{attr2} = $cfg{attr}{$attr2}{short} ;
      $cfg{cond}{$condCnt}{opr}   = $operator ;
      $condCnt++ ;
      next ;
    }

    if( $section eq 'help' )
    {
      chomp $line ;
      $line =~ s/^\s*// ;
      $line =~ s/\s*$// ;
      $^A ='' ;
      formline $majorHelpFormat, $line ;
      $help .= $^A ;
      next ;  
    }

    if( $section eq 'program' )
    {
      $line =~ /^\s*(\S+)\s*=\s*(\w+)\s*$/ || 
        die "unknown format $line in section $section" ;
      my $key   = $1 ;
      my $value = $2 ;
      $cfg{prg}{$key} = $value ;
      next ;
    }

    die "unknown section $section" ;
  }

  die "no help text" unless length $help > 0 ;
  $help =~ s/\n/\\n/g ;
  $cfg{prg}{help} = $help ;

  close CFG ;

  return %cfg ; 
}

################################################################################
#
################################################################################
sub printHead_h
{
  my $headFile = $_[0] ;
  my $_prg    = $_[1] ;

  open  HEAD, ">$headFile" ;
  print HEAD "
/******************************************************************************/
/*                  C O M M A N D   L I N E   A N A L Y S E R                 */
/*                                                                            */
/*   ATTENTION:                                                               */
/*      This file has been generated.                                         */
/*      Don't change it.                                                      */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
#include <limits.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#if(0)
#define CMD_LONG_NAME_LENGTH $cmd_long_name_length
#endif

#define CMDL_TYPE_EMPTY  0
#define CMDL_TYPE_INT    1
#define CMDL_TYPE_CHR    2
#define CMDL_TYPE_STR    3

#define CMDL_APPL_OBL 1   // appliance obligatory
#define CMDL_APPL_OPT 0   // appliance optional

#define COND_OPR_OR         \'$cond_opr_or\'    
#define COND_OPR_AND        \'$cond_opr_and\'   
#define COND_OPR_XOR        \'$cond_opr_xor\'   
#define COND_OPR_NOT_OR     \'$cond_opr_nor\'   
#define COND_OPR_NOT_AND    \'$cond_opr_nand\'  
#define COND_OPR_NOT_XOR    \'$cond_opr_nxor\'  
#define COND_OPR_IF         \'$cond_opr_if\'  

#define COND_OPR_GT         \'$cond_opr_gt\'
#define COND_OPR_LT         \'$cond_opr_lt\'
#define COND_OPR_EQ         \'$cond_opr_eq\'

#define MACRO_ARGC_STR      \"$macroArgcId\"
#define MACRO_ARGC_ID       '1'

#define PROGRAM_NAME   \"".$_prg->{name}."\" 

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/

/******************************************************************************/
/*   S T R U C T                                                              */
/******************************************************************************/
struct sCmdLnCfg
{
#if(0)
  char    longAttr[CMD_LONG_NAME_LENGTH] ;
#else
  char    *longAttr ;
#endif
  char    shortAttr    ;
  int     appliance    ;    // obligatory || optional
  int     type         ;    // char, char*, int
  int     element      ;    // nr. of member in value array
  int     *intValue    ;
  char    *chrValue    ;
  char   **strValue    ;
  char     *help       ;
  struct sCmdLnCfg *next  ;
};

struct sCmdLnAttr
{
  char    shortAttr    ;
  int     type         ;
  int     element      ;    // nr. of member in value array
  int     *intValue    ;
  char    *chrValue    ;
  char   **strValue    ;
  struct sCmdLnAttr *next  ;
} ;

struct sCmdLnCond
{
  char attr1 ;
  char attr2 ;
  char opr   ;
  struct sCmdLnCond *next ;
} ;

struct sCmdLnMacro
{
  enum { $macroArgcStr = MACRO_ARGC_ID } macro ;
  char    opr   ;
  int     value ;
  struct sCmdLnMacro *next ;
} ;


/******************************************************************************/
/*   T Y P E S                                                                */
/******************************************************************************/
typedef struct sCmdLnCfg   tCmdLnCfg  ;
typedef struct sCmdLnAttr  tCmdLnAttr ;
typedef struct sCmdLnCond  tCmdLnCond ;
typedef struct sCmdLnMacro tCmdLnMacro;

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
void usage();

tCmdLnCfg*  findShortNameCfg( char shortName ) ;
tCmdLnCfg*  findLongNameCfg( const char *longName ) ;
tCmdLnAttr* findShortAttr( const char shortName ) ;
tCmdLnAttr* findLongAttr(  const char *longName ) ;

int initCmdLnCfg()  ;
int initCmdLnCond() ;
int initCmdLnMacro();

int getCmdLnAttr( int argc, const char* argv[] ) ;
int handleCmdLn(  int argc, const char* argv[] ) ;
int checkMacro(   int argc, const char* argv[] ) ;

int          getFlagAttr(       const char *longName ) ;
const int*   getIntArrayAttr(   const char *longName ) ;
int          getIntAttr(        const char *longName ) ;
const char** getStrArrayAttr(   const char *longName ) ;
const char*  getStrAttr(        const char *longName ) ;
const char*  getCharArrayAttr(  const char *longName ) ;
char         getCharAttr(       const char *longName ) ;

int getAttrSize( const char *longName ) ;

void revOutver4bin_() ;    // funciton defined in verElf
";

foreach my $library (@library)
{
  $library =~ s/\.\w+$// ;
  print HEAD "void revOutver4lib_$library() ;   //function defined in verElf\n";
}

print HEAD "
void version() ;
" ; 
  close HEAD ;
}

################################################################################
#
################################################################################
sub printHead_c
{
  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;
  my $_prg    = $_[2] ;

  open SRC, ">$cFile" ;

  print SRC "
/******************************************************************************/
/*                  C O M M A N D   L I N E   A N A L Y S E R                 */
/*                                                                            */
/*   ATTENTION:                                                               */
/*      This file has been generated.                                         */
/*      Don't change it.                                                      */
/*                                                                            */
/******************************************************************************/

";
  print SRC "

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// ---------------------------------------------------------
// own
// ---------------------------------------------------------
#include \"$hFile\"

/******************************************************************************/
/*   G L O B A L S                                                            */
/******************************************************************************/
tCmdLnCfg*   anchorCfg   ;
tCmdLnAttr*  anchorAttr  ;
tCmdLnCond*  anchorCond  ;
tCmdLnMacro* anchorMacro ;

#define ERR_TXT_LNG 255
char errText[ERR_TXT_LNG] = \"\\0\" ;

/******************************************************************************/
/*   P R A G M A                                                              */
/******************************************************************************/
#ifdef UNUSED
#elif  defined(__GNUC__)
#      define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif  defined(__LCLINT__)
#      define UNUSED(x) /*\@unused\@*/ x
#else
#      define UNUSED(x) x
#endif

/******************************************************************************/
/*   F U N C T I O N S                                                        */
/******************************************************************************/
";
  close SRC ;
}

sub printInternal
{
  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;
  my $_prg    = $_[2] ;

  open SRC, ">>$cFile" ;

  print SRC "
/******************************************************************************/
/* version function                                                           */
/******************************************************************************/
//void version( )
//{
//  printf( \"call: %s, please adjust clo.pl\\n\",__FUNCTION__ ); 
//}

/******************************************************************************/
/* revision function                                                          */
/******************************************************************************/
void revision( )
{
  printf(\"\\n\"); 
  revOutver4bin_() ;

  printf(\"\\n\"); 
" ;
foreach my $library (@library)
{
  $library =~ s/\..+$// ;
  print SRC "  revOutver4lib_$library() ;\n" ;
  print SRC "  printf(\"\\n\") ; " ;
}
  print SRC "
}

/******************************************************************************/
/* print usage                                                                */
/******************************************************************************/
void usage( )
{
  tCmdLnCfg *p ;
  int i ; 

  fprintf(stderr,\"%s \",PROGRAM_NAME ) ;         // print the name of the prg
                                                  //
 if( anchorCfg == NULL )                          // if usage() is called
 {                                                //  directly from main(),
    initCmdLnCfg() ;                              //  before HandleCmdLn(),
    initCmdLnCond() ;                             //  than anchorCfg==null,
  }                                               //  than help text has to be
                                                  //  initialized
  if( anchorCfg == NULL )                         //
  {                                               //
    fprintf( stderr, \"\\n\\tno help available\\n\");//  
    goto _door ;                                  // initializing has failed
  }                                               //
                                                  //
  p = anchorCfg ;                                 // print obligatory attr
  while( p->next != NULL )                        //
  {                                               //
    p = p->next ;                                 //
    if( p->appliance == CMDL_APPL_OBL )           //
    {                                             //
      fprintf(stderr,\" -%c\", p->shortAttr );    //
      switch ( p->type )                          //
      {                                           //
        case CMDL_TYPE_EMPTY :                    //
        {                                         //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_INT :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" nr\");              //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %d\",p->intValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_CHR :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" %c\",p->shortAttr); //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %c\",p->chrValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_STR :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" %s\",p->longAttr);  //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %s\",p->strValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
      }                                           //
    }                                             //
  }                                               //
                                                  //
  p = anchorCfg ;                                 //
  while( p->next != NULL )                        // print optional attr
  {                                               //
    p = p->next ;                                 //
    if( p->appliance == CMDL_APPL_OPT )           //
    {                                             //
      fprintf(stderr,\" [-%c\", p->shortAttr );  //
      switch ( p->type )                          //
      {                                           //
        case CMDL_TYPE_EMPTY :                    //
        {                                         //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_INT :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" nr\");              //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %d\",p->intValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_CHR :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" %c\",p->shortAttr); //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %c\",p->chrValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
        case CMDL_TYPE_STR :                      //
        {                                         //
          if( p->element == 0 )                   //
          {                                       //
            fprintf(stderr,\" %s\",p->longAttr);  //
            break ;                               //
          }                                       //
          for( i=0; i< p->element; i++ )          //
          {                                       //
            fprintf(stderr,\" %s\",p->strValue[i]);
          }                                       //
          break ;                                 //
        }                                         //
      }                                           //
      fprintf(stderr,\"]\");                      //
    }                                             //
  }                                               //
                                                  //
  fprintf(stderr,\"\\n%s options:\\n\",\"".$_prg->{help}."\" ) ;
                                                  // help text
  p = anchorCfg ;                                 //
  while( p->next != NULL )                        //
  {                                               //
    p = p->next ;                                 //
    fprintf(stderr,\"%s\",p->help);               //
  }                                               //
  if( strlen(errText) > 0 )                       //
  {                                               //
    fprintf(stderr,\"\\n%s\\n\",errText );    
  }                                               //
  fprintf(stderr,\"\\n\") ;                       //
                                                  //
_door :                                           //
  return ;                                        //
}

/******************************************************************************/
/* find config node corresponding to shrot name                               */
/******************************************************************************/
tCmdLnCfg* findShortNameCfg( char shortName )
{
  tCmdLnCfg *p = NULL ;

  if( anchorCfg == NULL )  goto _door; 

  p = anchorCfg->next ;

  if( p == NULL ) goto _door ; 

  while(1)
  {
    if( p->shortAttr == shortName ) goto _door ;
    if(p->next==NULL) { p=NULL; goto _door ; }
    p=p->next ;
  }

_door:  
  return p ;
}

/******************************************************************************/
/* find config node corresponding to long name                                */
/******************************************************************************/
tCmdLnCfg* findLongNameCfg( const char *longName )
{
  tCmdLnCfg *p = NULL ;

  if( anchorCfg == NULL ) goto _door ;
  p = anchorCfg->next ;

  if( p == NULL ) goto _door ;

  while(1)
  {
    if( p->longAttr == NULL ) { p=NULL ; goto _door; }
    if( strcmp( p->longAttr, longName ) == 0 ) goto _door ;
    if(p->next==NULL) { p=NULL; goto _door ; }
    p=p->next ;
  }

_door:
  return p ;
}

/******************************************************************************/
/* find attribute node corresponding to short name                            */
/******************************************************************************/
tCmdLnAttr* findShortAttr( const char shortName )
{
  tCmdLnAttr *p ;

  if( anchorAttr == NULL ) goto _door ;

  p = anchorAttr->next ;

  if( p == NULL ) goto _door ;

  while(1)
  {
    if( p->shortAttr == shortName ) goto _door ;
    if(p->next==NULL) { p=NULL; goto _door ; }
    p=p->next ;
  }

_door:
  return p ;
}

/******************************************************************************/
/* find attribute node corresponding to short name                            */
/******************************************************************************/
tCmdLnAttr* findLongAttr( const char *longName )
{
  tCmdLnCfg  *cfgNode ;
  tCmdLnAttr *attrNode = NULL ;

  cfgNode = findLongNameCfg( longName ) ;

  if( cfgNode == NULL ) goto _door ;

  attrNode = findShortAttr( cfgNode->shortAttr ) ;

_door:
  return attrNode ;
}

/******************************************************************************/
/* get the nr. of elements for this node                                      */
/******************************************************************************/
int getAttrSize( const char *longName )
{
  tCmdLnAttr *nodeAttr ;

  nodeAttr = findLongAttr( longName ) ;

  if( nodeAttr == NULL ) return -1 ;

  return nodeAttr->element ;
}

/******************************************************************************/
/* get command line attribute of type empty to longName                       */
/******************************************************************************/
int getFlagAttr( const char *longName )
{
  tCmdLnAttr *nodeAttr ;

  nodeAttr = findLongAttr( longName ) ;

  if( nodeAttr == NULL ) return 1 ;                  // longName not found 
                  
  if( nodeAttr->type != CMDL_TYPE_EMPTY ) return 2 ; // wrong type
                  
  return 0 ;                                         // longName found
} 

/******************************************************************************/
/* get command line attribute of type *int belonging to longName              */
/******************************************************************************/
const int* getIntArrayAttr( const char *longName )
{
  tCmdLnAttr *nodeAttr ;
  int *p = NULL ;

  nodeAttr = findLongAttr( longName ) ;

  if( nodeAttr == NULL ) goto _door ;

  if( nodeAttr->type != CMDL_TYPE_INT ) goto _door ; // wrong type

  p = nodeAttr->intValue ; 
  
_door :
  return (const int *) p ; 
}

/******************************************************************************/
/* get command line attribute of type int belonging to longName               */
/******************************************************************************/
int getIntAttr( const char *longName )
{
  int *p ; 
  int rc ;

  p = (int*) getIntArrayAttr( longName ) ;

  if( p == NULL ) 
  {
    rc = INT_MIN ;
    goto _door ;
  }

  if( getAttrSize( longName ) != 1 )
  {
    rc = INT_MAX ;
    goto _door ;
  }

  rc = *p ;
 
_door :   
  return rc ;
}

/******************************************************************************/
/* get command line attribute of type *string belonging to longName           */
/******************************************************************************/
const char** getStrArrayAttr( const char* longName ) 
{
  tCmdLnAttr *nodeAttr ;

  char **s = NULL ;

  nodeAttr = findLongAttr( longName ) ;

  if( nodeAttr == NULL ) goto _door ;

  if( nodeAttr->type != CMDL_TYPE_STR ) goto _door ; // wrong type

  s = nodeAttr->strValue ; 
  
_door :
  return (const char**) s ; 
}

/******************************************************************************/
/* get command line attribute of type string belonging to longName           */
/******************************************************************************/
const char*  getStrAttr( const char* longName ) 
{
  char **s ;
  char *rc = NULL ;

  s = (char**) getStrArrayAttr( longName ) ;

  if( s == NULL ) goto _door ;

  if( getAttrSize( longName ) != 1 ) goto _door ;

  rc = *s ;
_door :
  return rc ;
}

/******************************************************************************/
/* get command line attribute of type *char belonging to longName            */
/******************************************************************************/
const char*  getCharArrayAttr( const char* longName ) 
{
  tCmdLnAttr *nodeAttr ;

  char *c = NULL ;

  nodeAttr = findLongAttr( longName ) ;

  if( nodeAttr == NULL ) goto _door ;

  if( nodeAttr->type != CMDL_TYPE_STR ) goto _door ; // wrong type

  c = nodeAttr->chrValue ; 
  
_door :
  return c ; 
}

/******************************************************************************/
/* get command line attribute of type char belonging to longName              */
/******************************************************************************/
char   getCharAttr( const char* longName ) 
{
  int *c ; 
  int rc = 0 ;

  c = (int*) getIntArrayAttr( longName ) ;

  if( c    == NULL ) goto _door ;

  if( getAttrSize( longName ) != 1 ) goto _door ;

  rc = *c ;
 
_door :   
  return rc ;
}

" ;
  close SRC ;
}

sub printInit
{
  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;
  my $_cond   = $_[2] ;
  my $_macro  = $_[3] ;
# my $_prg    = $_[3] ;

  open SRC, ">>$cFile" ;

print SRC "
/******************************************************************************/
/* init command line config  es                                               */
/******************************************************************************/
int initCmdLnCfg()
{
  int sysRc = 0 ;
  errno = 0 ;

  tCmdLnCfg *p ;
  tCmdLnCfg *q ;

  anchorCfg = (tCmdLnCfg*) malloc(sizeof(tCmdLnCfg)) ;
  if( errno != 0 ) { sysRc = errno ; goto _door ; }
  p=anchorCfg ;
";

  foreach my $long (keys %$_cfg)
  {
    $long =~ s/^\s*// ;
    $long =~ s/\s*$// ;

    die "long name of the cml attr to long\n" 
      if length($long) > $cmd_long_name_length ;

    print SRC "  q = (tCmdLnCfg*) malloc(sizeof(tCmdLnCfg)) ;

  /****************************************************************************/
  /* command line attribte $long                                    */
  /****************************************************************************/
  q->longAttr = (char*) malloc( sizeof(\"$long\\0\") );
  memcpy( q->longAttr, \"$long\", sizeof(\"$long\\0\") );

  p->next = q ;
  p = q ;
  q->next = NULL ;
    ";

    my $_subCfg = $_cfg->{$long} ; 

    exists $_subCfg->{short} || 
      die "no short name for cmd line attribute $long\n" ;
    
    print SRC "
  //--------------------------------------------------------
  // command line attribute $long short form 
  //--------------------------------------------------------\n";
    $_subCfg->{short} =~ /^\S$/ ||
      die "short name for cmd line attribute $long has to be char \n" ;
    print SRC "  q->shortAttr = \'$_subCfg->{short}\' ;\n"; 

    print SRC "
  //--------------------------------------------------------
  // command line attribute $long appliance
  //--------------------------------------------------------\n" ;
    exists $_subCfg->{appliance} ||
      die "appliance for cmd line attribute $long not set" ;
    if( $_subCfg->{appliance} eq 'obligatory' )
    {
      print SRC "  q->appliance = CMDL_APPL_OBL ; \n" ;
    }
    elsif( $_subCfg->{appliance} eq 'optional' )
    {
      print SRC "  q->appliance = CMDL_APPL_OPT ; \n" ;
    }
    else
    {
      die "unknown appliance for $long cmd line attribute\n" ;
    }

    print SRC "
  //--------------------------------------------------------
  // command line attribute $long element count
  //--------------------------------------------------------
  q->element = 0; " ;

    print SRC "
  //--------------------------------------------------------
  // command line attribute $long help text
  //--------------------------------------------------------" ;
    exists $_subCfg->{help} || 
      die "help for cmd line attribute $long not known\n" ;
    $^A = '' ;
    my $optTxt = $_subCfg->{help} ;
       $optTxt .=" (optional)" if $_subCfg->{appliance} eq 'optional' ;
    formline $minorHelpFormat1, $_subCfg->{short}, 
                                $_subCfg->{long} ; 
    my $buff = $^A ;
       $buff =~ s/:-:$// ;

    $^A = '' ;
    formline $minorHelpFormat2, $optTxt ;
    $^A   =~ s/^\s+// ;
    $buff .= $^A ;
    $buff =~ s/\n+/\\n/g ;
    my $helpLng = length( $buff ) ;
    print SRC "  
  q->help = (char*) malloc( $helpLng * sizeof(char) ) ;
  if( errno != 0 ) { sysRc = errno ; goto _door ; }

  memcpy( q->help, \"$buff\",".$helpLng.");" ;

print SRC "
  //--------------------------------------------------------
  // command line attribute $long type
  //--------------------------------------------------------\n" ;
    exists $_subCfg->{type} || 
      die "type of cmd line attribute $long not known\n" ;
    if(    $_subCfg->{type} eq 'int' )
    {
      print SRC "  q->type = CMDL_TYPE_INT ;\n" ;
    }
    elsif( $_subCfg->{type} eq 'char' )
    {
      print SRC "  q->type = CMDL_TYPE_CHR ;\n" ;
    }
    elsif( $_subCfg->{type} eq 'str' )
    {
      print SRC "  q->type = CMDL_TYPE_STR ;\n" ;
    }
    elsif( $_subCfg->{type} eq 'empty' )
    {
      print SRC "  q->type = CMDL_TYPE_EMPTY ;\n" ;
    }
    else 
    {
      die "type $_subCfg->{type} of cmd line attribute $long not valide\n" ;
    }

    print SRC "
  //--------------------------------------------------------
  // command line attribute $long values
  //--------------------------------------------------------\n" ;
    print SRC "  q->intValue = NULL ; \n" ;
    print SRC "  q->chrValue = NULL ; \n" ;
    print SRC "  q->strValue = NULL ; \n" ;

    exists $_subCfg->{value}   && 
    $_subCfg->{value} eq 'any' && 
    delete $_subCfg->{value} ;

    exists $_subCfg->{value}   && 
    $_subCfg->{value} eq '*'   && 
    delete $_subCfg->{value} ;

    if( exists $_subCfg->{value} )
    {
      my @values = split " ",  $_subCfg->{value} ;
      my $cnt= scalar @values ;
      print SRC "  q->element = $cnt ; \n" ;

      if( $cnt > 0 )
      {
        my $i=0 ;
        if(    $_subCfg->{type} eq 'int' )
        {
          print SRC "  q->intValue = (int*) malloc( $cnt * sizeof(int) ) ;" ;
          foreach my $value (@values)
          {
            print SRC "\n  q->intValue[$i] = $value ; \n";
            $i++ ;
          }
        }
        elsif( $_subCfg->{type} eq 'char' )
        {
          print SRC "  q->chrValue = (char*) malloc( $cnt * sizeof(char) ) ;" ;
          print SRC "  if( errno != 0 ) { sysRc = errno ; goto _door ; } " ;
          foreach my $value (@values)
          {
            print SRC "\n  q->chrValue[i] = $value ;";
            $i++ ;
          }
        }
        elsif( $_subCfg->{type} eq 'str' )
        {
          print SRC "  q->strValue = (char**) malloc( $cnt * sizeof(char*) ) ;";
          foreach my $value (@values)
          {
            print SRC "
  q->strValue[$i] = (char*) malloc( sizeof(char*) * sizeof(\"$value\") );
  if( errno != 0 ) { sysRc = errno ; goto _door ; }
  memcpy( q->strValue[$i], \"$value\", sizeof(\"$value\") ); ";
            $i++ ;
          }
        }
        print SRC "\n" ;
      }
    }
  }
 
  print SRC "
_door :
  return sysRc ;
}

/******************************************************************************/
/* init conditionals                                                          */
/******************************************************************************/
int initCmdLnCond()
{
  int sysRc = 0 ;
  errno = 0 ;
  "; 

  if( scalar keys %$_cond ==  0 ) 
  {
    print SRC "
  anchorCond = (tCmdLnCond*) malloc(sizeof(tCmdLnCond)) ;

  if( errno != 0 ) { sysRc = errno ; goto _door ; }
  anchorCond->next = NULL;

  _door:

  return sysRc ;
}
  ";
  }
  else
  {
    print SRC "
  tCmdLnCond *p ;
  tCmdLnCond *q ;

  anchorCond = (tCmdLnCond*) malloc(sizeof(tCmdLnCond)) ;
  if( errno != 0 ) { sysRc = errno ; goto _door ; }

  p=anchorCond ;
  p->next = NULL ;
  ";

    foreach my $condId ( keys %$_cond )
    {
      print SRC "
  q = (tCmdLnCond*) malloc( sizeof(tCmdLnCond) ) ; 
  if( errno != 0 ) { sysRc = errno ; goto _door ; }
  q->attr1 = \'".$_cond->{$condId}{attr1}."\' ;
  q->attr2 = \'".$_cond->{$condId}{attr2}."\' ;
  q->opr   = \'".$_cond->{$condId}{opr}."\' ;
  q->next = NULL ;
  p->next = q ;
  p=q ;
  " ;
    }

  print SRC "
  _door:
  return sysRc ;
}
  ";
  }

  print SRC "
/******************************************************************************/
/* init macros                                                                */
/******************************************************************************/
int initCmdLnMacro()
{
  int sysRc = 0 ;
  errno = 0 ;
";

  if( scalar keys %$_macro == 0 )
  {
    print SRC "
  return sysRc ;
}
    ";
  }
  else
  {
    print SRC "
  tCmdLnMacro *p ; 
  tCmdLnMacro *q ; 

  anchorMacro = (tCmdLnMacro*) malloc(sizeof(tCmdLnMacro)) ;

  p=anchorMacro ;
  p->next=NULL;

    ";
    foreach my $macro (keys %$_macro)
    {
      print SRC "
  q = (tCmdLnMacro*) malloc( sizeof(tCmdLnMacro) ) ; 
  if( errno != 0 ) { sysRc = errno ; goto _door ; }
      ";
      if( $macro eq $macroArgcStr )
      {
        print SRC "
  q->macro = MACRO_ARGC_ID ;
  q->opr   = \'".$_macro->{$macro}{opr}."\' ;
  q->value = $_macro->{$macro}{value} ;
  q->next=NULL;
  p->next = q;
  p=q;

        ";
      }
    }
  print SRC "
  _door:
  return sysRc ;
       
}
  ";
  }   # else scalar keys
  close SRC ;
}

################################################################################
sub printGet
{
  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;

  open SRC, ">>$cFile" ;

print SRC "
/******************************************************************************/
/* analyse command line attributes                                            */
/******************************************************************************/
int getCmdLnAttr(int argc, const char* argv[] )
{
  int i,j,k ;
  int element ;
  int sysRc = 0 ;

  errno = 0 ;

  tCmdLnCfg  *nodeCfg  = NULL ;
  tCmdLnAttr *nodeAttr = NULL ;
  tCmdLnAttr *pAttr    = NULL ;

  anchorAttr = (tCmdLnAttr*) malloc(sizeof(tCmdLnAttr)) ;
  if( errno != 0 ) { sysRc = errno ; goto _door ; } 
  pAttr = anchorAttr ;

  // -------------------------------------------------------
  // go through all arguments
  // -------------------------------------------------------
  for(i=1;i<argc;i++)
  {
    // -----------------------------------------------------
    // identify and check existance of the major attribute 
    // -----------------------------------------------------
    if( argv[i][0] == '-'  )                        // check if major attribute 
    {                                               //
      if( argv[i][1] == '-' )                       // check if major attribute 
      {                                             //   (gnu form)
        if( strlen(argv[i]) < 3 )                   //
        {                                           //
          sysRc = 1  ;                              //
          goto _door ;                              //
        }                                           //
        nodeCfg = findLongNameCfg( &argv[i][2] ) ;  //
      }                                             //
      else                                          // check if major attribute 
      {                                             //   (ux form)
        if( strlen(argv[i])!=2 )                    //
        {                                           //
          sysRc = 1  ;                              //
          goto _door ;                              //
        }                                           //
        nodeCfg = findShortNameCfg( argv[i][1] ) ;  //
      }                                             //
                                                    //
      if(nodeCfg==NULL)                             // check if attr exists 
      {                                             //   in config 
        sysRc=1;                                    //
        snprintf( errText, ERR_TXT_LNG,             //
               \"    unknown attribute %s\", argv[i]);  //
        goto _door;                                 //
      }                                             //
                                                    // allocate additional node
      nodeAttr = (tCmdLnAttr*) malloc(sizeof(tCmdLnAttr)) ;
      pAttr->next = nodeAttr ;                      //
      pAttr = nodeAttr       ;                      //
      nodeAttr->next = NULL  ;                      //
      nodeAttr->shortAttr = nodeCfg->shortAttr ;    //
      nodeAttr->type = nodeCfg->type ;              //
                                                    //
      if( nodeCfg->type == CMDL_TYPE_EMPTY )        //
      {                                             //
        nodeCfg = NULL ;                            //
      }                                             //
      continue ;                                    //
    }                                               //
                                                    //
    if( nodeCfg == NULL )                           // check existance
    {                                               //
      sysRc = 1  ;                                  //
      goto _door ;                                  //
    }                                               //
                                                    //
    // -----------------------------------------------------
    // handle minor attribute 
    // -----------------------------------------------------
    nodeAttr->intValue = NULL ;                     // init value arrays
    nodeAttr->chrValue = NULL ;                     //
    nodeAttr->strValue = NULL ;                     //
                                                    // count minor attributes
    j = i ;                                         // until last minor 
    while( j < argc )                               // 
    {                                               //  or
      if( argv[j][0] == '-' ) break ;               // next major attribute
      j++ ;                                         //  has been reached 
    }                                               //
    element = j - i ;                               // nr. of minor attributes
    if( element == 0 )                              //  if no attribute -> error
    {                                               //  there has to be at least
      sysRc=1 ;                                     //  one cmdLn attr for all
      goto _door ;                                  //  data types but 
    }                                               //  data_type=empty
    nodeAttr->element = element ;                   //
                                                    // fill up value arrays
    switch( nodeCfg->type )                         //   depending on value type
    {                                               //
                                                    //
      case CMDL_TYPE_EMPTY  :                       // epmty value handeld in
      {                                             //  major attribute section
        nodeCfg = NULL ;                            //
        continue       ;                            //
      }                                             //
                                                    //
      case CMDL_TYPE_INT    :                       // handle intiger
      {                                             //
        errno = 0 ;                                 // flash errno for strtol
        nodeAttr->intValue = (int*) malloc(element*sizeof(int)) ;
        if( errno != 0 ) { sysRc = errno ; goto _door ; } 
        for( j=i,k=0; j<i+element; j++,k++ )        // convert all minor 
        {                                           //   attributes to initiger
          nodeAttr->intValue[k]=(int)strtol(argv[j],NULL,10) ;
          switch( errno )                           // check errno for atol
          {                                         //
            case EINVAL  :                          // err invalid value
            case ERANGE  :                          // error out of range
              sysRc = errno ;                       //
              goto _door ;                          //
            default      :                          //
              break      ;                          //
          }                                         //
        }                                           //
        break ;                                     //
      }                                             //
                                                    //
      case CMDL_TYPE_CHR    :                       // handle char
      {                                             //
        nodeAttr->chrValue=(char*)malloc(element*sizeof(char)) ;
        if( errno != 0 ) { sysRc = errno ; goto _door ; } 
        for( j=i,k=0; j<i+element; j++,k++ )        //
        {                                           //
          if( strlen(argv[j] ) > 1 )                // check if it is a char
          {                                         //
            sysRc = 1  ;                            //
            goto _door ;                            //
          }                                         //
          nodeAttr->chrValue[k] = *argv[j] ;        // convert str to char
        }                                           //
        break ;                                     //
      }                                             //
                                                    //
      case CMDL_TYPE_STR    :                       // handle string (char*)
      {                                             // allocate array of strings
        nodeAttr->strValue=(char**)malloc(element*sizeof(char*));
        for( j=i,k=0; j<i+element; j++,k++ )        // allocate single string 
        {                                           //  as member of array
          nodeAttr->strValue[k]=(char*)malloc( strlen(argv[j]) *
                                               sizeof(char)   );
          strcpy(nodeAttr->strValue[k],argv[j]);    // copy cml attr to 
        }                                           //   allocated string
        break ;                                     //
      }                                             //
    }                                               //
    i+=element-1;                                   //
  }                                                 //

_door:
  return sysRc ;
}
";
  close SRC ;

}

################################################################################
sub printAnalyse
{

  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;

  open SRC, ">>$cFile" ;

print SRC "
/******************************************************************************/
/* analyse command line attributes                                            */
/******************************************************************************/
int checkCmdLn()
{
  int sysRc = 0 ;

  tCmdLnCfg  *pCfg = anchorCfg  ;
  tCmdLnAttr *pAtt = anchorAttr ;
  tCmdLnCond *pCnd = anchorCond ;

  tCmdLnAttr *pAtt1 ;
  tCmdLnAttr *pAtt2 ;

  int i,j ;
  int found ;

  if( pCfg == NULL && pAtt != NULL )          // if config empty but something
  {                                           //   on cmdLn -> error
    sysRc = 1  ;                              //
    goto _door ;                              //
  }                                           //

  // -------------------------------------------------------
  // check all possible attributes on consitance
  // -------------------------------------------------------
  while( pCfg->next != NULL )                 // break at last config node 
  {                                           //
    pCfg = pCfg->next ;                       // anchor is empty
                                              //
    pAtt = findShortAttr( pCfg->shortAttr ) ; // search for attr node (cmdLn) 
                                              //   that correspods config node
    if( pCfg->appliance == CMDL_APPL_OBL  &&  //
        pAtt == NULL  )                       // for appliance = obligatory
    {                                         //   cmdLn attr has to exist
      sysRc = 1  ;                            //
      goto _door ;                            //
    }                                         //
                                              //
    if( pAtt == NULL ) continue ;             // ignore non-existing cmdLn
                                              //  attributes if appliance 
    switch( pCfg->type )                      //  optional 
    {                                         //
      case CMDL_TYPE_EMPTY:                   // nothing to do, no data
        break ;                               //
                                              //
      // ---------------------------------------
      // check data type int
      // ---------------------------------------
      case CMDL_TYPE_INT  :                   // 
        if( pCfg->intValue == NULL )          // any initiger values are allowed
        {                                     //
          if( pAtt->intValue == NULL )        //
          {                                   //
            sysRc = 1 ;                       //
            goto _door ;                      //
          }                                   //
          break ;                             //
        }                                     //
        for(i=0;i<pAtt->element;i++)          //
        {                                     // only special values given by 
          found = 0 ;                         //   config (pCfg) are allowed  
          for( j=0; j<pCfg->element; j++ )    // check if every value given by  
          {                                   //   pAttr (cmdln) can be found in
            if( pAtt->intValue[i] ==          //   pCfg  (config)
                pCfg->intValue[j]  )          //
            {                                 //
              found = 1 ;                     //
              break     ;                     //
            }                                 //
          }                                   //
          if( !found )                        // error if no value is matching
          {                                   //
            sysRc = 1  ;                      //
            goto _door ;                      //
          }                                   //
        }                                     //
        break ;                               //
                                              //
      // ---------------------------------------
      // check data type char
      // ---------------------------------------
      case CMDL_TYPE_CHR  :                   //
        if( pCfg->chrValue==NULL )            // any values are allowed
        {                                     //
          if( pAtt->chrValue == NULL )        //
          {                                   //
            sysRc = 1 ;                       //
            goto _door ;                      //
          }                                   //
          break ;                             //
        }                                     //
        for( i=0; i<pAtt->element; i++ )      //
        {                                     // only special values given by 
          found = 0 ;          //   config (pCfg) are allowed
          for(j=0;j<pCfg->element;j++)        //
          {                                   // check if every value given by
            if( pAtt->chrValue[i] ==          //   pAttr (cmdln) can be found in
                pCfg->chrValue[j]  )          //   pCfg  (config)
            {                                 //
              found = 1 ;                     //
              break     ;                     //
            }                                 //
          }                                   //
          if( !found )                        // error if value from cmdLn 
          {                                   //  (pAtt) can not be found in 
            sysRc = 1  ;                      //  config (pCfg)
            goto _door ;                      //
          }                                   //
        }                                     //
        break ;                               //
                                              //
      // ---------------------------------------
      // check data type string (char*)
      // ---------------------------------------
      case CMDL_TYPE_STR  :                   //
      {                                       //
        if( pCfg->strValue == NULL )          // any values are allowed
        {                                     //
          if( pAtt->strValue == NULL )        // but no value was found
          {                                   //
            sysRc = 1 ;                       //
            goto _door ;                      //
          }                                   //
                                              //
	  if( pCfg->element == 0 &&           // check if only one value was set
              pAtt->element == 1  )           //
          {                                   //
            break;                            //
          }                                   //
          else if(pCfg->element<pAtt->element)// to many values found on 
          {                                   //  command line 
            sysRc = 1;                        //
            goto _door;                       //
          }                                   //
                                              //
          break ;                             //
        }                                     //
                                              //
        for( i=0; i<pAtt->element; i++ )      //
        {                                     // only special values given by
          found = 0 ;                         //   config (pCfg) are allowed
          for(j=0;j<pCfg->element;j++)        //
          {                                   // check if every value given by
            if(strcmp(pAtt->strValue[i],      //   pAttr (cmdln) can be found in
                      pCfg->strValue[j])==0)  //   pCfg  (config)
            {                                 //
              found = 1 ;                     //
              break     ;                     //
            }                                 //
            if( !found )                      // error if value from cmdLn 
            {                                 //  (pAtt) can not be found in 
              sysRc = 1  ;                    //  config (pCfg)
              goto _door ;                    //
            }                                 //
          }                                   //
        }                                     //
        break ;                               //
      }   // -- case                          //
    }     // -- switch                        //
  }       // -- while                         //
                                              //
  // -------------------------------------------------------
  // check conditionals
  // -------------------------------------------------------
  while( pCnd->next != NULL )                 // break at last conditional node 
  {                                           //
    pCnd = pCnd->next ;                       // 
                                              //
    pAtt1 = findShortAttr( pCnd->attr1 ) ;    //
    pAtt2 = findShortAttr( pCnd->attr2 ) ;    //
                                              //
    switch( pCnd->opr )                       //
    {                                         //
      case COND_OPR_AND :                     //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( pAtt1 && pAtt2 ) break ;          //
        sysRc = 1  ;                          //
        goto _door ;                          //
      case COND_OPR_XOR :                     //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( (!!pAtt1) != (!!pAtt2) ) break ;  // boolean xor operator
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
      case COND_OPR_OR :                      //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( pAtt1 || pAtt2 ) break ;          //
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
      case COND_OPR_NOT_AND :                 //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( !(pAtt1 && pAtt2) ) break ;       //
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
      case COND_OPR_NOT_XOR :                 //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if(!((!!pAtt1)!=(!!pAtt2))) break ;   //
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
      case COND_OPR_NOT_OR :                  //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( !(pAtt1 || pAtt2) ) break ;       //
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
      case COND_OPR_IF :                      //
        if( pAtt1 == NULL &&                  //
            pAtt2 == NULL  ) break ;          //
        if( !pAtt2 ) break ;
        if( pAtt1 ) break ;
        sysRc = 1  ;                          //
        goto _door ;                          //
        break      ;                          //
    }                                         //
  }                                           //

_door :
  return sysRc ;
}
";
  close SRC ;
}

################################################################################
#
################################################################################
sub printHandler
{
  my $srcFile = $_[0] ;
  my $_cfg    = $_[1] ;
  my $_macro  = $_[2] ;

  open SRC, ">>$cFile" ;

print SRC "
/******************************************************************************/
/* handle command line attributes                                             */
/******************************************************************************/
int handleCmdLn( int argc, const char* argv[])
{
  int sysRc ;

  if( argc == 2 )
  {
    if( memcmp( argv[1], \"--revision\", sizeof(\"--revision\")) == 0 ) 
    {
      revision() ;
      sysRc = 2 ;
      goto _doorDefault ;
    }

    if( memcmp( argv[1], \"--version\", sizeof(\"--version\")) == 0 ) 
    {
      version() ;
      sysRc = 2 ;
      goto _doorDefault ;
    }
  }

  sysRc = initCmdLnCfg() ;
  if( sysRc !=0 ) goto _doorErr ;

  sysRc = initCmdLnCond() ;
  if( sysRc !=0 ) goto _doorErr ;
  ";
  close SRC ;

  if( scalar keys %$_macro )
  {
  open SRC, ">>$cFile" ;
  print SRC "
    sysRc = initCmdLnMacro() ;
    if( sysRc !=0 ) goto _doorErr ;
  ";
  close SRC;
  }

  open SRC, ">>$cFile" ;
  print SRC "
  sysRc = getCmdLnAttr( argc, argv ) ;
  if( sysRc !=0 ) goto _doorErr ;

  sysRc = checkCmdLn( ) ;
  if( sysRc !=0 ) goto _doorErr ;

  sysRc = checkMacro( argc, argv );
  if( sysRc != 0 ) { goto _doorErr ; } ;

_doorErr :
  if( sysRc !=0 ) usage( argv[0] ) ;

_doorDefault :
  return sysRc ;
}

/******************************************************************************/
/* check macro                                                                */
/******************************************************************************/
int checkMacro(  int argc, const char* UNUSED(argv[]) )
{
  int sysRc = 0 ;

  if( anchorMacro == NULL ) goto _door;
  tCmdLnMacro *pMacro = anchorMacro ;
  
  while( pMacro->next != NULL )         // break at last conditional node 
  {
    pMacro = pMacro->next ;
    switch( pMacro->macro ) 
    {
      // ---------------------------------------------------
      // check the number of command line arguments
      // ---------------------------------------------------
      case MACRO_ARGC_ID:
      {
        switch( pMacro->opr )
        {
          case COND_OPR_GT:
          {
            if( argc > pMacro->value ) break;
            sysRc=2;
            goto _door;
          }
          case COND_OPR_LT:
          {
            if( argc < pMacro->value ) break;
            sysRc=2;
            goto _door;
          }
          case COND_OPR_EQ:
          {
            if( argc == pMacro->value ) break;
            sysRc=2;
            goto _door;
          }
        }
        break;
      }
      // ---------------------------------------------------
      // should be check by perl, can not occure
      // ---------------------------------------------------
      default :
      {
        sysRc = 1 ;
        goto _door;
      }
    }
  }

  _door:
  return sysRc;
}
";
  close SRC ;
}


################################################################################
# main
################################################################################

my %cfg = readCfg $cfgFile ;

if( $fileType eq 'h' )
{
  printHead_h $hFile, $cfg{prg} ;
  exit ;
}

printHead_c   $cFile, $cfg{attr}, $cfg{prg} ;
printInternal $cFile, $cfg{attr}, $cfg{prg} ;
printInit     $cFile, $cfg{attr}, $cfg{cond}, $cfg{macro} ;
printGet      $cFile, $cfg{attr};
printAnalyse  $cFile, $cfg{attr};
printHandler  $cFile, $cfg{attr}, $cfg{macro} ;


