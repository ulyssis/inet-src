//
// Generated file, do not edit! Created by opp_msgc 4.3 from transport/contract/SCTPCommand.msg.
//

#ifndef _SCTPCOMMAND_M_H_
#define _SCTPCOMMAND_M_H_

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
#include <vector>

#include "IPvXAddress.h"
#include "SCTPCommand.h"

typedef std::vector<IPvXAddress> AddressVector;
// }}



/**
 * Enum generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * enum SCTPErrorCode
 * {
 * 
 * }
 * </pre>
 */
enum SCTPErrorCode {
};

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPCommand extends cPacket
 * {
 *     int assocId = -1;   
 *     int sid = -1;
 *     int numMsgs = 1;
 *     int ssn = -1;
 *     unsigned short sendUnordered = false;
 *     double lifetime = 0;
 *     IPvXAddress localAddr = IPvXAddress("0.0.0.0");
 *     IPvXAddress remoteAddr = IPvXAddress("0.0.0.0");
 *     int gate = -1;
 * }
 * </pre>
 */
class INET_API SCTPCommand : public ::cPacket
{
  protected:
    int assocId_var;
    int sid_var;
    int numMsgs_var;
    int ssn_var;
    unsigned short sendUnordered_var;
    double lifetime_var;
    IPvXAddress localAddr_var;
    IPvXAddress remoteAddr_var;
    int gate_var;

  private:
    void copy(const SCTPCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPCommand&);

  public:
    SCTPCommand(const char *name=NULL);
    SCTPCommand(const SCTPCommand& other);
    virtual ~SCTPCommand();
    SCTPCommand& operator=(const SCTPCommand& other);
    virtual SCTPCommand *dup() const {return new SCTPCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getAssocId() const;
    virtual void setAssocId(int assocId);
    virtual int getSid() const;
    virtual void setSid(int sid);
    virtual int getNumMsgs() const;
    virtual void setNumMsgs(int numMsgs);
    virtual int getSsn() const;
    virtual void setSsn(int ssn);
    virtual unsigned short getSendUnordered() const;
    virtual void setSendUnordered(unsigned short sendUnordered);
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
    virtual IPvXAddress& getLocalAddr();
    virtual const IPvXAddress& getLocalAddr() const {return const_cast<SCTPCommand*>(this)->getLocalAddr();}
    virtual void setLocalAddr(const IPvXAddress& localAddr);
    virtual IPvXAddress& getRemoteAddr();
    virtual const IPvXAddress& getRemoteAddr() const {return const_cast<SCTPCommand*>(this)->getRemoteAddr();}
    virtual void setRemoteAddr(const IPvXAddress& remoteAddr);
    virtual int getGate() const;
    virtual void setGate(int gate);
};

inline void doPacking(cCommBuffer *b, SCTPCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPErrorInfo extends SCTPCommand
 * {
 *     int errorCode enum(SCTPErrorCode);
 *     string messageText;
 * }
 * </pre>
 */
class INET_API SCTPErrorInfo : public ::SCTPCommand
{
  protected:
    int errorCode_var;
    opp_string messageText_var;

  private:
    void copy(const SCTPErrorInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPErrorInfo&);

  public:
    SCTPErrorInfo(const char *name=NULL);
    SCTPErrorInfo(const SCTPErrorInfo& other);
    virtual ~SCTPErrorInfo();
    SCTPErrorInfo& operator=(const SCTPErrorInfo& other);
    virtual SCTPErrorInfo *dup() const {return new SCTPErrorInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getErrorCode() const;
    virtual void setErrorCode(int errorCode);
    virtual const char * getMessageText() const;
    virtual void setMessageText(const char * messageText);
};

inline void doPacking(cCommBuffer *b, SCTPErrorInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPErrorInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPOpenCommand extends SCTPCommand
 * {
 *    
 *     AddressVector localAddresses;
 *     IPvXAddress remoteAddr;            
 *     AddressVector remoteAddresses;
 *     int localPort = -1;              
 *     int remotePort = -1;             
 *     bool fork = false;               
 *     string queueClass = "SCTPQueue"; 
 *     string sctpAlgorithmClass;       
 *     uint32 inboundStreams;
 *     uint32 outboundStreams;
 *     uint32 numRequests;
 *     uint32 messagesToPush;
 * }
 * </pre>
 */
class INET_API SCTPOpenCommand : public ::SCTPCommand
{
  protected:
    AddressVector localAddresses_var;
    IPvXAddress remoteAddr_var;
    AddressVector remoteAddresses_var;
    int localPort_var;
    int remotePort_var;
    bool fork_var;
    opp_string queueClass_var;
    opp_string sctpAlgorithmClass_var;
    uint32 inboundStreams_var;
    uint32 outboundStreams_var;
    uint32 numRequests_var;
    uint32 messagesToPush_var;

  private:
    void copy(const SCTPOpenCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPOpenCommand&);

  public:
    SCTPOpenCommand(const char *name=NULL);
    SCTPOpenCommand(const SCTPOpenCommand& other);
    virtual ~SCTPOpenCommand();
    SCTPOpenCommand& operator=(const SCTPOpenCommand& other);
    virtual SCTPOpenCommand *dup() const {return new SCTPOpenCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual AddressVector& getLocalAddresses();
    virtual const AddressVector& getLocalAddresses() const {return const_cast<SCTPOpenCommand*>(this)->getLocalAddresses();}
    virtual void setLocalAddresses(const AddressVector& localAddresses);
    virtual IPvXAddress& getRemoteAddr();
    virtual const IPvXAddress& getRemoteAddr() const {return const_cast<SCTPOpenCommand*>(this)->getRemoteAddr();}
    virtual void setRemoteAddr(const IPvXAddress& remoteAddr);
    virtual AddressVector& getRemoteAddresses();
    virtual const AddressVector& getRemoteAddresses() const {return const_cast<SCTPOpenCommand*>(this)->getRemoteAddresses();}
    virtual void setRemoteAddresses(const AddressVector& remoteAddresses);
    virtual int getLocalPort() const;
    virtual void setLocalPort(int localPort);
    virtual int getRemotePort() const;
    virtual void setRemotePort(int remotePort);
    virtual bool getFork() const;
    virtual void setFork(bool fork);
    virtual const char * getQueueClass() const;
    virtual void setQueueClass(const char * queueClass);
    virtual const char * getSctpAlgorithmClass() const;
    virtual void setSctpAlgorithmClass(const char * sctpAlgorithmClass);
    virtual uint32 getInboundStreams() const;
    virtual void setInboundStreams(uint32 inboundStreams);
    virtual uint32 getOutboundStreams() const;
    virtual void setOutboundStreams(uint32 outboundStreams);
    virtual uint32 getNumRequests() const;
    virtual void setNumRequests(uint32 numRequests);
    virtual uint32 getMessagesToPush() const;
    virtual void setMessagesToPush(uint32 messagesToPush);
};

inline void doPacking(cCommBuffer *b, SCTPOpenCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPOpenCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPSendCommand extends SCTPCommand
 * {
 *     bool last;
 *     unsigned int ppid = 0;
 *     bool primary = true;
 * }
 * </pre>
 */
class INET_API SCTPSendCommand : public ::SCTPCommand
{
  protected:
    bool last_var;
    unsigned int ppid_var;
    bool primary_var;

  private:
    void copy(const SCTPSendCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPSendCommand&);

  public:
    SCTPSendCommand(const char *name=NULL);
    SCTPSendCommand(const SCTPSendCommand& other);
    virtual ~SCTPSendCommand();
    SCTPSendCommand& operator=(const SCTPSendCommand& other);
    virtual SCTPSendCommand *dup() const {return new SCTPSendCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool getLast() const;
    virtual void setLast(bool last);
    virtual unsigned int getPpid() const;
    virtual void setPpid(unsigned int ppid);
    virtual bool getPrimary() const;
    virtual void setPrimary(bool primary);
};

inline void doPacking(cCommBuffer *b, SCTPSendCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPSendCommand& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPConnectInfo extends SCTPCommand
 * {
 *     
 *     
 *     AddressVector remoteAddresses;
 *     int localPort;
 *     int remotePort;
 *     int status;
 *     int inboundStreams;
 *     int outboundStreams;
 * }
 * </pre>
 */
class INET_API SCTPConnectInfo : public ::SCTPCommand
{
  protected:
    AddressVector remoteAddresses_var;
    int localPort_var;
    int remotePort_var;
    int status_var;
    int inboundStreams_var;
    int outboundStreams_var;

  private:
    void copy(const SCTPConnectInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPConnectInfo&);

  public:
    SCTPConnectInfo(const char *name=NULL);
    SCTPConnectInfo(const SCTPConnectInfo& other);
    virtual ~SCTPConnectInfo();
    SCTPConnectInfo& operator=(const SCTPConnectInfo& other);
    virtual SCTPConnectInfo *dup() const {return new SCTPConnectInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual AddressVector& getRemoteAddresses();
    virtual const AddressVector& getRemoteAddresses() const {return const_cast<SCTPConnectInfo*>(this)->getRemoteAddresses();}
    virtual void setRemoteAddresses(const AddressVector& remoteAddresses);
    virtual int getLocalPort() const;
    virtual void setLocalPort(int localPort);
    virtual int getRemotePort() const;
    virtual void setRemotePort(int remotePort);
    virtual int getStatus() const;
    virtual void setStatus(int status);
    virtual int getInboundStreams() const;
    virtual void setInboundStreams(int inboundStreams);
    virtual int getOutboundStreams() const;
    virtual void setOutboundStreams(int outboundStreams);
};

inline void doPacking(cCommBuffer *b, SCTPConnectInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPConnectInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPStatusInfo extends SCTPCommand
 * {
 *     int state;
 *     string stateName;
 *     IPvXAddress pathId;
 *     bool active;
 * }
 * </pre>
 */
class INET_API SCTPStatusInfo : public ::SCTPCommand
{
  protected:
    int state_var;
    opp_string stateName_var;
    IPvXAddress pathId_var;
    bool active_var;

  private:
    void copy(const SCTPStatusInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPStatusInfo&);

  public:
    SCTPStatusInfo(const char *name=NULL);
    SCTPStatusInfo(const SCTPStatusInfo& other);
    virtual ~SCTPStatusInfo();
    SCTPStatusInfo& operator=(const SCTPStatusInfo& other);
    virtual SCTPStatusInfo *dup() const {return new SCTPStatusInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getState() const;
    virtual void setState(int state);
    virtual const char * getStateName() const;
    virtual void setStateName(const char * stateName);
    virtual IPvXAddress& getPathId();
    virtual const IPvXAddress& getPathId() const {return const_cast<SCTPStatusInfo*>(this)->getPathId();}
    virtual void setPathId(const IPvXAddress& pathId);
    virtual bool getActive() const;
    virtual void setActive(bool active);
};

inline void doPacking(cCommBuffer *b, SCTPStatusInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPStatusInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPPathInfo extends SCTPCommand
 * {
 *     IPvXAddress remoteAddress;
 * }
 * </pre>
 */
class INET_API SCTPPathInfo : public ::SCTPCommand
{
  protected:
    IPvXAddress remoteAddress_var;

  private:
    void copy(const SCTPPathInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPPathInfo&);

  public:
    SCTPPathInfo(const char *name=NULL);
    SCTPPathInfo(const SCTPPathInfo& other);
    virtual ~SCTPPathInfo();
    SCTPPathInfo& operator=(const SCTPPathInfo& other);
    virtual SCTPPathInfo *dup() const {return new SCTPPathInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual IPvXAddress& getRemoteAddress();
    virtual const IPvXAddress& getRemoteAddress() const {return const_cast<SCTPPathInfo*>(this)->getRemoteAddress();}
    virtual void setRemoteAddress(const IPvXAddress& remoteAddress);
};

inline void doPacking(cCommBuffer *b, SCTPPathInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPPathInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPResetInfo extends SCTPCommand
 * {
 *     IPvXAddress remoteAddr;
 *     unsigned short requestType = 0;
 *     char streams[];
 * }
 * </pre>
 */
class INET_API SCTPResetInfo : public ::SCTPCommand
{
  protected:
    IPvXAddress remoteAddr_var;
    unsigned short requestType_var;
    char *streams_var; // array ptr
    unsigned int streams_arraysize;

  private:
    void copy(const SCTPResetInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPResetInfo&);

  public:
    SCTPResetInfo(const char *name=NULL);
    SCTPResetInfo(const SCTPResetInfo& other);
    virtual ~SCTPResetInfo();
    SCTPResetInfo& operator=(const SCTPResetInfo& other);
    virtual SCTPResetInfo *dup() const {return new SCTPResetInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual IPvXAddress& getRemoteAddr();
    virtual const IPvXAddress& getRemoteAddr() const {return const_cast<SCTPResetInfo*>(this)->getRemoteAddr();}
    virtual void setRemoteAddr(const IPvXAddress& remoteAddr);
    virtual unsigned short getRequestType() const;
    virtual void setRequestType(unsigned short requestType);
    virtual void setStreamsArraySize(unsigned int size);
    virtual unsigned int getStreamsArraySize() const;
    virtual char getStreams(unsigned int k) const;
    virtual void setStreams(unsigned int k, char streams);
};

inline void doPacking(cCommBuffer *b, SCTPResetInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPResetInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPInfo extends SCTPCommand
 * {
 *     int text = 0;
 * }
 * </pre>
 */
class INET_API SCTPInfo : public ::SCTPCommand
{
  protected:
    int text_var;

  private:
    void copy(const SCTPInfo& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPInfo&);

  public:
    SCTPInfo(const char *name=NULL);
    SCTPInfo(const SCTPInfo& other);
    virtual ~SCTPInfo();
    SCTPInfo& operator=(const SCTPInfo& other);
    virtual SCTPInfo *dup() const {return new SCTPInfo(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getText() const;
    virtual void setText(int text);
};

inline void doPacking(cCommBuffer *b, SCTPInfo& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPInfo& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>transport/contract/SCTPCommand.msg</tt> by opp_msgc.
 * <pre>
 * class SCTPRcvCommand extends SCTPCommand
 * {
 *     uint32 ppid;
 *     uint32 tsn;
 *     uint32 cumTsn;
 * }
 * </pre>
 */
class INET_API SCTPRcvCommand : public ::SCTPCommand
{
  protected:
    uint32 ppid_var;
    uint32 tsn_var;
    uint32 cumTsn_var;

  private:
    void copy(const SCTPRcvCommand& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const SCTPRcvCommand&);

  public:
    SCTPRcvCommand(const char *name=NULL);
    SCTPRcvCommand(const SCTPRcvCommand& other);
    virtual ~SCTPRcvCommand();
    SCTPRcvCommand& operator=(const SCTPRcvCommand& other);
    virtual SCTPRcvCommand *dup() const {return new SCTPRcvCommand(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual uint32 getPpid() const;
    virtual void setPpid(uint32 ppid);
    virtual uint32 getTsn() const;
    virtual void setTsn(uint32 tsn);
    virtual uint32 getCumTsn() const;
    virtual void setCumTsn(uint32 cumTsn);
};

inline void doPacking(cCommBuffer *b, SCTPRcvCommand& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, SCTPRcvCommand& obj) {obj.parsimUnpack(b);}


#endif // _SCTPCOMMAND_M_H_
