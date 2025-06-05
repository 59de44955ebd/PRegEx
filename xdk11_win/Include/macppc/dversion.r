/*
ADOBE SYSTEMS INCORPORATED
Copyright 1996 Ð 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/


#include "dversion.h"
#include "types.r"

/////////////////////////////////////////////////////////////////////////////
//
// MAC RESOURCES
//
/////////////////////////////////////////////////////////////////////////////

// Construct BCD manglings of version numbers
//
#define VER_MAJORVERSION_BCD	16 * ((VER_MAJORVERSION / 10) % 10) + (VER_MAJORVERSION  % 10)
#define VER_SUBVERSION_BCD		16 *  (VER_MINORVERSION % 10)       + (VER_BUGFIXVERSION % 10)
#define VER_BUILDNUMBER_BCD		16 * ((VER_BUILDNUM     / 10) % 10) + (VER_BUILDNUM      % 10)


resource 'vers' (1) {
	VER_MAJORVERSION_BCD,
	VER_SUBVERSION_BCD,
	VER_MACBUILDSTAGE,
	VER_BUILDNUMBER_BCD,
	verUS,
	VER_VERSION_STRING,										// Short version string
	"Director XDK Example " VER_VERSION_STRING				// "Version" item in Get Info
};

