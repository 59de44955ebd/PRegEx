/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_ByteSwap
#define _H_ByteSwap

#ifndef _H_moatypes
#include "moatypes.h"
#endif

#ifdef MACINTOSH
#include <Types.h>
#endif // MACINTOSH


// inline swapping routines
inline void Swap2Shorts( MoaShort& s1, MoaShort& s2 )
{
	MoaShort temp = s1;
	s1 = s2;
	s2 = temp;
}

// use the PowerPC's reversed byte load instructions to burn rubber
// NOTE: do not use the second parameter, it is used as an optimization.
#if __powerc
inline void SwapShort( register MoaShort& value, register MoaLong temp = 0 )
{
	asm
	{
		// temp is 0 and is used as index initially
		lhbrx	temp, value, temp	// load the value but byte swapped
		sth		temp, 0(value)		// store that back
	}
}

inline void SwapShort( register MoaUshort& value, register MoaLong temp = 0 )
{
	asm
	{
		// temp is 0 and is used as index initially
		lhbrx	temp, value, temp	// load the value but byte swapped
		sth		temp, 0(value)		// store that back
	}
}

inline void SwapLong( register MoaLong& value, register MoaLong temp = 0 )
{
	asm
	{
		// temp is 0 and is used as index initially
		lwbrx	temp, value, temp	// load the value but byte swapped
		stw		temp, 0(value)		// store that back
	}
}

// do the unsigned one too, this stops warnings...
inline void SwapLong( register MoaUlong& value, register MoaLong temp = 0 )
{
	asm
	{
		// temp is 0 and is used as index initially
		lwbrx	temp, value, temp	// load the value but byte swapped
		stw		r4, 0(value)		// store that back
	}
}

#else
// C++ versions of byteswap routines.
inline void SwapShort( MoaShort& s )
{
	MoaUshort temp = (s >> 8) & 0xFF;
	s = temp | ((s & 0xFF) << 8);
}

inline void SwapShort( MoaUshort& s )
{
	MoaUshort temp = (s >> 8) & 0xFF;
	s = temp | ((s & 0xFF) << 8);
}

inline void SwapLong( MoaLong& l )
{
	// first swap bytes within word
	MoaShort* sh = (MoaShort*)&l;
	::SwapShort( sh[0] );
	::SwapShort( sh[1] );
	
	// Swap the words within the long
	::Swap2Shorts( sh[0], sh[1] );
}

// do the unsigned one too, this stops warnings...
inline void SwapLong( MoaUlong& l )
{
	// first swap bytes within word
	MoaShort* sh = (MoaShort*)&l;
	::SwapShort( sh[0] );
	::SwapShort( sh[1] );
	
	// Swap the words within the long
	::Swap2Shorts( sh[0], sh[1] );
}
#endif // MACINTOSH

#if defined( MACINTOSH ) || defined( USING_MACTYPES )
inline void SwapRect( Rect& r )
{
	::SwapShort( r.top );
	::SwapShort( r.left );
	::SwapShort( r.bottom );
	::SwapShort( r.right );
}

inline void SwapPoint( Point& p )
{
	::SwapShort( p.v );
	::SwapShort( p.h );
}
#else
inline void SwapRect( RECT& r )
{
	::SwapLong( r.top );
	::SwapLong( r.left );
	::SwapLong( r.bottom );
	::SwapLong( r.right );
}

inline void SwapPoint( POINT& p )
{
	::SwapLong( p.x );
	::SwapLong( p.y );
}
#endif
#endif	// _H_ByteSwap


