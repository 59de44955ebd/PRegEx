/*
-------------------------------------------------------------------------
Regular Expression Xtra Licensing Statement
Version 2.0
-------------------------------------------------------------------------

This is a Scripting Xtra for Macromedia Director which lets you use regular
expressions as implemented by PCRE http://pcre.org/, plus a whole lot more.

Written by:

      Chris Thorman <chris@thorman.com>
         Ravi Singh <ravi@ravware.com>

Copyright (c) 2001-2008 Chris Thorman

-----------------------------------------------------------------------------
Permission is granted to anyone to use this software for any purpose on any
computer system, and to redistribute it freely, subject to the following
restrictions:

1. This software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

2. The origin of this software must not be misrepresented, either by
   explicit claim or by omission.

3. Altered versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

4. If PRegEx is embedded in any software that is released under the GNU
   General Purpose License (GPL), then the terms of that license shall
   supersede any condition above with which it is incompatible.

(Thanks to Philip Hazel, creator of PCRE, for the above licensing statement.)
-----------------------------------------------------------------------------
*/


#ifndef _H_rereg
#define _H_rereg

/*****************************************************************************
 *  HOW TO CUSTOMIZE THIS FILE
 *  --------------------------
 *  1. Save this file under a different file name.
 *  2. Use a search and replace utility (case sensitive) to replace the
 *     following:
 *
 *     Replace         With	
 *     -------		     ----
 *     cregister	   	 <this file name>
 *     CRegister       <name of the class you defined>
 *
 *  3. Add and modify source code by looking for '--> insert -->' comment
 *  4. Create a Xtra.cpp file that contains the Xtra definition.
 **********************************************************************************/ 

/*****************************************************************************
 *  XTRA SPECIFIC DEFINE(S)
 *  -----------------------
 *	Any #define's specific to this Xtra.  
 *****************************************************************************/ 

/*****************************************************************************
 *  INCLUDE FILE(S)
 *  ---------------
 *	This .h file should automatically include all the support files needed for 
 *  this particular class. In addition, this file may include other .h files 
 *  that define additional callback interfaces for use by a third party.   
 *****************************************************************************/ 
#ifndef _H_moaxtra
	#include "moaxtra.h"
#endif

#ifndef _H_remain
	#include "re_main.h"
#endif

/* NOTE: #include any .h file that contains the CLSID of the class(es) that you
   you will be registering */


/*****************************************************************************
 *  CONFIGURATION DEFINE(S)
 *  -----------------------
 *	Uncomment the line below to activate debugging or load control code.
 ****************************************************************************/ 
//#define MOA_DEBUG

#define USING_LOAD_CONTROL

/*****************************************************************************
 *	CLASS SPECIFIC DEFINE(S)
 *	-----------------------
 *	Any #define's specific to this class 
 ****************************************************************************/ 
#ifndef UNUSED
	#define UNUSED(x) x
#endif

/*****************************************************************************
 *	CLSID
 *	-----
 *	The CLSID is a GUID that unquely identifies your MOA class.  To generate a
 *	GUID, use the genUID.app utility (Mac) or the GUIDGEN.EXE utility (Win).
 *	The following line will produce a pre-compiler error if not replaced with
 *	a valid CLSID.
 ****************************************************************************/ 
// December 1,2000
// {D581DFE6-C795-11d4-85DD-E0C947C10000}
DEFINE_GUID(CLSID(CREGEXPRESSIONRegister), 
0xd581dfe6, 0xc795, 0x11d4, 0x85, 0xdd, 0xe0, 0xc9, 0x47, 0xc1, 0x0, 0x0);




/*****************************************************************************
 *  CLASS INSTANCE VARIABLES
 *  ------------------------
 *  Class instance variable are variables whose scope is exclusive to the
 *  methods implemented by your MOA class.  Variables necessary for the
 *  implementation of your MOA class should be places here.
 *****************************************************************************/ 
EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(CREGEXPRESSIONRegister) 
	/*
	 * ---> insert additional variable(s) -->
	 */ 
EXTERN_END_DEFINE_CLASS_INSTANCE_VARS

/*****************************************************************************
 *  CLASS INTERFACE(S)
 *  ------------------
 *  The interface(s) implemented by your MOA class are specified here.  Note
 *	that at least one class in your Xtra should implement the IMoaRegister
 *	interface.
 *  NOTE: Because C++ does not use a lpVtbl to reference an interface's methods, 
 *  the actual method declaration is done here.
 *
 *  Syntax:
 *  EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(<class-name>, <interface-name>) 
 *		EXTERN_DEFINE_METHOD(<return-type>, <method-name>,(<argument-list>)) 
 *	EXTERN_END_DEFINE_CLASS_INTERFACE
 ****************************************************************************/ 
EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONRegister, IMoaRegister) 
	EXTERN_DEFINE_METHOD(MoaError, Register, (PIMoaCache, PIMoaDict))
EXTERN_END_DEFINE_CLASS_INTERFACE

/*
 * --> insert additional interface(s) -->
 */ 

#endif /* _H_rereg */
