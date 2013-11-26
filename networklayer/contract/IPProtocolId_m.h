//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/contract/IPProtocolId.msg.
//

#ifndef _IPPROTOCOLID_M_H_
#define _IPPROTOCOLID_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0403
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API 
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API 
#  endif
#endif

// cplusplus {{
#include "INETDefs.h"
// }}



/**
 * Enum generated from <tt>networklayer/contract/IPProtocolId.msg</tt> by opp_msgc.
 * <pre>
 * enum IPProtocolId
 * {
 * 
 *     
 *     IP_PROT_ICMP = 1;
 *     IP_PROT_IGMP = 2;
 *     IP_PROT_IP = 4; 
 *     IP_PROT_TCP = 6;
 *     IP_PROT_EGP = 8;
 *     IP_PROT_IGP = 9;
 *     IP_PROT_UDP = 17;
 *     IP_PROT_XTP = 36;
 *     IP_PROT_IPv6 = 41;
 *     IP_PROT_RSVP = 46;
 *     IP_PROT_IPv6_ICMP = 58;
 *     IP_PROT_NONE = 59;
 *     IP_PROT_OSPF = 89;
 *     IP_PROT_SCTP = 132;
 *     IP_PROT_DSR  = 48;
 *     IP_PROT_MANET = 138;
 * 	IP_PROT_BERGER = 253; 
 * 
 *     IP_PROT_IPv6EXT_HOP = 0;       
 *     IP_PROT_IPv6EXT_DEST = 60;     
 *     IP_PROT_IPv6EXT_ROUTING = 43;  
 *     IP_PROT_IPv6EXT_FRAGMENT = 44; 
 *     IP_PROT_IPv6EXT_AUTH = 51;     
 *     IP_PROT_IPv6EXT_ESP = 50;      
 *     IP_PROT_IPv6EXT_MOB = 135;      
 * }
 * </pre>
 */
enum IPProtocolId {
    IP_PROT_ICMP = 1,
    IP_PROT_IGMP = 2,
    IP_PROT_IP = 4,
    IP_PROT_TCP = 6,
    IP_PROT_EGP = 8,
    IP_PROT_IGP = 9,
    IP_PROT_UDP = 17,
    IP_PROT_XTP = 36,
    IP_PROT_IPv6 = 41,
    IP_PROT_RSVP = 46,
    IP_PROT_IPv6_ICMP = 58,
    IP_PROT_NONE = 59,
    IP_PROT_OSPF = 89,
    IP_PROT_SCTP = 132,
    IP_PROT_DSR = 48,
    IP_PROT_MANET = 138,
    IP_PROT_BERGER = 253,
    IP_PROT_IPv6EXT_HOP = 0,
    IP_PROT_IPv6EXT_DEST = 60,
    IP_PROT_IPv6EXT_ROUTING = 43,
    IP_PROT_IPv6EXT_FRAGMENT = 44,
    IP_PROT_IPv6EXT_AUTH = 51,
    IP_PROT_IPv6EXT_ESP = 50,
    IP_PROT_IPv6EXT_MOB = 135
};


#endif // _IPPROTOCOLID_M_H_
