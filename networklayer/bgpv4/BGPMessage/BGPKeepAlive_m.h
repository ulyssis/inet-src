//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/bgpv4/BGPMessage/BGPKeepAlive.msg.
//

#ifndef _BGPKEEPALIVE_M_H_
#define _BGPKEEPALIVE_M_H_

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
#include "BGPHeader_m.h"
// }}



/**
 * Class generated from <tt>networklayer/bgpv4/BGPMessage/BGPKeepAlive.msg</tt> by opp_msgc.
 * <pre>
 * packet BGPKeepAliveMessage extends BGPHeader
 * {
 *     type = BGP_KEEPALIVE;
 * }
 * </pre>
 */
class INET_API BGPKeepAliveMessage : public ::BGPHeader
{
  protected:

  private:
    void copy(const BGPKeepAliveMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const BGPKeepAliveMessage&);

  public:
    BGPKeepAliveMessage(const char *name=NULL, int kind=0);
    BGPKeepAliveMessage(const BGPKeepAliveMessage& other);
    virtual ~BGPKeepAliveMessage();
    BGPKeepAliveMessage& operator=(const BGPKeepAliveMessage& other);
    virtual BGPKeepAliveMessage *dup() const {return new BGPKeepAliveMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
};

inline void doPacking(cCommBuffer *b, BGPKeepAliveMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, BGPKeepAliveMessage& obj) {obj.parsimUnpack(b);}


#endif // _BGPKEEPALIVE_M_H_
