//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/berger/BergerTestPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BergerTestPkt_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(BergerTestPkt);

BergerTestPkt::BergerTestPkt(const char *name, int kind) : cPacket(name,kind)
{
    this->hops_var = 0;
}

BergerTestPkt::BergerTestPkt(const BergerTestPkt& other) : cPacket(other)
{
    copy(other);
}

BergerTestPkt::~BergerTestPkt()
{
}

BergerTestPkt& BergerTestPkt::operator=(const BergerTestPkt& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void BergerTestPkt::copy(const BergerTestPkt& other)
{
    this->route_var = other.route_var;
    this->hops_var = other.hops_var;
    this->nextHop_var = other.nextHop_var;
    this->dst_var = other.dst_var;
}

void BergerTestPkt::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->route_var);
    doPacking(b,this->hops_var);
    doPacking(b,this->nextHop_var);
    doPacking(b,this->dst_var);
}

void BergerTestPkt::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->route_var);
    doUnpacking(b,this->hops_var);
    doUnpacking(b,this->nextHop_var);
    doUnpacking(b,this->dst_var);
}

Route& BergerTestPkt::getRoute()
{
    return route_var;
}

void BergerTestPkt::setRoute(const Route& route)
{
    this->route_var = route;
}

int BergerTestPkt::getHops() const
{
    return hops_var;
}

void BergerTestPkt::setHops(int hops)
{
    this->hops_var = hops;
}

IPv4Address& BergerTestPkt::getNextHop()
{
    return nextHop_var;
}

void BergerTestPkt::setNextHop(const IPv4Address& nextHop)
{
    this->nextHop_var = nextHop;
}

IPv4Address& BergerTestPkt::getDst()
{
    return dst_var;
}

void BergerTestPkt::setDst(const IPv4Address& dst)
{
    this->dst_var = dst;
}

class BergerTestPktDescriptor : public cClassDescriptor
{
  public:
    BergerTestPktDescriptor();
    virtual ~BergerTestPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(BergerTestPktDescriptor);

BergerTestPktDescriptor::BergerTestPktDescriptor() : cClassDescriptor("BergerTestPkt", "cPacket")
{
}

BergerTestPktDescriptor::~BergerTestPktDescriptor()
{
}

bool BergerTestPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<BergerTestPkt *>(obj)!=NULL;
}

const char *BergerTestPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int BergerTestPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int BergerTestPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *BergerTestPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "route",
        "hops",
        "nextHop",
        "dst",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int BergerTestPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "route")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextHop")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *BergerTestPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "Route",
        "int",
        "IPv4Address",
        "IPv4Address",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *BergerTestPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int BergerTestPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    BergerTestPkt *pp = (BergerTestPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BergerTestPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    BergerTestPkt *pp = (BergerTestPkt *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRoute(); return out.str();}
        case 1: return long2string(pp->getHops());
        case 2: {std::stringstream out; out << pp->getNextHop(); return out.str();}
        case 3: {std::stringstream out; out << pp->getDst(); return out.str();}
        default: return "";
    }
}

bool BergerTestPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    BergerTestPkt *pp = (BergerTestPkt *)object; (void)pp;
    switch (field) {
        case 1: pp->setHops(string2long(value)); return true;
        default: return false;
    }
}

const char *BergerTestPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "Route",
        NULL,
        "IPv4Address",
        "IPv4Address",
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *BergerTestPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    BergerTestPkt *pp = (BergerTestPkt *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRoute()); break;
        case 2: return (void *)(&pp->getNextHop()); break;
        case 3: return (void *)(&pp->getDst()); break;
        default: return NULL;
    }
}


