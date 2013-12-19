#ifndef DEFINES_H
#define DEFINES_H

#define DISABLE_COPY_AND_ASSIGN(Type) \
    Type(Type const&); \
    void operator=(Type const&)

#endif // DEFINES_H
