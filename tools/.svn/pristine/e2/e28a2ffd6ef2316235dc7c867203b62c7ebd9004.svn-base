#!/usr/bin/perl

use strict ;

my $cFile = $ARGV[0] ; shift @ARGV ;
my @mFile = @ARGV ;

foreach my $cat (@mFile)
{
  print SRC  #include \"$cat\"\n ";
}

my %cat ;

my $baseDef = "_______" ;
my $id ;

foreach my $cat (@ARGV)
{
  open CAT, $cat ;

  foreach my $line (<CAT>) 
  {
    chomp $line ;
                         
    next unless $line =~ /^\s*\#define\s+(\S+)\s+(.+)\s*$/ ;
    my $define = $1 ;   
    my $value  = $2 ;
 
    unless( $define =~ /${baseDef}$/ )
    {
      $baseDef = $define ;
      $id = $value ;
      $cat{$id}{define} = $define ; 
      next ; 
    }
    $define =~ /^([^_]+)_([^_]+)_(.+)/ ;
    my $definePrefix =  $1 ;
    my $class =  $2 ;
    $cat{$id}{$definePrefix} = $value ;  
    $cat{$id}{class} = $class ;  
  }
  close CAT ;
}

open SRC, ">$cFile" ;
print SRC  "
/******************************************************************************/
/*               D O   N O T   C H A N G E   T H I S   C O D E                */
/*                         it will created automaticly                        */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                         */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <catalog.h>

tMsgItem* buildCatalog( ) 
{
  tMsgItem* anchor = (tMsgItem*) malloc( sizeof(tMsgItem) ) ;
  tMsgItem* p = anchor ;
" ;

foreach my $id ( sort keys %cat )
{
  print SRC "
  p->next = (tMsgItem*) malloc( sizeof(tMsgItem) ) ;
  p = p->next ;
  p->next = NULL ;
  p->id = $id ;
  strcpy(p->define,\"$cat{$id}{define}\") ;
  strcpy(p->class,\"$cat{$id}{class}\") ;
  strcpy(p->lev,\"$cat{$id}{LEV}\") ;
  strcpy(p->txt,$cat{$id}{TXT}) ;
  " ;
}

print SRC "
  return anchor ;  
}
" ;

close SRC ;
