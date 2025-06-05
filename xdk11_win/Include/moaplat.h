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
	Purpose
		Include appropriate moatyedg file for the platform.
*/

#ifndef	NO_PRAGMA_ONCE
#pragma	once
#endif

#ifndef _H_moaplat
#define	_H_moaplat


/*--------------------------------------------------------------------------*/
/* For Metrowerks CoreWarrior for Windows  
/  Strictly speaking, this ought to go further down in the headers.
/  However, the fiddly tweaks needed to set up the proper ifdef conditions
/  make the whole thing more complicated than it's worth. */ 
#if defined(__INTEL__)  /* CW's symbol for compiling under Windows */
	#define _WINDOWS	/* symbols the rest of the system expects */
	#define _WIN32
	#define NO_STRICT 1 /* otherwise, CW defines STRICT, which makes us barf. */ 
#endif



/*--------------------------------------------------------------------------*/
#if (defined(WINDOWS) || defined(_WINDOWS)|| defined(WINVER))
	#if (defined(WIN32) || defined(_WIN32))
		#if (defined(__INTEL__))
			#include "moatyedg.h" /* CW Mac does not understand windows paths; 
								  /  you must define this path explicitly in project settings. */
		#else
			#include "win32/moatyedg.h"
		#endif
	#else
		#include "win16/moatyedg.h"
	#endif
#endif /* WINDOWS || _WINDOWS */

#if (defined(MACINTOSH) || defined(_MACINTOSH) || defined(macintosh))		
	#if defined(__MACH__)
		#include "macmach/moatyedg.h"
	#else 
		#if defined(__MWERKS__)
			#include "macppc/moatyedg.h"
		#else
			#error unknown macintosh development environment
		#endif
	#endif
#endif



/*-------------------------------------------------------------------------*/

#endif	/* _H_moaplat */
