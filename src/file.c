/******************************************************************************/
/*                        F I L E   U T I L I T I E S                         */
/*                                                                            */
/*  functions:                                                                */
/*    - checkFileRights                                                       */
/*    - fileSize                                                              */
/*    - flushFile                                                             */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include "genlib.h"

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

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
/*   check file access rights                                                 */
/******************************************************************************/
int checkFileRights( const char* fName, int mode )
{
  int rc ;
  int errRc = NO_ERROR ;

  rc = access( fName, mode ) ;

  if( rc != 0 ) errmsg( fName ) ;

_door:

  return errRc ;
}

/******************************************************************************/
/*   file size                                                                */
/*                                                                            */
/*   return code:                                                             */
/*     size of the file if ok                                                 */
/*     -errno if error (negativ errno)                                        */
/******************************************************************************/
long fileSize( const char* fName )
{
  int sysRc ;
  struct stat fAttr ;

  sysRc = stat( fName, &fAttr ) ;

  if( sysRc != 0 )
  {
    sysRc = errno ;
    goto _door ;
  }

  return (long) fAttr.st_size ;

_door : 
  return -sysRc ;

}

/******************************************************************************/
/* flush the file                                                             */
/*                                                                            */
/*   equal to >>fileName                                                      */
/******************************************************************************/
int flushFile( const char* fName ) 
{
  int sysRc ;
  FILE  *fp ;

  sysRc = checkFileWrite( fName ) ;  // check if file can be rewriten
  if( sysRc != 0 )                   // if not return errno from func
  {                              //
    sysRc = errno ;                   //
    goto _door ;                    //
  }                                //
                                     //
  fp = fopen( fName, "w" ) ;         // open file 
  if( fp == NULL )                   // if error return errno from func
  {                                  //
    sysRc = errno ;                  //
    goto _door ;                     //
  }                                  //
                                     //
  sysRc = fclose( fp ) ;             // close file, (file is flushed)
  if( sysRc != 0 )                   // if err return errno form func
  {                                  //
    sysRc = errno ;                  //
    goto _door ;                     //
  }                                  //
                                     //
_door :
  return sysRc ;
}

/******************************************************************************/
/*   make recursive directory              */
/******************************************************************************/
int mkdirRecursive( const char *dir, mode_t mode )
{
  int sysRc = 0 ;
  char subDir[NAME_MAX];
  
  if( dir == NULL ) goto _door;

  sysRc = mkdir( dir, 0775 );                  // create goal directory 
  if( sysRc == -1 )                                 //
  {                                                //
    switch( errno )
    {
      case EEXIST: 
      {
        errno = 0;
	sysRc = 0;
	goto _door;
      }
      case ENOENT:
      {
        errno = 0;
	strcpy(subDir,dir);
	sysRc = mkdirRecursive( dirname((char*) subDir), mode );
        if( sysRc != 0 )
	{
          goto _door;
	}
        sysRc = mkdirRecursive( dir, mode );
        if( sysRc != 0 )
        {
          goto _door;
        }
	default :
        {
	  sysRc = errno ;
          goto _door;
        }
      }
    }
  }                                                //

  _door:

  return sysRc;
}