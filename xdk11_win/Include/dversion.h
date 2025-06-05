/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

/*
if you want to set up different version information for different xtras in the XDK,
make a copy of this file in the source folder for the example project. The local copy will
be found before the copy in the include folder and so you can customize it as you wish.
*/
					
#ifndef DVERSION_H										
#define DVERSION_H										

#define VER_BUILDNUM 1							
#define VER_BUILDNUM_STRING "1"					

#define VER_COUNTRY VER_COUNTRY_US			

//#define VER_MAJORVERSION 10				    
#define VER_MAJORVERSION_STRING "10"

//#define VER_MINORVERSION 1
#define VER_MINORVERSION_STRING "1"     
														
#define VER_BUGFIXVERSION 4
#define VER_BUGFIXVERSION_STRING "4"

#if VER_BUGFIXVERSION > 0
	#define	VER_VERSION_STRING	VER_MAJORVERSION_STRING "." VER_MINORVERSION_STRING "." VER_BUGFIXVERSION_STRING 
#else
	#define	VER_VERSION_STRING	VER_MAJORVERSION_STRING "." VER_MINORVERSION_STRING 
#endif

// following is used for the build development in the apple 'vers' resource
#define VER_MACBUILDSTAGE	development
//#define VER_MACBUILDSTAGE	alpha
//#define VER_MACBUILDSTAGE	beta
//#define VER_MACBUILDSTAGE	final

// following are used in version info for the windows resource 
#define VER_ORIGINALFILENAME	"ExampleXtra.x32"
#define VER_COMPANY				"Unknown Company, Inc."
#define VER_FILEDESCRIPTION		"Director Xtra"
#define VER_PRODUCTNAME			"XDK Example Xtra"
#define VER_INTERNALNAME		"Xtra"

#endif													
