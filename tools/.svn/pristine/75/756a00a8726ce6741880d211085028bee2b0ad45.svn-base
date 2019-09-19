#!/usr/bin/perl

use strict ;

my $buildFile ;

my $majorFlag ;

while( defined $ARGV[0] )
{
  if( $ARGV[0] =~ s/^-// ) 
  {
    $majorFlag = $ARGV[0] ;
    shift @ARGV ;
    next ;
  }

  if( $majorFlag eq 'b' )
  {
    $buildFile = $ARGV[0] ;
    shift @ARGV ;
    next ;
  }

  die "not known attribute" ;
}


open OLD, "$buildFile" || die "can not open file $buildFile"  ;
open NEW, ">$buildFile.swp" || die "can not open file $buildFile.swp"  ;


my $ver = <OLD> ;
chomp $ver ;
close OLD ;

$ver++ ;

print NEW "$ver\n" ;
close NEW ;

unlink  $buildFile ;
link   "$buildFile.swp", $buildFile;
unlink "$buildFile.swp";


