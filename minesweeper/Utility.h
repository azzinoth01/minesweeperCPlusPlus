#pragma once
#include <d3d11.h>
#include <string>

#define REMOVE_COPY(type)\
type(const type& base)=delete; \
type& operator=(const type& base)=delete;

#define REMOVE_MOVE(type)\
type(const type&& base)=delete; \
type& operator=(const type&& base)=delete;

#define REMOVE_COPY_MOVE(type)\
REMOVE_COPY(type)\
REMOVE_MOVE(type)

#define ARRAY_COUNT(arrayVar)(sizeof(arrayVar)/ sizeof((arrayVar[0])))


bool Failed(HRESULT result);

bool IsFlagSet(unsigned int flag, unsigned int mask);

