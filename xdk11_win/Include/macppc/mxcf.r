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
File: mxcf.r		(mac)

Rez template for the standard MXcf resource.

This file should be rezzed into every fat Macintosh Xtra.
It is not necessary for an application.
*/

#if 0

type 'TMPL' {
	wide array {
		pstring;
		literal longint;
	};
};

resource 'TMPL' (128, "MXcf") {
	{
		"Pad for long count", 			'FWRD',
		"MemberArray", 					'OCNT',
		"-----", 						'LSTC',
		"Arch Type", 					'TNAM',
		"Offset (0 = default)", 		'DLNG',
		"Length (0 = default)", 		'DLNG',
		"-----", 						'LSTE',
	}
};

#endif

type 'MXcf' {
	longint = $$CountOf(memberArray);
	wide array memberArray {
		literal longint archType, kPowerPC = 'pwpc', k68kCodeResource = 'cr68';
		longint offset, kZeroOffset = 0;
		longint length, kWholeFork = 0;
	};
};

resource 'MXcf' (128) {
	{
		kPowerPC, kZeroOffset, kWholeFork,
		k68kCodeResource, kZeroOffset, kWholeFork,
	}
};

