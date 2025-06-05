/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_awtypes
#define _H_awtypes

/*
	Purpose:
	
	Authorware-specific data types, constants, and macros.	
*/

#include "mmtypes.h"

#ifdef MACINTOSH
#include <Palettes.h>
#endif

/* ----------------------------------------------------------------------------
/
/  Authorware-specific types.
/
/ -------------------------------------------------------------------------- */

/* Authorware icon id */

typedef MoaLong	MoaAwIconId, FAR * PMoaAwIconId;

/* Palette type for get/set palette operations */

#ifdef _WINDOWS
	typedef HPALETTE		MoaMmHpal;
#endif

#ifdef MACINTOSH
	typedef PaletteHandle	MoaMmHpal;
#endif

typedef MoaMmHpal FAR		*PMoaMmHpal;

/* Expression compiler flags (for IMoaAwAssetCallback::StoreExpression) */

typedef MoaUlong MoaAwExprFlags;

#define kMoaAwExprFlags_None		0
#define kMoaAwExprFlags_IsScript	1

/* Information used by IMoaAwAssetCallback::Notify.
   IMoaAwAssetCallback will send out the kMoaAwMsg_ExpressionChanged
   notification message with PMoaAwExpressionInfo in refCon
   when the value of a watched expression is changed.
*/

typedef struct
{
	MoaLong		expressionId;	/* Id of expression */
	PMoaMmValue	pResult;		/* Result value of expression */
} MoaAwExpressionInfo, FAR * PMoaAwExpressionInfo;


/* ----------------------------------------------------------------------------
/
/  Authorware-specific error codes
/
/ -------------------------------------------------------------------------- */

#define		kMoaAwErr_Base						0x1300
//			kMoaAwErr_Base has reserved			0x1300-0x13ff

/* Expression errors */

#define		kMoaAwErr_ExprTooLong			MAKE_MOAERR(kMoaAwErr_Base + 101)
#define		kMoaAwErr_TokenTooLong			MAKE_MOAERR(kMoaAwErr_Base + 102)
#define		kMoaAwErr_MissingQuote			MAKE_MOAERR(kMoaAwErr_Base + 103)
#define		kMoaAwErr_UnknownOperator		MAKE_MOAERR(kMoaAwErr_Base + 104)
#define		kMoaAwErr_SyntaxError			MAKE_MOAERR(kMoaAwErr_Base + 105)
#define		kMoaAwErr_OperatorError			MAKE_MOAERR(kMoaAwErr_Base + 106)
#define		kMoaAwErr_BadTestFunction		MAKE_MOAERR(kMoaAwErr_Base + 107)
#define		kMoaAwErr_MissingRParen			MAKE_MOAERR(kMoaAwErr_Base + 108)
#define		kMoaAwErr_MissingLParen			MAKE_MOAERR(kMoaAwErr_Base + 109)
#define		kMoaAwErr_StackOverflow			MAKE_MOAERR(kMoaAwErr_Base + 110)
#define		kMoaAwErr_CantAssign			MAKE_MOAERR(kMoaAwErr_Base + 111)
#define		kMoaAwErr_NeedAssign			MAKE_MOAERR(kMoaAwErr_Base + 112)
#define		kMoaAwErr_OperandMissing		MAKE_MOAERR(kMoaAwErr_Base + 113)
#define		kMoaAwErr_TooManyFcnArgs		MAKE_MOAERR(kMoaAwErr_Base + 114)
#define		kMoaAwErr_VarRequired			MAKE_MOAERR(kMoaAwErr_Base + 115)
#define		kMoaAwErr_NeedFcnOrAssign		MAKE_MOAERR(kMoaAwErr_Base + 116)
#define		kMoaAwErr_InternalErr			MAKE_MOAERR(kMoaAwErr_Base + 117)
#define		kMoaAwErr_ExprExpected			MAKE_MOAERR(kMoaAwErr_Base + 118)
#define		kMoaAwErr_UcdCallbackError		MAKE_MOAERR(kMoaAwErr_Base + 119)
#define		kMoaAwErr_UndefinedFunction		MAKE_MOAERR(kMoaAwErr_Base + 120)
#define		kMoaAwErr_UndefinedVariable		MAKE_MOAERR(kMoaAwErr_Base + 121)
#define		kMoaAwErr_UndefinedIcon			MAKE_MOAERR(kMoaAwErr_Base + 122)
#define		kMoaAwErr_CantAtSysVar			MAKE_MOAERR(kMoaAwErr_Base + 123)
#define		kMoaAwErr_CantAtUserVar			MAKE_MOAERR(kMoaAwErr_Base + 124)
#define		kMoaAwErr_TitleNotUnique		MAKE_MOAERR(kMoaAwErr_Base + 125)
#define		kMoaAwErr_NameTooLong			MAKE_MOAERR(kMoaAwErr_Base + 126)
#define		kMoaAwErr_ReservedTitle			MAKE_MOAERR(kMoaAwErr_Base + 127)
#define		kMoaAwErr_TooFewFcnArgs			MAKE_MOAERR(kMoaAwErr_Base + 128)
#define		kMoaAwErr_NotEmbedable			MAKE_MOAERR(kMoaAwErr_Base + 129)
#define		kMoaAwErr_ReservedWord			MAKE_MOAERR(kMoaAwErr_Base + 130)
#define		kMoaAwErr_CantUseAtInLib		MAKE_MOAERR(kMoaAwErr_Base + 131)
#define		kMoaAwErr_MissingStatement		MAKE_MOAERR(kMoaAwErr_Base + 132)
#define		kMoaAwErr_MissingIf				MAKE_MOAERR(kMoaAwErr_Base + 133)
#define		kMoaAwErr_MissingThen			MAKE_MOAERR(kMoaAwErr_Base + 134)
#define		kMoaAwErr_MissingEnd			MAKE_MOAERR(kMoaAwErr_Base + 135)
#define		kMoaAwErr_MissingEol			MAKE_MOAERR(kMoaAwErr_Base + 136)
#define		kMoaAwErr_MissingWhileOrWith	MAKE_MOAERR(kMoaAwErr_Base + 137)
#define		kMoaAwErr_MissingRepeat			MAKE_MOAERR(kMoaAwErr_Base + 138)
#define		kMoaAwErr_BadRepeatWith			MAKE_MOAERR(kMoaAwErr_Base + 139)
#define		kMoaAwErr_NotInRepeat			MAKE_MOAERR(kMoaAwErr_Base + 140)
#define		kMoaAwErr_MissingArgList		MAKE_MOAERR(kMoaAwErr_Base + 141)
#define		kMoaAwErr_BadSymbol				MAKE_MOAERR(kMoaAwErr_Base + 142)
#define		kMoaAwErr_BadList				MAKE_MOAERR(kMoaAwErr_Base + 143)
#define		kMoaAwErr_MissingRBracket		MAKE_MOAERR(kMoaAwErr_Base + 144)
#define		kMoaAwErr_BadSubscript			MAKE_MOAERR(kMoaAwErr_Base + 145)

/* Other Authorware errors */

#define		kMoaAwErr_MissingRecord			MAKE_MOAERR(kMoaAwErr_Base + 200)
#define		kMoaAwErr_RecordManagerError	MAKE_MOAERR(kMoaAwErr_Base + 201)
#define		kMoaAwErr_BufferTooSmall		MAKE_MOAERR(kMoaAwErr_Base + 202)
#define		kMoaAwErr_PropsTooBig			MAKE_MOAERR(kMoaAwErr_Base + 203)


/* ----------------------------------------------------------------------------
/
/  Authorware-specific notification message codes.
/
/ -------------------------------------------------------------------------- */

#define		kMoaAwMsg_Base					0x10000
#define		kMoaAwMsg_ExpressionChanged		kMoaAwMsg_Base + 1


/* ----------------------------------------------------------------------------
/
/	Other constants
/
/ -------------------------------------------------------------------------- */


#endif /* _H_awtypes */
