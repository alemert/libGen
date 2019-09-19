/******************************************************************************/
/*       l o g g e r   s t a n d a r d   m e s s a g e   c a t a l o g        */
/******************************************************************************/

#ifndef _LG_XYM_CAT_
#define _LG_XYM_CAT_

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define     LXYM_SEND_INF        2000
#define LEV_LXYM_SEND_INF        INF
#define TXT_LXYM_SEND_INF        "Messae send to Xymon with status %s" 

#define     LXYM_SEND_ERR        2001
#define LEV_LXYM_SEND_ERR        ERR
#define TXT_LXYM_SEND_ERR        "Messae send to Xymon with status %s" 

#define     LXYM_NO_RECIPIENT    2010
#define LEV_LXYM_NO_RECIPIENT    ERR
#define TXT_LXYM_NO_RECIPIENT    "no xymon recipients listed, XMSRV=NULL adn XMSERVERS=NULL"

#define     LXYM_HTTP_RECIPIENT  2011
#define LEV_LXYM_HTTP_RECIPIENT  ERR
#define TXT_LXYM_HTTP_RECIPIENT  "Unable to parse HTTP recipient"

#define     LXYM_RECONNECT       2012
#define LEV_LXYM_RECONNECT       INF
#define TXT_LXYM_RECONNECT       "reconnect to adress %s port %d"

#define     LXYM_CONNECT_ERROR   2013
#define LEV_LXYM_CONNECT_ERROR   WAR
#define TXT_LXYM_CONNECT_ERROR   "connect to Xymon daemon@%s:%d failed (%s)"

#define     LXYM_SEND_ERROR     2014
#define LEV_LXYM_SEND_ERROR     WAR
#define TXT_LXYM_SEND_ERROR     "%s error while sending to Xymon daemon@%s:%d"

#define     LXYM_SEND_TIMEOUT     2015
#define LEV_LXYM_SEND_TIMEOUT     WAR
#define TXT_LXYM_SEND_TIMEOUT     "Timeout while talking to Xymon daemon@%s:%d - retrying"

#define     LXYM_CONN_CLOSE     2016
#define LEV_LXYM_CONN_CLOSE     DBG
#define TXT_LXYM_CONN_CLOSE     "Connection to xymon deamon closed"

#define     LXYM_SETUP     2017
#define LEV_LXYM_SETUP     DBG
#define TXT_LXYM_SETUP     "Transport setup is xymondportnumber = %d xymonproxyhost = %s xymonproxyport %d"

#define     LXYM_RECIPIENT_LIST  2030
#define LEV_LXYM_RECIPIENT_LIST  DBG
#define TXT_LXYM_RECIPIENT_LIST  "recipient listed as %s"

#define     LXYM_PORT            2031
#define LEV_LXYM_PORT            DBG
#define TXT_LXYM_PORT            "working with xymon port %d"

#define     LXYM_HTTP_HOST       2032
#define LEV_LXYM_HTTP_HOST       DBG
#define TXT_LXYM_HTTP_HOST       "Xymon: HTTP protocol directtly to host %s"

#define     LXYM_HTTP_PROXY      2033
#define LEV_LXYM_HTTP_PROXY      DBG
#define TXT_LXYM_HTTP_PROXY      "Xymon: HTTP protocol via proxy to host %s"

#define     LXYM_HTTP_MSG        2034
#define LEV_LXYM_HTTP_MSG        DBG
#define TXT_LXYM_HTTP_MSG        "HTTP message is %s"

#endif
