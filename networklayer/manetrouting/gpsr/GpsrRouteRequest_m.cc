//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/gpsr/GpsrRouteRequest.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "GpsrRouteRequest_m.h"

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




Register_Class(GpsrRouteRequest);

GpsrRouteRequest::GpsrRouteRequest(const char *name, int kind) : cPacket(name,kind)
{
}

GpsrRouteRequest::GpsrRouteRequest(const GpsrRouteRequest& other) : cPacket(other)
{
    copy(other);
}

GpsrRouteRequest::~GpsrRouteRequest()
{
}

GpsrRouteRequest& GpsrRouteRequest::operator=(const GpsrRouteRequest& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void GpsrRouteRequest::copy(const GpsrRouteRequest& other)
{
    this->src_var = other.src_var;
    this->dst_var = other.dst_var;
    this->srcPos_var = other.srcPos_var;
    this->dstPos_var = other.dstPos_var;
}

void GpsrRouteRequest::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->src_var);
    doPacking(b,this->dst_var);
    doPacking(b,this->srcPos_var);
    doPacking(b,this->dstPos_var);
}

void GpsrRouteRequest::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->dst_var);
    doUnpacking(b,this->srcPos_var);
    doUnpacking(b,this->dstPos_var);
}

IPv4Address& GpsrRouteRequest::getSrc()
{
    return src_var;
}

void GpsrRouteRequest::setSrc(const IPv4Address& src)
{
    this->src_var = src;
}

IPv4Address& GpsrRouteRequest::getDst()
{
    return dst_var;
}

void GpsrRouteRequest::setDst(const IPv4Address& dst)
{
    this->dst_var = dst;
}

Coord& GpsrRouteRequest::getSrcPos()
{
    return srcPos_var;
}

void GpsrRouteRequest::setSrcPos(const Coord& srcPos)
{
    this->srcPos_var = srcPos;
}

Coord& GpsrRouteRequest::getDstPos()
{
    return dstPos_var;
}

void GpsrRouteRequest::setDstPos(const Coord& dstPos)
{
    this->dstPos_var = dstPos;
}

class GpsrRouteRequestDescriptor : public cClassDescriptor
{
  public:
    GpsrRouteRequestDescriptor();
    virtual ~GpsrRouteRequestDescriptor();

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

Register_ClassDescriptor(GpsrRouteRequestDescriptor);

GpsrRouteRequestDescriptor::GpsrRouteRequestDescriptor() : cClassDescriptor("GpsrRouteRequest", "cPacket")
{
}

GpsrRouteRequestDescriptor::~GpsrRouteRequestDescriptor()
{
}

bool GpsrRouteRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GpsrRouteRequest *>(obj)!=NULL;
}

const char *GpsrRouteRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GpsrRouteRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int GpsrRouteRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *GpsrRouteRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "src",
        "dst",
        "srcPos",
        "dstPos",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int GpsrRouteRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dst")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcPos")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstPos")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GpsrRouteRequestDescriptor::getFieldTypeString(void *object, int field) const
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
        "Coord",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *GpsrRouteRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GpsrRouteRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRouteRequest *pp = (GpsrRouteRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GpsrRouteRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRouteRequest *pp = (GpsrRouteRequest *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDst(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSrcPos(); return out.str();}
        case 3: {std::stringstream out; out << pp->getDstPos(); return out.str();}
        default: return "";
    }
}

bool GpsrRouteRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRouteRequest *pp = (GpsrRouteRequest *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GpsrRouteRequestDescriptor::getFieldStructName(void *object, int field) const
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
        "Coord",
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *GpsrRouteRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GpsrRouteRequest *pp = (GpsrRouteRequest *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrc()); break;
        case 1: return (void *)(&pp->getDst()); break;
        case 2: return (void *)(&pp->getSrcPos()); break;
        case 3: return (void *)(&pp->getDstPos()); break;
        default: return NULL;
    }
}


