#pragma once


//Moore property template
//allows for c#-like properties
//instead of the dreaded get/setters
// !!! ALL PROPERTIES MUST BE INITIALIZED IN THE BASE CLASS CONSTRUCTOR !!!
template <typename This, typename Base, typename T>
class _property
{
protected:
	Base& ref;

public:
	_property (Base& b)
		: ref (b)
	{}

	_property& operator= (const T& rhs)
	{
		((This*)this)->set (rhs);
		return *this;
	}
	operator T () const
	{
		return ((This*)this)->get ();
	}
};

//macros to simplify property definitions
#define PROP_INIT(THIS,BASE,T) \
using prop = typename _property<THIS, BASE, T>; \
using prop::prop;

#define PROP(THIS,BASE,T) : _property<THIS,BASE,T>

#define property(NAME,BASE,T) \
class NAME##Property PROP (NAME##Property, BASE, T) \
{ \
	PROP_INIT (NAME##Property, BASE, T); \
	void set (const T&); \
	const T get () const; \
} NAME