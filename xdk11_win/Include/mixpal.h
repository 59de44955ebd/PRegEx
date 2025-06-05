/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_mixpal
#define _H_mixpal

#ifndef _H_mixagent
	#include "mixagent.h"
#endif

#ifndef	_H_mixpix
	#include "mixpix.h"
#endif

typedef	RenderPixelColorSpace FAR *PRenderPixelColorSpace;
typedef	const RenderPixelColorSpace FAR *ConstPRenderPixelColorSpace;

#undef INTERFACE
#define INTERFACE IMoaReceptorPalette
DECLARE_INTERFACE_(IMoaReceptorPalette, IMoaReceptor)
{
	STD_IUNKNOWN_METHODS
	
	STDMETHOD(SetRefCon)(THIS_
		moa_in PMoaVoid refCon
	) PURE;

	STDMETHOD(SetStatus)(THIS_
		moa_in MoaError status
	) PURE;

	STDMETHOD(SetPalette)(THIS_
		moa_in ConstPRenderPixelColorSpace pRenderPixelColorSpace
	) PURE;

	STDMETHOD(EndPalette)(THIS) PURE;
};
typedef IMoaReceptorPalette FAR * PIMoaReceptorPalette;
DEFINE_GUID(IID_IMoaReceptorPalette, 0xbedde900, 0x3cac, 0x11d0, 0xa1, 0x83, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

#endif

