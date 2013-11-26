//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/gr/GrNeighborInfo.msg.
//

#ifndef _GRNEIGHBORINFO_M_H_
#define _GRNEIGHBORINFO_M_H_

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
#include "IPv4Address.h"
// }}



/**
 * Class generated from <tt>networklayer/manetrouting/gr/GrNeighborInfo.msg</tt> by opp_msgc.
 * <pre>
 * packet GrNeighborInfo
 * {
 * 	IPv4Address routerAddress;
 * 	double routerXPos;
 * 	double routerYPos;
 * }
 * </pre>
 */
class INET_API GrNeighborInfo : public ::cPacket
{
  protected:
    IPv4Address routerAddress_var;
    double routerXPos_var;
    double routerYPos_var;

  private:
    void copy(const GrNeighborInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GrNeighborInfo&);

  public:
    GrNeighborInfo(const char *name=NULL, int kind=0);
    GrNeighborInfo(const GrNeighborInfo& other);
    virtual ~GrNeighborInfo();
    GrNeighborInfo& operator=(const GrNeighborInfo& other);
    virtual GrNeighborInfo *dup() const {return new GrNeighborInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual IPv4Address& getRouterAddress();
    virtual const IPv4Address& getRouterAddress() const {return const_cast<GrNeighborInfo*>(this)->getRouterAddress();}
    virtual void setRouterAddress(const IPv4Address& routerAddress);
    virtual double getRouterXPos() const;
    virtual void setRouterXPos(double routerXPos);
    virtual double getRouterYPos() const;
    virtual void setRouterYPos(double routerYPos);
};

inline void doPacking(cCommBuffer *b, GrNeighborInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, GrNeighborInfo& obj) {obj.parsimUnpack(b);}


#endif // _GRNEIGHBORINFO_M_H_
