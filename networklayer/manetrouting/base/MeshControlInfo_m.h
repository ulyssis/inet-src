//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/base/MeshControlInfo.msg.
//

#ifndef _MESHCONTROLINFO_M_H_
#define _MESHCONTROLINFO_M_H_

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
#include "Ieee802Ctrl_m.h"
#include "uint128.h"
// }}



/**
 * Class generated from <tt>networklayer/manetrouting/base/MeshControlInfo.msg</tt> by opp_msgc.
 * <pre>
 * class MeshControlInfo extends Ieee802Ctrl
 * {
 * 
 *     int inputId;     
 *     bool previousFix; 
 *     Uint128 vectorAddress[]; 
 * }
 * </pre>
 */
class INET_API MeshControlInfo : public ::Ieee802Ctrl
{
  protected:
    int inputId_var;
    bool previousFix_var;
    Uint128 *vectorAddress_var; // array ptr
    unsigned int vectorAddress_arraysize;

  private:
    void copy(const MeshControlInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MeshControlInfo&);

  public:
    MeshControlInfo();
    MeshControlInfo(const MeshControlInfo& other);
    virtual ~MeshControlInfo();
    MeshControlInfo& operator=(const MeshControlInfo& other);
    virtual MeshControlInfo *dup() const {return new MeshControlInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getInputId() const;
    virtual void setInputId(int inputId);
    virtual bool getPreviousFix() const;
    virtual void setPreviousFix(bool previousFix);
    virtual void setVectorAddressArraySize(unsigned int size);
    virtual unsigned int getVectorAddressArraySize() const;
    virtual Uint128& getVectorAddress(unsigned int k);
    virtual const Uint128& getVectorAddress(unsigned int k) const {return const_cast<MeshControlInfo*>(this)->getVectorAddress(k);}
    virtual void setVectorAddress(unsigned int k, const Uint128& vectorAddress);
};

inline void doPacking(cCommBuffer *b, MeshControlInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MeshControlInfo& obj) {obj.parsimUnpack(b);}


#endif // _MESHCONTROLINFO_M_H_
