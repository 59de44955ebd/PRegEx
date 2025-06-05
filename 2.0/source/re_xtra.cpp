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



/*****************************************************************************
 *  HOW TO CUSTOMIZE THIS FILE
 *  --------------------------
 *  1. Save this file under a different file name.
 *  2. Use a search and replace utility (case sensitive) to replace the
 *     following:
 *
 *     Replace         With	
 *     -------			   ----
 *     cscript		     <its file name>
 *     CScript         <name of the class you defined>
 *
 *     cregster        <its file name>
 *     CRegister       <name of the class you defined>
 *
 *  3. Add and modify source code by looking for '--> insert -->' comment
 ****************************************************************************/ 

/*****************************************************************************
 *  INCLUDE FILE(S)
 *  ---------------
 *	This .cpp file should automatically include all the support files needed
 *	for this particular class. In addition, this file may include other .h
 *	files defining additional callback interfaces for use by a third party.   
 ****************************************************************************/ 
#ifndef _H_remain
	#include "re_main.h"
#endif

#ifndef _H_rereg
	#include "re_reg.h"
#endif


/*****************************************************************************
 *  UTILITY MACROS
 *  --------------
 *	These macros calculate a precise version for your Xtra to be used in the
 *	Xtra definition below.  The first 4 #defines represent the release types
 *	you can choose when assembling your version.
 ****************************************************************************/ 
#define VERSION_DEVELOPMENT  0
#define VERSION_ALPHA        1
#define VERSION_BETA         2
#define VERSION_RELEASE      3

// Other Data in GlobalData.H
#define XTRA_RELEASE          VERSION_RELEASE
#define XTRA_RELEASE_VERSION  1

#define XTRA_MAJOR_VERSION    0
#define XTRA_MINOR_VERSION    0
#define XTRA_SUB_VERSION      1
 


#define MAKE_VERSION(major, minor, sub, releaseType, releaseVersion) \
	                  (unsigned long)(((unsigned long)major << 24) + \
	                  ((unsigned long)minor << 16) + \
	                  ((unsigned long)sub << 8) + \
	                  ((unsigned long)releaseType << 6) + \
	                  (unsigned long)releaseVersion )

 
#define XTRA_VERSION_NUMBER MAKE_VERSION(XTRA_MAJOR_VERSION, \
                                         XTRA_MINOR_VERSION, \
                                         XTRA_SUB_VERSION, \
                                         XTRA_RELEASE_VERSION, \
                                         XTRA_RELEASE)

/*****************************************************************************
 *  XTRA DEFINITION
 *  ---------------
 *  The Xtra definition specfies the classes and interfaces defined by your
 *  MOA Xtra.
 *
 *  Syntax:
 *	BEGIN_XTRA_DEFINES_CLASS(<class-name>,<version>)
 *	CLASS_DEFINES_INTERFACE(<class-name>, <interface-name>,<version>) 
 ****************************************************************************/ 
BEGIN_XTRA
	BEGIN_XTRA_DEFINES_CLASS(CREGEXPRESSIONRegister, XTRA_VERSION_NUMBER)
		CLASS_DEFINES_INTERFACE(CREGEXPRESSIONRegister, IMoaRegister, XTRA_VERSION_NUMBER)
		/*
		 * ---> insert additional interface(s) -->
		 */ 
	END_XTRA_DEFINES_CLASS
	BEGIN_XTRA_DEFINES_CLASS(CREGEXPRESSIONScript, XTRA_VERSION_NUMBER)
		CLASS_DEFINES_INTERFACE(CREGEXPRESSIONScript, IMoaMmXScript, XTRA_VERSION_NUMBER)
		#ifdef USING_INIT_FROM_DICT
		CLASS_DEFINES_INTERFACE(CREGEXPRESSIONScript, IMoaInitFromDict, XTRA_VERSION_NUMBER)	
		#endif
		#ifdef USING_NOTIFICATION_CLIENT
		CLASS_DEFINES_INTERFACE(CREGEXPRESSIONScript, IMoaNotificationClient, XTRA_VERSION_NUMBER)	
		#endif
		/*
		 * ---> insert additional interface(s) -->
		 */ 
	END_XTRA_DEFINES_CLASS
	/*
	 * ---> insert additional class(es) -->
	 */ 
END_XTRA

