/******************************************************************************/
/* change title on for new project                                            */
/******************************************************************************/

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/

// ---------------------------------------------------------
// system
// ---------------------------------------------------------
#include <string.h>

// ---------------------------------------------------------
// MQ
// ---------------------------------------------------------
#include <cmqc.h>
#include <cmqbc.h>
#include <cmqcfc.h>

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------
#include <msgcat/lgmqm.h>
#include <mqreason.h>
#include <mqdump.h>

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/

/******************************************************************************/
/*   G L O B A L E S                                                          */
/******************************************************************************/
#ifdef C_MODULE_MQ_BASE
  MQGMO _gDefGMO = {MQGMO_DEFAULT} ;
#else
  extern MQGMO _gDefGMO ;
#endif

/******************************************************************************/
/*   M A C R O S                                                              */
/******************************************************************************/
#define logMQCall( lev, call, reason ) logger( LMQM_ ##lev ##_CALL       , \
                                                call                     , \
                                                (char*) mqrc2str( reason ) )

#define mqOpenUserBag(  pBag ) mqOpenBagAPI( MQCBO_USER_BAG,  pBag );
#define mqOpenAdminBag( pBag ) mqOpenBagAPI( MQCBO_ADMIN_BAG, pBag );

#define mqSetInqAttr(     bag, ... )                              \
        mqAddInqAttrFunc( bag,                                    \
                          ( sizeof( (MQLONG[]){0,##__VA_ARGS__} ) \
                            / sizeof(MQLONG)-1)                 , \
                           ##__VA_ARGS__      )

#if(0)
#define mqOpenQueue( queue, hConn, ObjDesc, opt, pHobj )           \
        {                                            \
          memcpy( ObjDesc.ObjectName, queue, MQ_Q_NAME_LENGTH ) ; \
          mqOpenObject( hConn, &ObjDesc, opt, pHobj ) ;           \
        }
#endif

/******************************************************************************/
/*   P R O T O T Y P E S                                                      */
/******************************************************************************/
MQLONG mqConn( char* qmName, PMQHCONN pHconn ) ;
MQLONG mqDisc( PMQHCONN pHconn ) ;

MQLONG mqOpenObject( MQHCONN hConn    , // connection handle
                     PMQOD   pObjDesc , // pointer to object descriptor
                     MQLONG  options  , // options for MQOPEN
                     PMQHOBJ pHobj  ) ; // pointer to object handle
                                        //
MQLONG mqCloseObject( MQHCONN hConn   , // connection handle
                      PMQHOBJ pHobj ) ; // pointer to object handle
                                        //
MQLONG mqPut( MQHCONN _hConn      ,     // connection handle
              MQHOBJ  _hQueue     ,     // pointer to queue handle
              PMQMD   _msgDscr    ,     // message descriptor
              PMQPMO  _pPutMsgOpt ,     // Options controlling MQPUT
              PMQVOID _buffer     ,     // message buffer
              MQLONG  _msgLng    );     // message length (buffer length)
                                        //
MQLONG mqGet( MQHCONN _hConn      ,     // connection handle
              MQHOBJ  _hQueue     ,     // pointer to queue handle
              PMQVOID _buffer     ,     // message buffer
              PMQLONG _bufLng     ,     // buffer length
              PMQMD   _msgDscr    ,     // message descriptor
              MQGMO   _getMsgOpt  ,     // wait interval
              MQLONG  _wait      );     // get message option
                                        //
MQLONG mqBegin(    MQHCONN _hConn );    // connection handle
MQLONG mqCommit(   MQHCONN _hConn );    // connection handle
MQLONG mqRollback( MQHCONN _hConn );    // connection handle
MQLONG mqSetTrigger( MQHCONN Hconn  ,   // connection handle
                     MQHOBJ  Hqueue);   // queue handle

PMQVOID resizeMqMessageBuffer( PMQVOID message, PMQLONG newSize );

MQLONG mqTrimStr( MQLONG _buffLng, PMQCHAR _pBuff, PMQCHAR _pStr );

MQLONG mqOpenBagAPI(  MQLONG opt       ,   // Bag options
                      PMQHBAG bag     );
MQLONG mqCloseBag(    PMQHBAG bag     );

MQLONG mqReadBag(  MQHCONN hConn    ,
                   MQHOBJ  odQueue  ,
                   PMQMD   msgDscr  ,
                   PMQGMO  getMsgOpt,
                   MQHBAG  bag     );


MQLONG mqResetQmgrLog( MQHCONN Hconn ); 

MQLONG mqExecPcf( MQHCONN _hConn   ,     // connection handle
                  MQLONG  _pcfCmd  ,     // PCF command
                  MQHBAG  _cmdBag  ,     // command bag
                  MQHBAG  _resBag );     // response bag

MQLONG mqAddInqAttrFunc( MQHBAG bag ,    // Admin-bag
                         int     argc,   // amount of inquire attributes
                         ...        );   // va_args list of inquire attributes

MQLONG mqAddStr( MQHBAG _bag      , 
		 MQLONG _selector ,
		 MQLONG _buffLng  ,
		 PMQCHAR _buffer );

MQLONG mqAddInt( MQHBAG _bag     , 
		 MQLONG _selector,
		 MQLONG _value );

MQLONG mqBagCountItem( MQHBAG _bag      , 
                       MQLONG _selector);


MQLONG mqItemInfoInq( MQHBAG _bag           , 
                      MQLONG _selector      ,
                      MQLONG index          , 
                      PMQLONG _pOutSelector , 
                      PMQLONG _pOutItemType);

MQLONG mqIntInq( MQHBAG _bag       , 
                 MQLONG _selector  ,
                 MQLONG _index     , 
                 PMQINT32 _pSelVal);

MQLONG mqBagInq( MQHBAG _inBag, 
                 MQLONG _cnt, 
                 PMQHBAG _outBag );

MQLONG mqStrInq( MQHBAG _bag       ,   // admin bag
                 MQLONG _selector  ,   // selector
                 MQLONG _itemIndex ,   // item index
                 MQLONG _maxBuffLng,   // buffer length
                 PMQCHAR _buffer   ,   // buffer
                 PMQLONG _lng     );   // real buffer length

MQLONG mqAddStrFilter( MQHBAG _bag       ,  // command bag
                       MQLONG _selector  ,  // selector
                       MQLONG _buffLng   ,  // buffer length
                       PMQCHAR _buffer   ,  // buffer
                       MQLONG  _operator);  // compare operator
