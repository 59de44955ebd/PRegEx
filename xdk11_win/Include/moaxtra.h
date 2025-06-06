/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_moaxtra
#define _H_moaxtra

/*
	File: moaxtra.h (core)

	Abstract:
	
	The public header file for the MOA Services library.
	
	It provides all functionality necessary to construct
	a standalone Xtra.
*/

#ifdef PRECOMPILED_HEADER
	#error "moaxtra.h should not be precompiled"
#endif

/*---------------------------------------------------------------------------
/ 1. Include other headers we depend on.
/--------------------------------------------*/
/*-------------------------------------------------------------------------*/

#ifndef _H_moatypes
	#include "moatypes.h"
#endif

#include <stdarg.h>
#include <stdio.h>

/* this is correct -- not CPLUS or MOA_CPLUS_BINDINGS_ALLOWED. */
#ifdef __cplusplus
#if !(defined(__APPLE__) && defined(__MACH__))
	#include <new.h>
#endif
#endif

/*---------------------------------------------------------------------------
/ 2. Define constants and macros.
/--------------------------------------------*/

#if defined(MOA_CPLUS_BINDINGS_ALLOWED) && !defined(CINTERFACE)
	#define CPLUS
#else
	#undef CPLUS
#endif

#if defined(__cplusplus) && !defined(CINTERFACE) && !defined(MOA_CPLUS_BINDINGS_ALLOWED)
	#error "C++ bindings not allowed in this compiler configuration."
#endif

/*
	This macro is used to guarantee a unique name space. All global names
	are defined using this macro. Xtras should always use "DLL" for the
	name convention or they won't load correctly.
*/
#ifndef DLL
	#define DLL(name) Dll##name
#endif

/* -------------------------------------------------------------------------- */
/*
	The next section of code, defined by the macro DEBUG_PREFACE, consists
	of code that's only used when the MOA_DEBUG macro is defined. Not surprisingly,
	this is only used for debugging.
	
	Note that the code actually is included in the library in all cases (not
	just in debug versions), to simplify swapping debug and nondebug versions.
	(The linker should normally strip it out of nondebug versions at final link.)
*/

#if defined(MOA_APP_CODE)
	#define _DEBUG_NAMING_HACK(x)	_libcode##x
#else
	#define _DEBUG_NAMING_HACK(x)	_xcode##x
#endif

EXTERN_STDMETHODIMP_(void) _DEBUG_NAMING_HACK(_debugstr)(ConstPMoaChar msg, ...);
EXTERN_STDMETHODIMP_(void) _DEBUG_NAMING_HACK(_clobbermem)(PMoaVoid p, long sz);
EXTERN_STDMETHODIMP_(int) _DEBUG_NAMING_HACK(_isclobbered)(PMoaVoid p);

#define DEBUG_PREFACE \
	 \
	STDMETHODIMP_(void) _DEBUG_NAMING_HACK(_debugstr)(ConstPMoaChar msg, ...) \
	{ \
		char buffer[256]; \
		_MOA_VSPRINTF_(buffer, msg); \
		_MOA_DEBUGSTR_(buffer); \
	} \
	 \
	STDMETHODIMP_(void) _DEBUG_NAMING_HACK(_clobbermem)(PMoaVoid p, long sz) \
	{ \
		long _c_; \
		PPMoaVoid _p_; \
	 \
		MOA_ASSERT(!MOA_ISCLOBBERED(p), "Mem already clobbered"); \
		for (_c_ = (sz) / sizeof(PMoaVoid), _p_ = (PPMoaVoid)(p) ; _c_; _c_--, _p_++) *_p_ = MOA_CLOBBERVAL; \
		_MOA_FLUSH_CACHE; \
	} \
	 \
	STDMETHODIMP_(int) _DEBUG_NAMING_HACK(_isclobbered)(PMoaVoid p) \
	{ \
		return(!p || (*(PPMoaVoid)(p)) == MOA_CLOBBERVAL); \
	}

/*
	Note: Mac MPW C chokes on these macros. If you need to compile
	this under MPW C with MOA_DEBUG on, add " && !defined(applec) "
	to the next line.
*/
#if defined(MOA_DEBUG)

	#define MOA_DEBUGSTR(x)					\
		_DEBUG_NAMING_HACK(_debugstr) x
	#define MOA_CLOBBERMEM(p, sz)			\
		_DEBUG_NAMING_HACK(_clobbermem)((p), (sz))
	#define MOA_ISCLOBBERED(p)				\
		_DEBUG_NAMING_HACK(_isclobbered)(p)
	#define MOA_CLOBBERTEST(addr, msg) 		\
		do { if (MOA_ISCLOBBERED((PMoaVoid)(addr))) MOA_DEBUGSTR(("Clobbered in" msg)); } while (0);
	#define MOA_ASSERT(cond, msg)			\
		do { if (!(cond)) MOA_DEBUGSTR((msg)); } while (0);

#else

	#define MOA_DEBUGSTR(x)
	#define MOA_CLOBBERMEM(p, sz)
	#define MOA_ISCLOBBERED(p)
	#define MOA_CLOBBERTEST(addr, msg)
	#define MOA_ASSERT(cond, msg)

#endif

/* -------------------------------------------------------------------------- */
/*
	The last section of code, defined by the macro STD_PREFACE, is used
	by all Xtras everywhere.
*/

#define MOAEQUALID_PREFACE \
	STDAPI_(MoaLong) MoaEqualID(ConstPMoaID a, ConstPMoaID b) \
	{ \
		return( \
			a->Data1 == b->Data1 && \
			*(MoaLong*)(&a->Data2) == *(MoaLong*)(&b->Data2) && \
			*(MoaLong*)a->Data4 == *(MoaLong*)b->Data4 && \
			*(MoaLong*)(a->Data4+4) == *(MoaLong*)(b->Data4+4) \
		); \
	}

/* -------------------------------------------------------------------------- */
/*
	The final macro, XTRA_PREFACE, is the concatenation of all the other
	prefaces we need. This code will actually be generated by the
	BEGIN_XTRA macro.
*/
#if defined(MOA_APP_CODE)
	#define XTRA_PREFACE
#elif defined(MOA_LIB_LINKED)
	#define XTRA_PREFACE _MOA_XCODE_PREFACE DEBUG_PREFACE
#else
	#define XTRA_PREFACE _MOA_XCODE_PREFACE MOAEQUALID_PREFACE DEBUG_PREFACE
#endif

/* ========================================================================== */
/* ============================== COM definitions =========================== */
/* ========================================================================== */

#if !defined(_MOA_COM_PROVIDED_)
	/*
		Macros for declaring an interface. These are cunningly designed
		so that when expanded, they form a correct definition of the
		structures and such for either C or C++ (depending on the
		compiler used to process this file) (actually, depending
		on the __cplusplus definition).
		
		This follows the Microsoft conventions closely (or at least,
		a subset thereof).
		
		A synopsis is as follows:
		
		DECLARE_INTERFACE(theInterface) is used to declare a base interface.
		DECLARE_INTERFACE_(theInterface, baseInterface) is used to declare
			an interface that is based on another interface. In practice,
			you'll always use this one, since every interface must be
			derived from IMoaUnknown. Also note that you must still re-list
			all the derived methods.
	*/
	
	
	#ifdef CPLUS
		/* the macros for C++ */
	
		#define INTERFACE_PREFACE									struct
		
		#define _STDMETHOD(methodName) 								virtual MoaError STDMETHODCALLTYPE methodName
		#define _STDMETHOD_(resultType, methodName) 				virtual resultType STDMETHODCALLTYPE methodName
		#define STDMETHOD(methodName) 								_STDMETHOD(methodName)
		#define STDMETHOD_(resultType, methodName) 					_STDMETHOD_(resultType, methodName)
		
		#define PURE												= 0
		#define THIS_
		#define THIS												void
		#define _DECLARE_INTERFACE(theInterface)					_MOA_PTRCHECK INTERFACE_PREFACE theInterface
		#define _DECLARE_INTERFACE_(theInterface, baseInterface)	_MOA_PTRCHECK INTERFACE_PREFACE theInterface : public baseInterface
		#define DECLARE_INTERFACE(theInterface)						_DECLARE_INTERFACE(theInterface)
		#define DECLARE_INTERFACE_(theInterface, baseInterface)		_DECLARE_INTERFACE_(theInterface, baseInterface)
			
	#else /* not C++ */
	
		/* macros for plain C */
		#define INTERFACE_PREFACE						struct
	
		#define _STDMETHOD(methodName)					MoaError (STDMETHODCALLTYPE * methodName)
		#define _STDMETHOD_(resultType, methodName)		resultType (STDMETHODCALLTYPE * methodName)
		#define STDMETHOD(methodName) 					_STDMETHOD(methodName)
		#define STDMETHOD_(resultType, methodName) 		_STDMETHOD_(resultType, methodName)

		#define PURE
		#define THIS_									struct INTERFACE * This,
		#define THIS									struct INTERFACE * This
	
		#define _DECLARE_INTERFACE(theInterface)		_MOA_PTRCHECK \
														struct theInterface##Vtbl; \
														typedef INTERFACE_PREFACE theInterface { \
															struct theInterface##Vtbl * lpVtbl; \
														} theInterface; \
														typedef struct theInterface##Vtbl theInterface##Vtbl; \
														struct theInterface##Vtbl
	
		#define _DECLARE_INTERFACE_(theInterface, baseInterface)	DECLARE_INTERFACE(theInterface)
		#define DECLARE_INTERFACE(theInterface)						_DECLARE_INTERFACE(theInterface)
		#define DECLARE_INTERFACE_(theInterface, baseInterface)		_DECLARE_INTERFACE_(theInterface, baseInterface)

	#endif											
	
	#define EXTERN_GUID(name) \
		EXTERN_C MOA_READONLY(MoaID) name

	#if defined(INITGUID)
		/* with Xcode, we must forward declare the GUID with external linkage */
		/* to work around a template issue */
		#if (defined(__APPLE__) && defined(__MACH__))
			#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
				const extern MoaID name; const MoaID name = { l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8 }		
		#else
			#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
			EXTERN_C MOA_READONLY(MoaID) name = { l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8 }
		#endif
	#else
		#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
			EXTERN_GUID(name)
	#endif

	typedef ConstPMoaClassID REFCLSID;
	typedef ConstPMoaInterfaceID REFIID;

#else

	#if (_MSC_VER < 1100)
			#define EXTERN_GUID(itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8) EXTERN_C const IID itf
	#elif !defined(_MSC_VER)
		#define EXTERN_GUID(name) \
			EXTERN_C MOA_READONLY(MoaID) name
	#endif

#endif	/* _MOA_COM_PROVIDED_ */

#if defined(INITGUID) && !defined(NO_STD_GUID)
	/* with Xcode, we must forward declare the GUID with external linkage */
	/* to work around a template issue */
	#if (defined(__APPLE__) && defined(__MACH__))
		#define DEFINE_STD_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
			const extern MoaID name; const MoaID name = { l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8 }		
	#else
		#define DEFINE_STD_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
			EXTERN_C MOA_READONLY(MoaID) name = { l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8 }
	#endif
#else
	#define DEFINE_STD_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
		EXTERN_C MOA_READONLY(MoaID) name
#endif

#define STD_IUNKNOWN_METHODS \
	BEGIN_INTERFACE \
	STDMETHOD(QueryInterface) (THIS_ ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppvObj) PURE; \
	STDMETHOD_(MoaUlong, AddRef) (THIS) PURE; \
	STDMETHOD_(MoaUlong, Release) (THIS) PURE; \

/* ========================================================================== */
/* ========================== Standard Interfaces =========================== */
/* ========================================================================== */

/* --------------------------------------------------------------------- Misc */

#ifdef IID_NULL
	#undef IID_NULL
#endif

/* IID_NULL: 00000000000000000000000000000000 */
DEFINE_STD_GUID(IID_NULL, 0x00000000L, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

/* CLSID_AnyClass: af107ce031ea101c9a9f0000c0ddaa4b */
DEFINE_STD_GUID(CLSID_AnyClass, 0xaf107ce0L, 0x31ea, 0x101c, 0x9a, 0x9f, 0x00, 0x00, 0xc0, 0xdd, 0xaa, 0x4b);


/* ----------------------------------------------------------------- IMoaUnknown */
#undef INTERFACE
#define INTERFACE IMoaUnknown
DECLARE_INTERFACE_IMOAUNKNOWN
{
	STD_IUNKNOWN_METHODS
};
typedef IMoaUnknown * PIMoaUnknown;

/* IID_IMoaUnknown: 0000000000000000C000000000000046 */
DEFINE_STD_GUID(IID_IMoaUnknown, 0x00000000L, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

/* ------------------------------------------------------------ IMoaClassFactory */

/* this interface is for Moa internal use only. */

#undef INTERFACE
#define INTERFACE IMoaClassFactory

DECLARE_INTERFACE_(IMoaClassFactory, IMoaUnknown)
{
	STD_IUNKNOWN_METHODS

	STDMETHOD(CreateInstance) (THIS_ PIMoaUnknown pUnkOuter,
		ConstPMoaInterfaceID pInterfaceID,
		PPMoaVoid ppvObject) PURE;
 	STDMETHOD(LockServer) (THIS_ MoaUlong fLock) PURE;
};
typedef IMoaClassFactory * PIMoaClassFactory;

/* IID_IMoaClassFactory: 0000000100000000C000000000000046 */
DEFINE_STD_GUID(IID_IMoaClassFactory, 0x00000001L, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

/* --------------------------------------------------------------- IMoaCalloc */
#undef INTERFACE
#define INTERFACE IMoaCalloc

DECLARE_INTERFACE_(IMoaCalloc, IMoaUnknown)
{
	STD_IUNKNOWN_METHODS

	STDMETHOD_(PMoaVoid, NRAlloc) (THIS_ MoaUlong cb) PURE;
	STDMETHOD_(void, NRFree) (THIS_ PMoaVoid pv) PURE;
};
typedef IMoaCalloc * PIMoaCalloc;

/* IID_ICalloc: 3a698c2039c3101c9a9f0000c0ddaa4b */
DEFINE_STD_GUID(IID_IMoaCalloc, 0x3a698c20L, 0x39c3, 0x101c, 0x9a, 0x9f, 0x00, 0x00, 0xc0, 0xdd, 0xaa, 0x4b);

/* ------------------------------------------------------------- IMoaCallback */
#undef INTERFACE
#define INTERFACE IMoaCallback

DECLARE_INTERFACE_(IMoaCallback, IMoaUnknown)
{
	STD_IUNKNOWN_METHODS

	STDMETHOD(MoaCreateInstance) (THIS_	ConstPMoaClassID pClassID, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppvObj) PURE;
	STDMETHOD_(struct IMoaCache *, MoaGetCache) (THIS) PURE;

	STDMETHOD_(XtraResourceCookie, MoaBeginUsingResources) (THIS_ MoaFileRef fileRef, XtraResourceCookie * pSaveCookie) PURE;
	STDMETHOD_(void, MoaEndUsingResources) (THIS_ MoaFileRef fileRef, XtraResourceCookie saveCookie) PURE;
};
typedef IMoaCallback * PIMoaCallback;

/* IID_ICallback: c00bfc803164101c9a9c0000c0ddaa4b */
DEFINE_STD_GUID(IID_IMoaCallback, 0xc00bfc80L, 0x3164, 0x101c, 0x9a, 0x9c, 0x00, 0x00, 0xc0, 0xdd, 0xaa, 0x4b);

/* ========================================================================== */
/* ============================== Function types ============================ */
/* ========================================================================== */

/* STDMETHOD-protocol functions. */

typedef MOA_STD_METHOD_PROCPTR(MoaError, MoaCreatedProc)(PMoaVoid pObj);
typedef MOA_STD_METHOD_PROCPTR(void, MoaDestroyedProc)(PMoaVoid pObj);

/* this structure is for Moa internal use only. */
typedef struct {
	MoaClassID classID;
	MoaLong classVersion;
	MoaInterfaceID interfaceID;
	MoaLong interfaceVersion;
} MoaClassInterfaceInfo;
typedef MoaClassInterfaceInfo * PMoaClassInterfaceInfo;
typedef const MoaClassInterfaceInfo * ConstPMoaClassInterfaceInfo;

#undef XE_DLL
#define XE_DLL(x) DLL(x)

#define EXTERN_XTRA_ENTRIES \
	STDAPI XE_DLL(GetClassObject)(REFCLSID rclsid, REFIID riid, PPMoaVoid ppv); \
	STDAPI XE_DLL(CanUnloadNow)(void); \
	STDAPI XE_DLL(GetInterface)(PMoaVoid pObj, ConstPMoaClassID pClassID, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv); \
	STDAPI XE_DLL(GetClassForm)(ConstPMoaClassID pClassID, MoaLong * pObjSize, MoaCreatedProc * pCreateProc, MoaDestroyedProc * pDestroyProc); \
	STDAPI XE_DLL(GetClassInfo)(PIMoaCalloc pCalloc, ConstPMoaClassInterfaceInfo * ppClassInfo); \
	STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPMoaVoid ppv); \
	STDAPI DllCanUnloadNow(void); \
	STDAPI DllGetInterface(PMoaVoid pObj, ConstPMoaClassID pClassID, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv); \
	STDAPI DllGetClassForm(ConstPMoaClassID pClassID, MoaLong * pObjSize, MoaCreatedProc * pCreateProc, MoaDestroyedProc * pDestroyProc); \
	STDAPI DllGetClassInfo(PIMoaCalloc pCalloc, ConstPMoaClassInterfaceInfo * ppClassInfo);

EXTERN_XTRA_ENTRIES

#if defined(MOA_EXPORT_LIST)
#ifndef __GNUC__
#pragma export list DllGetClassObject, DllCanUnloadNow, DllGetInterface, DllGetClassForm, DllGetClassInfo, ppcSetFileRef
#endif
#endif

/* ========================================================================== */
/* ============================= Type Definitions =========================== */
/* ========================================================================== */

#define _BASE_STRUCTURES \
			MoaXtraMagicCookie		magicCookie; 	/* for internal use */ \
			PIMoaCallback			pCallback; 		/* callbacks, or NULL */ \
			PIMoaCalloc 			pCalloc; 		/* IMoaCalloc we used for ourself */ \
			ConstPMoaClassID	 	pClassID; 		/* ptr to our class id */ \
			MoaLong					refCount; 		/* our refcount */ \

#define _INTERFACE_STRUCTURES(macro_CLASS) \
			macro_CLASS *	 		pObj; 			/* pointer to the "real" object */ \
			MoaLong 				refCount; 		/* refcount for THIS INTERFACE */

/* This gyration is to allow for classes/interface to be replaced by Macros.
	a two-step token pasting allows for this. */
#ifdef COMPILER_LIMITED_MACRO_SPACE
	#define CLSID(macro_CLSID)						        CLSID_##macro_CLSID
	#define IID(macro_IID)							        IID_##macro_IID
	
	#define MOA_CREATEI(macro_CLASS, macro_INTF)			MoaCreate_##macro_CLASS##_##macro_INTF
	#define MOA_DESTROYI(macro_CLASS, macro_INTF)			MoaDestroy_##macro_CLASS##_##macro_INTF
	
	#define MOA_CREATEI_PARMS(macro_CLASS, macro_INTF)		MoaCreate_##macro_CLASS##_##macro_INTF(macro_CLASS##_##macro_INTF * This)
	#define MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF)		MoaDestroy_##macro_CLASS##_##macro_INTF(macro_CLASS##_##macro_INTF * This)
	
	#define MOA_CREATE(macro_NAME)					        MoaCreate_##macro_NAME
	#define MOA_DESTROY(macro_NAME)					        MoaDestroy_##macro_NAME
	
	#define MOA_CREATE_PARMS(macro_NAME)			        MoaCreate_##macro_NAME(macro_NAME * This)
	#define MOA_DESTROY_PARMS(macro_NAME)			        MoaDestroy_##macro_NAME(macro_NAME * This)
	
	#define INTF(macro_CLASS, macro_INTF)			    macro_CLASS##_##macro_INTF
	
	#define INTFQUERY(macro_CLASS, macro_INTF)			macro_CLASS##_##macro_INTF##_QI
	#define INTFQUERY_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_QI(macro_CLASS##_##macro_INTF * This, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv)
	
	#define INTFADDREF(macro_CLASS, macro_INTF)			macro_CLASS##_##macro_INTF##_AR
	#define INTFADDREF_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_AR(macro_CLASS##_##macro_INTF * This)
	
	#define INTFRELEASE(macro_CLASS, macro_INTF)		macro_CLASS##_##macro_INTF##_RL
	#define INTFRELEASE_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_RL(macro_CLASS##_##macro_INTF * This)
	
	#define INTFBUILD(macro_CLASS, macro_INTF)			Build_##macro_CLASS##_##macro_INTF
	#define INTFBUILD_PARMS(macro_CLASS, macro_INTF)	Build_##macro_CLASS##_##macro_INTF(macro_CLASS * pObj, PPMoaVoid ppIF)
	
	#define INTFVTBL(macro_INTF)					macro_INTF##Vtbl
	#define GETVTBL(macro_CLASS, macro_INTF)		_Get##macro_CLASS##macro_INTF##Vtbl
	#define THEVTBL(macro_CLASS, macro_INTF)		g_##macro_CLASS##macro_INTF##vt
	#define INITVTBL(macro_CLASS, macro_INTF)		g_##macro_CLASS##macro_INTF##vti
	
	#define CALL_BGI(macro_CLASS, macro_INTF, macro_OBJ, macro_PERR) \
													(macro_CLASS##_##macro_INTF *)DLL(BuildGenInterface) \
													((MBObject *)(macro_OBJ), \
													sizeof(macro_CLASS##_##macro_INTF), \
													(MoaCreatedProc)MoaCreate_##macro_CLASS##_##macro_INTF, \
													(PMoaVoid)GET_VTABLE(macro_CLASS, macro_INTF), \
													(macro_PERR))
	
#else
	#define _CLSID(macro_CLSID)						CLSID_##macro_CLSID
	#define CLSID(macro_CLSID)						_CLSID(macro_CLSID)
	#define _IID(macro_IID)							IID_##macro_IID
	#define IID(macro_IID)							_IID(macro_IID)

	#define _MOA_CREATEI(macro_CLASS, macro_INTF)			MoaCreate_##macro_CLASS##_##macro_INTF
	#define MOA_CREATEI(macro_CLASS, macro_INTF)			_MOA_CREATEI(macro_CLASS, macro_INTF)
	#define _MOA_DESTROYI(macro_CLASS, macro_INTF)			MoaDestroy_##macro_CLASS##_##macro_INTF
	#define MOA_DESTROYI(macro_CLASS, macro_INTF)			_MOA_DESTROYI(macro_CLASS, macro_INTF)
	
	#define _MOA_CREATEI_PARMS(macro_CLASS, macro_INTF)		MoaCreate_##macro_CLASS##_##macro_INTF(macro_CLASS##_##macro_INTF * This)
	#define MOA_CREATEI_PARMS(macro_CLASS, macro_INTF)		_MOA_CREATEI_PARMS(macro_CLASS, macro_INTF)
	#define _MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF)	MoaDestroy_##macro_CLASS##_##macro_INTF(macro_CLASS##_##macro_INTF * This)
	#define MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF)		_MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF)
	
	#define _MOA_CREATE(macro_NAME)					MoaCreate_##macro_NAME
	#define MOA_CREATE(macro_NAME)					_MOA_CREATE(macro_NAME)
	#define _MOA_DESTROY(macro_NAME)				MoaDestroy_##macro_NAME
	#define MOA_DESTROY(macro_NAME)					_MOA_DESTROY(macro_NAME)
	
	#define _MOA_CREATE_PARMS(macro_NAME)			MoaCreate_##macro_NAME(macro_NAME * This)
	#define MOA_CREATE_PARMS(macro_NAME)			_MOA_CREATE_PARMS(macro_NAME)
	#define _MOA_DESTROY_PARMS(macro_NAME)			MoaDestroy_##macro_NAME(macro_NAME * This)
	#define MOA_DESTROY_PARMS(macro_NAME)			_MOA_DESTROY_PARMS(macro_NAME)
	
	#define _INTF(macro_CLASS, macro_INTF)			macro_CLASS##_##macro_INTF
	#define INTF(macro_CLASS, macro_INTF)			_INTF(macro_CLASS, macro_INTF)
	
	#define _INTFQUERY(macro_CLASS, macro_INTF)			macro_CLASS##_##macro_INTF##_QI
	#define INTFQUERY(macro_CLASS, macro_INTF)			_INTFQUERY(macro_CLASS, macro_INTF)
	#define _INTFQUERY_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_QI(macro_CLASS##_##macro_INTF * This, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv)
	#define INTFQUERY_PARMS(macro_CLASS, macro_INTF)	_INTFQUERY_PARMS(macro_CLASS, macro_INTF)
	
	#define _INTFADDREF(macro_CLASS, macro_INTF)		macro_CLASS##_##macro_INTF##_AR
	#define INTFADDREF(macro_CLASS, macro_INTF)			_INTFADDREF(macro_CLASS, macro_INTF)
	#define _INTFADDREF_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_AR(macro_CLASS##_##macro_INTF * This)
	#define INTFADDREF_PARMS(macro_CLASS, macro_INTF)	_INTFADDREF_PARMS(macro_CLASS, macro_INTF)
	
	#define _INTFRELEASE(macro_CLASS, macro_INTF)		macro_CLASS##_##macro_INTF##_RL
	#define INTFRELEASE(macro_CLASS, macro_INTF)		_INTFRELEASE(macro_CLASS, macro_INTF)
	#define _INTFRELEASE_PARMS(macro_CLASS, macro_INTF)	macro_CLASS##_##macro_INTF##_RL(macro_CLASS##_##macro_INTF * This)
	#define INTFRELEASE_PARMS(macro_CLASS, macro_INTF)	_INTFRELEASE_PARMS(macro_CLASS, macro_INTF)
	
	#define _INTFBUILD(macro_CLASS, macro_INTF)			Build_##macro_CLASS##_##macro_INTF
	#define INTFBUILD(macro_CLASS, macro_INTF)			_INTFBUILD(macro_CLASS, macro_INTF)
	#define _INTFBUILD_PARMS(macro_CLASS, macro_INTF)	Build_##macro_CLASS##_##macro_INTF(macro_CLASS * pObj, PPMoaVoid ppIF)
	#define INTFBUILD_PARMS(macro_CLASS, macro_INTF)	_INTFBUILD_PARMS(macro_CLASS, macro_INTF)
	
	#define _INTFVTBL(macro_INTF)					macro_INTF##Vtbl
	#define INTFVTBL(macro_INTF)					_INTFVTBL(macro_INTF)
	#define _GETVTBL(macro_CLASS, macro_INTF)		_Get##macro_CLASS##macro_INTF##Vtbl
	#define GETVTBL(macro_CLASS, macro_INTF)		_GETVTBL(macro_CLASS, macro_INTF)
	#define _THEVTBL(macro_CLASS, macro_INTF)		g_##macro_CLASS##macro_INTF##vt
	#define THEVTBL(macro_CLASS, macro_INTF)		_THEVTBL(macro_CLASS, macro_INTF)
	#define _INITVTBL(macro_CLASS, macro_INTF)		g_##macro_CLASS##macro_INTF##vti
	#define INITVTBL(macro_CLASS, macro_INTF)		_INITVTBL(macro_CLASS, macro_INTF)
	
	#define _CALL_BGI(macro_CLASS, macro_INTF, macro_OBJ, macro_PERR) \
													(macro_CLASS##_##macro_INTF *)DLL(BuildGenInterface) \
													((MBObject *)(macro_OBJ), \
													sizeof(macro_CLASS##_##macro_INTF), \
													(MoaCreatedProc)MoaCreate_##macro_CLASS##_##macro_INTF, \
													(PMoaVoid)GET_VTABLE(macro_CLASS, macro_INTF), \
													(macro_PERR))
	#define CALL_BGI(macro_CLASS, macro_INTF, macro_OBJ, macro_PERR) \
													_CALL_BGI(macro_CLASS, macro_INTF, macro_OBJ, macro_PERR)
	
#endif

#ifdef CPLUS

	#define CALL_CALLOC(pCalloc, sz) (pCalloc)->NRAlloc(sz)
	#define CALL_NRFREE(pCalloc, p) (pCalloc)->NRFree(p)

	#define EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(macro_CLASS) \
		_MOA_PTRCHECK \
		struct macro_CLASS; \
		typedef struct macro_CLASS macro_CLASS; \
		EXTERN_STDMETHODIMP MOA_CREATE_PARMS(macro_CLASS); \
		EXTERN_STDMETHODIMP_(void) MOA_DESTROY_PARMS(macro_CLASS); \
		struct macro_CLASS : public IMoaUnknown \
		{ \
			_BASE_STRUCTURES \
			BEGIN_INTERFACE \
			STDMETHOD(QueryInterface) (THIS_ ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppvObj);\
			STDMETHOD_(MoaUlong, AddRef) (THIS);\
			STDMETHOD_(MoaUlong, Release) (THIS); \

	#define EXTERN_END_DEFINE_CLASS_INSTANCE_VARS \
		};

	// An extra operator delete in EXTERN_BEGIN_DEFINE_CLASS_INTERFACE is required
	// by Visual C++ 6 and CodeWarrior 6, but not allowed by CodeWarrior 5.
	#if defined(__MWERKS__) && __MWERKS__ < 0x2400
		#define EXTRA_MOA_DELETE(x)
	#else
		#define EXTRA_MOA_DELETE(x) inline void operator delete (PMoaVoid ptr, x * pObj) { ptr; pObj; };
	#endif

	#define EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(macro_CLASS, macro_INTF) \
		_MOA_PTRCHECK \
		struct INTF(macro_CLASS, macro_INTF); \
		typedef struct INTF(macro_CLASS, macro_INTF) INTF(macro_CLASS, macro_INTF); \
		EXTERN_STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF); \
		struct INTF(macro_CLASS, macro_INTF) : public macro_INTF \
		{ \
			_INTERFACE_STRUCTURES(macro_CLASS) \
			BEGIN_INTERFACE \
			STDMETHOD(QueryInterface) (THIS_ ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppvObj);\
			STDMETHOD_(MoaUlong, AddRef) (THIS);\
			STDMETHOD_(MoaUlong, Release) (THIS); \
			inline PMoaVoid operator new (size_t size, macro_CLASS * pObj) \
			{ \
				INTF(macro_CLASS, macro_INTF) * p = (INTF(macro_CLASS, macro_INTF) *)DLL(_MBNew)(size, pObj->pCalloc); \
				\
				if (p) { \
					p->pObj = pObj; \
					p->refCount = 1; \
					pObj->AddRef(); \
					pObj->AddRef(); \
					DLL(gXtraInterfaceCount)++; \
				} \
				\
				return((PMoaVoid)p); \
			} \
			inline void operator delete (PMoaVoid ptr) { ptr; } \
			EXTRA_MOA_DELETE(macro_CLASS) \
			INTF(macro_CLASS, macro_INTF) (MoaError * pErr); \
			~ INTF(macro_CLASS, macro_INTF) ();

	#define EXTERN_DEFINE_METHOD(macro_RETURNTYPE, macro_METHODNAME, macro_ARGLIST) \
		STDMETHOD_(macro_RETURNTYPE, macro_METHODNAME) macro_ARGLIST ;

	#define EXTERN_END_DEFINE_CLASS_INTERFACE \
		};
	
#else	/* not CPLUS */

	#define CALL_CALLOC(pCalloc, sz) (pCalloc)->lpVtbl->NRAlloc((PIMoaCalloc)(pCalloc), (sz))
	#define CALL_NRFREE(pCalloc, p) (pCalloc)->lpVtbl->NRFree((PIMoaCalloc)(pCalloc), (p))

	/* This macro simply declares the structure of your object. */
	#define EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(macro_CLASS) \
		_MOA_PTRCHECK \
		struct macro_CLASS; \
		typedef struct macro_CLASS macro_CLASS; \
		EXTERN_STDMETHODIMP MOA_CREATE_PARMS(macro_CLASS); \
		EXTERN_STDMETHODIMP_(void) MOA_DESTROY_PARMS(macro_CLASS); \
		struct macro_CLASS { \
			IMoaUnknownVtbl * lpVtbl; 		/* our vtable */ \
			_BASE_STRUCTURES

	#define EXTERN_END_DEFINE_CLASS_INSTANCE_VARS \
		};
	
	/* This macro simply declares the structure of a given interface to your object */
	#define EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(macro_CLASS, macro_INTF) \
		_MOA_PTRCHECK \
		struct INTF(macro_CLASS, macro_INTF); \
		typedef struct INTF(macro_CLASS, macro_INTF) INTF(macro_CLASS, macro_INTF); \
		EXTERN_STDMETHODIMP MOA_CREATEI_PARMS(macro_CLASS, macro_INTF); \
		EXTERN_STDMETHODIMP_(void) MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP INTFQUERY_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP_(MoaUlong) INTFADDREF_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP_(MoaUlong) INTFRELEASE_PARMS(macro_CLASS, macro_INTF); \
		EXTERN_STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF); \
		EXTERN_C PMoaVoid DLL(BuildGenInterface)(MBObject * pObj, MoaLong interfaceSize, MoaCreatedProc createdProc, PMoaVoid vtbl, MoaError * pErr); \
		\
		struct INTF(macro_CLASS, macro_INTF) { \
			INTFVTBL(macro_INTF) *	lpVtbl; \
			_INTERFACE_STRUCTURES(macro_CLASS) \

	#define EXTERN_DEFINE_METHOD(macro_RETURNTYPE, macro_METHODNAME, macro_ARGLIST)

	#define EXTERN_END_DEFINE_CLASS_INTERFACE \
		};
	
#endif

/* Not CPLUS -- we need to define this in case some files use C and some C++ */
#ifdef __cplusplus

	EXTERN_C PMoaVoid DLL(_MBNew)(size_t size, PIMoaCalloc pCalloc);
	EXTERN_C void DLL(_MBDelete)(PMoaVoid ptr, PIMoaCalloc pCalloc);

	#define DECLARE_MBNEW \
		\
		PMoaVoid DLL(_MBNew)(size_t size, PIMoaCalloc pCalloc) \
		{ \
			PMoaVoid ptr; \
			while ((ptr = CALL_CALLOC(pCalloc, size)) == NULL) { \
				_MOA_DO_NEW_HANDLER; \
			} \
			return(ptr); \
		} \
		\
		void DLL(_MBDelete)(PMoaVoid ptr, PIMoaCalloc pCalloc) \
		{ \
			MOA_CLOBBERTEST(ptr, "_MBDelete") \
			CALL_NRFREE(pCalloc, ptr); \
		} \
		
#else

	#define DECLARE_MBNEW 	/* empty */

#endif

EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(MBObject)
EXTERN_END_DEFINE_CLASS_INSTANCE_VARS

#ifndef CPLUS
#ifdef DEBUG_ALLOC
 #include "unnew.h"
#endif

EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(MBObject, IMoaUnknown)
EXTERN_END_DEFINE_CLASS_INTERFACE

#ifdef DEBUG_ALLOC
 #include "renew.h"
#endif

#endif

/* ========================================================================== */
/* =========================== Interface Routines =========================== */
/* ========================================================================== */

STDAPI_(MoaLong) MoaEqualID(ConstPMoaID a, ConstPMoaID b);

/* ========================================================================== */
/* ============================= Global Variables =========================== */
/* ========================================================================== */

#if !defined(MOA_APP_CODE)
    EXTERN_C MoaFileRef gXtraFileRef;
#endif

EXTERN_C MoaLong DLL(gXtraInterfaceCount);

/* ========================================================================== */
/* =========================== Macro Definitiions =========================== */
/* ========================================================================== */

/* ---------------------------------------------- VTable-constructing macros. */

/*
	By default, choose "safer vtable" over the slightly smaller and
	faster (but more error-prone) fast vtable macros.
*/
#ifndef SMALLER_VTABLE
	#undef SAFER_VTABLE
	#define SAFER_VTABLE 1
#endif

#if !defined(MOA_STATIC_ADDR_ALLOWED) && defined(MACINTOSH)
	#undef SMALLER_VTABLE
	#undef SAFER_VTABLE
	#define SAFER_VTABLE 1
#endif

#ifdef SAFER_VTABLE

	/*
		This is "safer" because it's not order-dependent.
	*/
	#define EXTERN_GET_VTABLE(macro_CLASS, macro_INTF) \
		EXTERN_C INTFVTBL(macro_INTF) * GETVTBL(macro_CLASS, macro_INTF)(void);
	
	#ifdef MOA_DEBUG
		#define _DBG_VT_NM(macro_CLASS, macro_INTF) \
			char* vtNm = "Bad Vtbl" #macro_CLASS #macro_INTF;
	#else
		#define _DBG_VT_NM(macro_CLASS, macro_INTF)
	#endif
	
	#define BEGIN_VTABLE(macro_CLASS, macro_INTF) \
	_MOA_PTRCHECK \
	INTFVTBL(macro_INTF) THEVTBL(macro_CLASS, macro_INTF); \
	char INITVTBL(macro_CLASS, macro_INTF) = 0; \
	\
	EXTERN_GET_VTABLE(macro_CLASS, macro_INTF) \
	INTFVTBL(macro_INTF) * GETVTBL(macro_CLASS, macro_INTF)(void) { \
		INTFVTBL(macro_INTF) * result; \
		result = &THEVTBL(macro_CLASS, macro_INTF); \
		if (!INITVTBL(macro_CLASS, macro_INTF)) { \
			INTFVTBL(macro_INTF) * lpVtbl = &THEVTBL(macro_CLASS, macro_INTF); \
			int vtErrChk = sizeof(INTFVTBL(macro_INTF)) / sizeof(PMoaVoid) - _MOA_VTABLE_EXTRA_ENTRIES; \
			_DBG_VT_NM(macro_CLASS, macro_INTF) \
			INITVTBL(macro_CLASS, macro_INTF) = 1; \

	#define VTABLE_ENTRY(macro_METHODNAME, macro_IMPLROUTINENAME) \
			*(PPMoaVoid)&(lpVtbl->macro_METHODNAME) = (PMoaVoid)(macro_IMPLROUTINENAME); vtErrChk--;

	#define FIRST_VTABLE_ENTRY(macro_METHODNAME, macro_IMPLROUTINENAME) \
			VTABLE_ENTRY(macro_METHODNAME, macro_IMPLROUTINENAME)
	
	#define END_VTABLE \
			MOA_ASSERT(vtErrChk == 0, vtNm); \
		}\
		return(result); \
	} \

	#define GET_VTABLE(macro_CLASS, macro_INTF) \
		GETVTBL(macro_CLASS, macro_INTF)()

#else

	#define EXTERN_GET_VTABLE(macro_CLASS, macro_INTF) \
		EXTERN_C MOA_READONLY(PMoaVoid) THEVTBL(macro_CLASS, macro_INTF)[sizeof(INTFVTBL(macro_INTF))/sizeof(PMoaVoid)];

	#define BEGIN_VTABLE(macro_CLASS, macro_INTF) \
		_MOA_PTRCHECK \
		MOA_READONLY(PMoaVoid) THEVTBL(macro_CLASS, macro_INTF)[sizeof(INTFVTBL(macro_INTF))/sizeof(PMoaVoid)] = {
	
	#define FIRST_VTABLE_ENTRY(macro_METHODNAME, macro_IMPLROUTINENAME) \
				_MOA_VTABLE_FILL_EXTRA_ENTRIES \
				(PMoaVoid)(macro_IMPLROUTINENAME)

	#define VTABLE_ENTRY(macro_METHODNAME, macro_IMPLROUTINENAME) \
			, (PMoaVoid)(macro_IMPLROUTINENAME)

	
	#define END_VTABLE \
			};

	#define GET_VTABLE(macro_CLASS, macro_INTF) \
		((INTFVTBL(macro_INTF) *)&THEVTBL(macro_CLASS, macro_INTF))
#endif

/* -------------------------------------------------- Xtra-Declaration macros */
/*
	These macros construct the DllGetClassObject, DllGetInterface,
	and DllCanUnloadNow routines; declare the types of the objects
	you specify; and glue to the Stub routines above.
*/

#define STD_CLASS_CREATE_DESTROY(macro_CLASS) \
	EXTERN_STDMETHODIMP MOA_CREATE_PARMS(macro_CLASS); \
	EXTERN_STDMETHODIMP_(void) MOA_DESTROY_PARMS(macro_CLASS); \
	STDMETHODIMP MOA_CREATE_PARMS(macro_CLASS) { This; return(kMoaErr_NoErr); } \
	STDMETHODIMP_(void) MOA_DESTROY_PARMS(macro_CLASS) { This; }

#ifdef CPLUS

	#define STD_INTERFACE_CREATE_DESTROY(macro_CLASS, macro_INTF) \
		INTF(macro_CLASS, macro_INTF)::INTF(macro_CLASS, macro_INTF)(MoaError * pErr) { *pErr = (kMoaErr_NoErr); } \
		INTF(macro_CLASS, macro_INTF)::~ INTF(macro_CLASS, macro_INTF)() { }

	#define BEGIN_DEFINE_CLASS_INTERFACE(macro_CLASS, macro_INTF) \
		_MOA_PTRCHECK \
		STDMETHODIMP INTF(macro_CLASS, macro_INTF)::QueryInterface(ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv) \
		{ \
			X_ENTER \
			MOA_CLOBBERTEST(this, #macro_CLASS "_" #macro_INTF "::QueryInterface") \
			X_STD_RETURN(this->pObj->QueryInterface(pInterfaceID, ppv)); \
			X_EXIT \
		} \
		 \
		STDMETHODIMP_(MoaUlong) INTF(macro_CLASS, macro_INTF)::AddRef() \
		{ \
			X_ENTER \
			MOA_CLOBBERTEST(this, #macro_CLASS "_" #macro_INTF "::AddRef") \
			this->pObj->AddRef(); \
			X_RETURN(MoaUlong, MOA_INTERLOCKED_INCREMENT(&this->refCount)); \
			X_EXIT \
		} \
		 \
		STDMETHODIMP_(MoaUlong) INTF(macro_CLASS, macro_INTF)::Release() \
		{ \
			X_ENTER \
			MBObject * localPObj; \
			MoaUlong result; \
			 \
			MOA_CLOBBERTEST(this, #macro_CLASS "_" #macro_INTF "::Release") \
			result = MOA_INTERLOCKED_DECREMENT(&this->refCount); \
			MOA_ASSERT(result >= 0, "saveRef must be positive"); \
			localPObj = (MBObject *)this->pObj; \
			\
			if (result == 0) { \
				delete this; \
				/* this call is necessary even in C++ because we overload delete \
					to do nothing. */ \
				DLL(_MBDelete)(this, localPObj->pCalloc); \
				DLL(gXtraInterfaceCount)--; \
				localPObj->Release(); \
			} \
		 	\
		 	localPObj->Release(); \
			X_RETURN(MoaUlong, result); \
			X_EXIT \
		} \
		 \
		EXTERN_STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF) \
		{ \
			X_ENTER_(pObj->magicCookie) \
			INTF(macro_CLASS, macro_INTF) * pIF = NULL; \
			MoaError err = kMoaErr_NoErr; \
			 \
			MOA_CLOBBERTEST(pObj, #macro_CLASS "_" #macro_INTF "::New") \
			pIF = new(pObj) INTF(macro_CLASS, macro_INTF)(&err); \
			\
			if (pIF) { \
				if (err) { \
					pIF->Release(); \
					pIF = NULL; \
				} \
			} \
			else { \
				err = kMoaErr_OutOfMem; \
			} \
		 	\
		 	*ppIF = (PMoaVoid)pIF; \
			X_STD_RETURN(err); \
			X_EXIT \
		}

	#define DEFINE_METHOD(macro_METHODNAME, macro_IMPLNAME)

	#define END_DEFINE_CLASS_INTERFACE

#else
	
	#define STD_INTERFACE_CREATE_DESTROY(macro_CLASS, macro_INTF) \
		EXTERN_STDMETHODIMP MOA_CREATEI_PARMS(macro_CLASS, macro_INTF); \
		EXTERN_STDMETHODIMP_(void) MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP MOA_CREATEI_PARMS(macro_CLASS, macro_INTF) { This; return(kMoaErr_NoErr); } \
		STDMETHODIMP_(void) MOA_DESTROYI_PARMS(macro_CLASS, macro_INTF) { This; }
	
	#define BEGIN_DEFINE_CLASS_INTERFACE(macro_CLASS, macro_INTF) \
		\
		_MOA_PTRCHECK \
		STDMETHODIMP INTFQUERY_PARMS(macro_CLASS, macro_INTF) \
		{ \
			X_ENTER \
			MOA_CLOBBERTEST(This, #macro_CLASS "_" #macro_INTF "::QueryInterface") \
			X_STD_RETURN(This->pObj->lpVtbl->QueryInterface((PIMoaUnknown)This->pObj, pInterfaceID, ppv)); \
			X_EXIT \
		} \
		 \
		STDMETHODIMP_(MoaUlong) INTFADDREF_PARMS(macro_CLASS, macro_INTF) \
		{ \
			X_ENTER \
			MOA_CLOBBERTEST(This, #macro_CLASS "_" #macro_INTF "::AddRef") \
			This->pObj->lpVtbl->AddRef((PIMoaUnknown)This->pObj); \
			X_RETURN(MoaUlong, MOA_INTERLOCKED_INCREMENT(&This->refCount)); \
			X_EXIT \
		} \
		 \
		STDMETHODIMP_(MoaUlong) INTFRELEASE_PARMS(macro_CLASS, macro_INTF) \
		{ \
			X_ENTER \
			MBObject * localPObj; \
			MoaUlong result; \
			 \
			MOA_CLOBBERTEST(This, #macro_CLASS "_" #macro_INTF "::Release") \
			result = MOA_INTERLOCKED_DECREMENT(&This->refCount); \
			MOA_ASSERT(result >= 0, "saveRef must be positive"); \
			localPObj = (MBObject *)This->pObj; \
			\
			if (result == 0) { \
				MOA_DESTROYI(macro_CLASS, macro_INTF)(This); \
				localPObj->pCalloc->lpVtbl->NRFree(localPObj->pCalloc, This); \
				DLL(gXtraInterfaceCount)--; \
				localPObj->lpVtbl->Release((PIMoaUnknown)localPObj); \
			} \
		 	\
		 	localPObj->lpVtbl->Release((PIMoaUnknown)localPObj); \
			X_RETURN(MoaUlong, result); \
			X_EXIT \
		} \
		 \
		EXTERN_GET_VTABLE(macro_CLASS, macro_INTF) \
		EXTERN_STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF); \
		STDMETHODIMP INTFBUILD_PARMS(macro_CLASS, macro_INTF) \
		{ \
			X_ENTER_(pObj->magicCookie) \
			INTF(macro_CLASS, macro_INTF) * pIF = NULL; \
			MoaError err = kMoaErr_NoErr; \
			 \
			MOA_CLOBBERTEST(pObj, #macro_CLASS "_" #macro_INTF "::New") \
			pIF = CALL_BGI(macro_CLASS, macro_INTF, pObj, &err); \
			\
			if (pIF) { \
				if (err) { \
					pIF->lpVtbl->Release((macro_INTF *)pIF); \
					pIF = NULL; \
				} \
			} \
			else { \
				err = kMoaErr_OutOfMem; \
			} \
		 	\
		 	*ppIF = (PMoaVoid)pIF; \
			X_STD_RETURN(err); \
			X_EXIT \
		} \
		BEGIN_VTABLE(macro_CLASS, macro_INTF) \
			FIRST_VTABLE_ENTRY(QueryInterface, INTFQUERY(macro_CLASS, macro_INTF)) \
			VTABLE_ENTRY(AddRef, INTFADDREF(macro_CLASS, macro_INTF)) \
			VTABLE_ENTRY(Release, INTFRELEASE(macro_CLASS, macro_INTF)) \
	
	#define DEFINE_METHOD(macro_METHODNAME, macro_IMPLNAME) \
			VTABLE_ENTRY(macro_METHODNAME, macro_IMPLNAME)
	
	#define END_DEFINE_CLASS_INTERFACE \
		END_VTABLE

#endif

#ifdef CPLUS

	#define STDINTERFACE_PREFACE \
		DECLARE_MBNEW
	
#else

	#define STDINTERFACE_PREFACE \
		\
		DECLARE_MBNEW \
		\
		EXTERN_C PMoaVoid DLL(BuildGenInterface)(MBObject * pObj, MoaLong interfaceSize, MoaCreatedProc createdProc, PMoaVoid vtbl, MoaError * pErr); \
		EXTERN_C PMoaVoid DLL(BuildGenInterface)(MBObject * pObj, MoaLong interfaceSize, MoaCreatedProc createdProc, PMoaVoid vtbl, MoaError * pErr) \
		{ \
			MBObject_IMoaUnknown * pIF = NULL; \
			PIMoaCalloc pCalloc = pObj->pCalloc; \
			\
			pIF = (MBObject_IMoaUnknown *)pCalloc->lpVtbl->NRAlloc(pCalloc, interfaceSize); \
			\
			if (pIF) { \
				pIF->lpVtbl = (IMoaUnknownVtbl *)vtbl; \
				pIF->pObj = pObj; \
				pIF->refCount = 1; \
				pObj->lpVtbl->AddRef((PIMoaUnknown)pObj); \
				pObj->lpVtbl->AddRef((PIMoaUnknown)pObj); \
				DLL(gXtraInterfaceCount)++; \
				*pErr = (*createdProc)((PMoaVoid)pIF); \
				/* do NOT release in event of error. */ \
			} \
			else { \
				*pErr = kMoaErr_OutOfMem; \
			} \
			return(pIF); \
		}

#endif

typedef MOA_STD_METHOD_PROCPTR(MoaError, XtraBuildInterfaceProc)(
	PMoaVoid pObj,
	PPMoaVoid ppIF
);

typedef MOA_STD_METHOD_PROCPTR(MoaError, XtraEnumClassFormProc)(
	ConstPMoaClassID pClassID,
	MoaLong classVersion,
	MoaLong objSize,
	MoaCreatedProc createProc,
	MoaDestroyedProc destroyProc,
	PMoaVoid refCon
);

typedef MOA_STD_METHOD_PROCPTR(MoaError, XtraEnumClassInterfacesProc)(
	ConstPMoaClassID pClassID,
	MoaLong classVersion,
	ConstPMoaInterfaceID pInterfaceID,
	MoaLong interfaceVersion,
	XtraBuildInterfaceProc buildProc,
	PMoaVoid refCon
);

#define _GLUE_GETCLASSOBJECT \
	STDAPI DLL(GetClassObject)(REFCLSID rclsid, REFIID riid, PPMoaVoid ppv); \
	STDAPIIMP DLL(GetClassObject)(REFCLSID rclsid, REFIID riid, PPMoaVoid ppv) { \
		rclsid; riid; ppv; /* avoid unused warnings in MPW C */ \
		return kMoaErr_BadClass; \
	} \

#define _GLUE_CANUNLOADNOW \
	STDAPI DLL(CanUnloadNow)(void); \
	STDAPIIMP DLL(CanUnloadNow)(void) { \
		X_ENTER_DLLENTRYPOINT \
		X_STD_RETURN((DLL(gXtraInterfaceCount) == 0 ? 0 : kMoaErr_XtraInUse)); \
		X_EXIT \
	} \

#define _GLUE_GETCLASSFORM \
	typedef struct { \
		MoaLong * pObjSize; \
		MoaCreatedProc * pCreateProc; \
		MoaDestroyedProc * pDestroyProc; \
		MoaBool found; \
	} _XtraGetClassFormRec; \
	STDMETHODIMP DLL(_XtraGetClassForm)(ConstPMoaClassID pClassID, MoaLong classVersion, MoaLong objSize, MoaCreatedProc createProc, MoaDestroyedProc destroyProc, _XtraGetClassFormRec * pInfo); \
	STDMETHODIMP DLL(_XtraGetClassForm)(ConstPMoaClassID pClassID, MoaLong classVersion, MoaLong objSize, MoaCreatedProc createProc, MoaDestroyedProc destroyProc, _XtraGetClassFormRec * pInfo) \
	{ \
		pClassID; classVersion; \
		*pInfo->pObjSize = objSize; \
		*pInfo->pCreateProc = createProc; \
		*pInfo->pDestroyProc = destroyProc; \
		pInfo->found = TRUE; \
		return (MoaError)1; \
	} \
	STDAPI DLL(GetClassForm)(ConstPMoaClassID pClassID, MoaLong * pObjSize, MoaCreatedProc * pCreateProc, MoaDestroyedProc * pDestroyProc); \
	STDAPIIMP DLL(GetClassForm)(ConstPMoaClassID pClassID, MoaLong * pObjSize, MoaCreatedProc * pCreateProc, MoaDestroyedProc * pDestroyProc) { \
		_XtraGetClassFormRec info; \
		X_ENTER_DLLENTRYPOINT \
		info.pObjSize = pObjSize; \
		info.pCreateProc = pCreateProc; \
		info.pDestroyProc = pDestroyProc; \
		info.found = FALSE; \
		DLL(SecretGlue)(pClassID, (XtraEnumClassFormProc)DLL(_XtraGetClassForm), NULL, &info); \
		X_STD_RETURN(info.found ? kMoaErr_NoErr : kMoaErr_BadClass); \
		X_EXIT \
	} \


#define _GLUE_GETINTERFACE \
	typedef struct { \
		ConstPMoaInterfaceID pInterfaceID; \
		XtraBuildInterfaceProc buildProc; \
	} _XtraGetClassInterfaceRec; \
	STDMETHODIMP DLL(_XtraGetClassInterface)(ConstPMoaClassID pClassID, MoaLong classVersion, ConstPMoaInterfaceID pInterfaceID, MoaLong interfaceVersion, XtraBuildInterfaceProc buildProc, _XtraGetClassInterfaceRec * pInfo); \
	STDMETHODIMP DLL(_XtraGetClassInterface)(ConstPMoaClassID pClassID, MoaLong classVersion, ConstPMoaInterfaceID pInterfaceID, MoaLong interfaceVersion, XtraBuildInterfaceProc buildProc, _XtraGetClassInterfaceRec * pInfo) \
	{ \
		pClassID; classVersion; interfaceVersion; \
		if (MoaEqualID(pInterfaceID, pInfo->pInterfaceID)) { \
			pInfo->buildProc = buildProc; \
			return (MoaError)1; \
		} \
		return (MoaError)0; \
	} \
	\
	STDAPI DLL(GetInterface)(PMoaVoid pObj, ConstPMoaClassID pClassID, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv); \
	STDAPIIMP DLL(GetInterface)(PMoaVoid pObj, ConstPMoaClassID pClassID, ConstPMoaInterfaceID pInterfaceID, PPMoaVoid ppv) { \
		_XtraGetClassInterfaceRec info; \
		X_ENTER_DLLENTRYPOINT \
		info.pInterfaceID = pInterfaceID; \
		info.buildProc = NULL; \
		DLL(SecretGlue)(pClassID, NULL, (XtraEnumClassInterfacesProc)DLL(_XtraGetClassInterface), &info); \
		X_STD_RETURN(info.buildProc ? (*info.buildProc)(pObj, ppv) : kMoaErr_BadInterface); \
		X_EXIT \
	} \

#define _GLUE_GETCLASSINFO \
	typedef struct { \
		MoaLong count; \
		PMoaClassInterfaceInfo pCur; \
	} _XtraGetClassInfoRec; \
	STDMETHODIMP DLL(_XtraGcfInfo)(ConstPMoaClassID pClassID, MoaLong classVersion, MoaLong objSize, MoaCreatedProc createProc, MoaDestroyedProc destroyProc, _XtraGetClassInfoRec * pInfo); \
	STDMETHODIMP DLL(_XtraGcfInfo)(ConstPMoaClassID pClassID, MoaLong classVersion, MoaLong objSize, MoaCreatedProc createProc, MoaDestroyedProc destroyProc, _XtraGetClassInfoRec * pInfo) \
	{ \
		objSize; createProc; destroyProc; \
		++pInfo->count; \
		if (pInfo->pCur) { \
			pInfo->pCur->classID = *pClassID; \
			pInfo->pCur->classVersion = classVersion; \
			pInfo->pCur->interfaceID = IID_IMoaClassFactory; \
			pInfo->pCur->interfaceVersion = 1; \
			++pInfo->pCur; \
		} \
		return 0; \
	} \
	STDMETHODIMP DLL(_XtraGciInfo)(ConstPMoaClassID pClassID, MoaLong classVersion, ConstPMoaInterfaceID pInterfaceID, MoaLong interfaceVersion, XtraBuildInterfaceProc buildProc, _XtraGetClassInfoRec * pInfo); \
	STDMETHODIMP DLL(_XtraGciInfo)(ConstPMoaClassID pClassID, MoaLong classVersion, ConstPMoaInterfaceID pInterfaceID, MoaLong interfaceVersion, XtraBuildInterfaceProc buildProc, _XtraGetClassInfoRec * pInfo) \
	{ \
		buildProc; \
		++pInfo->count; \
		if (pInfo->pCur) { \
			pInfo->pCur->classID = *pClassID; \
			pInfo->pCur->classVersion = classVersion; \
			pInfo->pCur->interfaceID = *pInterfaceID; \
			pInfo->pCur->interfaceVersion = interfaceVersion; \
			++pInfo->pCur; \
		} \
		return 0; \
	} \
	STDAPI DLL(GetClassInfo)(PIMoaCalloc pCalloc, ConstPMoaClassInterfaceInfo * ppClassInfo); \
	STDAPIIMP DLL(GetClassInfo)(PIMoaCalloc pCalloc, ConstPMoaClassInterfaceInfo * ppClassInfo) { \
		_XtraGetClassInfoRec info; \
		X_ENTER_DLLENTRYPOINT \
		info.count = 0; \
		info.pCur = NULL; \
		DLL(SecretGlue)(NULL, (XtraEnumClassFormProc)DLL(_XtraGcfInfo), (XtraEnumClassInterfacesProc)DLL(_XtraGciInfo), &info); \
		*ppClassInfo = (ConstPMoaClassInterfaceInfo)CALL_CALLOC(pCalloc, (info.count + 1) * sizeof(MoaClassInterfaceInfo)); \
		if (!*ppClassInfo) X_STD_RETURN(kMoaErr_OutOfMem); \
		info.pCur = (PMoaClassInterfaceInfo)*ppClassInfo; \
		DLL(SecretGlue)(NULL, (XtraEnumClassFormProc)DLL(_XtraGcfInfo), (XtraEnumClassInterfacesProc)DLL(_XtraGciInfo), &info); \
		info.pCur->classID = IID_NULL; \
		info.pCur->interfaceID = IID_NULL; \
		X_STD_RETURN(kMoaErr_NoErr); \
		X_EXIT \
	}

#define BEGIN_XTRA \
	_MOA_PTRCHECK \
	XTRA_PREFACE \
	STDINTERFACE_PREFACE \
	static MoaError DLL(SecretGlue)( \
		ConstPMoaClassID pClassID, \
		XtraEnumClassFormProc ecfProc, \
		XtraEnumClassInterfacesProc eciProc, \
		PMoaVoid refCon); \
	static MoaError DLL(SecretGlue)( \
		ConstPMoaClassID pClassID, \
		XtraEnumClassFormProc ecfProc, \
		XtraEnumClassInterfacesProc eciProc, \
		PMoaVoid refCon) { \
		\
		MoaError err = 0; \
		X_ENTER_DLLENTRYPOINT \
		pClassID; ecfProc; eciProc; \
		do { \


#define BEGIN_XTRA_AUGMENTS_CLASS(macro_CLASS, macro_CLASSVERSION) \
		if (!pClassID || MoaEqualID(pClassID, &CLSID(macro_CLASS)) || &(CLSID(macro_CLASS)) == &CLSID_AnyClass) { \
		ConstPMoaClassID pCurClassID = &CLSID(macro_CLASS); \
		MoaLong curClassVersion = macro_CLASSVERSION; \
		\
		if (eciProc) {

#define BEGIN_XTRA_DEFINES_CLASS(macro_CLASS, macro_CLASSVERSION) \
		if (!pClassID || MoaEqualID(pClassID, &CLSID(macro_CLASS)) || &(CLSID(macro_CLASS)) == &CLSID_AnyClass) { \
		ConstPMoaClassID pCurClassID = &CLSID(macro_CLASS); \
		MoaLong curClassVersion = macro_CLASSVERSION; \
		\
		err = ecfProc ? (*ecfProc)(pCurClassID, curClassVersion, sizeof(macro_CLASS), (MoaCreatedProc)(MOA_CREATE(macro_CLASS)), (MoaDestroyedProc)(MOA_DESTROY(macro_CLASS)), refCon) : 0; \
		if (err) break; \
		if (eciProc) {


#ifdef MOA_DEBUG
	#define _BX_DBG_CHK(c1, c2) MOA_ASSERT(c1 == c2, "Class Mismatch in macro");
#else
	#define _BX_DBG_CHK(c1, c2) ;
#endif

#define CLASS_DEFINES_INTERFACE(macro_CLASS, macro_INTF, macro_INTERFACEVERSION) \
			_BX_DBG_CHK(&CLSID(macro_CLASS), pCurClassID) \
			{ \
			/* this can cause problems when mixing C and C++ */ \
			/*STDMETHODIMP INTFBUILD(macro_CLASS, macro_INTF)(macro_CLASS * pObj, struct INTF(macro_CLASS, macro_INTF) * * ppIF);*/ \
			err = (*eciProc)(pCurClassID, curClassVersion, &IID(macro_INTF), macro_INTERFACEVERSION, (XtraBuildInterfaceProc)(INTFBUILD(macro_CLASS, macro_INTF)), refCon); \
			if (err) break; \
			}

#define END_XTRA_DEFINES_CLASS \
		} }

#define END_XTRA \
		} while (0); \
		X_EXIT \
		return err; \
	} \
	\
	MoaLong DLL(gXtraInterfaceCount) = 0; \
	\
	_GLUE_GETCLASSOBJECT \
	_GLUE_CANUNLOADNOW \
	_GLUE_GETCLASSFORM \
	_GLUE_GETINTERFACE \
	_GLUE_GETCLASSINFO


#undef INTERFACE /* leave it undefined */

#endif /* _H_moaxtra */

