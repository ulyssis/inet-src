//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/gr/GrNeighborInfo.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GrNeighborInfo_m.h"

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




Register_Class(GrNeighborInfo);

GrNeighborInfo::GrNeighborInfo(const char *name, int kind) : cPacket(name,kind)
{
    this->routerXPos_var = 0;
    this->routerYPos_var = 0;
}

GrNeighborInfo::GrNeighborInfo(const GrNeighborInfo& other) : cPacket(other)
{
    copy(other);
}

GrNeighborInfo::~GrNeighborInfo()
{
}

GrNeighborInfo& GrNeighborInfo::operator=(const GrNeighborInfo& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void GrNeighborInfo::copy(const GrNeighborInfo& other)
{
    this->routerAddress_var = other.routerAddress_var;
    this->routerXPos_var = other.routerXPos_var;
    this->routerYPos_var = other.routerYPos_var;
}

void GrNeighborInfo::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->routerAddress_var);
    doPacking(b,this->routerXPos_var);
    doPacking(b,this->routerYPos_var);
}

void GrNeighborInfo::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->routerAddress_var);
    doUnpacking(b,this->routerXPos_var);
    doUnpacking(b,this->routerYPos_var);
}

IPv4Address& GrNeighborInfo::getRouterAddress()
{
    return routerAddress_var;
}

void GrNeighborInfo::setRouterAddress(const IPv4Address& routerAddress)
{
    this->routerAddress_var = routerAddress;
}

double GrNeighborInfo::getRouterXPos() const
{
    return routerXPos_var;
}

void GrNeighborInfo::setRouterXPos(double routerXPos)
{
    this->routerXPos_var = routerXPos;
}

double GrNeighborInfo::getRouterYPos() const
{
    return routerYPos_var;
}

void GrNeighborInfo::setRouterYPos(double routerYPos)
{
    this->routerYPos_var = routerYPos;
}

class GrNeighborInfoDescriptor : public cClassDescriptor
{
  public:
    GrNeighborInfoDescriptor();
    virtual ~GrNeighborInfoDescriptor();

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

Register_ClassDescriptor(GrNeighborInfoDescriptor);

GrNeighborInfoDescriptor::GrNeighborInfoDescriptor() : cClassDescriptor("GrNeighborInfo", "cPacket")
{
}

GrNeighborInfoDescriptor::~GrNeighborInfoDescriptor()
{
}

bool GrNeighborInfoDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GrNeighborInfo *>(obj)!=NULL;
}

const char *GrNeighborInfoDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GrNeighborInfoDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int GrNeighborInfoDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *GrNeighborInfoDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "routerAddress",
        "routerXPos",
        "routerYPos",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int GrNeighborInfoDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerAddress")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerXPos")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerYPos")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GrNeighborInfoDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPv4Address",
        "double",
        "double",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *GrNeighborInfoDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GrNeighborInfoDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GrNeighborInfo *pp = (GrNeighborInfo *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GrNeighborInfoDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GrNeighborInfo *pp = (GrNeighborInfo *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRouterAddress(); return out.str();}
        case 1: return double2string(pp->getRouterXPos());
        case 2: return double2string(pp->getRouterYPos());
        default: return "";
    }
}

bool GrNeighborInfoDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GrNeighborInfo *pp = (GrNeighborInfo *)object; (void)pp;
    switch (field) {
        case 1: pp->setRouterXPos(string2double(value)); return true;
        case 2: pp->setRouterYPos(string2double(value)); return true;
        default: return false;
    }
}

const char *GrNeighborInfoDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "IPv4Address",
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *GrNeighborInfoDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GrNeighborInfo *pp = (GrNeighborInfo *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRouterAddress()); break;
        default: return NULL;
    }
}


