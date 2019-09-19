/******************************************************************************/
/*       l o g g e r   m q   e v e n t   m e s s a g e   c a t a l o g        */
/******************************************************************************/

#ifndef _LG_MQE_CAT_
#define _LG_MQE_CAT_

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
#define     LEVN_EVENT_ITEM_NOT_EXIST     3010
#define LEV_LEVN_EVENT_ITEM_NOT_EXIST     ERR
#define TXT_LEVN_EVENT_ITEM_NOT_EXIST     "event item %s does not exist"

#define     LEVN_EVENT_ITEM_TYPE_ERROR    3011
#define LEV_LEVN_EVENT_ITEM_TYPE_ERROR    ERR
#define TXT_LEVN_EVENT_ITEM_TYPE_ERROR    "event item %s has an unexpected type"

#define     LEVN_MISSING_CODE_FOR_SELECTOR  3012
#define LEV_LEVN_MISSING_CODE_FOR_SELECTOR  ERR
#define TXT_LEVN_MISSING_CODE_FOR_SELECTOR  "missing code for selector %d file: %s at line %d"

#define     LEVN_XML_UNKNWOWN_SELECTOR  3015
#define LEV_LEVN_XML_UNKNWOWN_SELECTOR  ERR
#define TXT_LEVN_XML_UNKNWOWN_SELECTOR  "Unknown selector %s found in xml file %s"

#endif
