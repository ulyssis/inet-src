//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/dymo_fau/DYMO_Packet.msg.
//

#ifndef _DYMO_PACKET_M_H_
#define _DYMO_PACKET_M_H_

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



/**
 * Class generated from <tt>networklayer/manetrouting/dymo_fau/DYMO_Packet.msg</tt> by opp_msgc.
 * <pre>
 * message DYMO_Packet extends cPacket
 * {
 *     unsigned int nextHopAddress;
 *     unsigned int destAddress;
 *     unsigned int srcAddress;
 *     simtime_t creationTime;
 * }
 * </pre>
 */
class INET_API DYMO_Packet : public ::cPacket
{
  protected:
    unsigned int nextHopAddress_var;
    unsigned int destAddress_var;
    unsigned int srcAddress_var;
    simtime_t creationTime_var;

  private:
    void copy(const DYMO_Packet& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DYMO_Packet&);

  public:
    DYMO_Packet(const char *name=NULL, int kind=0);
    DYMO_Packet(const DYMO_Packet& other);
    virtual ~DYMO_Packet();
    DYMO_Packet& operator=(const DYMO_Packet& other);
    virtual DYMO_Packet *dup() const {return new DYMO_Packet(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned int getNextHopAddress() const;
    virtual void setNextHopAddress(unsigned int nextHopAddress);
    virtual unsigned int getDestAddress() const;
    virtual void setDestAddress(unsigned int destAddress);
    virtual unsigned int getSrcAddress() const;
    virtual void setSrcAddress(unsigned int srcAddress);
    virtual simtime_t getCreationTime() const;
    virtual void setCreationTime(simtime_t creationTime);
};

inline void doPacking(cCommBuffer *b, DYMO_Packet& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, DYMO_Packet& obj) {obj.parsimUnpack(b);}


#endif // _DYMO_PACKET_M_H_
