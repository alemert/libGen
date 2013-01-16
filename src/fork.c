/******************************************************************************/
/*                        F O R K   U T I L I T I E S                         */
/*                                                                            */
/*   functions:                                                               */
/*     - startChild                                                           */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
/*   fork and exec process                                                    */
/******************************************************************************/
int startChild( const char *prg, char *stdOutFile,
                                 char *stdErrFile,
                                 char **cmdLn    )
{
  int errRc   = NO_ERROR ;  // buffer for errno
  int childRc = NO_ERROR ;  // exit code of child process
                            //
  pid_t pid ;               // pid of the forked process

  int stdOut[2] ;    // child to parent stdout
  int stdErr[2] ;    // child to parent stderr
  int stdIn[2]  ;    // parent to child stdout
  int stdOutRc  ;    // rc for reading from stdout
  int stdErrRc  ;    // rc for reading from stderr

  FILE *stdOutFp ;
  FILE *stdErrFp ;

  #define PIPE_BUFF_LEN   128

  char stdOutBuff[128] ;
  char stdErrBuff[128] ;

  // -------------------------------------------------------
  // defines with scope in this function
  // -------------------------------------------------------
  #define CHILD_2_PARENT_STD_WRITE   stdOut[1]
  #define CHILD_2_PARENT_STD_READ    stdOut[0]
  #define CHILD_2_PARENT_ERR_WRITE   stdErr[1]
  #define CHILD_2_PARENT_ERR_READ    stdErr[0]
  #define PARENT_2_CHILD_STD_WRITE   stdIn[1]
  #define PARENT_2_CHILD_STD_READ    stdIn[0]

  // -------------------------------------------------------
  // open the pipes
  // -------------------------------------------------------
  if( pipe( stdOut ) )
  {                        //
    errRc = errno  ;       // error handling
    perror("pipe") ;       // no automatic test for pipe()
    goto _door     ;       // quit function with errno
  }

  if( pipe( stdErr ) )
  {                        //
    errRc = errno  ;       // error handling
    perror("pipe") ;       // no automatic test for pipe()
    goto _door     ;       // quit function with errno
  }

  if( pipe( stdIn ) )
  {                        //
    errRc = errno  ;       // error handling
    perror("pipe") ;       // no automatic test for pipe()
    goto _door     ;       // quit function with errno
  }

  pid = fork() ;

  #ifdef __TDD__
    printf("%s(%d)pid=%d\n",__FILE__,__LINE__,pid);
  #endif

  switch( pid )
  {
    // -----------------------------------------------------
    // fork failed, quit function with errno
    // -----------------------------------------------------
    case -1 :
      errRc = errno ;
      perror("fork");
      break ;

    // -----------------------------------------------------
    // process is a child
    // -----------------------------------------------------
    case 0 :
      // ---------------------------------------------------
      // re-arange stdin / stdout
      // ---------------------------------------------------
      close( CHILD_2_PARENT_STD_READ )  ;  // close all file descriptors
      close( CHILD_2_PARENT_ERR_READ )  ;  //   that are not needed by child
      close( PARENT_2_CHILD_STD_WRITE ) ;  //

      dup2(  CHILD_2_PARENT_STD_WRITE , STDOUT_FILENO ) ;
      close( CHILD_2_PARENT_STD_WRITE ) ;
      dup2(  CHILD_2_PARENT_ERR_WRITE , STDERR_FILENO ) ;
      close( CHILD_2_PARENT_ERR_WRITE ) ;
      dup2(  PARENT_2_CHILD_STD_READ  , STDIN_FILENO  ) ;
      close( PARENT_2_CHILD_STD_READ  ) ;

      // ---------------------------------------------------
      // execv
      //  execv(binary,argv)
      //    binary  -> program name
      //    argv[0] -> process name
      //    argv[1..n] -> program attributes
      //    argv[n+1]  -> NULL
      // ---------------------------------------------------
      execv( prg, cmdLn ) ;

      errRc = errno ;  // this point can be reached only if error
      goto _door    ;

    // -----------------------------------------------------
    // process is parent
    // -----------------------------------------------------
    default :
      close( CHILD_2_PARENT_STD_WRITE ) ;  // close all file descriptors
      close( CHILD_2_PARENT_ERR_WRITE ) ;  //   not needed by parent
      close( PARENT_2_CHILD_STD_READ  ) ;  //
                                           //
      // ---------------------------------------------------
      // open files
      // ---------------------------------------------------
      stdOutFp = fopen( stdOutFile, "w" ) ;
      if( stdOutFp == NULL )
      {
        errRc = errno  ;       // error handling
        perror( stdOutFile ) ; //
        goto _door     ;       // quit function with errno
      }
 
      stdErrFp = fopen( stdErrFile, "w" ) ;
      if( stdErrFp == NULL )
      {
        errRc = errno  ;       // error handling
        perror( stdErrFile ) ; //
        goto _door     ;       // quit function with errno
      }

      // ---------------------------------------------------
      // loop until child is running
      // and until data to read on stdout or stderr (to read is correct)
      // ---------------------------------------------------
      while( 1 )                                    // loop until child runnig
      {                                             //
        while( 1 )                                  // loop until reading
        {                                           //   from pipes
          memset( stdOutBuff, '\0', 128 ) ;         // flush pipe buffer
          stdOutRc = read( CHILD_2_PARENT_STD_READ, // read from pipe
                           stdOutBuff,              //
                           PIPE_BUFF_LEN - 1 ) ;    //
          if( stdOutRc > 0 )                        // if somthing found on pipe
          {                                         //  print it out
            fprintf(stdOutFp,"%.128s",stdOutBuff);  //
          }                                         //
                                                    //
          memset( stdErrBuff, '\0', 128 ) ;         // flush pipe buffer
          stdErrRc = read( CHILD_2_PARENT_ERR_READ, // read from pipe
                           stdErrBuff,              //
                           PIPE_BUFF_LEN-1 );       //
          if( stdErrRc > 0 )                        // if somthing found on pipe
          {                                         //  print it out
            fprintf(stdErrFp,"%.128s",stdErrBuff);  //
          }                                         //
                                                    //
          if( (stdOutRc + stdErrRc) == 0 ) break ;  // if stdout and stderr
        }                                           //   empty -> break loop
                                                    //
        if( waitpid(pid,&childRc,WNOHANG)!=pid )    // if child ended
        {                                           //   -> break loop
           break ;                                  //
        }                                           //
      }                                             //
                                                    //
      childRc >>=   8 ;                             // get exit code from child
      childRc &=  127 ;                             //
      break ;                                       // break out switch: case
  }

  #ifdef __TDD__
    printf("%s(%d) rc=%d\n",__FILE__,__LINE__,childRc);
  #endif
_door :

  fclose( stdOutFp ) ;
  fclose( stdErrFp ) ;

  if( childRc > 0 ) return childRc ;
  return errRc ;
}
 
