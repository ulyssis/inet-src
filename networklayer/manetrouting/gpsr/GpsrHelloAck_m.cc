//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/gpsr/GpsrHelloAck.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GpsrHelloAck_m.h"

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




Register_Class(GpsrHelloAck);

GpsrHelloAck::GpsrHelloAck(const char *name, int kind) : cPacket(name,kind)
{
}

GpsrHelloAck::GpsrHelloAck(const GpsrHelloAck& other) : cPacket(other)
{
    copy(other);
}

GpsrHelloAck::~GpsrHelloAck()
{
}

GpsrHelloAck& GpsrHelloAck::operator=(const GpsrHelloAck& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void GpsrHelloAck::copy(const GpsrHelloAck& other)
{
    this->myAddress_var = other.myAddress_var;
    this->DstAddress_var = other.DstAddress_var;
    this->MyPos_var = other.MyPos_var;
}

void GpsrHelloAck::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->myAddress_var);
    doPacking(b,this->DstAddress_var);
    doPacking(b,this->MyPos_var);
}

void GpsrHelloAck::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->myAddress_var);
    doUnpacking(b,this->DstAddress_var);
    doUnpacking(b,this->MyPos_var);
}

IPv4Address& GpsrHelloAck::getMyAddress()
{
    return myAddress_var;
}

void GpsrHelloAck::setMyAddress(const IPv4Address& myAddress)
{
    this->myAddress_var = myAddress;
}

IPv4Address& GpsrHelloAck::getDstAddress()
{
    return DstAddress_var;
}

void GpsrHelloAck::setDstAddress(const IPv4Address& DstAddress)
{
    this->DstAddress_var = DstAddress;
}

Coord& GpsrHelloAck::getMyPos()
{
    return MyPos_var;
}

void GpsrHelloAck::setMyPos(const Coord& MyPos)
{
    this->MyPos_var = MyPos;
}

class GpsrHelloAckDescriptor : public cClassDescriptor
{
  public:
    GpsrHelloAckDescriptor();
    virtual ~GpsrHelloAckDescriptor();

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

Register_ClassDescriptor(GpsrHelloAckDescriptor);

GpsrHelloAckDescriptor::GpsrHelloAckDescriptor() : cClassDescriptor("GpsrHelloAck", "cPacket")
{
}

GpsrHelloAckDescriptor::~GpsrHelloAckDescriptor()
{
}

bool GpsrHelloAckDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GpsrHelloAck *>(obj)!=NULL;
}

const char *GpsrHelloAckDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GpsrHelloAckDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int GpsrHelloAckDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *GpsrHelloAckDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myAddress",
        "DstAddress",
        "MyPos",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int GpsrHelloAckDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myAddress")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DstAddress")==0) return base+1;
    if (fieldName[0]=='M' && strcmp(fieldName, "MyPos")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GpsrHelloAckDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPv4Address",
        "IPv4Address",
        "Coord",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *GpsrHelloAckDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GpsrHelloAckDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GpsrHelloAck *pp = (GpsrHelloAck *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GpsrHelloAckDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrHelloAck *pp = (GpsrHelloAck *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getMyAddress(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDstAddress(); return out.str();}
        case 2: {std::stringstream out; out << pp->getMyPos(); return out.str();}
        default: return "";
    }
}

bool GpsrHelloAckDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GpsrHelloAck *pp = (GpsrHelloAck *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GpsrHelloAckDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "IPv4Address",
        "IPv4Address",
        "Coord",
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *GpsrHelloAckDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrHelloAck *pp = (GpsrHelloAck *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getMyAddress()); break;
        case 1: return (void *)(&pp->getDstAddress()); break;
        case 2: return (void *)(&pp->getMyPos()); break;
        default: return NULL;
    }
}


