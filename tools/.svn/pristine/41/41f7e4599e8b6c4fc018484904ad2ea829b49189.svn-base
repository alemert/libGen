#!/usr/bin/perl

use strict ;

my $majorFlag ;
my @revFile ;
my $outFile ;
my $includePath ;
my @elfName ;

################################################################################
# command line 
################################################################################
my $historyFlag ;

while( defined $ARGV[0] )
{
  if( $ARGV[0] =~ s/^-(\w)$/$1/ )
  {
    $majorFlag = $ARGV[0] ;
    $historyFlag = $majorFlag ;
    shift @ARGV ;
    next ;
  }

  if( $majorFlag eq 'r' )      # revision file list 
  {                            #
    push @revFile, $ARGV[0] ;  #
    shift @ARGV ;              #
    next ;                     #
  }                            #
                               #
  if( $majorFlag eq 'o' )      # output file 
  {                            #
    $outFile = $ARGV[0] ;      #
    $majorFlag = '' ;          #
    shift @ARGV ;              #
    next ;                     #
  }                            #
                               #
  if( $majorFlag eq 'I' )      # include path
  {                            #
    $includePath = $ARGV[0] ;  #
    $majorFlag = '' ;          #
    shift @ARGV ;              #
    next ;                     #
  }                            #
                               #
  if( $majorFlag eq 'e' )      # elf name (binary and/or library name)
  {                            #
    push @elfName, $ARGV[0] ;  #
    shift @ARGV ;              #
    next ;                     #
  }                            #
                               #
  die "unknow flag -$historyFlag " ; 
}

die "usage " unless scalar @revFile > 0 ;
die "usage " unless scalar @elfName > 0 ;
die "usage " unless defined $outFile ;
die "usage " unless defined $includePath ;

################################################################################
# functions
################################################################################

################################################################################
# main
################################################################################
my $maxRev ;
my @allRev ;
foreach my $revFile (@revFile)
{
  open REV, "$includePath/$revFile" ;
  foreach my $line (<REV>)
  {
    next unless $line =~ /^\s*(#define)\s+(\w+)\s+(\d+)\s*$/ ;
    $maxRev = $3 if $3 > $maxRev ;
    push @allRev, $2 ;
  }
  close REV ;
}

my $majorDefine = $outFile ;
$majorDefine =~ s/^(.+)\/// ;
$majorDefine =~ s/\.(\w+)$// ;

my $bouildName  ;
foreach my $elfName ( @elfName )
{
  $bouildName = $elfName if $majorDefine eq 'ver4lib' && 
                            $elfName     =~ /\.[soa]+$/   ;

  $bouildName = $elfName if $majorDefine eq 'ver4bin' && 
                            $elfName     !~ /\.[soa]+$/  ;
}

die "can not handle elf name" unless defined $bouildName ;
my $bouildBaseName ;
if( $bouildName =~ /\./ )
{
  $bouildBaseName = $bouildName ;
  $bouildBaseName =~ s/\..+$// ;
}


open OUT, ">$outFile" ;

print OUT "
/******************************************************************************/
/* this file has been created automaticly, please do not change it            */
/******************************************************************************/

// ---------------------------------------------------------
// system includes
// ---------------------------------------------------------
#include <stdio.h>

// ---------------------------------------------------------
// revision includes
// ---------------------------------------------------------
" ;

foreach my $revFile (@revFile)
{
  print OUT "#include <$revFile>\n" ;
}

print OUT "
// ---------------------------------------------------------
// version include
// ---------------------------------------------------------
#include <include/version.h>
" if $majorDefine eq 'ver4bin' ;

print OUT "
// ---------------------------------------------------------
// major revision define
// ---------------------------------------------------------
" ;

printf OUT "#define %-16s%8d\n","REV_".uc ${majorDefine}."_M",$maxRev ;

if( $majorDefine eq 'ver4bin' )
{
  print OUT "
void version()
{
  printf(\"version: \"MAJOR_VER\".\"MINOR_VER\".\"FIX_VER\".\"BUILD_VER\"\\n\") ;
}
";  
}

print OUT "
/******************************************************************************/
/* revision output function                                                   */
/******************************************************************************/
void revOut${majorDefine}_${bouildBaseName}() 
{
" ;
  printf OUT "  %s %-30s %-20s) ;\n",  "printf(\"%-21s %8d\\n\","       , 
                                       '"build revision '.$bouildName.'"',
                                       ', '."REV_".uc ${majorDefine}."_M" ;

foreach my $rev (@allRev)
{
  my $src = lc $rev ;
  $src =~ s/^(rev)_//g ;
  $src =~ s/^(.+)_(\w+)/$1.$2/ ;
  printf OUT "  %s %-30s %-20s) ;\n",  "printf(\"      %-15s %8d\\n\",", 
                                       '"'.$src.'"'                ,
                                       ', '.$rev                   ;
}
print OUT "  printf(\"\\n\"); \n" ;

print OUT "
}
" ;

close OUT ;
