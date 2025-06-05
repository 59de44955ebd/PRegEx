/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_XMacUI
#define _H_XMacUI

/* ================================================================================

	Purpose:
	
	Provides some useful utilities for drawing mui compliant macintosh ui.
	
=================================================================================== */

#ifdef MACINTOSH

///////////////////////////////////////////////////////////////////////////////////
//
// Includes
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif

#ifndef _H_XMuiUI
#include "XMuiUI.h"
#endif

#if defined(__MWERKS__) && defined(__MC68K__)
	#pragma push
	#pragma pointers_in_D0
#endif 


///////////////////////////////////////////////////////////////////////////////////
//
// CMacUI Declares
//
///////////////////////////////////////////////////////////////////////////////////

// DO NOT INSTATIATE THIS CLASS -- contains some drawing routines
class CMacUI
{
// --------------------------------------------------------------------------------
// Construction and Destruction
// --------------------------------------------------------------------------------
	private:
		CMacUI( void )	{}
		~CMacUI( void ) {}

// --------------------------------------------------------------------------------
// Drawing routines
// --------------------------------------------------------------------------------
	public:
		static void 	DrawFrame( const Rect& ,
									CMuiUI::FrameStyle frameStyle = CMuiUI::kFlatFrameAndSunkenBevel, 
									CMuiUI::FrameOptions frameOptions = CMuiUI::kFrameAll);
		static void 	DrawRoundFrame( const Rect&, short tweak = 0);
		static void		DrawButtonOutline( const Rect&, Boolean enabled = true );

// --------------------------------------------------------------------------------
// Private routines
// --------------------------------------------------------------------------------
	private:		
		static Boolean	Use3D( void ) { return true; }
		static short	CalcCornerRadius( const Rect& theRect, Boolean small = false );
};


#if defined(__MWERKS__) && defined(__MC68K__)
	#pragma pop
#endif 

#endif // MACINTOSH
#endif	// _H_XMacUI

// EOF
