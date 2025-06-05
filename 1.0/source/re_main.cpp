/*
-------------------------------------------------------------------------
Regular Expression Xtra Licensing Statement
Version 1.0
-------------------------------------------------------------------------

This is a Scripting Xtra for Macromedia Director which lets you use regular
expressions as implemented by PCRE http://pcre.org/, plus a whole lot more.

Written by:

      Chris Thorman <chris@thorman.com>
         Ravi Singh <ravi@ravware.com>

Copyright (c) 2001 If.Net, Inc.

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


#ifndef _H_cscript
	#include "re_main.h"
#endif

//#include "resource.h"

#ifdef _WINDOWS

	#ifdef _DEBUG
	
		#include <crtdbg.h>	

#ifdef malloc // KLUDGE TO GET AROUND PROB FOR PCRE AND STDCALL
	#undef malloc
	#undef free
#endif

	#endif
#endif

#undef malloc
#undef free

//----------------------------------------------------------------------------
// Syntax:
// BEGIN_DEFINE_CLASS_INTERFACE(<class-name>, <interface-name>) 
//----------------------------------------------------------------------------
BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaMmXScript)
END_DEFINE_CLASS_INTERFACE

#ifdef USING_INIT_FROM_DICT
BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaInitFromDict)
END_DEFINE_CLASS_INTERFACE
#endif

#ifdef USING_NOTIFICATION_CLIENT
BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaNotificationClient)
END_DEFINE_CLASS_INTERFACE
#endif

CREGEXPRESSIONScript * pREGEXXtra = NULL;

extern "C" {
void * __stdcall stdcall_malloc( size_t size )
{
	return(malloc(size));
}
void __stdcall stdcall_free( void *memblock )
{
	free(memblock);
}
};

//#define stdcall_malloc(X) malloc(X)
//#define stdcall_free(X) free(X)

void * MyMalloc(size_t iDataSize)
{
	if (pREGEXXtra)
	{
//#ifndef _DEBUG
		return(pREGEXXtra->pCalloc->NRAlloc(iDataSize));
//#else
//		return(calloc(iDataSize,1));
//#endif
	}
	else
	{
		return(NULL);
	}
}


void MyFree(void * pData)
{
//#ifndef _DEBUG
		if ((pREGEXXtra) && (pData)) pREGEXXtra->pCalloc->NRFree(pData);
//#else
//		free(pData);
//#endif
}

// Nasty hack to modify pcre's escapes table so that 
// \n produces '\x0D' on all platforms.
extern "C" {extern short int escapes[];}

/*****************************************************************************
 * Class Syntax:
 * STDMETHODIMP MoaCreate_<class-name>(<class-name> FAR * This)
 * STDMETHODIMP MoaDestroy_<class-name>(<class-name> FAR * This)
 *
 * Interface Syntax:
 * <class_name>_<if_name>::<class_name>_<if_name>(MoaError FAR * pErr)
 * <class_name>_<if_name>::~<class_name>_<if_name>()
 ****************************************************************************/ 


//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
STDMETHODIMP MoaCreate_CREGEXPRESSIONScript(CREGEXPRESSIONScript FAR * This)
{
	X_ENTER
	
	MoaError err = kMoaErr_NoErr;
	
	// Set up all our interfaces
	This->pDrUtils  = NULL;
	This->pDrPlayer = NULL;
	This->pDrMovie  = NULL;
	This->pCallback->QueryInterface(&IID_IMoaStream2, (PPMoaVoid)&This->pStream);	
	This->pCallback->QueryInterface(&IID_IMoaFile2, (PPMoaVoid)&This->pFile);	
	This->pCallback->QueryInterface(&IID_IMoaMmUtils, (PPMoaVoid)&This->pUtils);	
	This->pCallback->QueryInterface(&IID_IMoaDrUtils, (PPMoaVoid)&This->pDrUtils);	
	This->pCallback->QueryInterface(&IID_IMoaMmValue, (PPMoaVoid)&This->pMmValue);
	This->pCallback->QueryInterface(&IID_IMoaMmWndWin, (PPMoaVoid)&This->pMmWndWin);
	
	This->pCallback->QueryInterface(&IID_IMoaDrPlayer, (PPMoaVoid)&This->pDrPlayer);
	This->pCallback->QueryInterface(&IID_IMoaMmList, (PPMoaVoid)&This->pMmList);

	This->PrintedDebugMessage = 0;
	
	// Initialize Internal Engine
	memset(&This->StateInfo,0,sizeof(&This->StateInfo));
	This->ClearInternalState(true);

	pREGEXXtra  = This;
	pcre_malloc = MyMalloc;
	pcre_free   = MyFree;

	// Nasty hack to modify pcre's escapes table so that 
	// \n produces '\x0D' on all platforms.
	escapes['n' - '0'] = '\x0D';

	X_STD_RETURN(err);	
	X_EXIT
}

//-----------------------------------------------------------------------------
// DeConstructor
//-----------------------------------------------------------------------------
STDMETHODIMP_(void) MoaDestroy_CREGEXPRESSIONScript(CREGEXPRESSIONScript FAR * This)
{
	This->ClearInternalState(true);
	
	if (This->pMmValue) This->pMmValue->Release();
	if (This->pMmWndWin) This->pMmWndWin->Release();
	if (This->pDrPlayer) This->pDrPlayer->Release();
	if (This->pMmList) This->pMmList->Release();
	if (This->pUtils)  This->pUtils->Release();
	if (This->pDrUtils)  This->pDrUtils->Release();		
	if (This->pFile)  This->pFile->Release();		
	if (This->pStream)  This->pStream->Release();		

#ifdef _WINDOWS
	#ifdef _DEBUG
		_CrtDumpMemoryLeaks( );
	#endif
#endif

	X_RETURN_VOID;
}


//-----------------------------------------------------------------------------
// CREGEXPRESSIONScript_IMoaMmXScript Create/Destroy 
//-----------------------------------------------------------------------------
CREGEXPRESSIONScript_IMoaMmXScript::CREGEXPRESSIONScript_IMoaMmXScript(MoaError FAR * pErr)
	{ *pErr = (kMoaErr_NoErr); }
CREGEXPRESSIONScript_IMoaMmXScript::~CREGEXPRESSIONScript_IMoaMmXScript() {}

#ifdef USING_INIT_FROM_DICT
/* -------------------------------- CREGEXPRESSIONScript_IMoaInitFromDict Create/Destroy */
CREGEXPRESSIONScript_IMoaInitFromDict::CREGEXPRESSIONScript_IMoaInitFromDict(MoaError FAR * pErr)
	{ *pErr = (kMoaErr_NoErr); }
CREGEXPRESSIONScript_IMoaInitFromDict::~CREGEXPRESSIONScript_IMoaInitFromDict() {}
#endif

#ifdef USING_NOTIFICATION_CLIENT
/* -------------------------- CREGEXPRESSIONScript_IMoaNotificationClient Create/Destroy */
CREGEXPRESSIONScript_IMoaNotificationClient::CREGEXPRESSIONScript_IMoaNotificationClient(MoaError FAR * pErr)
	{ *pErr = (kMoaErr_NoErr); }
CREGEXPRESSIONScript_IMoaNotificationClient::~CREGEXPRESSIONScript_IMoaNotificationClient() {}
#endif



		
// PRegEx (RE_) error-handling & memory checking macros.

#define RE_TryMoaOrMem(a) 	if (       (a) != kMoaErr_NoErr) {       MemError_LEAVE_FUNCTION;}
#define RE_TryMoaOrErr(a,b) if (       (a) != kMoaErr_NoErr) {Err = b;   goto LEAVE_FUNCTION;}
#define RE_TryMem(a) 	    if (       (a)  == NULL)          {      MemError_LEAVE_FUNCTION;}
#define RE_TryErr(a) 	    if ((Err = (a)) != REGERR_SUCCESS){          goto LEAVE_FUNCTION;}
#define RE_TryType(a,b,c)   {MoaMmValueType 	myType  = 0; pMmValue->ValueType((a), &myType); \
							 if (myType != (b))              {Err = (c); goto LEAVE_FUNCTION;}}
#define RE_TryAssert(a, b)  if (!(a))                        {Err = b;   goto LEAVE_FUNCTION;}
#define RE_MaybeFreePtr(a)  if (a)  						 {pCalloc->NRFree(a); (a) = NULL;}
#define RE_MaybeValRelease(a, b) if(b)                    {pMmValue->ValueRelease(a);  b = 0;}
#define RE_MaybeValRelPntr(a, b) if(b)           {pMmValue->ValueReleaseStringPtr(a);  b = 0;}
#define RE_MaybeMyFree(a)   if (a)  						          {MyFree(a); (a) = NULL;}

#define RETURNSTR(Msg) {pObj->pMmValue->StringToValue ((Msg), &callPtr->resultValue);}
#define RETURNINT(Msg) {pObj->pMmValue->IntegerToValue((Msg), &callPtr->resultValue);}
		

// PushContext

// Called internally any time a pregex-state-changing PRegEx function
// is called recursively (i.e. while another callback handler is active).

// Makes a copy of the current StateInfo record in an allocated
// handle; then zeroes out the main StateInfo record.

// Then stores a pointer to the previous context inside this one.
// This effectively gives us a linked list of pushed contexts, 
// of arbitrary length.

long CREGEXPRESSIONScript::PushContext(void)
{
	long Err = REGERR_SUCCESS;
	
	PRegExStateInfo * myPushedStateInfo;
	
	long			origAbortFlag = 0;
	long			origStopFlag  = 0 ;
	long			origSkipFlag  = 0 ;
	long			origLastFlag  = 0 ;
	
	long			ErrorsToMessageWindow; 
	
	// Remember these for below...
	origAbortFlag = StateInfo.CallbackAbort;
	origStopFlag  = StateInfo.CallbackStop ;
	origSkipFlag  = StateInfo.CallbackSkip ;
	origLastFlag  = StateInfo.CallbackLast ;
	
	// Preserve global prefs that should be context-independent.
	ErrorsToMessageWindow	= StateInfo.ErrorsToMessageWindow; 

	// Allocate some memory to hold the pushed state.	
	RE_TryMem(myPushedStateInfo = (PRegExStateInfo *)pCalloc->NRAlloc(sizeof(StateInfo)));

//commit:
	
	// Copy current StateInfo into pushed copy.
	memcpy(myPushedStateInfo, &StateInfo, sizeof(StateInfo));
	
	// Empty out current StateInfo
	memset(&StateInfo, 0, sizeof(StateInfo));
	
	// Transfer current settings of these stopper flags that might have been set
	// to signal the end of an active Exec... to the new, otherwise clean, context.
	StateInfo.CallbackAbort = origAbortFlag;
	StateInfo.CallbackStop  = origStopFlag;
	StateInfo.CallbackSkip  = origSkipFlag;
	StateInfo.CallbackLast  = origLastFlag;

	// Restore global prefs that should be context-independent.
	StateInfo.ErrorsToMessageWindow = ErrorsToMessageWindow;

	// Set the pointer in the current StateInfo to point to the pushed one.
	StateInfo.PushedStateInfo = (long *)myPushedStateInfo;
	
LEAVE_FUNCTION:
	
	if (Err != REGERR_SUCCESS)
	{
		RE_MaybeFreePtr(myPushedStateInfo);
	}
	return(Err);
}

// PopContext

// Called AFTER a callback handler returns to its parent PRegEx_*Exec function,
// IF there was a push in the meanwhile.  We know if there was a push because
// the InCallbackFunction flag will have been set to zero by the push.

// Before destroying the current context, first calls ClearInternalState, which
// releases any data structures attached to it.

// Then the formerly-pushed context takes the place of the current one.
// This routine does not allocate memory, so is highly unlikely to fail.

long CREGEXPRESSIONScript::PopContext(void)
{
	long Err = REGERR_SUCCESS;
	
	PRegExStateInfo * myPushedStateInfo;
	
	long			ErrorsToMessageWindow; 

	// Preserve global prefs that should be context-independent.
	ErrorsToMessageWindow	= StateInfo.ErrorsToMessageWindow; 

	// Get the pointer in the current StateInfo that points to the pushed one.
	myPushedStateInfo = (PRegExStateInfo *)StateInfo.PushedStateInfo;
	if (!myPushedStateInfo)
	{
		// Error! PopContext should never be called unnecessarily.
		// Could do a debug-time "assert" here.
		goto LEAVE_FUNCTION;
	}

	// Empty out and deallocate any structures attached to the current, 
	// about-to-be-destroyed, context, except its stack pointer,
	// which we already got above, and will deallocate below.
	ClearInternalState(false);

	// Copy the pushed context over top of the current state info.
	memcpy(&StateInfo, myPushedStateInfo, sizeof(StateInfo));
	
	// Restore global prefs that should be context-independent.
	StateInfo.ErrorsToMessageWindow = ErrorsToMessageWindow;

LEAVE_FUNCTION:
	
	// Free the memory used by the formerly-pushed context.
	RE_MaybeFreePtr(myPushedStateInfo);

	return(Err);
}

long CREGEXPRESSIONScript::CheckContext(void)
{
	long Err = REGERR_SUCCESS;
	
	// If we were in any function when a new state-changing operation 
	// may be initiated (e.g. new string, new pattern), we PUSH the current context
	// and turn off the InCallBackFunction flag, which then enables
	// other PRegEx functions to do whatever they want; we know that the correct
	// context will be restored by the time the recursive operations are complete.

	// If PRegEx_*Exec notices after returning from a callback that
	// this flag was turned OFF, then it will POP the context, thereby restoring
	// the context that was in effect before the recursive edit.
	
	if (StateInfo.InCallBackFunction)
	{
		RE_TryErr(PushContext());
		StateInfo.InCallBackFunction = 0;
	}
	
LEAVE_FUNCTION:
	return(Err);
}

//------------------------------------------------------------------------------------------
// StringWithNULsToMMValue
//
// Puts a string buffer of specified length into a MOA Value.  Allows NUL characters.
//
// Caller owns and must release pVal after _successful_ completion.
//
//------------------------------------------------------------------------------------------
long CREGEXPRESSIONScript::StringWithNULsToMMValue(char * pStr,long StrLength,MoaMmValue &pVal)
{
	long	Err = REGERR_SUCCESS;

	char * 	pTempMem = NULL;
	char * 	pValStr  = NULL;
	long	MustReleasePValStr = 0;

	long	MustReleasePVal = 0;
	
	if ((pStr == NULL) || (StrLength < 0))
	{
		Err = REGERR_UnexpectedInternalError;
		goto LEAVE_FUNCTION;
	}

	// Create a temporary buffer to initialize a value of the right size.
	RE_TryMem(pTempMem = (char *)pCalloc->NRAlloc(StrLength+1));

	// Set the Buffer to some non-zero character except for the trailing NULL.
	memset(pTempMem,'A',StrLength);
	pTempMem[StrLength] = 0;

	// Convert the String To a MoaMmValue
	RE_TryMoaOrMem(pMmValue->StringToValue(pTempMem,&pVal));
	MustReleasePVal = 1;
	
	// Now get a Ptr that we can copy the desired string data into (which may contain nulls).
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&pVal, (const char **)&pValStr));
	MustReleasePValStr = 1;
		
	memcpy(pValStr,pStr,StrLength);

LEAVE_FUNCTION:
	
	if (Err == REGERR_SUCCESS)
	{
		// Caller owns pVal now; we don't release it.
		MustReleasePVal = 0;
	}
	else
	{
		// Error occurred; we release pVal during cleanup below.
	}

	RE_MaybeValRelPntr(&pVal, MustReleasePValStr);
	RE_MaybeValRelease(&pVal, MustReleasePVal);

	RE_MaybeFreePtr(pTempMem);
	
	return(Err);
}

//------------------------------------------------------------------------------------------
// ClearInternalState
// 
// Resets most (or all) of PRegEx's internal state -- especially: search & match strings.
//------------------------------------------------------------------------------------------
void CREGEXPRESSIONScript::ClearInternalState(unsigned int bCompleteReset)
{
	if	(StateInfo.pCurrentPattern)
	{
		pcre_free(StateInfo.pCurrentPattern);
		StateInfo.pCurrentPattern = 0;
	}

	RE_MaybeMyFree(StateInfo.pCurrentString);
	RE_MaybeMyFree(StateInfo.pCurrentMatch);

	RE_MaybeValRelease(&StateInfo.SearchStringList, StateInfo.MustReleaseSearchStringList);

	if (!bCompleteReset)
	{
		// If not doing a complete reset, preserve the stack and also the status
		// of the "sticky" memory error.
		PRegExStateInfo * myPushedStateInfo	= (PRegExStateInfo *)StateInfo.PushedStateInfo ;
		long TempMemError					= StateInfo.MemErrorSticky ;
		long TempErrorsToMessageWindow		= StateInfo.ErrorsToMessageWindow;
		MoaMmValue	TempVoidValue			= StateInfo.ARandomVoidValue;
		
		memset(&StateInfo,0,sizeof(StateInfo));

		StateInfo.ErrorsToMessageWindow		= TempErrorsToMessageWindow;
		StateInfo.MemErrorSticky			= TempMemError;
		StateInfo.PushedStateInfo			= (long *)myPushedStateInfo;
		StateInfo.ARandomVoidValue			= TempVoidValue;
	}
	else
	{
		// If really doing a complete reset, we also have to 
		// recursively deallocate and blast all frames in
		// the stack.  Of course, this could create unexpected results
		// if a dumb Lingo caller calls PRegEx_Clear(true)  during the middle
		// of a recursive search or search/replace.  All contexts will be lost
		// and bad, though probably fatal things will not occur.  The docs will
		// warn against doing that, of course.  Basically, PRegEx_Clear(true) should
		// only be called from startMovie and/or stopMovie in the main movie; and in any
		// case, should never be called when there might be a recursive edit.
		// PRegEx_Clear(false) can be called at any time -- it just blows away any saved
		// strings or back ref strings or compiled patterns or state info IN THE CURRENT CONTEXT, 
		// leaving other, stacked, contexts untouched.
		PRegExStateInfo * myPushedStateInfo = 	(PRegExStateInfo *)StateInfo.PushedStateInfo ;
		
		memset(&StateInfo,0,sizeof(StateInfo));
		
		if (myPushedStateInfo)
		{
			PopContext();
			if (StateInfo.PushedStateInfo) ClearInternalState(bCompleteReset);
		
		}
	}
	
	StateInfo.CallbackAbort = 0;
	StateInfo.CallbackStop  = 0;
	StateInfo.CallbackSkip  = 0;
	StateInfo.CallbackLast  = 0;
	
}

//------------------------------------------------------------------------------------------
// ClearBackReferenceInformation
//
// Called when a match fails (except the match that 
// terminates an otherwise-successful global search and/or replace).
//------------------------------------------------------------------------------------------
void CREGEXPRESSIONScript::ClearBackReferenceInformation(void)
{
	StateInfo.MatchFound = 0;
	StateInfo.Replaced = 0;
	StateInfo.CurrentTotalBackRefs = 0;
	
	StateInfo.EntireMatchLen = 0;   // The Length of the Last Match
	StateInfo.SearchOffset   = 0;     // The starting Position of the Entite Match in pCurrentString

	RE_MaybeMyFree(StateInfo.pCurrentMatch);

	memset(StateInfo.SearchOvector,0,sizeof(StateInfo.SearchOvector));
	memset(StateInfo.CurrentSearchOvector,0,sizeof(StateInfo.CurrentSearchOvector));
}

//------------------------------------------------------------------------------------------
// PRegEx_SetMatchPattern
//
//
//-------------------------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_SetMatchPattern         (PMoaMmCallInfo callPtr                                                       )
{return(                   PRegEx_SetMatchPattern_Internal(               callPtr,      1        ,      2         ,      1              ));}
long CREGEXPRESSIONScript::PRegEx_SetMatchPattern_Internal(PMoaMmCallInfo callPtr, long patArgNum, long optsArgNum, long setReturnVal)
{
	long			Err = REGERR_SUCCESS;
	int				i;
	long			PRegExpressionStrLen = 0;
	bool			StudyPattern = false;
	char *			pPRegExpressionStr = NULL;
	bool			PatternBufferAlloced = false ; // We had to dynamically allocate
	
	MoaMmValue		PRegExpressionVal;
	
	MoaMmValue 		OptionsVal;
	long 			OptionsStrLen = 0;
	char			OptionsBuffer[7+1];

	// Push if necessary.
	RE_TryErr(CheckContext());
	
	StateInfo.CompiledOK = 0;

	// Get the RE. We know this is a string because we
	// have forced it to be so in the Xtra function prototype registry
	GetArgByIndex(patArgNum,  &PRegExpressionVal);

	// Clear out mode options.
	memset(OptionsBuffer,0,sizeof(OptionsBuffer));
	StateInfo.GlobalReplaceOption = 0;
	StateInfo.ExecOption = 0;

	// Reset Internal State
	{
		char *		TempPtrCurStr    = NULL;
		long		TempMustRelease	 = 0;
		long  		TempCurStringLen = 0;
		MoaMmValue	TempSearchStringList;

		// We have to be able to call SetSearchString and SetMatchPattern
		// interchangeably so we create a temp copy of the string vals
		// and clear out any leftover data. 
		TempPtrCurStr    		= StateInfo.pCurrentString;
		TempCurStringLen 		= StateInfo.CurrentStringLen;
		TempSearchStringList	= StateInfo.SearchStringList;
		TempMustRelease			= StateInfo.MustReleaseSearchStringList;

		StateInfo.pCurrentString   = 0;
		StateInfo.CurrentStringLen = 0;
		memset(&StateInfo.SearchStringList,0,sizeof(StateInfo.SearchStringList));

		ClearInternalState(false);

		// Copy Back the Data
		StateInfo.pCurrentString   				= TempPtrCurStr;
		StateInfo.CurrentStringLen 				= TempCurStringLen;
		StateInfo.SearchStringList				= TempSearchStringList;
		StateInfo.MustReleaseSearchStringList	= TempMustRelease;
	}

	// Get size of RE.
	// OK to use ValueStringLength because we already require that
	// the incoming string not contain any NUL characters (since PCRE
	// also requires that).
	RE_TryMoaOrMem(pMmValue->ValueStringLength(&PRegExpressionVal,&PRegExpressionStrLen));

	// Be sure the RE's not empty.
	RE_TryAssert(PRegExpressionStrLen != 0, REGERR_REMustNotBeEmpty)

	// Now that we have data , we will see if it is bigger than our static buffer
	// We want to avoid doing many allocations so we allocate one simple buffer
	// that should take care of most of the average needs, but just in case we
	// can allocate a dynamic buffer of any size
	if (PRegExpressionStrLen < (sizeof(StateInfo.SmallPatternBuffer)-1))
	{
		// Avoid doing allocations if the search pattern is small enough
		pPRegExpressionStr = StateInfo.SmallPatternBuffer;
		pMmValue->ValueToString(&PRegExpressionVal,StateInfo.SmallPatternBuffer,sizeof(StateInfo.SmallPatternBuffer)-1);
	}
	else
	{
		// Large Search Pattern, so We want to Dynamically Allocate
		// the memory
		RE_TryMem(pPRegExpressionStr = (char *)MyMalloc(PRegExpressionStrLen + 1 ));

		PatternBufferAlloced = true;
	}

	// Copy the Data
	// OK to use ValueToString because we know it has no NULs.
	RE_TryMoaOrMem(pMmValue->ValueToString(&PRegExpressionVal, pPRegExpressionStr, PRegExpressionStrLen + 1));


	// Parse the OPTIONAL "Options" argument.  
	// Optional means it may be absent or it may not be of type "string".
	// If that happens, we just leave all options defaulted to "off".
	 
	do
	{
		// OK if options not specified (they are almost always optional).
		if (callPtr->nargs < optsArgNum)              				break;	
		
		// Require options arg to be of type "string".
		GetArgByIndex(optsArgNum, &OptionsVal);
		RE_TryType(&OptionsVal, kMoaMmValueType_String, REGERR_InvalidOptionsSpecified);

		// Get length.  Zero-length is OK
		// But length must be less than or = 7.
		// We examine no more than the first 7 characters, since that's the max
		// number of options that exist.
		pMmValue->ValueStringLength(&OptionsVal,&OptionsStrLen);
		if (!OptionsStrLen)                           				break;
		RE_TryAssert(OptionsStrLen <= 7, REGERR_InvalidOptionsSpecified); 
		
		RE_TryMoaOrMem(pMmValue->ValueToString(&OptionsVal,OptionsBuffer,OptionsStrLen + 1));

		for (i = 0; i < OptionsStrLen; i++)
		{
			switch(tolower((int)OptionsBuffer[i]))
			{
				case 'i': { StateInfo.PCRECompileFlags |= PCRE_CASELESS;     } break;
				case 's': { StateInfo.PCRECompileFlags |= PCRE_DOTALL;       } break;
				case 'm': { StateInfo.PCRECompileFlags |= PCRE_MULTILINE;    } break;
				case 'x': { StateInfo.PCRECompileFlags |= PCRE_EXTENDED;     } break;
				case 'g': { StateInfo.GlobalReplaceOption = 1;               } break;
				case 'e': { StateInfo.ExecOption = 1;                        } break;
				case 't': { StudyPattern = true;                             } break;
				default : { RE_TryAssert(0, REGERR_InvalidOptionsSpecified); } break;
			}
		}
	} while(0);
	
	// Compile the Pattern
	StateInfo.pCurrentPattern   = pcre_compile(pPRegExpressionStr,
												StateInfo.PCRECompileFlags, 
												&StateInfo.pError,
												&StateInfo.erroroffset,
												StateInfo.pTables);

	// Bail now if it did not compile.
	RE_TryAssert(StateInfo.pCurrentPattern != 0, REGERR_REDidNotCompile);

	if (StudyPattern)
	{
		StateInfo.pExtraPatternInfo = pcre_study(StateInfo.pCurrentPattern,
												 0, 
												 &StateInfo.pError);
	}

LEAVE_FUNCTION:

	if (PatternBufferAlloced)
	{
		RE_MaybeMyFree(pPRegExpressionStr);
		PatternBufferAlloced = 0;
	}

	if (Err != REGERR_SUCCESS)
	{
		// Failed to compile, most likely.  In any case, wipe all state.
		ClearInternalState(false);
		StateInfo.CompiledOK = 0; 

		if (setReturnVal) 
		{
			pMmValue->IntegerToValue(Err,&callPtr->resultValue);
		}
	}
	else
	{
		StateInfo.CompiledOK = 1; 
		if (setReturnVal) {pMmValue->IntegerToValue(1,&callPtr->resultValue);}
	}
	return(Err);
}

//----------------------------------------------------------------------------
//
//
//
// PRegEx_SetSearchString     (SrchStrL)  ==> True unless mem err or bad params
//
// Sets a new string or SET OF STRINGS to be operated on.
// Resets all counters and buffers and flags.
// 
// - If stringP(), then copy of string used as first search buffer
// - If listP(), then SrchStrL[1] will be used as first search buffer
// - Set CanReplace = listP() (flag to enable replacing operations later)
// - Reset MemError to 0 (but not MemErrorSticky)
// - Reset FoundCount to 0
// - Reset Pos to 0
// - Reset ovector (match/backref structure) to empty
//
//
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_SetSearchString         (PMoaMmCallInfo callPtr                                  )
{return(                   PRegEx_SetSearchString_Internal(               callPtr,      1       ,      1           ));}
long CREGEXPRESSIONScript::PRegEx_SetSearchString_Internal(PMoaMmCallInfo callPtr, long whichArg, long setReturnVal)
{
	long   Err = REGERR_SUCCESS;
	MoaMmValueType	ValueType  = 0;
	MoaMmValue		StringVal;
	long			MustReleaseStringVal = 0;
	char *			StringValPtr = NULL;
	long			MustReleaseStringValPtr = 0;

	MoaMmValue		StringBufferList;
	long			StringBufferListLength = 0;

	// Push if necessary.
	RE_TryErr(CheckContext());
	
	// Release any prior search string data.
	RE_MaybeValRelease(&StateInfo.SearchStringList, StateInfo.MustReleaseSearchStringList);
	RE_MaybeMyFree(StateInfo.pCurrentString);
	RE_MaybeMyFree(StateInfo.pCurrentMatch);

	// Get SrchStrL list arg from caller.
	// Check we have a list and that it has at least one element.
	GetArgByIndex(whichArg, &StringBufferList);
	RE_TryType(&StringBufferList, kMoaMmValueType_List, REGERR_SearchStrLMustBeList);
	StringBufferListLength = pMmList->CountElements(&StringBufferList);
	RE_TryAssert(StringBufferListLength >= 1, REGERR_SearchStrLMustContainString);

	// Check we have a string value.
	pMmList->GetValueByIndex(&StringBufferList,1,&StringVal);
	MustReleaseStringVal = 1;
	RE_TryType(&StringVal, kMoaMmValueType_String, REGERR_SearchStrLMustContainString);
	
	// Figure out true length of the string by asking Lingo (since MOA is broken)
	StateInfo.CurrentStringLen = PRegEx_GetStringLengthThroughLingo(&StringVal);
	
	// If user specified an optional length, use it, 
	// assuming it's >= 0 and shorter than the actual length.
	if (StringBufferListLength > 1)
	{
		MoaMmValue StrLenVal;
		long		UserSuppliedLength = 0;
		
		pMmList->GetValueByIndex(&StringBufferList,2,&StrLenVal);
		RE_TryType(&StrLenVal, kMoaMmValueType_Integer, REGERR_SearchStrLLengthArgMustBeInteger);
		
		pMmValue->ValueToInteger(&StrLenVal, &UserSuppliedLength);
		
		if ((UserSuppliedLength >= 0                         ) &&
			(UserSuppliedLength <= StateInfo.CurrentStringLen)   )
		{
			StateInfo.CurrentStringLen = UserSuppliedLength;
		}
	}

	// pCurrentString holds the current SEARCH buffer for pcre functions.
	RE_TryMem(StateInfo.pCurrentString = (char *)MyMalloc(StateInfo.CurrentStringLen + 1));

	// Copy the data from the incoming string (pointer) into our
	// internal string.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&StringVal, (ConstPMoaChar*)&StringValPtr));
	MustReleaseStringValPtr = 1;
	memcpy(StateInfo.pCurrentString, StringValPtr, StateInfo.CurrentStringLen);

	// Set state variables indicating we have a string.
	StateInfo.CanReplace = 1;
	StateInfo.Pos        = 0;
	StateInfo.FoundCount = 0;
	StateInfo.FoundStringHadZeroWidth = 0;

	// Keep a copy of caller's list.  Add a reference so we now own it
	// even if caller abandons it.
	StateInfo.SearchStringList = StringBufferList;
	pMmValue->ValueAddRef(&StateInfo.SearchStringList);
	StateInfo.MustReleaseSearchStringList = 1;


LEAVE_FUNCTION:

	// Return boolean true if success or (negative) Err code if failure.
	if (Err == REGERR_SUCCESS) {if (setReturnVal) {pMmValue->IntegerToValue(1,  &callPtr->resultValue);}}
	else                       {if (setReturnVal) {pMmValue->IntegerToValue(Err,&callPtr->resultValue);}}
	
	RE_MaybeValRelPntr(&StringVal, MustReleaseStringValPtr);
	RE_MaybeValRelease(&StringVal, MustReleaseStringVal);
	
	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_GetNextMatch
// PRegEx_GetNextMatch_Internal
//
// Assuming we have a search string and replacement pattern all set
// up and compiled, performs one search, beginning at Pos, and then sets
// internal state variables according to the outcome.
//
// Public entry point parses one optional user argument and then 
// calls private internal version.
// 
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_GetNextMatch(PMoaMmCallInfo callPtr)
{
	long  		Err = REGERR_SUCCESS;
	
	long       	TotalArguments = callPtr->nargs;
	
	MoaMmValue	noBlastBRVal;
	long		noBlastBRValType = 0;

	long    	noBlastBR = 0;

	// Check if caller specified optional NoBlastBR flag
	if (TotalArguments >= 1)
	{
		GetArgByIndex(1, &noBlastBRVal);
		pMmValue->ValueType(&noBlastBRVal, &noBlastBRValType);
		if (noBlastBRValType != kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&noBlastBRVal,&noBlastBR);
		}
	}
		
	RE_TryErr(             PRegEx_GetNextMatch_Internal(callPtr,                     noBlastBR,     1            ));
	
LEAVE_FUNCTION:
	return(Err);
}

long CREGEXPRESSIONScript::PRegEx_GetNextMatch_Internal(PMoaMmCallInfo callPtr, long noBlastBR, long setReturnVal)
{
	long   Err = REGERR_SUCCESS;
	int    ExecBRCount = 0; 		// Return value from pcre_exec (see PCRE docs)
	int    MatchFailed = 0;

	// Push if necessary.
	RE_TryErr(CheckContext());

	// Check if we have a current string and pattern.
	RE_TryAssert(StateInfo.pCurrentString  != NULL, REGERR_TriedToMatchWithoutSearchStrL);
	RE_TryAssert(StateInfo.pCurrentPattern != 0   , REGERR_TriedToMatchWithoutSearchPattern);

	// Reset indicators of whether a match has been done.
	StateInfo.MatchFound = 0;
	StateInfo.Replaced = 0;
	
	// If previous successful match in a sequence of matches on the same string
	// had a zero width, then we advance the Pos now in order to avoid an infinite
	// loop.  This is standard practice in the world of regular expressions.
	
	// This can even be useful, for example, to match before every character in a string,
	// say, when splitting the string into a list of characters.
	if (StateInfo.FoundStringHadZeroWidth)
	{	
		StateInfo.Pos++;
		StateInfo.FoundStringHadZeroWidth = 0; // Reset till just down below.
	}

	if (StateInfo.Pos <= StateInfo.CurrentStringLen) // Workaround PCRE bug searching for "()"
	{
		ExecBRCount = pcre_exec(StateInfo.pCurrentPattern,
						        StateInfo.pExtraPatternInfo,
							    StateInfo.pCurrentString,
							    StateInfo.CurrentStringLen,
							    StateInfo.Pos,
							    0,	// pcre_exec options
							    StateInfo.SearchOvector,
							    sizeof(StateInfo.SearchOvector)/sizeof(int));
	}
	else
	{
		ExecBRCount = -1;	// Means: match failed.  We check this code below.
	}

	if (ExecBRCount == 0) 	// Error: match succeeded, but too many back references.  Should never happen.
	{
		// On the off chance it does happen, just set this to our known limit, and proceed.
		ExecBRCount = MAX_OVECTOR_ENTRIES;
	}

	if (ExecBRCount > 0)	// We have a match.
	{
		int i;
		
		StateInfo.FoundCount++; 
		StateInfo.CurrentTotalBackRefs = ExecBRCount - 1; 

		// First 2 vectors in ovector contain the Entire Match
		StateInfo.EntireMatchLen = (StateInfo.SearchOvector[1] - 
		                            StateInfo.SearchOvector[0]);
		StateInfo.SearchOffset   =  StateInfo.SearchOvector[0];
		
		// Important: recall for later if this match had zero width.
		// Zero width successful matches are perfectly OK, BUT, as a special case,
		// we always advance Pos by before beginning the NEXT iteration, otherwise
		// in global mode, we'll hang forever at this current Pos.
		
		if (StateInfo.EntireMatchLen == 0)
		{
			StateInfo.FoundStringHadZeroWidth = 1;
		}
		
		// Free up any previous match info.
		RE_MaybeMyFree(StateInfo.pCurrentMatch);

		// Allocate new buffer and copy Entire Match into it.
		RE_TryMem(StateInfo.pCurrentMatch = (char *)MyMalloc(StateInfo.EntireMatchLen + 1));

		memcpy(StateInfo.pCurrentMatch,&StateInfo.pCurrentString[StateInfo.SearchOffset],StateInfo.EntireMatchLen);

		// Make a copy of the "ovector" (match offsets) that PCRE returned
		// and downwardly-adjust all the offsets (that come in initially as offsets
		// in the full string) so they become offsets into our private copy of just
		// the matched section of the string.
		memcpy(&StateInfo.CurrentSearchOvector,StateInfo.SearchOvector,sizeof(StateInfo.CurrentSearchOvector));
		for (i = 0;i < ExecBRCount ;++i)
		{	
			// Do not adjust -1 meaning "no backref here" -- leave that flag intact.
			if (StateInfo.CurrentSearchOvector[i*2] == -1) continue;	
			
			StateInfo.CurrentSearchOvector[i*2]     -= StateInfo.SearchOffset;
			StateInfo.CurrentSearchOvector[(i*2)+1] -= StateInfo.SearchOffset;
		}

		// Advance Pos so the next search starts in the right place.
		StateInfo.Pos = StateInfo.SearchOffset + StateInfo.EntireMatchLen;

		StateInfo.MatchFound = 1;
		StateInfo.Replaced = 0;
	}
	else if (ExecBRCount == -1)
	{
		// No match
		MatchFailed = 1;

		// Clear back reference information when a search fails (unless asked not to)
		if (!noBlastBR) {ClearBackReferenceInformation();}

	}
	else if (ExecBRCount < -1)
	{
		Err = REGERR_UnexpectedInternalError;
		goto LEAVE_FUNCTION;
	}

LEAVE_FUNCTION:

	// Return 1 or 0 indicating match status; else return an error code.
	if (setReturnVal) 
	{
		if ((Err == REGERR_SUCCESS) && (StateInfo.MatchFound)) {pMmValue->IntegerToValue(1,   &callPtr->resultValue);}
		else if (MatchFailed)	                               {pMmValue->IntegerToValue(0,   &callPtr->resultValue);}
		else                                                   {pMmValue->IntegerToValue(Err, &callPtr->resultValue);}
	}
	
	return(Err);
}

// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
long CREGEXPRESSIONScript::GetBackRefStrlen(int BackRefID)
{
	long Length = 0;

	if ((BackRefID >= 0) &&
		(BackRefID <= StateInfo.CurrentTotalBackRefs) && 
		(StateInfo.pCurrentString))
	{
		Length = StateInfo.CurrentSearchOvector[(BackRefID*2)+1] - StateInfo.CurrentSearchOvector[BackRefID*2];
		return(Length);
	}
	else
	{
		return(0);
	}
}

// ----------------------------------------------------------------------------
// ** ASSUME THAT BUFFER IS BIG ENOUGH FOR STRING
// ----------------------------------------------------------------------------
long CREGEXPRESSIONScript::CopyBackRefToString(int BackRefID,char * pOutputStr)
{
	if ((BackRefID >= 0) &&
		(BackRefID <= StateInfo.CurrentTotalBackRefs) && 
		(StateInfo.pCurrentString))
	{
		int StrLen = GetBackRefStrlen(BackRefID);

		if (StrLen)
		{
			int StrPos = StateInfo.CurrentSearchOvector[BackRefID*2];
			// Retrieve the BackReference from the Original String
			memcpy(pOutputStr,&StateInfo.pCurrentMatch[StrPos],StrLen);
		}
		return(StrLen);
	}
	else
	{
		return(0);
	}
}



//----------------------------------------------------------------------------
// Interpolate_Internal
//
// Do iterpolations on incoming strings -- this allows for easy embedding of
// special characters using escape sequences, optional insertion of back references
// using \1, \2, etc, and also optional processing of arbitrary string-insertions
// using a property-list, simulating how Per uses ${foo} to insert $foo into a string 
// except that foo is looked up in a property list rather than the current lexical environment.
// 
// \\ ==> a single backslash character
// \t ==> a single tab character
// \n ==> a single newline character (same char as lingo RETURN constant)
// \x## ==> a single character with Ascii Hex value ## (two digits)
// \### ==> a single character with Ascii Octal value ### (three digits)
// \# or \## ==> Backreference (backslash followed by 1 or 2 digits)
//               (unless # is 0, in which case it means ascii zero char.)
// \(any other char) ==> the character itself. (e.g. \b = literal "b")
// ${b}  ==> optional string lookup in a property list.
// ${#b} ==> optional symbol lookup in a property list.
//
// if pOutputStr == NULL then this function just calculates the buffer size
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::Interpolate_Internal(MoaByte * pStr, int Length, MoaByte * pOutputStr, 
												long AllowBackRefs, long AllowVars, PMoaMmValue VarLookup, long * HadBackRefs)
{
	long 			StrLen = 0;
	long 			i = 0;
	long			CurOutputStrPos = 0;
	
	unsigned char	TempBuffer[4];
	
	long			HaveVar = 0;
	long			VarNameStartPos = 0;
	long			VarNameLength = 0;
	long 			IsSymbol = 0;
	
	if (HadBackRefs)  {*HadBackRefs = 0;}

	while (i < Length)
	{
		// First check for \-escapes
		if (pStr[i] == '\\')
		{			
			// Escape Sequence
			char NextChar = 0;
			
			// Check we aren't at the end of the String.
			if ((i+1) >= Length)
			{
				// We Just Have a Single BackSlash and the end of a Line
				// Just append on the backslash
				StrLen++;

				if (pOutputStr)
				{
					pOutputStr[CurOutputStrPos++] = '\\';
				}
				
				break; // Leave the Loop
			}
			
			i++; // Jump Past the Slash

			NextChar = pStr[i];
			
			if ((NextChar == 't'))
			{
				StrLen++;

				if (pOutputStr)
				{
					pOutputStr[CurOutputStrPos++] = '\t';
				}
			}
			else if ((NextChar == 'n'))
			{
				StrLen++;

				if (pOutputStr)
				{	
					// Newline = return = numtochar(13) = hex 0D on both platforms 
					pOutputStr[CurOutputStrPos++] = '\x0D';	
				}
	
			}
				// Hex: check that we have 2 more hex digits and convert to ASCII
			else if ((NextChar == 'x') && 
					 (i < Length-2) &&
					 (isxdigit(pStr[i+1])) && 
					 (isxdigit(pStr[i+2])) 
					 )
			{
				StrLen++;
				i++; // Jump Past X

				if (pOutputStr)
				{
					TempBuffer[0] = pStr[i];
					TempBuffer[1] = pStr[i+1];
					TempBuffer[2] = 0;
					
					pOutputStr[CurOutputStrPos++] =  (unsigned char)strtol((char *)TempBuffer,NULL,16);
				}
				
				i++; // Jump Past second hex digit.
			}
			else if (isdigit(NextChar))
			{
				long TotalLength = 1;
				long j = 0;
				// This Can be Either an Octal Value or BackReference
				// \0 , 
				
				// Find how many Digits
				j = i+1; 
				while ( (j < Length) && 
						( isdigit(pStr[j]) ) &&
						(TotalLength <= 3) // Max length of \### sequence is 3 digits.
						)
				{
					j++;
					TotalLength++;
				}
				
				if (TotalLength == 1)
				{
					if (pStr[i] == '0') // was pStr[i+1]
					{
						// Null Character
						StrLen++;

						if (pOutputStr)
						{
							pOutputStr[CurOutputStrPos++] = '\0';
						}
					}
					else 
					{
						// BackReference
						if (AllowBackRefs)
						{
							if (HadBackRefs)  {*HadBackRefs = 1;}

							int BackRefID = (int)NextChar - '0';
							StrLen += GetBackRefStrlen(BackRefID);

							if (pOutputStr)
							{
								CopyBackRefToString(BackRefID,(char *)&pOutputStr[CurOutputStrPos]);
								CurOutputStrPos += GetBackRefStrlen(BackRefID);
							}
						}
					}
				}
				else if (TotalLength == 2)
				{
					// Back Reference
					if (AllowBackRefs)
					{
						if (HadBackRefs)  {*HadBackRefs = 1;}

						TempBuffer[0] = pStr[i];
						TempBuffer[1] = pStr[i+1];
						TempBuffer[2] = 0;
						
						int BackRefID = strtol((char *)TempBuffer,NULL,10);

						
						StrLen += GetBackRefStrlen((int)BackRefID);
						if (pOutputStr)
						{
							CopyBackRefToString(BackRefID,(char *)&pOutputStr[CurOutputStrPos]);
							CurOutputStrPos += GetBackRefStrlen(BackRefID);
						}
					}
				}
				else if (TotalLength == 3)
				{
					// Octal Character

					StrLen++;
	
					if (pOutputStr)
					{
						TempBuffer[0] = pStr[i];
						TempBuffer[1] = pStr[i+1];
						TempBuffer[2] = pStr[i+2];
						TempBuffer[3] = 0;
						
						pOutputStr[CurOutputStrPos++] = (unsigned char)strtol((char *)TempBuffer,NULL,8);
					}
				}
				else if (TotalLength == 0)
				{
					// Bug
				}

				i+= TotalLength-1; // Jump past the remaining chars in the esc. sequence.  

			} // Next Character is a Digit
			else
			{
				// >> \{any other char} ==> the character itself. (e.g. \a = a literal "a")
				StrLen++;

				if (pOutputStr)
				{
					pOutputStr[CurOutputStrPos++] = NextChar;
				}
			}
		} // Is the Character a Slash
		
		// Then check for ${xyz} or ${#xyz} property-insertion syntax.
		else if ((pStr[i  ] == '$') &&	
				 (AllowVars)        &&
				 (i < Length - 2)   &&
				 (VariableScan(pStr, i, Length, &VarNameStartPos, &VarNameLength, &IsSymbol)))
		{
			MoaByte *	VarValueString = NULL;
			long		VarValueStringLength = 0;
			
			// LookupVariableNameInPropList will only fail if there is a memory error.
			// We should probably capture that and propagate the error, but right now Interpolate_Internal
			// is not set up for that.  So we just treat any entry generating an error as "not found"
			// and move on.
			// If the value was not found for any reason, then it will return an empty string, which
			// is what we will use.  This case is not distinguishable from a successful lookup that
			// results in an empty string being found.
			if (LookupVariableNameInPropList(&(pStr[VarNameStartPos]), VarNameLength, IsSymbol, VarLookup,
			                             &VarValueString, &VarValueStringLength) == REGERR_SUCCESS)
			{
				StrLen += VarValueStringLength;
				
				if (pOutputStr)
				{
					// Copy the string into the output buffer.
					memcpy(&(pOutputStr[CurOutputStrPos]), VarValueString, VarValueStringLength);
					CurOutputStrPos += VarValueStringLength;
				}
			
				// We must release the allocated string.
				RE_MaybeFreePtr(VarValueString);
			}
			
			// Jump past all the syntax stuff.
			i += (VarNameLength 		// Length of string inside the {}
				  + 3 					// Length of ${} characters themselves
				  + (IsSymbol ? 1 : 0)  // Length of optional # character if symbol
				  - 1);                 // minus 1 to account for i++ later in loop.
		}
		else
		{
			// Just a Normal Character
			StrLen++;

			if (pOutputStr)
			{
				pOutputStr[CurOutputStrPos++] = pStr[i];
			}
		}

		i++; // Goto Next Character

	} // While
	
//  LEAVE_FUNCTION:

	return(StrLen);
}

MoaByte tempString[256] = "XYZABC";


// LookupVariableNameInPropList
//
// Helper function for Interpolate_Internal.
//
// Given a string buffer (that may contain nulls), look
// up the variable name in a "VarLookup" property list.  The string
// is either interpreted as a string Value or as a symbol based on 
// the setting of IsSymbol.

// If this function succeeds, it returns a new buffer which must
// be freed by the caller.

long CREGEXPRESSIONScript::LookupVariableNameInPropList(MoaByte * myStr, long myStrLength, long AsSymbol, PMoaMmValue VarLookup,
			                             MoaByte ** VarValueString, long * VarValueStringLength)
{
	long       			Err	= REGERR_SUCCESS;
	
	MoaMmValue			MyStringVal;
	long				MustReleaseMyStringVal = 0;
	char *				MyStringValPtr = NULL;
	long				MustReleaseMyStringValPtr = 0;

	MoaMmSymbol			MySymbol = 0;
	MoaMmValue			MySymbolVal;
	long				MustReleaseMySymbolVal = 0;
	
	MoaMmValue			FoundValue;
	long				MustReleaseFoundValue = 0;
	char *				FoundValuePtr = NULL;
	long				MustReleaseFoundValuePtr = 0;

	MoaByte *			FoundBuffer = NULL;

	MoaMmValue			LookupValue;
	
	// Initialize return values.
	*VarValueString = NULL;
	*VarValueStringLength = 0;
	
	// First create a Moa string Value
	RE_TryErr(StringWithNULsToMMValue((char *)myStr, myStrLength, MyStringVal));
	MustReleaseMyStringVal = 1;
	
	LookupValue = MyStringVal;
	
	// If necessary, make it into a symbol, then make the symbol into a value.
	// Note: we cannot just use myStr directly because it is not guaranteed to be
	// null-terminated.  (In fact, it is NOT null-terminated.)
	if (AsSymbol)
	{
		RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&MyStringVal, (const char **)&MyStringValPtr));
		MustReleaseMyStringValPtr = 1;

		RE_TryMoaOrMem(pMmValue->StringToSymbol(MyStringValPtr, &MySymbol));
		RE_TryMoaOrMem(pMmValue->SymbolToValue(MySymbol, &MySymbolVal));
		MustReleaseMySymbolVal = 1;

		// Use this value in place of the other.		
		LookupValue = MySymbolVal;
	}	
	
	// Do the lookup.  If not found, then create an empty string value.
	RE_TryMoaOrErr(pMmList->GetValueByProperty(VarLookup, &LookupValue, &FoundValue), -999);
	MustReleaseFoundValue = 1;

	// Make sure we found a string.  If not, bail.
	RE_TryType(&FoundValue, kMoaMmValueType_String, REGERR_ReplPatMustBeString);
	
	// Get the length of the value we're returning.
	*VarValueStringLength = PRegEx_GetStringLengthThroughLingo(&FoundValue);
	
	// Get a string pointer.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&FoundValue, (const char **)&FoundValuePtr));
	MustReleaseFoundValuePtr = 1;
		
	// Get a buffer to hold the data.
	// Alloc a buffer to expand (or contract) into
	RE_TryMem(FoundBuffer = (MoaByte *)pCalloc->NRAlloc(*VarValueStringLength + 1));
	
	// Copy the data.
	memcpy(FoundBuffer, FoundValuePtr, *VarValueStringLength);
	FoundBuffer[*VarValueStringLength] = 0;		// Not necessary; just being defensive.
	
  LEAVE_FUNCTION:
  
	if (Err == REGERR_SUCCESS)
	{
		// Return the buffer we created to the caller.  The caller now owns it.
		*VarValueString = FoundBuffer;
		FoundBuffer = 0;
	}
	
	RE_MaybeFreePtr(FoundBuffer);

	RE_MaybeValRelPntr(&FoundValue, MustReleaseFoundValuePtr);
	RE_MaybeValRelease(&FoundValue, MustReleaseFoundValue);
	RE_MaybeValRelease(&MySymbolVal, MustReleaseMySymbolVal);
	RE_MaybeValRelPntr(&MySymbolVal, MustReleaseMyStringValPtr);
	RE_MaybeValRelease(&MyStringVal, MustReleaseMyStringVal);

	return(Err);
}			                             

// VariableScan
//
// Helper function for Interpolate_Internal.
//
// Scans from the current point in a string buffer to see if we have
// a valid ${...} or ${#....} syntax.

long CREGEXPRESSIONScript::VariableScan (unsigned char * aString, long startPos, long strLength, 
                   long * VarNameStartPos, long * VarNameLength, long * IsSymbol)
{
	long HaveVar		= 0;
	
	*VarNameStartPos	= 0;
	*VarNameLength		= 0;
	*IsSymbol			= 0;
	
	long				i;
	
	// Verify required starting characters.
	if (aString[startPos++] != '$') goto LEAVE_FUNCTION; 
	if (aString[startPos++] != '{') goto LEAVE_FUNCTION; 
	
	// If optional third character is a #, then this is a symbol.
	if ((startPos < strLength) && aString[startPos  ] == '#') {*IsSymbol = 1; startPos++;} 
	
	// Remember this position as the start of the variable name string.
	*VarNameStartPos = startPos;
	
	// Scan from this point till a } is found or the end of
	// the string is reached.
	for (i = startPos; i < strLength; i++)
	{
		if (aString[i] == '}')
		{
			*VarNameLength = i - *VarNameStartPos;	// Could be zero-length.  ${} is allowed.
			HaveVar = 1;
			break;
		}
	}
	
	// If we got to this point but didn't find the final "}", we zero
	// out any intermediate settings (not strictly necessary, but defensive).
	if (!HaveVar)
	{
		*IsSymbol = 0;
		*VarNameStartPos = 0;
		*VarNameLength = 0;
	}

  LEAVE_FUNCTION:

	return(HaveVar);
}

// ExpandCharRanges_Internal
//
// Process character-range dashes in InputMap and OutputMap for the Translate function.
//
// If pOutputStr is NULL, just returns the length that will be needed to hold the expanded string.
//
long CREGEXPRESSIONScript::ExpandCharRanges_Internal(MoaByte * pStr, unsigned long Length, MoaByte * pOutputStr)
{
	unsigned long	StrLen = 0;
	unsigned long	i = 0;
		
	for (i = 0; i < Length; i++) 
	{
		if ((i < (Length - 2)) && 	// Don't try to match if too close to the end of input string.
			(pStr[i+1] == '-'))		// Match if NEXT character will be a dash.
		{
			// Next char is a dash.  That means that this char, plus next char, plus following char
			// are considered to be a 3-char "range specifier".
			// Process them by adding a range of the appropriate length to the processed string
			// and then jump past them.
			
			MoaByte 		startChar 		= pStr[i  ];
			MoaByte   		endChar 		= pStr[i+2];
			long			PosOrNeg		= (startChar > endChar ? -1 : 1);			// Negative means range counts down.
			long			rangeLength		= ((endChar - startChar) * PosOrNeg) + 1;	// + 1 means the range is always inclusive.
			
			if (pOutputStr)
			{
				long j;
				for (j = 0; j < rangeLength; j++)
				{
					pOutputStr[StrLen+j] = (MoaByte)(((unsigned long)((long)startChar + (j * PosOrNeg))) & 0xFF);
				}
			}
			
			StrLen +=		rangeLength;	// output string grows by length
			i      += 		2;				// skip dash and end-range characters
		}
		else
		{
			// Next char is not a dash, or we are too close to the end of the string.
			// That means this character is not the start of a range. That makes this character a literal.
			// Just pass this one char from the raw string to the processed string.
			if (pOutputStr)
			{
				pOutputStr[StrLen] = pStr[i];
			}
			
			StrLen += 1;	// output string just gets 1 additional, non-special character.
		}
	}	
	
//  LEAVE_FUNCTION:

	return(StrLen);
}


//----------------------------------------------------------------------------
// PRegEx_ReplaceString : does one replace, given a string supplied in Lingo arg 1.
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_ReplaceString         (PMoaMmCallInfo callPtr)
{
	long 			Err 		= REGERR_SUCCESS;

	long       		TotalArguments = callPtr->nargs;

	MoaMmValue		ReplacePatVal;
	char *			ReplacePatValStrPtr = NULL;
	long			MustReleasePReplacePatStr = 0;
	
	long			ReplacePatStrLen = 0;

	// Make sure the replacement pattern is a string & get its length & pointer.
	RE_TryAssert(TotalArguments >= 1, REGERR_ReplPatMustBeString);
	GetArgByIndex(1, &ReplacePatVal);
	RE_TryType(&ReplacePatVal, kMoaMmValueType_String, REGERR_ReplPatMustBeString);
	ReplacePatStrLen = PRegEx_GetStringLengthThroughLingo(&ReplacePatVal);
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&ReplacePatVal, (const char **)&ReplacePatValStrPtr));
	MustReleasePReplacePatStr = 1;
		  
	// ReplaceString_Internal does the rest of the work.
	// Once upon a time, this factoring was needed, but now,
	// these functions could be combined again.  Or not.  Doesn't matter.
	RE_TryErr(PRegEx_ReplaceString_Internal(ReplacePatValStrPtr, ReplacePatStrLen));
		  
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{	// Success: return 1 (true)
		pMmValue->IntegerToValue(1, &callPtr->resultValue);
	}
	else
	{	// Failure: return error code.
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	RE_MaybeValRelPntr(&ReplacePatVal, MustReleasePReplacePatStr);
	
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_ReplaceString_Internal: 
//   -- Optionally calculate interpolations to yield altered replacement string,
//   -- Optionally perform the replacement in the internal buffer
//   -- Optionally copy internal string buffer back into caller's SrchStrL.
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_ReplaceString_Internal(char * ReplPatString, long ReplPatStringLength)
{
	long   		Err = REGERR_SUCCESS;
	
	char * 		InterpolatedStr = NULL;
	long   		InterpolatedLen = 0;
				
	char * 		MyReplaceString = NULL;
	long 		MyReplaceLength = NULL;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	// Check we actually found something.
	// It is meaningless to call this function unless a match has succeeded
	// and no intervening Replace has already been done.
	RE_TryAssert((StateInfo.MatchFound) && !(StateInfo.Replaced), REGERR_TriedToReplaceWithoutMatching);

	// Interpolating: modify a copy of the ReplPat Value suppplied by caller.
	
	// First get size of buffer to hold interpolated string.
	// Allocate the buffer.
	// Do the interpolations.
	InterpolatedLen 			= Interpolate_Internal((MoaByte *)ReplPatString, ReplPatStringLength, 
														NULL, 1, 0, NULL, NULL);
	RE_TryMem(InterpolatedStr	= (char *)pCalloc->NRAlloc(InterpolatedLen + 1 ));
	InterpolatedLen				= Interpolate_Internal((MoaByte *)ReplPatString, ReplPatStringLength, 
														(MoaByte *)InterpolatedStr, 1, 0, NULL, NULL);
	MyReplaceString				= InterpolatedStr;
	MyReplaceLength				= InterpolatedLen;

	// Replace (either keeping same length, shortening, or lengthening)
	if (MyReplaceLength == StateInfo.EntireMatchLen)
	{
		// Search and replace strings have same length.  Just overwrite data in our buffer.
		memcpy(&StateInfo.pCurrentString[StateInfo.SearchOffset],MyReplaceString,MyReplaceLength);
	}
	else if (MyReplaceLength < StateInfo.EntireMatchLen)
	{
		// The amount of replacement data is less than the
		// entire match so we just copy over and shift everything down.
	
		unsigned long BufferDifference = StateInfo.EntireMatchLen - MyReplaceLength;
		
		// Overwrite the data.
		memcpy(&StateInfo.pCurrentString[StateInfo.SearchOffset],MyReplaceString,MyReplaceLength);
		
		// Move part beyond this point downward.
		memmove(&StateInfo.pCurrentString[StateInfo.SearchOffset + MyReplaceLength],
			    &StateInfo.pCurrentString[StateInfo.SearchOffset + MyReplaceLength + BufferDifference],
				StateInfo.CurrentStringLen - (StateInfo.SearchOffset + StateInfo.EntireMatchLen));
				
		// Lop off other data
		StateInfo.pCurrentString[StateInfo.CurrentStringLen - BufferDifference] = 0; 

		StateInfo.Pos 				-= BufferDifference;
		StateInfo.CurrentStringLen	-= BufferDifference;
		
		// Note: resulting buffer is now bigger than the data we're storing in it.
	}
	else if (MyReplaceLength > StateInfo.EntireMatchLen)
	{
		// The amount of replacement data is larger than the amount of space for
		// the entire match so we will need to allocate more space.
		
		unsigned long		BufferDifference	= MyReplaceLength - StateInfo.EntireMatchLen;
		unsigned long		TotalNewSpace 		= StateInfo.CurrentStringLen + (BufferDifference);

		// Make a new buffer big enough to hold the new data. 
		char * 				pNewBuffer = NULL;
		RE_TryMem(pNewBuffer = (char *)MyMalloc(TotalNewSpace + 1));

		// Copy part of buffer up to this point into the new buffer.
		memcpy(pNewBuffer,StateInfo.pCurrentString,StateInfo.SearchOffset);
		
		// Copy replacement string into new buffer.
		memcpy(&pNewBuffer[StateInfo.SearchOffset],MyReplaceString,MyReplaceLength);

		// Copy the part of the old buffer past the match into the new buffer.
		memcpy(&pNewBuffer[StateInfo.SearchOffset + MyReplaceLength],
			   &StateInfo.pCurrentString[StateInfo.SearchOffset+StateInfo.EntireMatchLen],
			   StateInfo.CurrentStringLen - (StateInfo.EntireMatchLen + StateInfo.SearchOffset));

		// Free the old buffer.
		RE_MaybeMyFree(StateInfo.pCurrentString);

		// Retain the new buffer.  This persists until ClearInternalState.
		StateInfo.pCurrentString	 = pNewBuffer; 	 pNewBuffer = NULL; // StateInfo now owns.
		StateInfo.CurrentStringLen	 = TotalNewSpace;

		StateInfo.Pos				+= BufferDifference;
	}
			
	// The replacement has been made.
	StateInfo.Replaced = 1;

	// Put the replacement buffer back into the (caller's) list.
	RE_TryErr(ReplaceBufferBackToCallersList());
		
LEAVE_FUNCTION:

	RE_MaybeFreePtr(InterpolatedStr);

	return(Err);
}

// ReplaceBufferBackToCallersList
//
// Helper function for ReplaceString and Replace.
//
// This is how we return a potentially-modified pCurrentString back to the
// caller -- we create a MOA value which is a copy of our buffer and insert 
// it into their list.

long CREGEXPRESSIONScript::ReplaceBufferBackToCallersList(void)
{
	long   		Err = REGERR_SUCCESS;
	
	MoaMmValue 	TempValue;
	long		MustReleaseTempValue = 0;

	// Create a value we can add to the list.
	RE_TryErr(StringWithNULsToMMValue(StateInfo.pCurrentString, StateInfo.CurrentStringLen, TempValue));
	MustReleaseTempValue = 1;

	// Put the value back into the (caller's) list.
	RE_TryMoaOrMem(pMmList->SetValueByIndex(&StateInfo.SearchStringList, 1,&TempValue));

LEAVE_FUNCTION:
	RE_MaybeValRelease(&TempValue, MustReleaseTempValue);

	return(Err);
}

// ReplaceBufferBackToCallersList
//
// Helper function for ReplaceString and Replace.
//
// Opposite of ReplaceBufferBackToCallersList -- this is used only
// when aborting following a partially-completed global replace.

long CREGEXPRESSIONScript::CallersListBackToReplaceBuffer(void)
{
	long   			Err = REGERR_SUCCESS;
	
	MoaMmValue 		TempValue;
	long			MustReleaseTempValue = 0;
	char *			TempValueStringPtr = NULL;
	long			MustReleaseTempValueStringPtr = 0;
	
	unsigned long	BufferLength = 0;

	char * 			pNewBuffer = NULL;

	// Get the value back from the (caller's) list.
	RE_TryMoaOrMem(pMmList->GetValueByIndex(&StateInfo.SearchStringList, 1, &TempValue));
	MustReleaseTempValue = 1;
	
	// Get string and a pointer.
	RE_TryType(&TempValue, kMoaMmValueType_Integer, REGERR_SearchStrLLengthArgMustBeInteger);
	BufferLength = PRegEx_GetStringLengthThroughLingo(&TempValue);
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&TempValue,(const char **)&TempValueStringPtr));
	MustReleaseTempValueStringPtr = 1;

	// Allocate a buffer
	RE_TryMem(pNewBuffer = (char *)MyMalloc(BufferLength + 1));

	// Copy entire string into buffer.
	memcpy(pNewBuffer, TempValueStringPtr, BufferLength);

	// Free the old buffer.
	RE_MaybeMyFree(StateInfo.pCurrentString);

	// Retain the new buffer.  This persists until ClearInternalState.
	StateInfo.pCurrentString	 = pNewBuffer; 	 pNewBuffer = NULL; // StateInfo now owns.

	StateInfo.Pos				 = 0;

LEAVE_FUNCTION:

	RE_MaybeMyFree(pNewBuffer);

	RE_MaybeValRelPntr(&TempValue, MustReleaseTempValueStringPtr);
	RE_MaybeValRelease(&TempValue, MustReleaseTempValue);

	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_GetMatchString
// 
// Returns either entire match (if no arg or arg == 0), or
// a back reference string.
//
// If bad back ref number is requested, void is returned.
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_GetMatchString(PMoaMmCallInfo callPtr)
{
	long       			Err	= REGERR_SUCCESS;

	long       			TotalArguments = callPtr->nargs;

	MoaMmValue			BackRefVal;
	MoaMmValueType		BackRefValType;
	long       			BackRefID = 0;

	MoaMmValue			BackRefStringVal;
	long				MustReleaseBackRefStringVal = 0;

	// Return void by default.
	callPtr->resultValue = 	StateInfo.ARandomVoidValue;

	// If caller gave an argument, it is supposed to be an integer back ref number.
	if (TotalArguments >= 1)
	{
		GetArgByIndex(1, &BackRefVal);
		pMmValue->ValueType(&BackRefVal, &BackRefValType);
		if (BackRefValType == kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&BackRefVal, &BackRefID);
		}
	}

	// Call the internal routine to actually get the value or void
	// (and do range checking).

	RE_TryErr(PRegEx_GetMatchString_Internal(BackRefID, &BackRefStringVal, MustReleaseBackRefStringVal));
	callPtr->resultValue = BackRefStringVal;

 LEAVE_FUNCTION:
	
	if (Err != REGERR_SUCCESS)
	{
		RE_MaybeValRelease(&BackRefStringVal, MustReleaseBackRefStringVal);
	}

	return(Err);
}


// PRegEx_GetMatchSubString_Internal
//
// Given a startPos and an endPos, copies a substring out of the pCurrentMatch buffer.
//
// Assumes that startPos, endPos are in correct range!
// Caller owns the ResultStringValue.
// Be sure to ValueRelease it unless passing it directly back into the resultValue

long CREGEXPRESSIONScript::PRegEx_GetMatchSubString_Internal(long startPos, long endPos, char * whichString, PMoaMmValue ResultStringValue, long & MustReleaseValue)
{
	long		Err = REGERR_SUCCESS;
	
	long 		myStringLen = (endPos - startPos);
	
	// Make sure we have a valid string length and a buffer to copy from.
	RE_TryAssert(myStringLen >= 0,    REGERR_UnexpectedInternalError);
	RE_TryAssert(whichString != NULL, REGERR_UnexpectedInternalError);

	// Convert the appropriate string range to a Value.
	// Caller owns. 
	RE_TryErr(StringWithNULsToMMValue(&(whichString)[startPos], myStringLen, *ResultStringValue));
	MustReleaseValue = 1;
	
LEAVE_FUNCTION:	

	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_GetMatchString_Internal
//
// Caller owns the ResultStringValue.  Be sure to ValueRelease
// ResultStringValue if requested, unless passing it directly back
// into the resultValue.
//
// Note that if value is void, you won't be told you have to release it.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_GetMatchString_Internal(long BackRefID, PMoaMmValue ResultStringValue, long & MustReleaseValue)
{
	long 	Err = REGERR_SUCCESS;
	long	startPos = 0;
	long	endPos = 0;
	
	long	BackRefStringLen = GetBackRefStrlen(BackRefID);
	
	long	HaveBackRef = ((BackRefID >= 0) && 
						   (BackRefID <= StateInfo.CurrentTotalBackRefs) &&
						   (StateInfo.pCurrentMatch) && 
						   (StateInfo.CurrentSearchOvector[BackRefID*2] != -1));

	if (HaveBackRef)
	{
		// If have a back ref, get the corresponding substring.
		startPos	= StateInfo.CurrentSearchOvector[BackRefID*2];
		endPos		= startPos + BackRefStringLen;
		RE_TryErr(PRegEx_GetMatchSubString_Internal(startPos, endPos, StateInfo.pCurrentMatch, ResultStringValue, MustReleaseValue));
	}
	else
	{
		// Otherwise, return a void value.
		*ResultStringValue = StateInfo.ARandomVoidValue;
		MustReleaseValue = 0;
	}
	
LEAVE_FUNCTION:	

	return(Err);
}

//----------------------------------------------------------------------------
// AppendMatchStringSegmentToList
//
// Helper function for Split.
//
// Uses PRegEx_GetMatchString_Internal to get a value from any portion of the
// curernt match string and append it to a list.  
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::AppendMatchStringSegmentToList(PMoaMmValue aList, long startPos, long endPos)
{
	long Err = REGERR_SUCCESS;
	MoaMmValue	StringValue;
	long		MustReleaseStringValue = 0;
		
	RE_TryErr(PRegEx_GetMatchSubString_Internal(startPos, endPos, StateInfo.pCurrentString, &StringValue, MustReleaseStringValue));
		
	RE_TryMoaOrMem((pMmList->AppendValueToList(aList, &StringValue)));

LEAVE_FUNCTION:

	RE_MaybeValRelease(&StringValue, MustReleaseStringValue);

	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_GetMatchStart
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_GetMatchStart(PMoaMmCallInfo callPtr)
{
	long       			Err	= REGERR_SUCCESS;

	long       			TotalArguments = callPtr->nargs;

	MoaMmValue			BackRefVal;
	MoaMmValueType		BackRefValType;
	long       			BackRefID = 0;

	// Return void by default.
	callPtr->resultValue = StateInfo.ARandomVoidValue;

	// If caller gave an argument, it is supposed to be an integer back ref number.
	if (TotalArguments >= 1)
	{
		GetArgByIndex(1, &BackRefVal);
		pMmValue->ValueType(&BackRefVal, &BackRefValType);
		if (BackRefValType == kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&BackRefVal, &BackRefID);
		}
	}

	// IF the back ref number is in the right range, and we have an active match...
	if ((BackRefID >= 0) && 
		(BackRefID <= StateInfo.CurrentTotalBackRefs) &&
		StateInfo.pCurrentMatch)
	{
		// ... AND there was actually a matching back ref at this position...
		if (StateInfo.CurrentSearchOvector[BackRefID*2] != -1)
		{
			// ... Get the starting position from Ovector (re-adjusting to add back the SearchOffset).
			RE_TryMoaOrMem(pMmValue->IntegerToValue(StateInfo.CurrentSearchOvector[BackRefID*2] + StateInfo.SearchOffset, &callPtr->resultValue));
		}
	}
	// Otherwise, return void since there is no backref or match to give any info about.
	
 LEAVE_FUNCTION:
	
	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_GetMatchLen
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_GetMatchLen(PMoaMmCallInfo callPtr)
{
	long       			Err	= REGERR_SUCCESS;

	long       			TotalArguments = callPtr->nargs;

	MoaMmValue			BackRefVal;
	MoaMmValueType		BackRefValType;
	long       			BackRefID = 0;

	// Return void by default.
	callPtr->resultValue = StateInfo.ARandomVoidValue;

	// If caller gave an argument, it is supposed to be an integer back ref number.
	if (TotalArguments >= 1)
	{
		GetArgByIndex(1, &BackRefVal);
		pMmValue->ValueType(&BackRefVal, &BackRefValType);
		if (BackRefValType == kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&BackRefVal, &BackRefID);
		}
	}

	// IF the back ref number is in the right range, and we have an active match...
	if ((BackRefID >= 0) && 
		(BackRefID <= StateInfo.CurrentTotalBackRefs) &&
		StateInfo.pCurrentMatch)
	{
		// ... AND there was actually a matching back ref at this position...
		if (StateInfo.CurrentSearchOvector[BackRefID*2] != -1)
		{
			// ... Get the starting position from Ovector (re-adjusting to add back the SearchOffset).
			RE_TryMoaOrMem(pMmValue->IntegerToValue(GetBackRefStrlen(BackRefID), &callPtr->resultValue));
		}
	}
	// Otherwise, return void since there is no backref or match to give any info about.

LEAVE_FUNCTION:
	
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_SetPos
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_SetPos(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	long TotalArguments = callPtr->nargs;

	MoaMmValue PosVal;
	long       Pos = 0;

	// Push if necessary.
	RE_TryErr(CheckContext());

	GetArgByIndex(1,&PosVal);
	pMmValue->ValueToInteger(&PosVal,&Pos);
	
	// Limit Pos to min of 0      (meaning: before start of string)
	// and max of string length   (meaning: after end of string)
	Pos = __max(0, Pos);
	Pos = __min(Pos, StateInfo.CurrentStringLen);
	
	StateInfo.Pos = Pos;
	
LEAVE_FUNCTION:

	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_Clear
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_Clear(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	long TotalArguments = callPtr->nargs;	
	MoaMmValue bCompleteResetVal;
	long       bCompleteReset = 0;
				
	// Push if necessary.
	RE_TryErr(CheckContext());

	if (TotalArguments > 0)
	{
		GetArgByIndex(1,&bCompleteResetVal);
		pMmValue->ValueToInteger(&bCompleteResetVal,&bCompleteReset);
	}

	ClearInternalState((unsigned int)bCompleteReset);
	
LEAVE_FUNCTION:	

	return(Err);	
}

//----------------------------------------------------------------------------
//
// PRegEx_QuoteMeta 
//
// Processes potentially-"special" characters by adding a backslash in front
// of them so they can be used as a search string without the special characters
// being interpreted as Regular Expression syntax.  Prudent programmers always
// call this before passing any potentially-user-supplied ("tainted") data
// into a regular expression, unless the express intent is for the user-supplied
// data to contain regular expression syntax.
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_QuoteMeta(PMoaMmCallInfo callPtr)
{
	long 			Err 	= REGERR_SUCCESS;
	
	MoaMmValue		InStringVal;
	MoaByte *		InStringValPtr;
	long			MustReleaseInStringValPtr;

	long			InStringLength = 0;
	long			OutStringLength = 0;
	
	MoaByte *		pOutString = NULL;
	MoaMmValue		OutStringVal;
	long			MustReleaseOutStringVal;

	// Get a string and its pointer from argument 1	
	GetArgByIndex(1, &InStringVal);
	RE_TryType(&InStringVal, kMoaMmValueType_String, REGERR_QuoteMetaNeedsString);
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&InStringVal,(const char **)&InStringValPtr));
	MustReleaseInStringValPtr = 1;
	
	// Get the InString length
	InStringLength = PRegEx_GetStringLengthThroughLingo(&InStringVal);

	// Calculate the OutStringLength by doing a dry-run through the engine.
	OutStringLength = QuoteMetaEngine(InStringValPtr, InStringLength, NULL   );
	
	// Alloc a buffer to expand (or contract) into
	RE_TryMem(pOutString = (MoaByte *)pCalloc->NRAlloc(OutStringLength + 1));
	
	// Expand the string by running the engine again.
	// Among other things, this eliminates any NUL chars that may have been in the InString.
	OutStringLength = QuoteMetaEngine(InStringValPtr, InStringLength, pOutString);
	
	// Convert the output string to a returnable value.
	RE_TryMoaOrMem(pMmValue->StringToValue((const char *)pOutString, &OutStringVal));
	MustReleaseOutStringVal = 1;

LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{	// Give output string back to caller.
		callPtr->resultValue = OutStringVal;
		MustReleaseOutStringVal = 0;
	}
	else
	{	// Otherwise, give caller an empty string and let output string get released if necessary.
		pMmValue->StringToValue("", &callPtr->resultValue);
	}
	
	RE_MaybeValRelease(&OutStringVal, MustReleaseOutStringVal);
	RE_MaybeFreePtr(pOutString);
	RE_MaybeValRelPntr(&InStringVal , MustReleaseInStringValPtr);
	
	return(Err);	
}

//----------------------------------------------------------------------------
// QuoteMetaEngine 
//
// Helper function for PRegEx_QuoteMeta
//
// scans a string and makes a copy, adding a slash in front of non-"word" chars.
// Converts NUL (zero) character to "\0".
//
// If pOutStr is NULL, just does the scanning and length calculation. 
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::QuoteMetaEngine(MoaByte * pInStr, long InStrLen, MoaByte *pOutStr)
{
	int i = 0 , j = 0;
	int OutStrLen = 0;
	int CurChar  = 0;
		
	for (i = 0; i < InStrLen; ++i)
	{
		CurChar = (int)pInStr[i];

		if ((CurChar >= 'a' && CurChar <= 'z') ||
			(CurChar >= 'A' && CurChar <= 'Z') || 
			(CurChar >= '0' && CurChar <= '9') || 
			(CurChar == '_'))
		{
			// Word character: pass through unaltered.
			if (pOutStr) pOutStr[OutStrLen] = CurChar;
			OutStrLen++;
		}
		else
		{
			// Not a word character: pass through backslash plus char itself or 0 for NUL.
			if (pOutStr)
			{
				pOutStr[OutStrLen++] = '\\';
				pOutStr[OutStrLen++] = (CurChar == 0x00 ? '0' : CurChar);	// if NUL, use \0 for it.
			}
			else
			{
				OutStrLen += 2;
			}
		}
	}

	return(OutStrLen);
}


//----------------------------------------------------------------------------
// Begin_Internal
//
// Common startup behavior for ALL high-level RE-related functions.  Processes
// first three arguments (SearchStrL, RE, Opts), plus does any necessary validations.
// Just calls internal versions of SetSearchString and SetMatchPattern.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::Begin_Internal(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	// Set search and match strings
	RE_TryErr(PRegEx_SetSearchString_Internal(callPtr, 1, 0   ));
	RE_TryErr(PRegEx_SetMatchPattern_Internal(callPtr, 2, 3, 0));
	
LEAVE_FUNCTION:

	return(Err);	
}


//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_Search         (PMoaMmCallInfo callPtr                       ) 
{return(                   PRegEx_Search_Internal(               callPtr,      0,             1));}

long CREGEXPRESSIONScript::PRegEx_SearchExec     (PMoaMmCallInfo callPtr                       )
{return(                   PRegEx_Search_Internal(               callPtr,      1,             1));}

long CREGEXPRESSIONScript::PRegEx_Search_Internal(PMoaMmCallInfo callPtr, long execMode, long setReturnVal)
{
	long Err = REGERR_SUCCESS;
	
	// State data pertaining to calling the callback function if necessary.
	PRegExCallbackInfo	myPRegExCallbackInfo;			
	long				MustReleaseCallbackReturnValue = 0;

	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	RE_TryErr(Begin_Internal(callPtr));	
	
	// Allow optional setting of execMode from "e" option (like in Perl)
	execMode = execMode || StateInfo.ExecOption;

	// If in exec mode, validate and prepare to call the callback function.
	if (execMode)
	{
		RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 4, 0, 5));
	}

	while ((PRegEx_GetNextMatch_Internal(callPtr, StateInfo.FoundCount > 0, 0) == REGERR_SUCCESS)
		   && (StateInfo.MatchFound))
	{
		if (execMode)
		{
			// In execmode, we call the callback function, but simply ignore/discard any return
			// value from it.  What would we do with it anyway?
			if ((Err = PRegEx_Call_Callback_Exec(& myPRegExCallbackInfo, 
											    NULL, 
											    NULL,
											    0)) != REGERR_SUCCESS) goto LEAVE_FUNCTION;		
		}
		
		// When "abort"ing,  stop immediately and discard all work to this point.
		if (myPRegExCallbackInfo.CallerRequestsAbort)
		{
			Err = REGERR_CallbackRequestedAbort;
			goto LEAVE_FUNCTION; // ABORT BECAUSE CALLER WANTED US TO
		}	

		// In plain-old searching, as opposed to replacing, there is no difference
		// between Stop and Last; they each simply trigger us to end the loop successfully.
		if (myPRegExCallbackInfo.CallerRequestsStop) {break;}
		
		// The skip flag doesn't mean anything for SearchExec.
		if (myPRegExCallbackInfo.CallerRequestsSkip) {}
		
		if (myPRegExCallbackInfo.CallerRequestsLast)  {break;}

		// If not in global mode, we leave after once through the loop.
		if (!StateInfo.GlobalReplaceOption)	{break;}
	}
	
	
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{
		// return gFoundCount
		if (setReturnVal)
		{
			pMmValue->IntegerToValue(StateInfo.FoundCount, &callPtr->resultValue);
		}
	}
	else
	{
		if (setReturnVal) 
		{
			pMmValue->IntegerToValue(Err, &callPtr->resultValue);
		}
	}
	if (execMode)
	{
		PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);
	}
	
	return(Err);	
}


//----------------------------------------------------------------------------
// PRegEx_SearchBegin
// PRegEx_SearchContinue
//
// These two function as a pair to allow searching in a while() loop.
// They ignore the "global" flag -- presumably, if you're using them at all,
// you want to search globally.
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_SearchBegin(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	RE_TryErr(Begin_Internal(callPtr));	
		
LEAVE_FUNCTION:

	// Return true or (negative) error code.
	if (Err == REGERR_SUCCESS) {pMmValue->IntegerToValue(1,   &callPtr->resultValue);}
	else                       {pMmValue->IntegerToValue(Err, &callPtr->resultValue);}

	return(Err);	
}

long CREGEXPRESSIONScript::PRegEx_SearchContinue(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	RE_TryErr(PRegEx_GetNextMatch_Internal(callPtr, StateInfo.FoundCount > 0, 0));

LEAVE_FUNCTION:
	
	// Return true/false to indicate match status or (negative) error code.
	if (Err != REGERR_SUCCESS)      {pMmValue->IntegerToValue(Err, &callPtr->resultValue);}
	else if (!StateInfo.MatchFound) {pMmValue->IntegerToValue(0,   &callPtr->resultValue);}
	else                            {pMmValue->IntegerToValue(1,   &callPtr->resultValue);}
	
	return(Err);
}



//----------------------------------------------------------------------------
// AppendBackRefsToList
//
// Helper for Extract* and Split.
//
// Appends all the current back refs, if any, to the given list.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::AppendBackRefsToList(PMoaMmValue aList)
{
	long 			Err = REGERR_SUCCESS;
	long 			BRNum;
	MoaMmValue		BackRefStringValue;
	long			MustReleaseBackRefStringValue = 0;
	
	for (BRNum = 1; BRNum <= StateInfo.CurrentTotalBackRefs; BRNum++)
	{
		// Release values that get allocated during the loop.
		RE_MaybeValRelease(&BackRefStringValue, MustReleaseBackRefStringValue);
		
		// Get the backref string.
		RE_TryErr(PRegEx_GetMatchString_Internal(BRNum, &BackRefStringValue, MustReleaseBackRefStringValue));

		// Append to the list.
		RE_TryMoaOrMem((pMmList->AppendValueToList(aList, &BackRefStringValue)));
	}

LEAVE_FUNCTION:

	// Release values from final or partial loop execution.
	RE_MaybeValRelease(&BackRefStringValue, MustReleaseBackRefStringValue);

	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_Join
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Join                   (PMoaMmCallInfo callPtr)
{
	long Err 				= REGERR_SUCCESS;

	long TotalArguments		= callPtr->nargs;
	
	MoaMmValue 		myList;
	MoaMmValueType	myListType  = 0;
	
	MoaMmValue		DelimString;
	MoaMmValueType	DelimStringType = 0;
	long			mustReleaseDelimString = 0;
	
	long			DelimStringLength = 0;

	char *	 		DelimStringPtr = NULL;
	long			mustReleaseDelimStringPtr = 0;
	
	long 			numItems = 0;
	
	MoaMmValue *	ListValues = NULL;
	long       *	ListValueLengths = NULL;

	long			itemNum = 0;
	long			totalLength = 0;
	
	long			numValuesRetrieved = 0;
	
	MoaMmValue		ResultStringValue;
	char *			ResultStringValuePtr = NULL;
	long			MustReleaseResultStringValue = 0;
	long			mustReleaseResultStringValuePtr = 0;

	char *			curPos = NULL;
		
	MoaMmValue 		thisValue;
	char *	 		thisValueStringPtr;
	long			mustReleaseThisValueStringPtr = 0;
	
	char *			pTempMem = NULL;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	// Get the list (arg 1)
	GetArgByIndex(1, &myList);
	RE_TryType(&myList, kMoaMmValueType_List, REGERR_ExpectedListArgument);
	
	// Get the delimiter string (optional arg 2 -- default to "")
	if (TotalArguments >=2)
	{
		GetArgByIndex(2, &DelimString);
		RE_TryType(&DelimString, kMoaMmValueType_String, REGERR_ExpectedStringArgument);
		
		DelimStringLength = PRegEx_GetStringLengthThroughLingo(&DelimString);
		mustReleaseDelimString = 0;
	}
	else
	{
		RE_TryMoaOrMem(pMmValue->StringToValue("", &DelimString));
		DelimStringLength = 0;
		mustReleaseDelimString = 1;
	}

	// Prepare to copy the delimiter string by getting a stringPtr to it.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&DelimString, (const char **)&DelimStringPtr));
	mustReleaseDelimStringPtr = 1;


	// Count # of elements in incoming list.
	numItems = pMmList->CountElements(&myList);
	
	// Make two arrays of MmValues and their lengths.
	
	ListValues       = (MoaMmValue *)pCalloc->NRAlloc(numItems * sizeof(MoaMmValue));
	ListValueLengths = (long *      )pCalloc->NRAlloc(numItems * sizeof(long      ));

	if (!ListValues || !ListValueLengths)
	{
		MemError_LEAVE_FUNCTION;
	}
	
	// Retrieve all the values from the list and get their lengths.
	// Sum lengths to get the total size of the string buffer we will need.
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&myList, itemNum,  &(ListValues[itemNum - 1])));
		numValuesRetrieved++;	// Will gang-release all these during the cleanup phase.

		ListValueLengths[itemNum - 1] = PRegEx_GetStringLengthThroughLingo(&(ListValues[itemNum - 1]));
		
		totalLength += ListValueLengths[itemNum - 1];
	}
	
	// Add additional room for the delimiters strings (N-1 of them)
	totalLength += (DelimStringLength * (numItems - 1));
	
	// Allocate the buffer to hold the result string
	// + 1 for trailing null byte.
	RE_TryMem(pTempMem = (char *)pCalloc->NRAlloc(totalLength+1));

	// Set the Buffer to some non-zero character except for the trailing NULL.
	memset(pTempMem,'A',totalLength);
	pTempMem[totalLength] = 0;

	// Convert the String To a MoaMmValue.  This copies the data in the buffer
	// and creates our result value at the same time.
	RE_TryMoaOrMem(pMmValue->StringToValue(pTempMem,&ResultStringValue));
	MustReleaseResultStringValue = 1;
	
	// Can free the temp buffer now to save space.
	RE_MaybeFreePtr(pTempMem);

	// Now get a Ptr into which we can copy the desired string data (which may contain nulls).
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&ResultStringValue, (const char **)&ResultStringValuePtr));
	mustReleaseResultStringValuePtr = 1;

	// Copy all the strings & delimiters into the destination string.
	curPos = ResultStringValuePtr;
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		thisValue 		=       ListValues[itemNum - 1];
		long thisLength = ListValueLengths[itemNum - 1];
		
		// If we have a string of non-zero length, copy it now.
		if (thisLength > 0)
		{
			RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&thisValue, (const char **)&thisValueStringPtr));
			mustReleaseThisValueStringPtr = 1;
			
			memcpy(curPos, thisValueStringPtr, thisLength);  
			curPos[thisLength] = 0; // Null terminate just because.
			curPos += thisLength;
					
			RE_MaybeValRelPntr(&thisValue, mustReleaseThisValueStringPtr);
		}

		// Add the delimiter after every item EXCEPT the last.  That's how Join behaves.
		if ((itemNum < numItems) && (DelimStringLength))
		{
			memcpy(curPos, DelimStringPtr, DelimStringLength);  
			curPos[DelimStringLength] = 0; // Null terminate just because.
			curPos += DelimStringLength;	
		}	
	}	
		
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{
		// Success: Return the string value we've concocted.
		callPtr->resultValue = ResultStringValue;
		MustReleaseResultStringValue = 0; // Caller now owns.
	}
	else
	{
		// Failure: return empty string
		pMmValue->StringToValue("", &(callPtr->resultValue));
	}

	// Release any values we retrieved from the list during processing.
	if (numValuesRetrieved)
	{
		for (itemNum = 1; itemNum <= numValuesRetrieved; itemNum++)
		{
			pMmValue->ValueRelease(&(ListValues[itemNum - 1]));
		}
	}

	RE_MaybeValRelPntr(&ResultStringValue, mustReleaseResultStringValuePtr);
	RE_MaybeValRelPntr(&thisValue, mustReleaseThisValueStringPtr);
	RE_MaybeFreePtr(pTempMem);
	
	RE_MaybeFreePtr(ListValues);
	RE_MaybeFreePtr(ListValueLengths);

	RE_MaybeValRelPntr(&DelimString, mustReleaseDelimStringPtr);

	RE_MaybeValRelease(&DelimString, mustReleaseDelimString);
	RE_MaybeValRelease(&ResultStringValue, MustReleaseResultStringValue);
		
	return(Err);	
}


//----------------------------------------------------------------------------
// PRegEx_GetCallersOrNewInitList
//
// Internal helper routine that checks a given argument number in
// callPtr for a caller-supplied argument list or PList.  If the
// argument is absent, it creates a new list of the desired type; if
// present, it retrieves, checks that the type matches, and generates
// an error if it does not.  If success, the list is returned via
// listValue, and mustRelease will be set to true if the list was
// newly created, and hence now owned by the caller.  (Of course, the
// calling function can generally get away without releasing it, even
// in this case, simply by always returning it to its caller.)
//----------------------------------------------------------------------------


long CREGEXPRESSIONScript::PRegEx_GetCallersOrNewInitList(PMoaMmCallInfo callPtr, long ArgNum, long PList, 
														 PMoaMmValue listValue, long * mustRelease)
{
	long			Err					= REGERR_SUCCESS;
	long			TotalArguments		= callPtr->nargs;
	long			myDesiredType		= (PList ? kMoaMmValueType_PropList     : kMoaMmValueType_List       );
	long			myWrongTypeErr		= (PList ? REGERR_ExpectedPListArgument : REGERR_ExpectedListArgument);

	*mustRelease	= 0;

	if (TotalArguments >= ArgNum)
	{
		// If there is an argument in the desired position, then get
		// the list (and insist that it be one).

		GetArgByIndex(ArgNum, listValue);
		RE_TryType(listValue, myDesiredType, myWrongTypeErr);
	}
	else
	{
		// Otherwise create a list of the correct type

		RE_TryMoaOrMem((PList 
						? pMmList->NewPropListValue(listValue) 
						: pMmList->NewListValue    (listValue)));
		
		*mustRelease	= 1;
	}

 LEAVE_FUNCTION:
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_GetRequiredIncomingListArg
//
// Internal helper routine that checks a given argument number in
// callPtr for a caller-supplied List (or PList).  If the argument is
// absent, or the wrong type, then an apppriate error message is
// generated.  Otherwise, the list value is placed into IncomingList.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_GetRequiredIncomingListArg(PMoaMmCallInfo callPtr, long ArgNum, 
															long PList, PMoaMmValue IncomingList)
{
	long			Err					= REGERR_SUCCESS;
	long			TotalArguments		= callPtr->nargs;
	long			myDesiredType		= (PList ? kMoaMmValueType_PropList     : kMoaMmValueType_List       );
	long			myWrongTypeErr		= (PList ? REGERR_ExpectedPListArgument : REGERR_ExpectedListArgument);

	RE_TryAssert(TotalArguments >= ArgNum,  myWrongTypeErr);
	GetArgByIndex(ArgNum, IncomingList);
	RE_TryType(IncomingList, myDesiredType, myWrongTypeErr);

 LEAVE_FUNCTION:
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_Split
// PRegEx_ExtractIntoList
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_Split                   (PMoaMmCallInfo callPtr)
{
	return(                PRegEx_ExtractIntoList_Internal(               callPtr,      1        ));
}
long CREGEXPRESSIONScript::PRegEx_ExtractIntoList         (PMoaMmCallInfo callPtr)
{
	return(                PRegEx_ExtractIntoList_Internal(               callPtr,      0        ));
}
long CREGEXPRESSIONScript::PRegEx_ExtractIntoList_Internal(PMoaMmCallInfo callPtr, long splitMode)
{
	long			Err		= REGERR_SUCCESS;
	
	long			TotalArguments		= callPtr->nargs;

	MoaMmValue 		myList;
	MoaMmValueType	myListType  = 0;
	long			mustReleaseReturnList = 0;
	
	MoaMmValue		mySplitMaxLimitValue;
	MoaMmValueType	mySplitMaxLimitValueType = 0;
	
	long			mySplitMaxLimit = 0;

	// Push if necessary.
	RE_TryErr(CheckContext());

	// Get new list or list optionally passed by caller in arg 4.
	RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 4, 0, &myList, &mustReleaseReturnList));

	if (splitMode)
	{
		// Get optional limit argument from caller 
		if (TotalArguments >= 5)
		{
			GetArgByIndex(5, &mySplitMaxLimitValue);
			pMmValue->ValueType(&mySplitMaxLimitValue,	&mySplitMaxLimitValueType);
		}
		
		if (mySplitMaxLimitValueType == kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&mySplitMaxLimitValue,	&mySplitMaxLimit);
		}
		else
		{
			mySplitMaxLimit = 0;
		}
	}

	RE_TryErr(Begin_Internal(callPtr));	
	
	// Anchor the first split string at the start of the search string
	StateInfo.LastSplitPos = 0;
	
	while ((PRegEx_GetNextMatch_Internal(callPtr, StateInfo.FoundCount > 0, 0) == REGERR_SUCCESS)
		&& (StateInfo.MatchFound))
	{
		
		if (splitMode && !((StateInfo.FoundCount==1) && StateInfo.FoundStringHadZeroWidth))
		{
			// Append the string between StateInfo.LastSplitPos and StateInfo.SearchOffset to the list.
			// Note: Append even if its length is zero.
			
			RE_TryErr(AppendMatchStringSegmentToList(&myList, StateInfo.LastSplitPos, StateInfo.SearchOffset));
			
			
			// Set the starting pos for next split to be the current ending pos.
			StateInfo.LastSplitPos = StateInfo.Pos;
		}
		
		RE_TryErr(AppendBackRefsToList(&myList)); // ABORT if failure appending to list.
		
		if (!StateInfo.GlobalReplaceOption)	{break;}

		// When splitting, obey the Max argument.
		if (splitMode && (mySplitMaxLimit > 0) && (StateInfo.FoundCount >= (mySplitMaxLimit - 1)))
		{
			break;
		}
	}
	
	if (splitMode)
	{
		// Append the string between StateInfo.LastSplitPos and (end of search string) to the list.
		// Note: Append even if there were no matches and the string is the same as the entire search string
		
		// Normally don't append empty trailing strings.
		// But do them if a negative mySplitMaxLimit was given.
		 
		long	finalStringIsEmpty   = (StateInfo.CurrentStringLen - StateInfo.LastSplitPos <= 0);
		long	searchStrWasEmpty 	 = (StateInfo.CurrentStringLen == 0) && (StateInfo.FoundCount == 0);
		
		long	appendFinal = (!finalStringIsEmpty  
							   ? 1					 	// Have string.  append it.
		                       : (mySplitMaxLimit < 0   
		                          ? 1 					// It's empty, but caller asks us to append anyway
		                          : (searchStrWasEmpty 
		                          	 ? 1				// Empty string, but append because original was empty.
		                          	 : 0)));            // Empty string: don't append.
		if (appendFinal)					  
		{
			RE_TryErr(AppendMatchStringSegmentToList(&myList, StateInfo.LastSplitPos, StateInfo.CurrentStringLen));		
		}
	}
	
	
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)	 // Return the list.  Add a reference if we're returning the caller's own list.
	{
		if (!mustReleaseReturnList) pMmValue->ValueAddRef(&myList);
		callPtr->resultValue = myList;
	}
	else                         // Return an error code. // Release the list if we created one and we're not returning it.
	{
		RE_MaybeValRelease(&myList, mustReleaseReturnList);
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}

	return(Err);	
}

long CREGEXPRESSIONScript::PRegEx_SortListThroughLingo(PMoaMmValue ListToSort)
{
	long Err = REGERR_SUCCESS;

	MoaMmSymbol SortSymbol = 0;
	pMmValue->StringToSymbol("sort",&SortSymbol);
	pDrPlayer->CallHandler(SortSymbol, 1, ListToSort, NULL);
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_GetStringLengthThroughLingo
//
// Internal helper function.
// 
// Uses the Lingo Length operator to get the true length of a string
// (that may include NULLs) since MOA incorrectly uses the C library to determine
// string lengths.  (i.e. this is a workaround to bug in ValueStringLength()).
//
// If the value passed to this function is not a string, then 0 is returned.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_GetStringLengthThroughLingo(PMoaMmValue aString)
{
	long 			Err = REGERR_SUCCESS;
		
	MoaMmValue		lengthResult;
	
	MoaMmSymbol		LengthSymbol = 0;
	
	long			stringLength = 0;

	// Return zero if we don't have a string
	RE_TryType(aString, kMoaMmValueType_String, REGERR_SUCCESS);

	// Call the handler
	pMmValue->StringToSymbol("length", &LengthSymbol);
	pDrPlayer->CallHandler(LengthSymbol, 1, aString, &lengthResult);
	
	// Return zero if we didn't get an integer back.
	RE_TryType(&lengthResult, kMoaMmValueType_Integer, REGERR_SUCCESS);
	
	// Get the integer.
	pMmValue->ValueToInteger(&lengthResult, &stringLength);
	
LEAVE_FUNCTION:

	return(stringLength);
}

//----------------------------------------------------------------------------
// PRegEx_ExtractIntoSPList
// PRegEx_ExtractIntoSPListSym
// 
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_ExtractIntoSPList(PMoaMmCallInfo callPtr)
{
	return(                PRegEx_ExtractIntoSPList_Internal(callPtr, 0));
}
long CREGEXPRESSIONScript::PRegEx_ExtractIntoSPListSym(PMoaMmCallInfo callPtr)
{
	return(                PRegEx_ExtractIntoSPList_Internal(callPtr, 1));
}
long CREGEXPRESSIONScript::PRegEx_ExtractIntoSPList_Internal(PMoaMmCallInfo callPtr, long symbolMode)
{
	long Err = REGERR_SUCCESS;
	
	MoaMmValue 		myList;
	MoaMmValueType	myListType  = 0;
	long			mustReleaseReturnList = 0;
		
	MoaMmValue		myExtraKey;
	long			haveExtraKey = 0;

	// Push if necessary.
	RE_TryErr(CheckContext());

	// Get new list or list optionally passed by caller in arg 4.
	RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 4, 1, &myList, &mustReleaseReturnList));

	RE_TryErr(Begin_Internal(callPtr));	
	
	while ((PRegEx_GetNextMatch_Internal(callPtr, StateInfo.FoundCount > 0, 0) == REGERR_SUCCESS)
		   && (StateInfo.MatchFound))
	{
		RE_TryErr(InsertBackRefsIntoSPList(&myList, &myExtraKey, &haveExtraKey, symbolMode));

		if (!StateInfo.GlobalReplaceOption)	{break;}
	}

	// If any key is left over after all pairs have been put together,
	// then we own it, and we need to pair it up with "void" now that we're all done.
	
  	if (haveExtraKey)
  	{
		RE_TryErr(SetAProp(&myList, &myExtraKey, &StateInfo.ARandomVoidValue, symbolMode));
	}
		
	// sort myList
	
	// Mainly this is to ensure the list is marked as "sorted".
	// According to folklore, but not documented anywhere, this will force
	// Lingo to index the list using a hash table structure for key lookups.
	// (What would it have done otherwise? Brute-force linear search?
	// Allegedly so.  Hard to fathom the uselessness of that.)

	RE_TryErr(PRegEx_SortListThroughLingo(&myList));	

LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)	 // Return the list.  Add a reference if we're returning the caller's own list.
	{
		if (!mustReleaseReturnList) pMmValue->ValueAddRef(&myList);
		callPtr->resultValue = myList;
	}
	else                         // Return an error code. // Release the list if we created one and we're not returning it.
	{
		RE_MaybeValRelease(&myList, mustReleaseReturnList);
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}

	// If we have the leftover key, we own it and now need to release it.
	RE_MaybeValRelease(&myExtraKey, haveExtraKey);
	
	return(Err);	
}


//----------------------------------------------------------------------------
// InsertBackRefsIntoSPList
//
// Internal helper function for PRegEx_ExtractIntoSPList*
//
// When inserting to an SPList (sorted property list), we have to 
// carefully put together sequential key/value pairs, allowing for the
// possibility of an odd number of items.  If this happens, the unmatched
// key gets returned as a non-void "nextKey", which the caller then may
// choose to pass in on the next go-round to become the first part of the
// next pair, OR, if the caller is not going to call us gain, the caller
// will simply match that final orphaned key with a "void" value.
//
// Note that we always use "setAProp", which replaces any existing
// identical key (there will be no duplicate keys).
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::InsertBackRefsIntoSPList(PMoaMmValue aList, PMoaMmValue initialKeyValuePtr, long *haveInitialKey, long symbolMode)
{
	long				Err = REGERR_SUCCESS;
	long				BRNum;
		
	// Initialize "initial key" state from caller.

	MoaMmValue			KeyValue 			= *initialKeyValuePtr;			
	long 				MustReleaseKeyValue = *haveInitialKey;
	
	long				haveUnpairedKey 	= *haveInitialKey;
	
	// We never have an "initial value".
	
	MoaMmValue			ValueValue;			
	long				MustReleaseValueValue = 0; 
	
	// Loop through the back refs, each time getting EITHER a key or a value as needed.
	// After each value is gotten, the pair can be added and both items can be released.
	// At the end, if there is an extra key left over, return to caller; caller owns.
	for (BRNum = 1; BRNum <= StateInfo.CurrentTotalBackRefs; BRNum++)
	{
		if (!haveUnpairedKey)
		{
			// Need a key.
			RE_TryErr(PRegEx_GetMatchString_Internal(BRNum, &KeyValue,   MustReleaseKeyValue  )); haveUnpairedKey = 1;
		}
		else
		{
			// Have a key.  Get a value to match.
			RE_TryErr(PRegEx_GetMatchString_Internal(BRNum, &ValueValue, MustReleaseValueValue)); haveUnpairedKey = 0;
			
			// Set the key/value pair in the property list.
			RE_TryErr(SetAProp(aList, &KeyValue, &ValueValue, symbolMode));
			
			// Key and value have both now been added.  Release them.
			RE_MaybeValRelease(&KeyValue,	MustReleaseKeyValue  );
			RE_MaybeValRelease(&ValueValue, MustReleaseValueValue);
		}
	}
	
LEAVE_FUNCTION:
	
	// Let caller know whether they own the leftover key.
	// Caller may choose pass it back to us as an initial key, or may
	// pair it up with another value (like void, for example).
	
	*haveInitialKey			= haveUnpairedKey;
	*initialKeyValuePtr		= KeyValue;
	
	// Release key and value again now for hygiene
	// in case they failed to be released during the loop.
	// Of course, don't release key if caller now owns.
	if (!haveUnpairedKey)
	{
		RE_MaybeValRelease(&KeyValue,   MustReleaseKeyValue  );	
	}
	RE_MaybeValRelease    (&ValueValue, MustReleaseValueValue);

	return(Err);
}


//----------------------------------------------------------------------------
// SetAProp
//
// Why doesn't MOA provide SetAProp?  Insane that we have to write
// this.  
//
// Anyway, writing our own gives us an opportunity to add the optional
// "symbolMode" where it converts in incoming value of type string
// into a symbol.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::SetAProp (PMoaMmValue myList, PMoaMmValue myProp, PMoaMmValue myVal, long symbolMode) 
{
	long			Err = REGERR_SUCCESS;
	
	MoaMmValueType  myPropType = 0;

	MoaMmValue		TempValue;
	long			MustReleaseTempValue = 0;
	
	MoaMmSymbol		mySymbol;
	MoaMmValue		mySymbolVal;
	long			mustReleaseMySymbolVal = 0;
	
	char *			mySymbolStringPtr = NULL;
	long			mustReleaseMySymbolStringPtr = 0;
	

	// If in symbolMode we are asked to add a key that's a string,
	// then convert it to a symbol first.

	if (symbolMode                                        )	{pMmValue->ValueType(myProp, &myPropType);}
	if (symbolMode && myPropType == kMoaMmValueType_String)
	{
		// Convert myProp from a string value to the corresponding symbol value.
		// You would think that pMmValue->ValueToSymbol would do the same thing as the following
		// three lines, but you'd be wrong.  It doesn't seem to work.
		RE_TryMoaOrMem(pMmValue->ValueToStringPtr(myProp, (const char **)&mySymbolStringPtr));
		mustReleaseMySymbolStringPtr = 1;

		RE_TryMoaOrMem(pMmValue->StringToSymbol(mySymbolStringPtr, &mySymbol));
		RE_TryMoaOrMem(pMmValue->SymbolToValue(mySymbol, &mySymbolVal));
		mustReleaseMySymbolVal = 1;
		
		// Use mySymbolVal in place of myProp.
		myProp = &mySymbolVal;
	}

	// Assume that if GetValueByProperty fails, it means that the property
	// does not exist.
	
	if (pMmList->GetValueByProperty(myList, myProp, &TempValue) != kMoaErr_NoErr)
	{
		// No value yet with this property.  Add one.

		RE_TryMoaOrMem(pMmList->AppendValueToPropList(myList, myProp, myVal));
	}
	else
	{
		// Value already exists with this property.  We will overwrite
		// it.  Must also mark existing one as releasable.

		RE_TryMoaOrMem(pMmList->SetValueByProperty   (myList, myProp, myVal));
		MustReleaseTempValue = 1;
	}
	
LEAVE_FUNCTION:

	RE_MaybeValRelPntr(myProp, mustReleaseMySymbolStringPtr);
	RE_MaybeValRelease(&mySymbolVal, mustReleaseMySymbolVal      );
	RE_MaybeValRelease(&TempValue, MustReleaseTempValue        );
	
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_Call_Callback_Prep
// PRegEx_Call_Callback_Exec
// PRegEx_Call_Callback_Exec_2Args
// PRegEx_Call_Callback_Tidy
//
// These internal functions assist in calling a callback function, 
// including any necessary housekeeping, passing it its optional argument,
// and then retrieving a return value from the callback.
//
// Call _Prep once before beginning; abort if it fails.
//
// Call _Exec once after each match. 
//
// Abort immediately if _Exec fails.  (Usually it will fail because of a bad
// callback function, or the return value was not a string, if you requested 
// receiving the return value by passing a non-null CallbackReturnValue pointer.)
// _Exec will put the caller's return value into CallbackReturnValue, 
// and will set a boolean MustReleaseCallbackReturnValue letting you know 
// if you need to ValueRelease the value you got.  (You may need to ValueRelease
// the value regardless of the success/failure of the callback).  If calling
// _Exec repeatedly, don't forget to release EACH TIME, or you'll have a leak.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Call_Callback_Prep(PMoaMmCallInfo callPtr, 
													PPRegExCallbackInfo myPPRegExCallbackInfo, 
													long CallbackFuncArgNum, 
													PMoaMmValue FirstCallbackArgVal,
													long SecondCallbackArgArgNum)
{
	long 				Err = REGERR_SUCCESS;
	
	long 				TotalArguments = callPtr->nargs;
				
	MoaMmValue			CallbackFuncValue;
	MoaMmValueType		CallbackFuncValueType  = 0;
	
	MoaMmValue 			SecondCallbackArgVal;

	// Get the symbol for the callback function
	GetArgByIndex		(CallbackFuncArgNum, &CallbackFuncValue);
	RE_TryType(&CallbackFuncValue, kMoaMmValueType_Symbol, REGERR_CallbackFuncMustBeSymbol);
	
	// Get the symbol object from the value object.  This is what
	// we need to make the call.
	 
	pMmValue->ValueToSymbol(&CallbackFuncValue, &myPPRegExCallbackInfo->CallbackFuncSymbol);
    
	myPPRegExCallbackInfo->CallbackNumArgs = 0;
	myPPRegExCallbackInfo->CallbackArgList = 0;
						   
    // Flatten all of the arguments in FirstCallbackArgVal (if any) into our buffer
    // of argument values.
    
    RE_TryErr(PRegEx_Call_Callback_Prep_AddArgs(myPPRegExCallbackInfo, FirstCallbackArgVal));


    // Flatten the ones from SecondCallbackArgVal as well. Since this
    // value is always derived from the Lingo caller, we do the work of getting 
    // the value from the callPtr, rather than making our immediate C caller 
    // give us the value.
    
    if (                 SecondCallbackArgArgNum <= 0)  goto LEAVE_FUNCTION;
    if (TotalArguments < SecondCallbackArgArgNum     )  goto LEAVE_FUNCTION;
	
	GetArgByIndex(SecondCallbackArgArgNum, &SecondCallbackArgVal);	
	
    RE_TryErr(PRegEx_Call_Callback_Prep_AddArgs(myPPRegExCallbackInfo, &SecondCallbackArgVal));
    
LEAVE_FUNCTION:

	return(Err);
}


long CREGEXPRESSIONScript::PRegEx_Call_Callback_Prep_AddArgs(PPRegExCallbackInfo myPPRegExCallbackInfo, 
													        PMoaMmValue ArgListOrSingleValue)
{
	long Err = REGERR_SUCCESS;
	MoaMmValueType			ArgListType = 0;
	long					ThisArgCount = 0;
	MoaMmValue *			oldCallbackArgList	 = NULL;
	long NewArgCount = 0;
	
	if (ArgListOrSingleValue == NULL) goto LEAVE_FUNCTION; // None to be added.
	
	// Figure out how many items we'll be adding.
	pMmValue->ValueType	(ArgListOrSingleValue, &ArgListType);
	
	if (ArgListType == kMoaMmValueType_List)
	{
		// It's a list: we'll be adding all of its elements
		ThisArgCount += pMmList->CountElements(ArgListOrSingleValue);
	}
	else
	{
		// It's a non-list: we'll just be adding this single value.
		ThisArgCount += 1;
	}
	
	if (ThisArgCount < 1)
	{			
		goto LEAVE_FUNCTION;		// None to be added.
	}

	// Allocate and/or resize arg list to accommodate new size.
	if (myPPRegExCallbackInfo->CallbackArgList == NULL)
	{
		myPPRegExCallbackInfo->CallbackNumArgs = 0; // Should already be 0, but what the hell.

		// Allocate new buffer.
		NewArgCount = ThisArgCount;
				
		RE_TryMem(myPPRegExCallbackInfo->CallbackArgList = (MoaMmValue *)pCalloc->NRAlloc(ThisArgCount * sizeof(MoaMmValue)));
	}
	else
	{
		// Resize by creating a new arg list buffer; copying in old ones.
		NewArgCount				= myPPRegExCallbackInfo->CallbackNumArgs + ThisArgCount;
		
		oldCallbackArgList	 	= myPPRegExCallbackInfo->CallbackArgList; // free below after successful realloc/copy
		
		RE_TryMem(myPPRegExCallbackInfo->CallbackArgList = (MoaMmValue *)pCalloc->NRAlloc(NewArgCount * sizeof(MoaMmValue)));
		
		memcpy( myPPRegExCallbackInfo->CallbackArgList, oldCallbackArgList, 
			   (myPPRegExCallbackInfo->CallbackNumArgs * sizeof(MoaMmValue)));

		RE_MaybeFreePtr(oldCallbackArgList);

	}

	// Add all the new elements to the properly-sized arg list buffer
	long argNum;
	for (argNum = 0; argNum < ThisArgCount; argNum++)
	{
		if (ArgListType == kMoaMmValueType_List)
		{
			// It's a list: we'll be adding all of its elements
			// Note: getting from a list adds a reference count that must be released when we Tidy.
			pMmList->GetValueByIndex(ArgListOrSingleValue, argNum + 1, 
				&(myPPRegExCallbackInfo->CallbackArgList[myPPRegExCallbackInfo->CallbackNumArgs + argNum]));
		}
		else
		{
			// It's a non-list: we'll just be adding this single value.
			      myPPRegExCallbackInfo->CallbackArgList[myPPRegExCallbackInfo->CallbackNumArgs + argNum] = *ArgListOrSingleValue;
			// We add a reference count so that we can Release it along with all the other elements later when we Tidy
			pMmValue->ValueAddRef(&(myPPRegExCallbackInfo->CallbackArgList[myPPRegExCallbackInfo->CallbackNumArgs + argNum]));
		}
	}
	
	// Update the field that says how many items we now have flattened into our arg list buffer.
	myPPRegExCallbackInfo->CallbackNumArgs += ThisArgCount;

LEAVE_FUNCTION:

	return(Err);
}

long CREGEXPRESSIONScript::PRegEx_Call_Callback_Prep_ReplaceArgValue(PPRegExCallbackInfo myPPRegExCallbackInfo, 
																	long argNum,
													                PMoaMmValue newValue)
{
	long Err = REGERR_SUCCESS;
	if ((!myPPRegExCallbackInfo->CallbackArgList) || 
	    (!myPPRegExCallbackInfo->CallbackNumArgs)    )
	{
		Err = REGERR_UnexpectedInternalError;
		goto LEAVE_FUNCTION;
	}
	
	// Release the one that was there before.
	pMmValue->ValueRelease(&(myPPRegExCallbackInfo->CallbackArgList[argNum-1]));

	myPPRegExCallbackInfo->CallbackArgList[argNum-1] = *newValue;	

	// Add a reference to the newly-added one.  (will be released again on _Tidy)
	pMmValue->ValueAddRef(&(myPPRegExCallbackInfo->CallbackArgList[argNum-1]));

LEAVE_FUNCTION:
	return(Err);
}

long CREGEXPRESSIONScript::PRegEx_Call_Callback_Exec_2Args(PPRegExCallbackInfo myPPRegExCallbackInfo, 
															PMoaMmValue CallbackReturnValue, 
															long *MustReleaseCallbackReturnValue, 
															long RequireStringReturnType,
															PMoaMmValue Arg1,
															PMoaMmValue Arg2)
{
	long Err = REGERR_SUCCESS;

	RE_TryErr(PRegEx_Call_Callback_Prep_ReplaceArgValue(myPPRegExCallbackInfo, 1, Arg1));

	RE_TryErr(PRegEx_Call_Callback_Prep_ReplaceArgValue(myPPRegExCallbackInfo, 2, Arg2));


	RE_TryErr(PRegEx_Call_Callback_Exec(myPPRegExCallbackInfo, 
										CallbackReturnValue, 
										MustReleaseCallbackReturnValue, 
										RequireStringReturnType));

LEAVE_FUNCTION:

	return(Err);
}



long CREGEXPRESSIONScript::PRegEx_Call_Callback_Exec(PPRegExCallbackInfo myPPRegExCallbackInfo, 
													PMoaMmValue CallbackReturnValue, 
													long *MustReleaseCallbackReturnValue, 
													long RequireStringReturnType)
{
	long Err = REGERR_SUCCESS;
	MoaError CallHandlerErr = kMoaErr_NoErr;

	MoaMmValueType			CallbackFuncReturnValueType  = 0;
    
	// Ensure stopper flags are turned off in the current context.
	// They always should be at this point, but who knows what weirdness
	// our callers might come up with.
	
	StateInfo.CallbackAbort = 0;
	StateInfo.CallbackStop  = 0;
	StateInfo.CallbackSkip  = 0;
	StateInfo.CallbackLast  = 0;

	StateInfo.InCallBackFunction = 1;
	CallHandlerErr = 
		pDrPlayer->CallHandler(myPPRegExCallbackInfo->CallbackFuncSymbol, 
							   myPPRegExCallbackInfo->CallbackNumArgs, 	// May be zero
							   myPPRegExCallbackInfo->CallbackArgList,  	// May be NULL if none.
							   CallbackReturnValue); // may be NULL if caller doesn't want it.
							   
	RE_TryMoaOrErr(CallHandlerErr, REGERR_CallbackFunctionFailed);

	// Get copies of these flags before the context might change due to a pop.
	myPPRegExCallbackInfo->CallerRequestsAbort = StateInfo.CallbackAbort;
	myPPRegExCallbackInfo->CallerRequestsStop  = StateInfo.CallbackStop ;
	myPPRegExCallbackInfo->CallerRequestsSkip  = StateInfo.CallbackSkip ;
	myPPRegExCallbackInfo->CallerRequestsLast  = StateInfo.CallbackLast ;

	// Reset stopper flags to off in the current context
	StateInfo.CallbackAbort = 0;
	StateInfo.CallbackStop  = 0;
	StateInfo.CallbackSkip  = 0;
	StateInfo.CallbackLast  = 0;

	// If StateInfo.InCallBackFunction got turned OFF while the Lingo
	// handler was running, it means that some other PRegEx function did it...
	// ...which means that function also did a PUSH (via CheckContext) as a protection
	// to allow recursive use of PRegEx functions inside a callback.

	if (!StateInfo.InCallBackFunction)
	{
		// Since that happened, it is now our obligation to POP that context back
		// so the rest of this function and its caller and peers at this stack 
		// depth will see the context they were expecting to see!
		PopContext();
	}
	StateInfo.InCallBackFunction = 0;

	if (MustReleaseCallbackReturnValue) *MustReleaseCallbackReturnValue = 1;
	
	// If calling function requested a return value, we check to be sure
	// it's a string.  If it's not, that's a fatal error.
	if (CallbackReturnValue && RequireStringReturnType)
	{
		RE_TryType(CallbackReturnValue, kMoaMmValueType_String, REGERR_CallbackFuncDidNotReturnString);
	}


LEAVE_FUNCTION:

	return(Err);
}

void CREGEXPRESSIONScript::PRegEx_Call_Callback_Tidy(PPRegExCallbackInfo myPPRegExCallbackInfo)
{
	if (myPPRegExCallbackInfo->CallbackArgList == NULL)  goto LEAVE_FUNCTION;

	// Release all the elements in our arg buffer (if any)
	long argNum;
	for (argNum = 0; argNum < myPPRegExCallbackInfo->CallbackNumArgs; argNum++)
	{
		pMmValue->ValueRelease(&(myPPRegExCallbackInfo->CallbackArgList[argNum]));
	}

	// Free the memory allocated for the argument buffer.
	RE_MaybeFreePtr(myPPRegExCallbackInfo->CallbackArgList);
	
LEAVE_FUNCTION:
	myPPRegExCallbackInfo->CallbackNumArgs = 0;
	return;
}


//----------------------------------------------------------------------------
// 
// PRegEx_Map(List, #MapFunction, ArgList)
//  -- Calls MapFunction on each element in List.  MapFunction also gets
//     an additional, optional ArgList, which can be used to pass
//     additional parameters to the function if needed.  For each item, MapFunction
//     returns put the return value into a list and returns the list that
//     was created with all the return values in it.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Map(PMoaMmCallInfo callPtr)
{
	long 				Err = REGERR_SUCCESS;
			
	MoaMmValue			CallbackReturnValue;
	long				MustReleaseCallbackReturnValue = 0;
	
	MoaMmValue			thisItemValue;
	long				MustReleaseThisItemValue = 0;

	MoaMmValue			PlaceholderFirstArgValue;
	long				MustReleasePlaceholder = 0;

	MoaMmValue        	callerList;
	MoaMmValueType	  	callerListType = 0;
	
	long	numItems;

	// State data pertaining to calling the callback function.
	PRegExCallbackInfo	myPRegExCallbackInfo;			
	
	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
	
	// Create the list that will hold our results.  Go ahead and "return" it now.
	MoaMmValue returnList;
	pMmList->NewListValue(&returnList);   // Will not need to free because will return to caller, no matter what.
	callPtr->resultValue = returnList;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	// Get caller's list.  Bail now if it is not a list.
	GetArgByIndex(1, &callerList);		// Will not need to free because it's an incoming arg; MOA frees.
	RE_TryType(&callerList, kMoaMmValueType_List, REGERR_ExpectedListArgument);
	
	// Make a temporary first value as a placeholder; it will not
	// actually be passed to the function because it will be overwritten
	// with a different first argument each time through.
	
	pMmValue->IntegerToValue(0, &PlaceholderFirstArgValue);		// WILL need to free because we created it and will not return it.
	MustReleasePlaceholder = 1;
	
	// Validate and prepare to call the callback function.
	RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 2, &PlaceholderFirstArgValue, 3));

	// Now, call the function for every item in the caller's list; get each
	// return value and append it to our list.
	numItems = pMmList->CountElements(&callerList);
	long	itemNum;

	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		// Get the next item from the list
		pMmList->GetValueByIndex(&callerList, itemNum, &thisItemValue);	// WILL need to free.
		MustReleaseThisItemValue = 1;
		
		// Insert it at the head of the argument list for the callback function, 
		// replacing the placeholder item that we had put there.
		RE_TryErr(PRegEx_Call_Callback_Prep_ReplaceArgValue(& myPRegExCallbackInfo, 1, &thisItemValue));

		// Call the callback function.
		RE_TryErr(PRegEx_Call_Callback_Exec(& myPRegExCallbackInfo, 
										   & CallbackReturnValue, 
										   & MustReleaseCallbackReturnValue, 
										   0));
		
		// When "abort"ing,  stop immediately and discard all work to this point.
		if (myPRegExCallbackInfo.CallerRequestsAbort)
		{
			Err = REGERR_CallbackRequestedAbort;
			goto LEAVE_FUNCTION; // ABORT BECAUSE CALLER WANTED US TO
		}	

		// When "stop"ping,  keep all additions up to this point, but not including current one.
		if (myPRegExCallbackInfo.CallerRequestsStop) 
		{
			break;
		}
		
		// The skip flag just means we don't append this value.
		if (!myPRegExCallbackInfo.CallerRequestsSkip) 
		{
			// Add the return value to the result list.
			RE_TryMoaOrMem((pMmList->AppendValueToList(&returnList, &CallbackReturnValue)));
		}

		// When "last"ing, keep all additions up to AND INCLUDING this current one.
		if (myPRegExCallbackInfo.CallerRequestsLast) 
		{
			break;
		}
		
		// If we got an item out of the caller's list, we have to free it before going
		// around the loop again.
		RE_MaybeValRelease(&thisItemValue, MustReleaseThisItemValue);
		
		// If callback function retrieved a value with a bumped ref count, we
		// need to release it now before proceeding with another iteration of the loop.
		RE_MaybeValRelease(&CallbackReturnValue, MustReleaseCallbackReturnValue);
	}
	
	
LEAVE_FUNCTION:

	RE_MaybeValRelease(&PlaceholderFirstArgValue, MustReleasePlaceholder);

	// We check this again down here in case the loop got 
	// aborted before this item was released.
	RE_MaybeValRelease(&thisItemValue, MustReleaseThisItemValue);

	
	// We check this again down here in case the loop got 
	// aborted before the return value was released.
	RE_MaybeValRelease(&CallbackReturnValue, MustReleaseCallbackReturnValue);
	
	PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);
	
	return(Err);	
}

//----------------------------------------------------------------------------
// 
// PRegEx_Grep
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_Grep(PMoaMmCallInfo callPtr)
{
	long 				Err = REGERR_SUCCESS;
			
	MoaMmValue			CallbackReturnValue;
	long				MustReleaseCallbackReturnValue = 0;
	
	MoaMmValue			thisItemValue;
	long				MustReleaseThisItemValue = 0;

	MoaMmValue			PlaceholderFirstArgValue;
	long				MustReleasePlaceholder = 0;
	
	MoaMmValue       	callerList;
	MoaMmValueType	  	callerListType = 0;
	
	MoaMmValue			Arg2Value;
	MoaMmValueType		Arg2ValueType = 0;
	
	MoaMmValue			TempListValue;
	long				MustReleaseTempListValue = 0;
			
	long				execMode = 0;

	long	numItems;

	// State data pertaining to calling the callback function.
	PRegExCallbackInfo	myPRegExCallbackInfo;			
	
	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
	
	// Create the list that will hold our results.  Go ahead and "return" it now.
	MoaMmValue returnList;
	pMmList->NewListValue(&returnList);   // Will not need to free because will return to caller, no matter what.
	callPtr->resultValue = returnList;
	
	// Push if necessary.
	RE_TryErr(CheckContext());

	// Get caller's list.  Bail now if it is not a list.
	GetArgByIndex(1, &callerList);		// Will not need to free because it's an incoming arg; MOA frees.
	RE_TryType(&callerList, kMoaMmValueType_List, REGERR_ExpectedListArgument);
	
	// Decide whether we're in callback-function-mode ("execMode") or in match-against-RE mode.
	GetArgByIndex(2, &Arg2Value);		// Will not need to free because it's an incoming arg; MOA frees.
	pMmValue->ValueType(&Arg2Value,&Arg2ValueType);
	if (Arg2ValueType == kMoaMmValueType_Symbol)
	{
		execMode = 1;
	}
	else if (Arg2ValueType == kMoaMmValueType_String)
	{
		execMode = 0;
	}
	else
	{
		Err = REGERR_GrepNeedsFunctionNameOrPRegEx;
		goto LEAVE_FUNCTION;
	}
	
	if (execMode)
	{
		// Make a temporary first value as a placeholder; it will not
		// actually be passed to the function because it will be overwritten
		// with a different first argument each time through.
		
		pMmValue->IntegerToValue(0, &PlaceholderFirstArgValue);		// WILL need to free because we created it and will not return it.
		MustReleasePlaceholder = 1;
		
		// Validate and prepare to call the callback function.
		RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 2, &PlaceholderFirstArgValue, 3));
	}

	// Now, call the function or run the PRegEx for every item in the caller's list; get each
	// return value and append it to our list.
	numItems = pMmList->CountElements(&callerList);
	long	itemNum;

	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		// Get the next item from the list
		pMmList->GetValueByIndex(&callerList, itemNum, &thisItemValue);	// WILL need to free.
		MustReleaseThisItemValue = 1;
		
		long booleanVal = 0;
		// Either call callback or run the pregex to arrive at a boolean value.
		if (execMode)
		{
			// Insert it at the head of the argument list for the callback function, 
			// replacing the placeholder item that we had put there.
			RE_TryErr(PRegEx_Call_Callback_Prep_ReplaceArgValue(& myPRegExCallbackInfo, 1, &thisItemValue));

			// Call the callback function.
			RE_TryErr(PRegEx_Call_Callback_Exec(& myPRegExCallbackInfo, 
											   & CallbackReturnValue, 
											   & MustReleaseCallbackReturnValue, 
											   0));
		
			pMmValue->ValueToInteger(&CallbackReturnValue, &booleanVal);
		}
		else
		{
			MoaMmValue		TempSrchStrArgs[3];
			MoaMmValueType	thisItemType;

			// Get the first argument to the Search function: a list of a string.
			// As a convenience, we allow for the case where the caller only provided
			// a bare string; we make a temporary list and put the string in it for
			// compatibility with SetSearchString.  (TO DO: Later, as a speed optimization, we
			// should probably modify SetSearchString to accept bare strings or lists,
			// rather than going through this effort.)
					
			pMmValue->ValueType(&thisItemValue, &thisItemType);
			if (thisItemType == kMoaMmValueType_String)
			{
				// Allocate a new temporary list.
				RE_TryMoaOrMem((pMmList->NewListValue(&TempListValue)));
				MustReleaseTempListValue = 1;

				// Place the current string argument into the list 
				RE_TryMoaOrMem((pMmList->AppendValueToList(&TempListValue, &thisItemValue)));
			}
			else
			{
				// Otherwise, assume the argument is a list 
				// (an appropriate error will come back if it wasn't).
				TempListValue = thisItemValue;
			}			
			
			TempSrchStrArgs[0] = TempListValue;		// First argument is: SrchStrL.
			

			// The second and third arguments are RE and Options; they
			// are already in the arg list (Arg3, Options, is optional).		
			
			long		mustReleaseStringValue = 0;
			TempSrchStrArgs[1] = (callPtr)->pArgs[1];
			
			if (callPtr->nargs > 2) 
			{
				TempSrchStrArgs[2] = (callPtr)->pArgs[2];
			}
			
			// Now, temporarily replace the pArgs in callPtr with 
			// our temporary arg list so we can use the internal mechanisms for calling
			// PRegEx_Search_Internal, then do the search, and restore.
			long SearchErr = REGERR_SUCCESS;
			{
				MoaMmValue * 	SavedArgPointer;
				
				SavedArgPointer = callPtr->pArgs;
				callPtr->pArgs 	= (MoaMmValue *)&TempSrchStrArgs;
				SearchErr 		= PRegEx_Search_Internal(callPtr, 0, 0);
				callPtr->pArgs	= SavedArgPointer;
			}
			
			if ((SearchErr == REGERR_SearchStrLMustBeList            ) || 
				(SearchErr == REGERR_SearchStrLMustContainString     ) || 
				(SearchErr == REGERR_SearchStrLLengthArgMustBeInteger))
			{
				// If Search simply didn't like something about the
				// supposed SearchStrL argument, we just treat this
				// item as a non-match and move on.
				booleanVal = 0;
			}
			else if (SearchErr != REGERR_SUCCESS)
			{
				// But if any other error occurred, say, perhaps, a memory
				// error or a PRegEx that did not compile, we abort prematurely.
				Err = SearchErr;
				goto LEAVE_FUNCTION;
			}
			else
			{
				// Search succeded.  The boolean value is set based on whether there was any match.
				booleanVal = (StateInfo.FoundCount >= 1);
			}
		}
		
		// When "abort"ing,  stop immediately and discard all work to this point.
		if (myPRegExCallbackInfo.CallerRequestsAbort)
		{
			Err = REGERR_CallbackRequestedAbort;
			goto LEAVE_FUNCTION; // ABORT BECAUSE CALLER WANTED US TO
		}	

		// When "stop"ping,  keep all additions up to this point, but not including current one.
		if (myPRegExCallbackInfo.CallerRequestsStop) 
		{
			break;
		}
		
		// The skip flag just means we don't append this value, regardless of the boolean return status.
		// Not too useful for "grep", since returning "false" accomplishes the same thing!
		// But whatever.  Can't hurt to respect it.
		
		if (!myPRegExCallbackInfo.CallerRequestsSkip) 
		{
		// Add the ORIGINAL value to the result list, only if the Boolean interpretation of the
		// return value is TRUE.
			if (booleanVal)
			{
				RE_TryMoaOrMem((pMmList->AppendValueToList(&returnList, &thisItemValue)));
			}
		}
		
		// When "last"ing, keep all additions up to AND INCLUDING this current one.
		if (myPRegExCallbackInfo.CallerRequestsLast) 
		{
			break;
		}
		
		// If we got an item out of the caller's list, we have to free it before going
		// around the loop again.
		RE_MaybeValRelease(&thisItemValue, MustReleaseThisItemValue);
		
		// If callback function retrieved a value with a bumped ref count, we
		// need to release it now before proceeding with another iteration of the loop.
		RE_MaybeValRelease(&CallbackReturnValue, MustReleaseCallbackReturnValue);
		
		// If we created a temporary list value, release it here..
		RE_MaybeValRelease(&TempListValue, MustReleaseTempListValue);
	}
	
	
LEAVE_FUNCTION:

	RE_MaybeValRelease(&PlaceholderFirstArgValue, MustReleasePlaceholder);

	// We check this again down here in case the loop got 
	// aborted before this item was released.
	RE_MaybeValRelease(&thisItemValue, MustReleaseThisItemValue);

	// We check this again down here in case the loop got 
	// aborted before the return value was released.
	RE_MaybeValRelease(&CallbackReturnValue, MustReleaseCallbackReturnValue);
	
	// Ditto....
	RE_MaybeValRelease(&TempListValue, MustReleaseTempListValue);

	if (execMode)
	{
		PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);
	}

	return(Err);	
}


//----------------------------------------------------------------------------
// PRegEx_Sort
//
// Returns a shallow copy of a list, with the items in the copy sorted
// according to an order determined by a SortFunction
// 
// PRegEx_Sort(List, DeepCopy, #SortFunction, [ArgList])
// 
//  -- Returns a new list consisting of a shallow OR Deep copy of the old
//     list, sorted according to the ordering implied by SortFunction,
//     which takes as arguments two values (of any type), here dubbed A
//     and B, from the list to be compared, plus optional additional
//     arguments if required.  For any pair, SortFunction must return -1
//     if A is less than B, 0 if A == B, and 1 if A > B.  Sort does NOT
//     modify the original list in any way, as Lingo's "sort" function
//     does.  Rather, it makes a sorted copy which you may, at your
//     option, use in place of the original.
//
// Currently using an algorithm based on the traditional Bubble Sort
// algorithm.  Some pseudocode demonstrating that algorithm is found at
// the URL given here and is shown below.
//
// http://members.tripod.de/Swordfighter/prc/csort.html
// 
// void bubblesort(short int *a,int n)
//    {
//     int i,j,tmp;
//     for(i=n;i>0;i--)
//         for(j=1;j<i;j++)
//            {
//             if(a[j-1]>a[j])
//                {
//                 tmp=a[j-1];
//                 a[j-1]=a[j];
//                 a[j]=tmp;
//                }
//            }
//    }
//
// It should be noted that bubblesort is NOT the fastest sort algorithm
// in the world and anyone is invited to choose another one and send along
// a replacement implementation.  Please!  :-) 
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Sort(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	MoaMmValue			TempListValue;
	long				MustReleaseTempListValue = 0;
	
	MoaMmValue			PlaceholderValue;
	long				MustReleasePlaceholderValue = 0;
	
	// State data pertaining to calling the callback function if necessary.
	PRegExCallbackInfo	myPRegExCallbackInfo;			
	long				MustReleaseCallbackReturnValue = 0;
	
	MoaMmValue			CallbackResult;
	MoaMmValueType		CallbackFuncReturnValueType = 0;
	long				CallbackResultInteger = 0;
		
	long				numItems = 0;		// Num sortable values in list
	MoaMmValue *		valArray = NULL;	// Array of sortable values.
	
	long				numElementsToRelease = 0;
	long				itemNum = 0;

	MoaMmValue returnList;

	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
		
	// The first stop in Sort is CopyList, which will interpret arguments 
	// 1 and 2 (list and DeepCopy).  Then, we manipulate
	// the list it generates.
	
	{
		// HACK ALERT!  Since we want CopyList() to only look at our
		// first two arguments, when normally it looks at the first 3,
		// we temporarily fake it out into thinking that it only has 2
		// (or 1) by temporarily modifying callPtr.  Very bad form.

		long tempArgCount = callPtr->nargs;
		callPtr->nargs = __min(callPtr->nargs, 2);
		Err = PRegEx_CopyList(callPtr);
		callPtr->nargs = tempArgCount;
		if (Err != REGERR_SUCCESS) goto LEAVE_FUNCTION;
	}

	// Retrieve the list that was created by CopyList.
	returnList = callPtr->resultValue;
		
	// Make a list with two copies of a placeholder value
	RE_TryMoaOrMem(pMmValue->IntegerToValue(0, &PlaceholderValue));
	MustReleasePlaceholderValue = 1;
	RE_TryMoaOrMem(pMmList->NewListValue(&TempListValue));
	MustReleaseTempListValue = 1;
	RE_TryMoaOrMem((pMmList->AppendValueToList(&TempListValue, &PlaceholderValue)));
	RE_TryMoaOrMem((pMmList->AppendValueToList(&TempListValue, &PlaceholderValue)));
		
	// Validate SortFunction and ArgList arguments, and prepare to call the callback function.
	RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 3, &TempListValue, 4));
	
	// First make a simple array of all the values in the list for quicker access.
	numItems = pMmList->CountElements(&returnList);
	RE_TryMem(valArray = (MoaMmValue *)pCalloc->NRAlloc(numItems * sizeof(MoaMmValue)));
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&returnList, itemNum, &(valArray[itemNum-1])));
		numElementsToRelease++;
	}

	// Now sort the array of values in place.
	long			i,j;
	MoaMmValue		tmpVal;
	
	for(i = numItems; i > 0; i--)
	for(j = 1;        j < i; j++)
	{
		// Call the callback with the two values; it will return 1 if the 
		// first value is greater than the second.
		RE_TryErr(PRegEx_Call_Callback_Exec_2Args(  & myPRegExCallbackInfo, 
												   & CallbackResult, 
												   & MustReleaseCallbackReturnValue, 
												   0,
												   &(valArray[j-1]),
												   &(valArray[j])
												   ));
	
		RE_TryType(&CallbackResult, kMoaMmValueType_Integer, REGERR_SortFunctionDidNotReturnInteger);

		RE_TryMoaOrMem(pMmValue->ValueToInteger(&CallbackResult, &CallbackResultInteger));
		
		RE_MaybeValRelease(&CallbackResult, MustReleaseCallbackReturnValue);
		
			
		if (CallbackResultInteger == 1)	//  if (valArray[j-1] > valArray[j])
		{
			
			tmpVal=valArray[j-1];
			valArray[j-1]=valArray[j];
			valArray[j]=tmpVal;
		}
	}

	// Now our array of values is sorted.
	// Stick them back into the list.
	
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		RE_TryMoaOrMem(pMmList->SetValueByIndex(&returnList, itemNum, &(valArray[itemNum-1])));
	}
	
	// The list has already been "returned".  We're done.


LEAVE_FUNCTION:

	RE_MaybeValRelease(&CallbackResult, MustReleaseCallbackReturnValue);
				
	if (numElementsToRelease)
	{
		for (itemNum = 1; itemNum <= numElementsToRelease; itemNum++)
		{
			pMmValue->ValueRelease(&(valArray[itemNum - 1]));
		}
		numElementsToRelease = 0;
	}

	RE_MaybeFreePtr(valArray);

	RE_MaybeValRelease(&PlaceholderValue, MustReleasePlaceholderValue);
				
	RE_MaybeValRelease(&TempListValue, MustReleaseTempListValue);
				
	PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);

	return(Err);	
}

//----------------------------------------------------------------------------
// PRegEx_CopyList
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_CopyList(PMoaMmCallInfo callPtr)
{
	long Err 				= REGERR_SUCCESS;
	
	long			TotalArguments = callPtr->nargs;
	
	MoaMmValue		IncomingList;
	
	MoaMmValue		Arg2Value;
	MoaMmValueType	Arg2ValueType;
	
	MoaMmValue		ReturnList;
	long			MustReleaseReturnList = 0;

	long			DeepCopy = 0;
	long			PList	 = 0;	// Whether we have a List or PList to start with.

	// We're always in "append" mode because we provide the initial
	// list for the internal copy routine(s), either from caller's
	// list or anew.

	long			AppendMode = 1;	

	// Get caller's PList or List from arg 1; bail if failure; set PList accordingly.
	if ((Err = PRegEx_GetRequiredIncomingListArg(callPtr, 1, 1, &IncomingList)) != REGERR_SUCCESS)
		{Err = PRegEx_GetRequiredIncomingListArg(callPtr, 1, 0, &IncomingList);}
	else{PList = 1;}
	RE_TryAssert((Err == REGERR_SUCCESS), REGERR_ExpectedListArgument);
	
	// Get an optional boolean "DeepCopy" argument from the caller.
	if (TotalArguments >= 2)
	{
		GetArgByIndex(2, &Arg2Value);
		pMmValue->ValueType(&Arg2Value,	&Arg2ValueType);
		if (Arg2ValueType == kMoaMmValueType_Integer)
		{
			pMmValue->ValueToInteger(&Arg2Value, &DeepCopy);
			DeepCopy = DeepCopy || 0;
			DeepCopy = DeepCopy && 1;
		}	
	}
	
	// Get new list or Plist optionally passed by caller in arg 3.
	RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 3, PList, &ReturnList, &MustReleaseReturnList));
	
	// If we plan to return a property list, always mark it as sorted,
	// whether it's our caller's or our own newly-created list.
	if (PList)  { RE_TryErr(PRegEx_SortListThroughLingo(&ReturnList));}
	
	if (PList)	{ RE_TryErr(PRegEx_CopyPList_Internal(&IncomingList, &ReturnList, AppendMode, DeepCopy));}
	else        { RE_TryErr(PRegEx_CopyList_Internal (&IncomingList, &ReturnList, AppendMode, DeepCopy));}
		
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)	 // Return the list.  Add a reference if we're returning the caller's own list.
	{
		if (!MustReleaseReturnList) pMmValue->ValueAddRef(&ReturnList);
		callPtr->resultValue =                             ReturnList;
	}
	else                         // Return an error code. // Release the list if we created one and we're not returning it.
	{
		RE_MaybeValRelease(&ReturnList, MustReleaseReturnList);
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	return(Err);	
}

//----------------------------------------------------------------------------
// PRegEx_Reverse
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_Reverse(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	MoaMmValue 			returnList;
	long				mustReleaseReturnList = 0;

	MoaMmValue 			itemA;
	long				mustReleaseItemA = 0;

	MoaMmValue 			itemB;
	long				mustReleaseItemB = 0;

	long				numItems = 0;		// Num sortable values in list
	long				itemNum = 0;

	// The first stop in Reverse is CopyList, which will interpret arguments 
	// 1 and 2 (List and DeepCopy).  Then, we manipulate
	// the list it generates, or pass through any errors it encounters.
	RE_TryErr(PRegEx_CopyList(callPtr));

	// Borrow the list that was created by CopyList.
	// We own it now unless we give it back again to the caller. 
	returnList = callPtr->resultValue;
	mustReleaseReturnList = 1;
		
	// Count it.
	numItems = pMmList->CountElements(&returnList);

	// Reverse in place.  Work from both ends toward the middle.
	// If the end points meet or cross, we're done.
	for (itemNum = 1; itemNum <= numItems / 2; itemNum++)
	{
		long endItemNum = ((numItems - itemNum) + 1);
		if ( endItemNum <= itemNum) break;
		
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&returnList, itemNum,    &itemA)); mustReleaseItemA = 1;
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&returnList, endItemNum, &itemB)); mustReleaseItemB = 1;
		
		RE_TryMoaOrMem(pMmList->SetValueByIndex(&returnList, itemNum,    &itemB));
		RE_TryMoaOrMem(pMmList->SetValueByIndex(&returnList, endItemNum, &itemA));
		
		RE_MaybeValRelease(&itemA, mustReleaseItemA);
		RE_MaybeValRelease(&itemB, mustReleaseItemB);
	}

LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{
		// Success.  Caller now owns returnList again.
		callPtr->resultValue = returnList;	
		mustReleaseReturnList = 0;
	}
	else
	{
		// Failure.  Return void.  returnList will be freed in cleanup below.
		callPtr->resultValue = StateInfo.ARandomVoidValue;
	}
	
	RE_MaybeValRelease(&itemA,		mustReleaseItemA);
	RE_MaybeValRelease(&itemB, 		mustReleaseItemB);
	RE_MaybeValRelease(&returnList, mustReleaseReturnList);

	return(Err);	
}

//----------------------------------------------------------------------------
// PRegEx_CopyList_Internal
// PRegEx_CopyPList_Internal
//
// Internal helper functions for PRegEx_CopyList.  They cooperate to call one
// another recursively as needed.
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_CopyList_Internal(PMoaMmValue origList, PMoaMmValue newList, long AppendMode, long DeepCopy)
{
	long 			Err = REGERR_SUCCESS;

	long 			numItems = pMmList->CountElements(origList);
	long			itemNum = 0;
	
	MoaMmValue 		thisItemValue;
	MoaMmValueType 	thisItemValueType;
	long			mustReleaseThisItem = 0;

	MoaMmValue		valueCopy; 
	long			mustReleaseValueCopy = 0;
	
	// Create a new list to hold the copied items (caller owns)
	if (!AppendMode) {RE_TryMoaOrMem(pMmList->NewListValue(newList));}
	
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		pMmList->GetValueByIndex(origList, itemNum,  &thisItemValue);
		mustReleaseThisItem = 1;
		
		pMmValue->ValueType(&thisItemValue,	&thisItemValueType);
		
		// Get value either by deep-copying it if appropriate, or just by using the same value.
		if (DeepCopy && (thisItemValueType == kMoaMmValueType_List))
		{
			RE_TryErr(PRegEx_CopyList_Internal(&thisItemValue, &valueCopy, 0, DeepCopy));
			mustReleaseValueCopy = 1;
		}
		else if (DeepCopy && (thisItemValueType == kMoaMmValueType_PropList))
		{
			RE_TryErr(PRegEx_CopyPList_Internal(&thisItemValue, &valueCopy, 0, DeepCopy));
			mustReleaseValueCopy = 1;
		}
		else
		{
			valueCopy = thisItemValue;
			mustReleaseValueCopy = 0;
		}
		
		// Add the value we got to the new list.
		RE_TryMoaOrMem((pMmList->AppendValueToList(newList, &valueCopy)));
			
			
		// Release the item we got
		RE_MaybeValRelease(&thisItemValue, mustReleaseThisItem);
		
		// Release the copy we made
		RE_MaybeValRelease(&valueCopy, mustReleaseValueCopy);
	}

  LEAVE_FUNCTION:
  
	// Re-check these down here in case of premature exit from the loop.
	RE_MaybeValRelease(&thisItemValue, mustReleaseThisItem);
	RE_MaybeValRelease(&valueCopy, mustReleaseValueCopy);
	
	return(Err);	
}

long CREGEXPRESSIONScript::PRegEx_CopyPList_Internal(PMoaMmValue origList, PMoaMmValue newList, long AppendMode, long DeepCopy)
{
	long 			Err = REGERR_SUCCESS;

	long 			numItems = pMmList->CountElements(origList);
	long			itemNum = 0;
	
	MoaMmValue 		thisItemValue;
	MoaMmValueType 	thisItemValueType;
	long			mustReleaseThisItemValue = 0;

	MoaMmValue 		thisItemKey;
	long			mustReleaseThisItemKey = 0;

	MoaMmValue		valueCopy; 
	long			mustReleaseValueCopy = 0;
	
	// Create a new list to hold the copied items (caller owns)
	if (!AppendMode) {RE_TryMoaOrMem(pMmList->NewPropListValue(newList))};
	
	for (itemNum = 1; itemNum <= numItems; itemNum++)
	{
		pMmList->GetPropertyNameByIndex(origList, itemNum,  &thisItemKey);
		mustReleaseThisItemKey = 1;
		
		pMmList->GetValueByIndex(origList, itemNum,  &thisItemValue);
		mustReleaseThisItemValue = 1;
		
		pMmValue->ValueType(&thisItemValue,	&thisItemValueType);
		
		// Get value either by deep-copying it if appropriate, or just by using the same value.
		if (DeepCopy && (thisItemValueType == kMoaMmValueType_List))
		{
			RE_TryErr(PRegEx_CopyList_Internal(&thisItemValue, &valueCopy, 0, DeepCopy));
			mustReleaseValueCopy = 1;
		}
		else if (DeepCopy && (thisItemValueType == kMoaMmValueType_PropList))
		{
			RE_TryErr(PRegEx_CopyPList_Internal(&thisItemValue, &valueCopy, 0, DeepCopy));
			mustReleaseValueCopy = 1;
		}
		else
		{
			valueCopy = thisItemValue;
			mustReleaseValueCopy = 0;
		}
		
		// Add the value we got to the new list.
		RE_TryMoaOrMem(pMmList->AppendValueToPropList(newList, &thisItemKey, &valueCopy));
			
		// Release the key we got
		RE_MaybeValRelease(&thisItemKey, mustReleaseThisItemKey);
		
		// Release the value we got
		RE_MaybeValRelease(&thisItemValue, mustReleaseThisItemValue);
		
		// Release the copy we made
		RE_MaybeValRelease(&valueCopy, mustReleaseValueCopy);
	}

  LEAVE_FUNCTION:
  
	// Re-check these down here in case of premature exit from the loop.
	RE_MaybeValRelease(&thisItemKey, mustReleaseThisItemKey);
	RE_MaybeValRelease(&thisItemValue, mustReleaseThisItemValue);
	RE_MaybeValRelease(&valueCopy, mustReleaseValueCopy);
	
	return(Err);	
}



//----------------------------------------------------------------------------
// PRegEx_Replace
// PRegEx_ReplaceExec
// 
// A cool, optimized, global replace.
// Note: trades lots of memory to get more speed, but still tries to be careful.
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Replace         (PMoaMmCallInfo callPtr                           ) 
{return(                   PRegEx_Replace_Internal(               callPtr,      0                   ));}

long CREGEXPRESSIONScript::PRegEx_ReplaceExec     (PMoaMmCallInfo callPtr                           )
{return(                   PRegEx_Replace_Internal(               callPtr,      1                   ));}
long CREGEXPRESSIONScript::PRegEx_Replace_Internal(PMoaMmCallInfo callPtr, long execMode            )
{
	long 				Err = REGERR_SUCCESS;
		
	long				TotalArguments = callPtr->nargs;

	MoaMmValue			ReplacePatVal;
	char *				ReplacePatValStrPtr = NULL;
	long				MustReleaseReplacePatValStrPtr = 0;
	long				ReplacePatStrLen = 0;

	MoaMmValue			CallbackReturnVal;
	long				MustReleaseCallbackReturnVal = 0;
	char *				CallbackReturnValStrPtr = NULL;
	long				MustReleaseCallbackReturnValStrPtr = 0;
	long				CallbackReturnValStrLen = 0;
	
	char *				MyReplacePatString = NULL;	// Points to one or the other of the above two.
	long				MyReplacePatLength = 0;		// ditto.
	
	
	char * 				InterpolatedStr = NULL;
	long   				InterpolatedLen = 0;
		
	// State data pertaining to calling the callback function if necessary.
	PRegExCallbackInfo	myPRegExCallbackInfo;			

	long				HadBackRefs = 0;
	
	long				ReplNum = 0;
	
	unsigned long		NewBufferSize = 0;
	char * 				pNewBuffer = NULL;

	
	// This flag means that the replace string won't change on each iteration.
	// It gets set if the ReplPat was found to have no backrefs and we are 
	// not in "exec" mode.
	long				SingleReplaceString = 0;

	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
	
	GlobalReplaceInfo	myGrInfo;			
	RE_TryErr(GlobalReplaceList_Init(&myGrInfo));

	// Push if necessary.
	RE_TryErr(CheckContext());

	// Process initial arguments (and Opts)
	RE_TryErr(Begin_Internal(callPtr));	

	// Allow optional setting of execMode from "e" option (like in Perl)
	execMode = execMode || StateInfo.ExecOption;

	// Validate and prepare replacement argument.
	if (execMode)
	{
		// If in exec mode, validate and prepare to call the callback function.
		RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 4, 0, 5));
	}
	else
	{			
		// Otherwise, in regular mode, get the 4th argument, a string containing ReplPat
		RE_TryAssert(TotalArguments >= 4, REGERR_ReplPatMustBeString);
		GetArgByIndex(4, &ReplacePatVal);
		RE_TryType(&ReplacePatVal, kMoaMmValueType_String, REGERR_ReplPatMustBeString);
    	ReplacePatStrLen = PRegEx_GetStringLengthThroughLingo(&ReplacePatVal);
		RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&ReplacePatVal, (const char **)&ReplacePatValStrPtr));
		MustReleaseReplacePatValStrPtr = 1;
	}
	
	// Enter the replacement loop.
	while ((PRegEx_GetNextMatch_Internal(callPtr, StateInfo.FoundCount > 0, 0) == REGERR_SUCCESS) && (StateInfo.MatchFound))
	{
		// Release things that potentially get allocated on each pass through this loop.
		// Putting these at the top of the loop allows for the safe use of "continue".
		RE_MaybeValRelPntr(&CallbackReturnVal, MustReleaseCallbackReturnValStrPtr);
		RE_MaybeValRelease(&CallbackReturnVal, MustReleaseCallbackReturnVal);

		// Get ReplacePatVal
		if (execMode)
		{
			// In execMode, get the ReplPat string by calling the callback function.  
			// We don't perform any interpolations on the resulting string.
			RE_TryErr(PRegEx_Call_Callback_Exec(& myPRegExCallbackInfo, 
											    & CallbackReturnVal, 
											    & MustReleaseCallbackReturnVal, 
											    1));		
	    	CallbackReturnValStrLen = PRegEx_GetStringLengthThroughLingo(&CallbackReturnVal);
			RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&CallbackReturnVal, (const char **)&CallbackReturnValStrPtr));
			MustReleaseCallbackReturnValStrPtr = 1;

			MyReplacePatString = CallbackReturnValStrPtr;	
			MyReplacePatLength = CallbackReturnValStrLen;	
		}
		else
		{
			// Regular mode.  Get replace string and length by interpolating
			// the value supplied by the caller. 
			if ((StateInfo.FoundCount == 1) || (HadBackRefs))
			{
				// Always run interpolations the first time through.
				// But only re-run them each time through if, on the first run,
				// any back-references were encountered.
				RE_MaybeFreePtr(InterpolatedStr);

				InterpolatedLen 			= Interpolate_Internal((MoaByte *)ReplacePatValStrPtr, ReplacePatStrLen, 
															NULL, 1, 0, NULL, &HadBackRefs);
				RE_TryMem(InterpolatedStr	= (char *)pCalloc->NRAlloc(InterpolatedLen + 1 ));
				InterpolatedLen				= Interpolate_Internal((MoaByte *)ReplacePatValStrPtr, ReplacePatStrLen, 
															(MoaByte *)InterpolatedStr, 1, 0, NULL, &HadBackRefs);
			}
			else
			{
				SingleReplaceString = 1;
			}

			MyReplacePatString = InterpolatedStr;	
			MyReplacePatLength = InterpolatedLen;	
		}
	
		// When "abort"ing,  stop immediately and discard all work to this point.
		if (myPRegExCallbackInfo.CallerRequestsAbort)
		{
			Err = REGERR_CallbackRequestedAbort;
			goto LEAVE_FUNCTION; // ABORT BECAUSE CALLER WANTED US TO
		}	

		// When "stop"ping,  keep all replaces up to this point, but not including current one.
		if (myPRegExCallbackInfo.CallerRequestsStop) {break;}
		
		// The skip flag just means we don't perform this one replacement.
		// It is safe to "continue" because we've moved our per-loop cleanup to the TOP of the loop.
		if (myPRegExCallbackInfo.CallerRequestsSkip) {continue;}

		// Perform/Prepare/Store the replacements, building up a To Do List of pending replacements.
		//
		// Four cases:
		//  - Same lengths:          Just make the replacement.
		//  - Single replace string: Add an entry saying use the same string each time.
		//  - Shorter replacement:   Do replacement into the main buffer.  Add entry saying that's where data is. 
		//  - Longer replacement:    Create temp buffer to hold replacement.  Add temp buffer to the list. 
		{
			if (MyReplacePatLength == StateInfo.EntireMatchLen)
			{
				// Search and replace strings have same length. 
				// Just overwrite data in our buffer.
				// No need to store any info in our pending-replacement list.
				memcpy(&StateInfo.pCurrentString[StateInfo.SearchOffset],MyReplacePatString,MyReplacePatLength);
			}
			else if (SingleReplaceString)
			{
				// If we know we will have a single replace string every time, we simply
				// add a marker to the list saying that when the
				// list is processed, we can copy the same replace string each time.
				// In this case, it doesn't matter yet whether the string
				// will be longer or shorter.
				GlobalReplaceList_Add(&myGrInfo, 
										StateInfo.SearchOffset, 
										StateInfo.EntireMatchLen, 
										(char *)0x00000001,	// 1 means get data from MyReplacePatString each time.
										MyReplacePatLength);
			}
			else if (MyReplacePatLength < StateInfo.EntireMatchLen)
			{
				// The length of replacement data is less than the
				// entire match.  Since there is room in the existing buffer to
				// store the replacement, we do that.  Basically, we're just using our 
				// buffer as temporary storage rather than allocating new storage.
				
				memcpy(&StateInfo.pCurrentString[StateInfo.SearchOffset], MyReplacePatString, MyReplacePatLength);
		
				GlobalReplaceList_Add(&myGrInfo, 
										StateInfo.SearchOffset, 
										StateInfo.EntireMatchLen, 
										NULL, 				// Null means copy data from the original buffer.
										MyReplacePatLength);
			}
			else if (MyReplacePatLength > StateInfo.EntireMatchLen)
			{
				// The amount of replacement data is larger than the amount of space for
				// the entire match so we will need to allocate a temporary buffer for it and store
				// the data there for later processing.
				
				// Make a new buffer big enough to hold the replacement string. 
				char * pReplacement = NULL;
				RE_TryMem(pReplacement = (char *)pCalloc->NRAlloc(MyReplacePatLength));
				
				// Copy the data into it.
				memcpy(pReplacement,MyReplacePatString,MyReplacePatLength);
				
				// Add this item to our list.
				GlobalReplaceList_Add(&myGrInfo, 
										StateInfo.SearchOffset, 
										StateInfo.EntireMatchLen, 
										pReplacement,		// A pointer means use this buffer; later free it.
										MyReplacePatLength);
										
				// The list now "owns" this buffer.
				// It will either be freed as the items in the list are processed,
				// or if still around at that point, during the _Tidy call.
				pReplacement = NULL;
			}
		}
			
		// When "last"ing, keep all replaces up to AND INCLUDING this current one.
		if (myPRegExCallbackInfo.CallerRequestsLast) {break;}

		// If not in global mode, we stop searching after once through the loop.
		if (!StateInfo.GlobalReplaceOption)	{break;}
	}
	
	// Done with searching and building the replacement list.
	
	// Allocate a buffer to hold the new data. 
	// Potential CPT TO DO optimization: don't create new buffer if all replacements are shorter.
	
	NewBufferSize = (StateInfo.CurrentStringLen 
					+ myGrInfo.TotalReplaceLengths 
					- myGrInfo.TotalFoundLengths);
											   
	RE_TryMem(pNewBuffer = (char *)MyMalloc(NewBufferSize));
				
	//pUtils->PrintMessage1("Buffer size before replacement is:  (%d)\n", StateInfo.CurrentStringLen);
	//pUtils->PrintMessage1("Number of replacements pending in list:  (%d)\n", myGrInfo.NumItems);
	//pUtils->PrintMessage1("Amount of allocated space in list:  (%d)\n", myGrInfo.NumItemsAllocated);
	//pUtils->PrintMessage1("New buffer after replacement is:  (%d)\n", NewBufferSize);
	
	// Process the replacement list.
	// Each undone item has one entry in the list.
	// We copy pieces alternately from the unmatched portions of the original string
	// and from the list of replacements, finally copying
	// the leftover part at the end.
	if (1)
	{
		long	PreviousMatchEnd		= 0;	// Pointer in search buffer
		long	ReplacementBufOffset	= 0;	// Pointer in replacement buffer
		long	CopyAmount				= 0;
		
		for (ReplNum = 0; ReplNum < myGrInfo.NumItems; ReplNum++)
		{
			long   ThisFoundStart		= myGrInfo.FoundStarts   [ReplNum];
			long   ThisFoundLength		= myGrInfo.FoundLengths  [ReplNum];
			char * ThisReplaceString	= myGrInfo.ReplaceStrings[ReplNum];
			long   ThisReplaceLength	= myGrInfo.ReplaceLengths[ReplNum];
			
			//pUtils->PrintMessage1("Doing replacement number:  (%d)\n", ReplNum);

			// Copy the part of the input buffer prior to where this
			// Found section began.
			CopyAmount = ThisFoundStart - PreviousMatchEnd;
			memcpy(&pNewBuffer[ReplacementBufOffset], 
				   &StateInfo.pCurrentString[PreviousMatchEnd], 
				   CopyAmount);
			ReplacementBufOffset += CopyAmount;
			
			//pUtils->PrintMessage1("Copied (%d) chars from unmatched...\n", CopyAmount);

			// Remember where this match ended so we know where
			// to begin the next time through the loop, and afterward.
			PreviousMatchEnd = ThisFoundStart + ThisFoundLength;
			
			// Choose the correct replacement string.
			// Case Ptr : data is in ThisReplaceString.
			// Case 1   : data is in MyReplacePatString
			// Case NULL: data is in main buffer.
			MoaByte *                                     DataSource = (MoaByte *)ThisReplaceString;		
			if (ThisReplaceString == (char *)0x00000001) {DataSource = (MoaByte *)MyReplacePatString;}
			if (ThisReplaceString == NULL              ) {DataSource = (MoaByte *)&StateInfo.pCurrentString[ThisFoundStart];}

			// Copy the replacement string.
			CopyAmount = ThisReplaceLength;
			memcpy(&pNewBuffer[ReplacementBufOffset], DataSource, CopyAmount);
			ReplacementBufOffset += CopyAmount;
			
			//pUtils->PrintMessage1("Copied (%d) chars from replacement...\n", CopyAmount);

			// Free the temporary buffer, if any.
			if (myGrInfo.ReplaceStrings[ReplNum] == (char *)0x00000001) {myGrInfo.ReplaceStrings[ReplNum] = NULL;}
			RE_MaybeFreePtr(myGrInfo.ReplaceStrings[ReplNum]);
		}
		
		// Copy the leftover part after the last match up to the end
		// of the search string.
		
		CopyAmount = StateInfo.CurrentStringLen - PreviousMatchEnd;
		memcpy(&pNewBuffer[ReplacementBufOffset], 
			   &StateInfo.pCurrentString[PreviousMatchEnd], 
			   CopyAmount);
		// ReplacementBufOffset += CopyAmount;	// See right below:
		
		//pUtils->PrintMessage1("Copied (%d) chars from end...\n", CopyAmount);

		
		// Adjust pos to reflect the change in position
		// of the end of the final matched/replaced section.
		StateInfo.Pos				 = ReplacementBufOffset;
		
		// The replacement has been made.
		StateInfo.Replaced = 1;
		
		// Free the old buffer.
		RE_MaybeMyFree(StateInfo.pCurrentString);

		// Retain the new buffer.  This persists until ClearInternalState.
		StateInfo.pCurrentString	 = pNewBuffer;  pNewBuffer = NULL;	// Caller now owns.
		StateInfo.CurrentStringLen	 = NewBufferSize;	
		
		// Put the replacement buffer back into the (caller's) list.
		RE_TryErr(ReplaceBufferBackToCallersList());
	}

	
LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{
		pMmValue->IntegerToValue(StateInfo.FoundCount, &callPtr->resultValue);
	}
	else
	{
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	RE_MaybeMyFree(pNewBuffer);
	
	RE_MaybeFreePtr(InterpolatedStr);

	RE_MaybeValRelPntr(&CallbackReturnVal, MustReleaseCallbackReturnValStrPtr);
	RE_MaybeValRelease(&CallbackReturnVal, MustReleaseCallbackReturnVal);
	
	RE_MaybeValRelPntr(&ReplacePatVal, 	   MustReleaseReplacePatValStrPtr);
	
	if (execMode)
	{
		PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);
	}
	
	GlobalReplaceList_Tidy(&myGrInfo);

	if (Err != REGERR_SUCCESS)
	{
		// Some error (possibly an abort) made us fail partway through.
		// Back out any partial changes to the in-memory buffer by
		// re-copying the value from the SrchStrL, which we will not yet
		// have overwritten due to the error signal.
		
		CallersListBackToReplaceBuffer();	// Don't trap Err on this!
		ClearBackReferenceInformation();	// Don't trap Err on this!
	}

	return(Err);	
}


//----------------------------------------------------------------------------
// GlobalReplaceList_Init
// GlobalReplaceList_Add
// GlobalReplaceList_Tidy
//
// Helper functions for PRegEx_Replace_Internal.
//
// These three calls maintain the internal data structures that hold lists of pending
// replacements as needed by PRegEx_Replace_Internal.
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::GlobalReplaceList_Init(PGlobalReplaceInfo GrInfo)
{
	long Err = REGERR_SUCCESS;
	
	// Set all fields to zero/null
	memset(GrInfo, 0, sizeof(GlobalReplaceInfo));
	
	// Set an arbitrary initial size (2 or 3 is best)
	GrInfo->NumItemsAllocated = 3;
	
	// Allocate buffers of that size.
	RE_TryMem(GrInfo->FoundStarts		= (long *) pCalloc->NRAlloc(GrInfo->NumItemsAllocated * sizeof(long  )));
	RE_TryMem(GrInfo->FoundLengths		= (long *) pCalloc->NRAlloc(GrInfo->NumItemsAllocated * sizeof(long  )));
	RE_TryMem(GrInfo->ReplaceStrings	= (char **)pCalloc->NRAlloc(GrInfo->NumItemsAllocated * sizeof(char *)));
	RE_TryMem(GrInfo->ReplaceLengths	= (long *) pCalloc->NRAlloc(GrInfo->NumItemsAllocated * sizeof(long  )));
		
LEAVE_FUNCTION:

	if (Err != REGERR_SUCCESS)
	{
		RE_MaybeFreePtr(GrInfo->FoundStarts);
		RE_MaybeFreePtr(GrInfo->FoundLengths);
		RE_MaybeFreePtr(GrInfo->ReplaceStrings);
		RE_MaybeFreePtr(GrInfo->ReplaceLengths);

		GrInfo->NumItemsAllocated = 0;
	}
	
	return(Err);
}

long CREGEXPRESSIONScript::GlobalReplaceList_Add(PGlobalReplaceInfo GrInfo, long FoundStart, long FoundLength, 
             																char * ReplaceString, long ReplaceLength)
{
	long Err = REGERR_SUCCESS;
	
	long * 			FoundStarts		= NULL;
	long *			FoundLengths	= NULL;
	char **			ReplaceStrings	= NULL;
	long *			ReplaceLengths	= NULL;

	long			ProposedNewNumber = GrInfo->NumItems + 1;
	
	// If we need to lengthen the buffers, we double their size each time.
	// This guarantees no more than, say, 12 reallocations, even for a huge search/replace.  (3 * 2^12 = 12,000 items)
	if (ProposedNewNumber > GrInfo->NumItemsAllocated)
	{
		long	NewAllocCount = GrInfo->NumItemsAllocated * 2;

		// Allcate new buffers, stored in temporary variables.
		RE_TryMem(FoundStarts		= (long *) pCalloc->NRAlloc(NewAllocCount * sizeof(long  )));
		RE_TryMem(FoundLengths		= (long *) pCalloc->NRAlloc(NewAllocCount * sizeof(long  )));
		RE_TryMem(ReplaceStrings	= (char **)pCalloc->NRAlloc(NewAllocCount * sizeof(char *)));
		RE_TryMem(ReplaceLengths	= (long *) pCalloc->NRAlloc(NewAllocCount * sizeof(long  )));
		
		// If it worked, copy any existing items into the temporary buffers.
		memcpy(&(FoundStarts[0]),		&(GrInfo->FoundStarts[0]), 		(GrInfo->NumItems * sizeof(long  )));
		memcpy(&(FoundLengths[0]),		&(GrInfo->FoundLengths[0]), 	(GrInfo->NumItems * sizeof(long  )));
		memcpy(&(ReplaceStrings[0]),	&(GrInfo->ReplaceStrings[0]), 	(GrInfo->NumItems * sizeof(char *)));
		memcpy(&(ReplaceLengths[0]),	&(GrInfo->ReplaceLengths[0]), 	(GrInfo->NumItems * sizeof(long  )));
		
		// Then deallocate the existing buffers...
		RE_MaybeFreePtr(GrInfo->FoundStarts);
		RE_MaybeFreePtr(GrInfo->FoundLengths);
		RE_MaybeFreePtr(GrInfo->ReplaceStrings);
		RE_MaybeFreePtr(GrInfo->ReplaceLengths);
		
		// Then move the newly-allocated buffers into the structure, replacing
		// the now-deallocated pointers to the old ones.
		GrInfo->FoundStarts			= FoundStarts;
		GrInfo->FoundLengths		= FoundLengths;
		GrInfo->ReplaceStrings		= ReplaceStrings;
		GrInfo->ReplaceLengths		= ReplaceLengths;
		
		// Empty these variables because the buffers they pointed to 
		// are now "owned" by the main data structure.
		FoundStarts		= NULL;
		FoundLengths	= NULL;
		ReplaceStrings	= NULL;
		ReplaceLengths	= NULL;

		// Save new allocation size.
		GrInfo->NumItemsAllocated = NewAllocCount;
	}
	
	// Bump the number of items (we are now certain to have the room).
	GrInfo->NumItems = ProposedNewNumber;
	
	// Add the caller's latest set of items to the lists.
	GrInfo->FoundStarts		[GrInfo->NumItems - 1] = FoundStart;
	GrInfo->FoundLengths	[GrInfo->NumItems - 1] = FoundLength;
	GrInfo->ReplaceStrings	[GrInfo->NumItems - 1] = ReplaceString;
	GrInfo->ReplaceLengths	[GrInfo->NumItems - 1] = ReplaceLength;

	// Aggregate all the size changes represented by all replacements
	// present in this list.
	GrInfo->TotalFoundLengths 	+= FoundLength;
	GrInfo->TotalReplaceLengths += ReplaceLength;
	GrInfo->HaveLengtheningReplaces = GrInfo->HaveLengtheningReplaces || (ReplaceLength > FoundLength);
	
LEAVE_FUNCTION:
	
	// If any of these got allocated, free them.
	RE_MaybeFreePtr(FoundStarts);
	RE_MaybeFreePtr(FoundLengths);
	RE_MaybeFreePtr(ReplaceStrings);
	RE_MaybeFreePtr(ReplaceLengths);
	
	return(Err);
}

void CREGEXPRESSIONScript::GlobalReplaceList_Tidy(PGlobalReplaceInfo GrInfo)
{
	// IMPORTANT!  We assume our owner has set to NULL or -1 any 
	// ReplaceStrings that have already been deallocated or that
	// are not stored here in this list.
	
	// Any that remain, we must deallocate now.
	
	long itemNum;
	for (itemNum = 0; itemNum < GrInfo->NumItems; itemNum++)
	{
		if (GrInfo->ReplaceStrings[itemNum] != NULL      && 		// NULL means data is stored in main buffer.
		    GrInfo->ReplaceStrings[itemNum] != (char *)0x00000001)	// 0x00000001 means use same replace string each time.
		{
			pCalloc->NRFree(GrInfo->ReplaceStrings[itemNum]      );
		     	            GrInfo->ReplaceStrings[itemNum] = NULL;
		}
	}

	// Deallocate all buffers owned by this structure.
	RE_MaybeFreePtr(GrInfo->FoundStarts);
	RE_MaybeFreePtr(GrInfo->FoundLengths);
	RE_MaybeFreePtr(GrInfo->ReplaceStrings);
	RE_MaybeFreePtr(GrInfo->ReplaceLengths);
		
	// Set all fields to zero.
	memset(GrInfo, 0, sizeof(GlobalReplaceInfo));
}



//----------------------------------------------------------------------------
// PRegEx_CallHandler
//
// 
//
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_CallHandler(PMoaMmCallInfo callPtr)
{
	long Err = REGERR_SUCCESS;
	
	long TotalArguments = callPtr->nargs;

	// State data pertaining to calling the callback function if necessary.
	PRegExCallbackInfo	myPRegExCallbackInfo;
				
	MoaMmValue			CallbackReturnValue;
	long				MustReleaseCallbackReturnValue = 0;

	InitPPRegExCallbackInfo	(&myPRegExCallbackInfo);
	
	PMoaMmValue			ArgList1ValuePtr = NULL;

	// Get the value passed in ArgList1 (which is our argument position #2), if any.
	if (TotalArguments >= 2)
	{
		MoaMmValue			ArgList1Value;
		GetArgByIndex (2,  &ArgList1Value);
		ArgList1ValuePtr = &ArgList1Value;
	}
	
	// Parse arguments and get ready to call the callback funct.
	RE_TryErr(PRegEx_Call_Callback_Prep(callPtr, &myPRegExCallbackInfo, 1, ArgList1ValuePtr, 3));

	RE_TryErr(PRegEx_Call_Callback_Exec(& myPRegExCallbackInfo, 
									    & CallbackReturnValue, 
									    & MustReleaseCallbackReturnValue,
									    0));
	
	// Return the return value, if any.
	
	if (MustReleaseCallbackReturnValue)
	{
		callPtr->resultValue = CallbackReturnValue;
		MustReleaseCallbackReturnValue = 0; // Returning something takes us off the hook for releasing a reference to it.
	}

	// Preserve the otherwise-unpreserved Abort/Last/Stop flags for our
	// caller to check if desired (normally the internal callback routines always arrange to
	// re-set these globals to zero when the callback is over; on the assumption that the
	// C-language function can check them from the callbackinfo record and then act.
	// In this case, we're relying on anyone using this routine from Lingo 
	// to check and then re-set these flags if there
	// is any chance the callback routine might have tried to set them.
	
	StateInfo.CallbackAbort = myPRegExCallbackInfo.CallerRequestsAbort;
	StateInfo.CallbackStop  = myPRegExCallbackInfo.CallerRequestsStop;
	StateInfo.CallbackSkip  = myPRegExCallbackInfo.CallerRequestsSkip;
	StateInfo.CallbackLast  = myPRegExCallbackInfo.CallerRequestsLast;
	
LEAVE_FUNCTION:

	// Checking again here becuase it's the right thing to do.
	RE_MaybeValRelease(&CallbackReturnValue, MustReleaseCallbackReturnValue);
	
	// Call the callback cleanup routine.
	PRegEx_Call_Callback_Tidy(&myPRegExCallbackInfo);

	// This routine is supposed to return the value of calling the callback function.
	// But what if there was a failure?  We return void because this is likely to be the
	// least in conflict with any legitimate return values (which, depending on the application, 
	// could include negative numbers which are indistinguishable from error codes.  
	// So in event of failre, we'll return void but we'll set Err, so it can be checked
	// afterwards, and if ErrorsToMessageWindow is turned on, they'll see that message, too.
	
	if (Err != REGERR_SUCCESS)
	{
		// pMmValue->IntegerToValue(Err,&callPtr->resultValue); // Do not return error code.
	}

	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_ReadEntireFile
// PRegEx_WriteEntireFile
// 
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_ReadEntireFile(PMoaMmCallInfo callPtr)
{
	long Err 				 = REGERR_SUCCESS;
	
	MoaMmValue		UnResolvedPath;
	char *			UnResolvedPathPtr = NULL;
	long			MustReleaseUnResolvedPathPtr = 0;
	
	char * 			pTempMem = NULL;
	MoaMmValue		FileBufVal;
	char *			FileBufValStringPtr = 0;
	long			MustReleaseFileBufVal = 0;
	long			MustReleaseFileBufValStringPtr = 0;

	unsigned long	FileSize = 0;
    
	long			FileOpened = 0;
	
	PIMoaPathName 	PathNameObj = NULL;
	PIMoaFile2		FileObj = NULL;
	PIMoaStream2	StreamObj = NULL;
	
	unsigned long	bytesRead = 0;
	
	MoaMmValue		resultList;
	long			MustReleaseResultList = 0;
	
	MoaMmValue		BytesReadValue;
	long			MustReleaseBytesReadValue = 0;
	
	long			HasNulls = 0;
	MoaMmValue		HasNullsValue;
	long			MustReleaseHasNullsValue = 0;
	
	long TotalArguments = callPtr->nargs;
	
	// Get unresolved path name from first argument.
	RE_TryAssert(TotalArguments >= 1, REGERR_ExpectedStringArgument);
	GetArgByIndex(1, &UnResolvedPath);
	RE_TryType(&UnResolvedPath, kMoaMmValueType_String, REGERR_ExpectedStringArgument);
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&UnResolvedPath, (const char **)&UnResolvedPathPtr));
	MustReleaseUnResolvedPathPtr = 1;

	// Make a Moa PathName object to hold it.
    RE_TryMoaOrMem((pCallback->MoaCreateInstance(&CLSID_CMoaPath, &IID_IMoaPathName,(PPMoaVoid)&PathNameObj)));
	RE_TryMoaOrErr((PathNameObj->InitFromString(UnResolvedPathPtr, kMoaPathDialect_LOCAL, 1, 0)), REGERR_FileNotFound);

	// Make a file object from the path object.
	char ResolvedPath[MOA_MAX_PATHNAME];
	RE_TryMoaOrErr((PathNameObj->GetPath(ResolvedPath, MOA_MAX_PATHNAME)), REGERR_FileNotFound);
    RE_TryMoaOrMem((pCallback->MoaCreateInstance(&CLSID_CMoaFile2, &IID_IMoaFile2, (PPMoaVoid)&FileObj)));
	RE_TryMoaOrMem((FileObj->SetPathName(PathNameObj)));
	
	// See if the file exists and get its size.
	RE_TryAssert((FileObj->IsExisting()), REGERR_FileNotFound);
	RE_TryMoaOrErr((FileObj->GetSize(&FileSize)), REGERR_FileNotFound);

	// Create a temporary buffer to initialize a value of the right size.
	RE_TryMem(pTempMem = (char *)pCalloc->NRAlloc(FileSize+1));

	// Set the Buffer to some non-zero character except for the trailing NULL.
	memset(pTempMem,'A',FileSize);
	pTempMem[FileSize] = 0;

	// Convert the Buffer to a MoaMmValue
	RE_TryMoaOrMem(pMmValue->StringToValue(pTempMem,&FileBufVal));
	MustReleaseFileBufVal = 1;
	
	RE_MaybeFreePtr(pTempMem);
	
	// Now get a Ptr that we can copy the desired string data into (which may contain NULs).
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&FileBufVal, (const char **)&FileBufValStringPtr));
	MustReleaseFileBufValStringPtr = 1;
	
	// Get a stream object from the file object and use it to open the file.
	RE_TryMoaOrErr((FileObj->GetStream(1024, &StreamObj)), REGERR_FileNotFound);
	RE_TryMoaOrErr((StreamObj->Open(kMoaStreamOpenAccess_ReadOnly, kMoaStreamSetPositionType_None)), REGERR_ErrorOpeningFile);
	FileOpened = 1;

	// Now we can read the entire file into the big buffer we created.
	RE_TryMoaOrErr((StreamObj->Read(FileBufValStringPtr, FileSize, &bytesRead)), REGERR_ErrorReadingFile);
	
	// Make sure we got all the bytes we had planned.
	RE_TryAssert(bytesRead == FileSize, REGERR_ErrorReadingFile);
	
	// Allocate a new temporary list.
	RE_TryMoaOrMem((pMmList->NewListValue(&resultList)));
	MustReleaseResultList = 1;

	// Place the current string argument into the list 
	RE_TryMoaOrMem((pMmList->AppendValueToList(&resultList, &FileBufVal)));
	
	// Add a second item: the length of the data (fileSize)
	RE_TryMoaOrMem((pMmValue->IntegerToValue(bytesRead, &BytesReadValue)));
	MustReleaseBytesReadValue = 1;
	RE_TryMoaOrMem((pMmList->AppendValueToList(&resultList, &BytesReadValue)));
	
	// Add a third item: the length of the data (fileSize)
	HasNulls = (strlen(FileBufValStringPtr) < FileSize);
	RE_TryMoaOrMem((pMmValue->IntegerToValue(HasNulls, &HasNullsValue)));
	MustReleaseHasNullsValue = 1;
	RE_TryMoaOrMem((pMmList->AppendValueToList(&resultList, &HasNullsValue)));
	
LEAVE_FUNCTION:

	if (FileOpened)		StreamObj->Close();
	
	if (StreamObj) 		StreamObj->Release();
	if (FileObj) 		FileObj->Release();
	if (PathNameObj)	PathNameObj->Release();

	RE_MaybeValRelease(&HasNullsValue, MustReleaseHasNullsValue);
	RE_MaybeValRelease(&BytesReadValue, MustReleaseBytesReadValue);
	RE_MaybeValRelPntr(&FileBufVal, MustReleaseFileBufValStringPtr);
	RE_MaybeValRelease(&FileBufVal, MustReleaseFileBufVal);	
	RE_MaybeValRelPntr(&UnResolvedPath, MustReleaseUnResolvedPathPtr);

	RE_MaybeFreePtr(pTempMem);
	
	if (Err == REGERR_SUCCESS)
	{
		// Return the result list.
		callPtr->resultValue = resultList;	// Don't release because caller now owns.
		MustReleaseResultList = 0;
	}
	else
	{
		// Free the result list because we won't be passing it back.
		RE_MaybeValRelease(&FileBufVal, MustReleaseResultList);	
		// Return an error code.
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	return(Err);
}

long CREGEXPRESSIONScript::PRegEx_WriteEntireFile(PMoaMmCallInfo callPtr)
{
	long Err 				 = REGERR_SUCCESS;
	
	MoaMmValue		UnResolvedPath;
	char *			UnResolvedPathPtr = NULL;
	long			MustReleaseUnResolvedPathPtr = 0;
	
	MoaMmValue		StringBufferListValue;
	MoaMmValueType	StringBufferListValueType = 0;
	
	MoaMmValue		FileBufVal;
	MoaMmValueType	FileBufValType = 0;
	char *			FileBufValStringPtr = 0;
	long			MustReleaseFileBufVal = 0;
	long			MustReleaseFileBufValStringPtr = 0;

	MoaMmValue		LengthIntValue;
	MoaMmValueType	LengthIntValueType = 0;
	long			MustReleaseLengthIntValue = 0;
	
	long			DefaultFileBufferLength = 0;
	unsigned long	FileBufferLength = 0;
    
	long			FileOpened = 0;
	long			FileCreated = 0;
	
	PIMoaPathName 	PathNameObj = NULL;
	PIMoaFile2		FileObj = NULL;
	PIMoaStream2	StreamObj = NULL;
	
	unsigned long	bytesWritten = 0;
		
	char			FileNameAlone[MOA_MAX_PATHNAME] = "";

	long			TotalArguments = callPtr->nargs;

	long			itemCount = 0;
	
	// Get the first argument, a string name of the path to be written.

	RE_TryAssert((TotalArguments >= 1), REGERR_ExpectedStringArgument);
	GetArgByIndex(1, &UnResolvedPath);
	RE_TryType(&UnResolvedPath, kMoaMmValueType_String, REGERR_ExpectedStringArgument);

	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&UnResolvedPath, (const char **)&UnResolvedPathPtr));
	MustReleaseUnResolvedPathPtr = 1;

	// Get the second argument: a "String Buffer" object -- a list (required) 
	// containing a string (required) plus a length integer (optional).
	
	RE_TryAssert((TotalArguments >= 2), REGERR_SearchStrLMustBeList);
	GetArgByIndex(2, &StringBufferListValue);
	RE_TryType(&StringBufferListValue, kMoaMmValueType_List, REGERR_SearchStrLMustBeList);
	
	itemCount = pMmList->CountElements(&StringBufferListValue);
	
	// Get the string buffer (element 1) from the String Buffer list.
	RE_TryAssert((itemCount >= 1), REGERR_SearchStrLMustContainString);

	RE_TryMoaOrMem(pMmList->GetValueByIndex(&StringBufferListValue, 1,  &FileBufVal));
	MustReleaseFileBufVal = 1;
	RE_TryType(&FileBufVal, kMoaMmValueType_String, REGERR_SearchStrLMustContainString);
	
	// Initialize the file buffer length by using Lingo to get the actual length.
	DefaultFileBufferLength = PRegEx_GetStringLengthThroughLingo(&FileBufVal);
	FileBufferLength = 0;
	
	// Get the optional length argument from the String Buffer list.
	// If absent, get the length from Lingo
	if (itemCount < 2)
	{
		FileBufferLength = DefaultFileBufferLength;
	}
	else
	{
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&StringBufferListValue, 2,  &LengthIntValue));
		MustReleaseLengthIntValue = 1;
		RE_TryType(&LengthIntValue, kMoaMmValueType_Integer, REGERR_SearchStrLLengthArgMustBeInteger);
		
		// Get the value of FileBufferLength and limit it to reasonable bounds:
		// no smaller than zero and no long than Lingo reports as the actual
		// length of the string.
		pMmValue->ValueToInteger(&LengthIntValue, (long *)&FileBufferLength);
		FileBufferLength = __max(0, (long)FileBufferLength);
		FileBufferLength = __min((long)FileBufferLength, DefaultFileBufferLength);
	}
	
	// We have now collected and validated all incoming arguments as
	// being in the correct format.
	
	// Next step is to validate the path name and get ready to create the file.
	
	// First see if the parent directory exists.  It's an error if it does not.
	
	// Create an as-yet UNRESOLVED path name object corresponding to the argument the
	// caller provided.
    RE_TryMoaOrMem((pCallback->MoaCreateInstance(&CLSID_CMoaPath, &IID_IMoaPathName,(PPMoaVoid)&PathNameObj)));
	RE_TryMoaOrErr((PathNameObj->InitFromString(UnResolvedPathPtr, kMoaPathDialect_LOCAL, 0, 0)), REGERR_DirNotFound);
		
	// Remove the final component, which is presumably the name of the file.
	RE_TryMoaOrErr((PathNameObj->RemoveFinal()), REGERR_DirNotFound);
		
	// Get the path string corresponding to the path with the element removed.
	char ParentDirRelPath[MOA_MAX_PATHNAME];
	RE_TryMoaOrErr((PathNameObj->GetPath(ParentDirRelPath, MOA_MAX_PATHNAME)), REGERR_DirNotFound);
	
	// Resolve it.  Fail if the directory (minus the final component) does not exist.
	RE_TryMoaOrErr((PathNameObj->Resolve(0)), REGERR_DirNotFound);

	// Subtract the shortened path from the original path to yield
	// the file name alone.
	strcpy(FileNameAlone, UnResolvedPathPtr + strlen(ParentDirRelPath) + 1);
		 
	// Make sure the file name has a reasonable length.
	RE_TryAssert((FileNameAlone[0] != 0 && strlen(FileNameAlone) <= 31), REGERR_ErrorWritingFile);

	// Add the file name back onto the now-resolved parent directory path.
	RE_TryMoaOrErr((PathNameObj->AddFinal(FileNameAlone)), REGERR_DirNotFound);

	// Get the resolved full path.
	char ResolvedPath[MOA_MAX_PATHNAME];
	RE_TryMoaOrErr((PathNameObj->GetPath(ResolvedPath, MOA_MAX_PATHNAME)), REGERR_FileNotFound);

	// Make a file object whose path is the one we've built.
    RE_TryMoaOrMem((pCallback->MoaCreateInstance(&CLSID_CMoaFile2, &IID_IMoaFile2, (PPMoaVoid)&FileObj)));
	RE_TryMoaOrMem((FileObj->SetPathName(PathNameObj)));

	// Now get a Ptr that we can copy the desired string data from (which may contain nulls).
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&FileBufVal, (const char **)&FileBufValStringPtr));
	MustReleaseFileBufValStringPtr = 1;
	
	// Create the file.
	RE_TryMoaOrErr((FileObj->CreateFile()), REGERR_ErrorOpeningFile);
	FileCreated = 1;
	
	// Get a stream object that can write to this file.
	RE_TryMoaOrErr((FileObj->GetStream(1024, &StreamObj)), REGERR_FileNotFound);

	// Open the file.
	RE_TryMoaOrErr((StreamObj->Open(kMoaStreamOpenAccess_WriteOnly, kMoaStreamSetPositionType_None)), REGERR_ErrorOpeningFile);
	FileOpened = 1;

	// Now we can write the entire file from the big buffer.
	RE_TryMoaOrErr((StreamObj->Write(FileBufValStringPtr, FileBufferLength, &bytesWritten)), REGERR_ErrorWritingFile);
	
	// Make sure we wrote all the bytes we had planned to.
	RE_TryAssert((bytesWritten == FileBufferLength), REGERR_ErrorWritingFile);
	
	// Can move this line to any point to test failure behavior.
	// long Test_Failure = 0; if (Test_Failure) {Err = REGERR_UnexpectedInternalError; goto LEAVE_FUNCTION;}
	
	// Close it.
	RE_TryMoaOrErr((StreamObj->Close()), REGERR_ErrorWritingFile);
	FileOpened = 0;	
	
LEAVE_FUNCTION:

	if (FileOpened)		StreamObj->Close();
	
	// If we terminated due to an error after creating the file, we delete it, or try anyway.
	// Don't want any partially-written files hanging around.
	if (FileCreated && (Err != REGERR_SUCCESS))
	{
		FileObj->Delete();
	}
	
	if (StreamObj) 		StreamObj->Release();
	if (FileObj) 		FileObj->Release();
	if (PathNameObj)	PathNameObj->Release();

	RE_MaybeValRelPntr(&FileBufVal, MustReleaseFileBufValStringPtr);
	RE_MaybeValRelease(&FileBufVal, MustReleaseFileBufVal);	
	RE_MaybeValRelease(&LengthIntValue, MustReleaseLengthIntValue);	
	RE_MaybeValRelPntr(&UnResolvedPath, MustReleaseUnResolvedPathPtr);

	if (Err == REGERR_SUCCESS)
	{
		// Return bytesWritten to indicate success (could be zero).
		pMmValue->IntegerToValue(bytesWritten, &callPtr->resultValue);
	}
	else
	{
		// Return an error code.
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	return(Err);
}

//----------------------------------------------------------------------------
// PRegEx_Keys / PRegEx_Values / PRegEx_PListToList[Strings]
//
// Return / append a list of the keys and/or values in an SPList.
//
// Internal "Mode" means: 2: keys AND values; 1: Keys only, 0: Values only
//
// Internal "KeysToStrings:" means convert any keys that are type
// "Symbol" to strings before adding to the list.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_PListToList        (PMoaMmCallInfo callPtr                   )
{return(				   PRegEx_KeysValues_Internal(               callPtr,	  2,         0));}
long CREGEXPRESSIONScript::PRegEx_PListToListStrings (PMoaMmCallInfo callPtr                   )
{return(				   PRegEx_KeysValues_Internal(               callPtr,	  2,         1));}
long CREGEXPRESSIONScript::PRegEx_Keys               (PMoaMmCallInfo callPtr                   )
{return(				   PRegEx_KeysValues_Internal(               callPtr,	  1,         0));}
long CREGEXPRESSIONScript::PRegEx_Values             (PMoaMmCallInfo callPtr                   )
{return(				   PRegEx_KeysValues_Internal(               callPtr,      0,         0));}
long CREGEXPRESSIONScript::PRegEx_KeysValues_Internal(PMoaMmCallInfo callPtr, long Mode, long KeysToStrings)
{
	long			Err = REGERR_SUCCESS;

	long			TotalArguments = callPtr->nargs;
	MoaMmValue		IncomingList;
	MoaMmValue		ReturnList;
	long			MustReleaseReturnList = 0;

	MoaMmValue		KeyValue;
	MoaMmValue		ValueValue;
	long			MustReleaseKeyValue = 0;
	long			MustReleaseValueValue = 0;

	MoaMmValue		SymStringValue;
	long			MustReleaseSymStringValue = 0;

	// Get caller's PList from arg 1
	RE_TryErr(PRegEx_GetRequiredIncomingListArg(callPtr, 1, 1, &IncomingList));

	// Get new list or list optionally passed by caller in arg 2.
	RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 2, 0, &ReturnList, &MustReleaseReturnList));
	
	// Iterate over list, copying all keys or values.
	{
		long numItems = pMmList->CountElements(&IncomingList);
		long itemNum;
		for (itemNum = 1; itemNum <= numItems; itemNum++)
		{
			// Release items that may be allocated during loop.
			RE_MaybeValRelease(&KeyValue      , MustReleaseKeyValue      );
			RE_MaybeValRelease(&ValueValue    , MustReleaseValueValue    );
			RE_MaybeValRelease(&SymStringValue, MustReleaseSymStringValue);

			if ((Mode == 2) || 
				(Mode == 1)   )
			{
				// Add this key to the list, optionally converting symbol to a string first.
				RE_TryMoaOrMem(pMmList->GetPropertyNameByIndex(&IncomingList, itemNum,  &KeyValue));   MustReleaseKeyValue = 1;
				if (KeysToStrings)	// In KeysToStrings mode, we check to see if key is a symbol.
				{
					MoaMmValueType	KeyValueType = 0;
					pMmValue->ValueType(&KeyValue,&KeyValueType);
					if (KeyValueType == kMoaMmValueType_Symbol) // If so, we convert to a string or fail trying.
					{
						char			mySymString[256];
						MoaMmSymbol		mySymbol = 0;
						RE_TryMoaOrMem(pMmValue->ValueToSymbol(&KeyValue, &mySymbol                               ));
						RE_TryMoaOrMem(pMmValue->SymbolToString(           mySymbol,  mySymString, 256            ));
						RE_TryMoaOrMem(pMmValue->StringToValue (                      mySymString, &SymStringValue));
						MustReleaseSymStringValue = 1;
					}
				}
				RE_TryMoaOrMem(pMmList->AppendValueToList     (&ReturnList,             (MustReleaseSymStringValue ? 
																						 &SymStringValue :
																						 &KeyValue)));			
			}
			if ((Mode == 2) || 
				(Mode == 0)   )
			{
				// Add this value to the list.
				RE_TryMoaOrMem(pMmList->GetValueByIndex       (&IncomingList, itemNum,  &ValueValue)); MustReleaseValueValue = 1;
				RE_TryMoaOrMem(pMmList->AppendValueToList     (&ReturnList,             &ValueValue));			
			}
		}
	}

 LEAVE_FUNCTION:
	
	if (Err == REGERR_SUCCESS)	 
	{
		// Return the list.  Add a reference if we're returning the caller's own list.
		if (!MustReleaseReturnList) pMmValue->ValueAddRef(&ReturnList);
		callPtr->resultValue =                             ReturnList;
		// Caller now owns return list.
		MustReleaseReturnList = 0;
	}
	else                         
	{
		// Return an error code. 
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
		// Allow ReturnList to be released if we created one and we're not returning it.
	}
	
	RE_MaybeValRelease(&KeyValue      , MustReleaseKeyValue      );
	RE_MaybeValRelease(&ValueValue    , MustReleaseValueValue    );
	RE_MaybeValRelease(&SymStringValue, MustReleaseSymStringValue);
	RE_MaybeValRelease(&ReturnList    , MustReleaseReturnList    );
	
	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_ListToSPList[Sym]
//
// Converts a regular list into a PList by pairwise adding all
// elements into a hash, optionally converting string-format keys into
// symbols as it goes.
//
// If an odd element is left over at the end, then it will become a
// key and its value will be "void".
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_ListToSPList         (PMoaMmCallInfo callPtr                 )
{return(				   PRegEx_ListToSPList_Internal(               callPtr,      0        ));}
long CREGEXPRESSIONScript::PRegEx_ListToSPListSym      (PMoaMmCallInfo callPtr                 )
{return(				   PRegEx_ListToSPList_Internal(               callPtr,      1        ));}
long CREGEXPRESSIONScript::PRegEx_ListToSPList_Internal(PMoaMmCallInfo callPtr, long SymbolMode)
{
	long			Err = REGERR_SUCCESS;

	long			TotalArguments = callPtr->nargs;
	MoaMmValue		IncomingList;
	MoaMmValue		ReturnList;
	long			MustReleaseReturnList = 0;

	MoaMmValue		KeyValue;
	MoaMmValue		ValueValue;
	long			MustReleaseKeyValue = 0;
	long			MustReleaseValueValue = 0;

	// Get caller's List from arg 1
	RE_TryErr(PRegEx_GetRequiredIncomingListArg(callPtr, 1, 0, &IncomingList));

	// Get new PList optionally passed by caller in arg 2.
	RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 2, 1, &ReturnList, &MustReleaseReturnList));
	
	// Mark outgoing PList as sorted whether it was the caller's or ours.
	RE_TryErr(PRegEx_SortListThroughLingo(&ReturnList));

	// Iterate over list, copying all keys or values.
	{
		long numItems = pMmList->CountElements(&IncomingList);
		long itemNum;
		for (itemNum = 1; itemNum <= numItems; itemNum++)
		{
			if (itemNum % 2 == 1)	// Odd-numbered item: it's a key.
			{
				RE_TryMoaOrMem(pMmList->GetValueByIndex       (&IncomingList, itemNum,  &KeyValue)); MustReleaseKeyValue = 1;
			}
			else // Even-numbered item: it's a value.
			{
				RE_TryMoaOrMem(pMmList->GetValueByIndex       (&IncomingList, itemNum,  &ValueValue)); MustReleaseValueValue = 1;
				
				// We now have a matching key/value pair.  Add to the list.
				RE_TryErr(SetAProp(&ReturnList, &KeyValue,  &ValueValue, SymbolMode));

				RE_MaybeValRelease(&KeyValue      , MustReleaseKeyValue      );
				RE_MaybeValRelease(&ValueValue    , MustReleaseValueValue    );
			}
		}

		// If we have an odd key left over at the end, add it, with "void".
		if (MustReleaseKeyValue)
		{
			RE_TryErr(SetAProp(&ReturnList, &KeyValue,  &StateInfo.ARandomVoidValue, SymbolMode));
		}
	}

 LEAVE_FUNCTION:
	
	
	if (Err == REGERR_SUCCESS)	 
	{
		// Return the list.  Add a reference if we're returning the caller's own list.
		if (!MustReleaseReturnList) pMmValue->ValueAddRef(&ReturnList);
		callPtr->resultValue =                             ReturnList;
		// Caller now owns return list.
		MustReleaseReturnList = 0;
	}
	else                         
	{
		// Return an error code. 
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
		// Allow ReturnList to be released if we created one and we're not returning it.
	}
	
	RE_MaybeValRelease(&KeyValue      , MustReleaseKeyValue      );
	RE_MaybeValRelease(&ValueValue    , MustReleaseValueValue    );
	RE_MaybeValRelease(&ReturnList    , MustReleaseReturnList    );
	
	return(Err);
}


//----------------------------------------------------------------------------
// GetSlice / SetSlice
//
// Get: a List or PList, plus a regular list of item numbers or keys,
// retrieves those items from the List or PList, and appends them to a
// new list or InitList supplied by caller, and returns the modified
// list.
//
// Set: Sets those values from a list provided in argument 3.  For
// convenience, returns the list that the caller provided in argument
// 1.
//----------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_GetSlice            (PMoaMmCallInfo callPtr              )
{return(				   PRegEx_GetSetSlice_Internal(               callPtr,	   0      ));}
long CREGEXPRESSIONScript::PRegEx_SetSlice            (PMoaMmCallInfo callPtr               )
{return(				   PRegEx_GetSetSlice_Internal(               callPtr,      1      ));}
long CREGEXPRESSIONScript::PRegEx_GetSetSlice_Internal(PMoaMmCallInfo callPtr, long SetMode)
{
	long			Err = REGERR_SUCCESS;

	long			TotalArguments = callPtr->nargs;
	MoaMmValue		IncomingList;

	MoaMmValue		KeysList;
	MoaMmValue		ValuesList;

	MoaMmValue		ReturnList;
	long			MustReleaseReturnList = 0;
	long			HaveCallersReturnList = 0;

	MoaMmValue		ValueValue;
	long			MustReleaseValueValue = 0;

	MoaMmValue		IndexValue;
	long			MustReleaseIndexValue = 0;

	long			PList = 0;		// Which mode we are in, based on incoming argument.

	long			numItems;
	long			numIndices;
	long			numValues;

	// Get caller's PList or List from arg 1; bail if failure; set PList accordingly.
	if ((Err = PRegEx_GetRequiredIncomingListArg(callPtr, 1, 1, &IncomingList)) != REGERR_SUCCESS)
		{Err = PRegEx_GetRequiredIncomingListArg(callPtr, 1, 0, &IncomingList);}
	else{PList = 1;}
	RE_TryAssert((Err == REGERR_SUCCESS), REGERR_ExpectedListArgument);
	
	// If we have a property list, always mark it as sorted, whether
	// it's our caller's or our own newly-created list.
	if (PList) {RE_TryErr(PRegEx_SortListThroughLingo(&IncomingList));}
			
	// Get caller's KeysList from arg 2
	RE_TryErr(PRegEx_GetRequiredIncomingListArg(callPtr, 2, 0, &KeysList));

	numItems	 = pMmList->CountElements(&IncomingList);
	numIndices	 = pMmList->CountElements(&KeysList);
	
	if (SetMode)
	{
		// Set mode: get caller's ValuesList must be in arg 3
		RE_TryErr(PRegEx_GetRequiredIncomingListArg(callPtr, 3, 0, &ValuesList));
		
		numValues	 = pMmList->CountElements(&ValuesList);
		
		// Set mode: For convenience, return list will be the caller's
		// incoming list.
		ReturnList = IncomingList;
		HaveCallersReturnList = 1;
	}
	else
	{
		// Get mode: Get new list or list optionally passed by caller in arg 3.
		RE_TryErr(PRegEx_GetCallersOrNewInitList(callPtr, 3, 0, &ReturnList, &MustReleaseReturnList));
	}

	// Iterate over list of indices, getting each index and then
	// getting or setting item at that index.
	{
		long itemNum;
		for (itemNum = 1; itemNum <= numIndices; itemNum++)
		{
			// Release items that may be allocated during loop.
			RE_MaybeValRelease(&ValueValue, MustReleaseValueValue);
			RE_MaybeValRelease(&IndexValue, MustReleaseIndexValue);

			// Get the index
			RE_TryMoaOrMem(pMmList->GetValueByIndex (&KeysList, itemNum,  &IndexValue)); MustReleaseIndexValue = 1;

			if (SetMode)
			{
				// Get the value to store at the index; if we have run out of values, use void.
				if (itemNum <= numValues)
					{RE_TryMoaOrMem(pMmList->GetValueByIndex (&ValuesList, itemNum,  &ValueValue)); MustReleaseValueValue = 1;}
				else {ValueValue = StateInfo.ARandomVoidValue;}

				if (PList)	// Prop list: treat index as a property whose value should be set.
				{	
					RE_TryErr(                    SetAProp(&IncomingList, &IndexValue,  &ValueValue, 0));
				}
				else		// Regular list: treat index as an integer (verify this) and set value at that loc.
				{
					long	myIndex = 0;
					RE_TryType(&IndexValue, kMoaMmValueType_Integer, REGERR_ListIndicesMustBeIntegers);
					pMmValue->ValueToInteger(&IndexValue, &myIndex);

					RE_TryMoaOrMem(pMmList->SetValueByIndex(&IncomingList,    myIndex,  &ValueValue));
				}
			}
			else // !SetMode (Get mode)
			{
				if (PList)	// Prop list: treat index as a property whose value should be looked up.
				{	
					// Get this value from the list; if not found, use a void value.
					// Assume an error means the property was not found.
					long propErr = pMmList->GetValueByProperty(&IncomingList, &IndexValue,  &ValueValue);
					if (propErr == kMoaErr_NoErr) {MustReleaseValueValue = 1;}
					else                          {ValueValue = StateInfo.ARandomVoidValue;}
					
					// Add to list
					RE_TryMoaOrMem(pMmList->AppendValueToList (&ReturnList,            	&ValueValue));
				}
				else		// Regular list: treat index as an integer (verify this) and look up value.
				{
					long	myIndex = 0;
					RE_TryType(&IndexValue, kMoaMmValueType_Integer, REGERR_ListIndicesMustBeIntegers);
					pMmValue->ValueToInteger(&IndexValue, &myIndex);
					
					// Get this value from the list; if not in range, use a void value.
					if ((myIndex >= 1) && (myIndex <= numItems))
						{RE_TryMoaOrMem(pMmList->GetValueByIndex  (&IncomingList, myIndex,  &ValueValue)); MustReleaseValueValue = 1;}
					else
						{ValueValue = StateInfo.ARandomVoidValue;}
					
					// Add to list.
					RE_TryMoaOrMem(pMmList->AppendValueToList(&ReturnList,             &ValueValue));			
				}
			}
		}
	}			

	LEAVE_FUNCTION:
		
	// Release items that may be allocated during loop.
	RE_MaybeValRelease(&ValueValue, MustReleaseValueValue);
	RE_MaybeValRelease(&IndexValue, MustReleaseIndexValue);
	
	if (Err == REGERR_SUCCESS)	 // Return the list.  Add a reference if we're returning the caller's own list.
	{
		if (!MustReleaseReturnList ||  HaveCallersReturnList) pMmValue->ValueAddRef(&ReturnList);
		callPtr->resultValue = ReturnList;
	}
	else                         // Return an error code. // Release the list if we created one and we're not returning it.
	{
		if ( MustReleaseReturnList || !HaveCallersReturnList) pMmValue->ValueRelease(&ReturnList);
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}
	
	return(Err);
}


//---------------------------------------------------------------------------
// PRegEx_Interpolate
//
// See Interpolate_Internal.
//
//---------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Interpolate(PMoaMmCallInfo callPtr)
{
	long 			Err 	= REGERR_SUCCESS;
	
	long			TotalArguments = callPtr->nargs;

	MoaMmValue		InStringVal;
	MoaByte *		InStringValPtr;
	long			MustReleaseInStringValPtr;
	
	MoaMmValue		LookupListVal;
	long			HaveLookupListVal = 0;

	long			InStringLength = 0;
	long			OutStringLength = 0;
	
	MoaByte *		pOutString = NULL;
	MoaMmValue		OutStringVal;
	long			MustReleaseOutStringVal;

	// Get a string and its pointer from argument 1	
	GetArgByIndex(1, &InStringVal);
	RE_TryType(&InStringVal, kMoaMmValueType_String, REGERR_QuoteMetaNeedsString);
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&InStringVal,(const char **)&InStringValPtr));
	MustReleaseInStringValPtr = 1;
	
	// Get the InString length
	InStringLength = PRegEx_GetStringLengthThroughLingo(&InStringVal);
	
	// If a second argument was supplied, we get it (it must be a PList
	// that will be used to look up values for interpolation). 
	if (TotalArguments >= 2)
	{
		RE_TryErr(PRegEx_GetRequiredIncomingListArg(callPtr, 2, 1, &LookupListVal));
		HaveLookupListVal = 1;
	}

	// Calculate the OutStringLength by doing a dry-run through the engine.
	OutStringLength = Interpolate_Internal(InStringValPtr, InStringLength, NULL   , 1, HaveLookupListVal, &LookupListVal, NULL);
	
	// Alloc a buffer to expand (or contract) into
	RE_TryMem(pOutString = (MoaByte *)pCalloc->NRAlloc(OutStringLength + 1));
	
	// Expand the string by running the engine again.
	// Among other things, this eliminates any NUL chars that may have been in the InString.
	OutStringLength = Interpolate_Internal(InStringValPtr, InStringLength, pOutString, 1, HaveLookupListVal, &LookupListVal, NULL);
	
	// Convert the output string to a returnable value.
	RE_TryErr(StringWithNULsToMMValue((char *)pOutString, OutStringLength, OutStringVal));
	MustReleaseOutStringVal = 1;

  LEAVE_FUNCTION:

	if (Err == REGERR_SUCCESS)
	{	// Give output string back to caller.
		callPtr->resultValue = OutStringVal;
		MustReleaseOutStringVal = 0;
	}
	else
	{	// Otherwise, give caller an empty string and let output string get released if necessary.
		pMmValue->StringToValue("", &callPtr->resultValue);
	}
	
	RE_MaybeValRelease(&OutStringVal, MustReleaseOutStringVal);
	RE_MaybeFreePtr(pOutString);
	RE_MaybeValRelPntr(&InStringVal , MustReleaseInStringValPtr);
	
	return(Err);	
}

//---------------------------------------------------------------------------
// PRegEx_Translate
//
// Like the tr/// operator in Perl.  Modifies a string in place by applying
// any user-supplied character mapping table to it.
//
//---------------------------------------------------------------------------

long CREGEXPRESSIONScript::PRegEx_Translate(PMoaMmCallInfo callPtr)
{
	long 				Err = REGERR_SUCCESS;
	
	long			TotalArguments = callPtr->nargs;
	
	MoaMmValue		StringBufferListValue;
	
	long			itemCount;
	
	MoaMmValue		StringBufVal;
	MoaByte *		StringBufValStringPtr = 0;
	long			MustReleaseStringBufVal = 0;
	long			MustReleaseStringBufValStringPtr = 0;
	
	long			DefaultStringBufferLength = 0;
	unsigned long	StringBufferLength = 0;

	MoaMmValue		LengthIntValue;
	long			MustReleaseLengthIntValue = 0;
	
	MoaMmValue		InputPatVal;
	MoaByte *		InputPatValStringPtr = 0;
	long			MustReleaseInputPatValStringPtr = 0;
	unsigned long	OrigInputLength = 0;
	unsigned long	NewInputLength = 0;
	MoaByte *		InputMap = NULL;
	MoaByte *		InputMap2 = NULL;
	
	MoaMmValue		OutputPatVal;
	MoaByte *		OutputPatValStringPtr = 0;
	long			MustReleaseOutputPatValStringPtr = 0;
	unsigned long	OrigOutputLength = 0;
	unsigned long	NewOutputLength = 0;
	MoaByte *		OutputMap2 = NULL;
	MoaByte *		OutputMap = NULL;
	
	MoaMmValue		TempReturnStringVal;
	long			MustReleaseTempReturnStringVal = 0;

	long			TotalChanged = 0;
	
	// Get the string buffer LIST from argument 1.
	RE_TryAssert((TotalArguments >= 1), REGERR_SearchStrLMustBeList);
	GetArgByIndex(1, &StringBufferListValue);
	RE_TryType(&StringBufferListValue, kMoaMmValueType_List, REGERR_SearchStrLMustBeList);

	// Get the string from it.	
	itemCount = pMmList->CountElements(&StringBufferListValue);
	RE_TryAssert((itemCount >= 1), REGERR_SearchStrLMustContainString);

	RE_TryMoaOrMem(pMmList->GetValueByIndex(&StringBufferListValue, 1,  &StringBufVal));
	MustReleaseStringBufVal = 1;
	RE_TryType(&StringBufVal, kMoaMmValueType_String, REGERR_SearchStrLMustContainString);
	
	// Get a stringPtr to the string.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&StringBufVal, (const char **)&StringBufValStringPtr));
	MustReleaseStringBufValStringPtr = 1;
	
	// Initialize the file buffer length by using Lingo to get the actual length.
	DefaultStringBufferLength = PRegEx_GetStringLengthThroughLingo(&StringBufVal);
	
	// Get the optional length argument from the String Buffer list.
	// If absent, get the length from Lingo
	if (itemCount < 2)
	{
		StringBufferLength = DefaultStringBufferLength;
	}
	else
	{
		RE_TryMoaOrMem(pMmList->GetValueByIndex(&StringBufferListValue, 2,  &LengthIntValue));
		MustReleaseLengthIntValue = 1;
		RE_TryType(&LengthIntValue, kMoaMmValueType_Integer, REGERR_SearchStrLLengthArgMustBeInteger);
		
		// Get the value of StringBufferLength and limit it to reasonable bounds:
		// no smaller than zero and no longer than Lingo reports as the actual
		// length of the string.
		pMmValue->ValueToInteger(&LengthIntValue, (long *)&StringBufferLength);
		StringBufferLength = __max(0, (long)StringBufferLength);
		StringBufferLength = __min((long)StringBufferLength, DefaultStringBufferLength);
	}

	// Get Input pattern string from argument 2.
	RE_TryAssert((TotalArguments >= 2), REGERR_ReplPatMustBeString);
	GetArgByIndex(2, &InputPatVal);
	RE_TryType(&InputPatVal, kMoaMmValueType_String, REGERR_ReplPatMustBeString);
	
	// Get a stringPtr to the Input pattern string.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&InputPatVal, (const char **)&InputPatValStringPtr));
	MustReleaseInputPatValStringPtr = 1;
	

	// Get Output pattern string from argument 3.
	RE_TryAssert((TotalArguments >= 2), REGERR_ReplPatMustBeString);
	GetArgByIndex(3, &OutputPatVal);
	RE_TryType(&OutputPatVal, kMoaMmValueType_String, REGERR_ReplPatMustBeString);
	
	// Get a stringPtr to the Output pattern string.
	RE_TryMoaOrMem(pMmValue->ValueToStringPtr(&OutputPatVal, (const char **)&OutputPatValStringPtr));
	MustReleaseOutputPatValStringPtr = 1;
	
	// Get the lengths of the input and output strings in an admittedly non-nul-friendly way.
	pMmValue->ValueStringLength(&InputPatVal, (long *)&(OrigInputLength) );
	pMmValue->ValueStringLength(&OutputPatVal,(long *)&(OrigOutputLength));

	// Finally done with argument processing.  Now we can get down to busisness.
	
	
	// We can bail early if there is no input map; there is nothing to do.	
	if (OrigInputLength == 0) goto LEAVE_FUNCTION;

	// If there is no output map, we bail; there must be at least 1 char.	
	// This could also be turned into an error message; for now we'll just ignore & return zero.
	if (OrigOutputLength == 0) goto LEAVE_FUNCTION;


	// Do char-escape interpolation on both the input and output strings.
	// Of course, suppress backref interpolation.
	
	NewInputLength  = Interpolate_Internal((MoaByte *) InputPatValStringPtr,  OrigInputLength, NULL, 0, 0, NULL, NULL);
	NewOutputLength = Interpolate_Internal((MoaByte *)OutputPatValStringPtr, OrigOutputLength, NULL, 0, 0, NULL, NULL);
	
	RE_TryMem(InputMap  = (MoaByte *)pCalloc->NRAlloc(NewInputLength ));
	RE_TryMem(OutputMap = (MoaByte *)pCalloc->NRAlloc(NewOutputLength));

	NewInputLength  = Interpolate_Internal((MoaByte *) InputPatValStringPtr,  OrigInputLength, (MoaByte *) InputMap, 0, 0, NULL, NULL);
	NewOutputLength = Interpolate_Internal((MoaByte *)OutputPatValStringPtr, OrigOutputLength, (MoaByte *)OutputMap, 0, 0, NULL, NULL);
	
	// Process the character-range syntaxes in both input and output strings: a-z etc.
		
	OrigInputLength  = NewInputLength;
	OrigOutputLength = NewOutputLength;
	
	NewInputLength  = ExpandCharRanges_Internal((MoaByte *) InputMap,  OrigInputLength, NULL);
	NewOutputLength = ExpandCharRanges_Internal((MoaByte *)OutputMap, OrigOutputLength, NULL);
	
	RE_TryMem(InputMap2  = (MoaByte *)pCalloc->NRAlloc(NewInputLength ));
	RE_TryMem(OutputMap2 = (MoaByte *)pCalloc->NRAlloc(NewOutputLength));

	NewInputLength  = ExpandCharRanges_Internal((MoaByte *) InputMap,  OrigInputLength, (MoaByte *) InputMap2);
	NewOutputLength = ExpandCharRanges_Internal((MoaByte *)OutputMap, OrigOutputLength, (MoaByte *)OutputMap2);
	
	
	// Now we have an input map and an output map.
	// Create a translation table with each char initially mapping to itself.
	// Then, for each char in the input map, set the value at the corresponding char
	// in the TRTable below to the same-numbered char in the Output map.
	
	// Initialize the translation table.
	MoaByte TRTable[256]; {unsigned long i; for (i = 0; i <= 255; i++) {TRTable[i]=(MoaByte)(i & 0xFF);}}

	// START DEBUGGGING
	if (0)
	{	
		// Quickie test of TRTable; just return it (instead of mapped string) and bail.
		TRTable[0] = 'a';
		RE_TryErr(StringWithNULsToMMValue((char *)TRTable, 256, TempReturnStringVal));
		MustReleaseTempReturnStringVal = 1;
		RE_TryMoaOrMem(pMmList->SetValueByIndex(&StringBufferListValue, 1, &TempReturnStringVal));
		
		goto LEAVE_FUNCTION;
	}
	// END DEBUGGGING
	
	// Copy all the specified input/output mappings into it.
	{	unsigned long i; 
		for (i = 0; i < NewInputLength; i++)
		{
			TRTable[InputMap2[i]] = OutputMap2[__min(i,NewOutputLength-1)];
		}
	}

	// Now, we can map the incoming value in place: for each character in it,
	// just replace the character with the result of running itself through the TRTable.
	{	unsigned long i; 
		for (i = 0; i < StringBufferLength; i++)
		{
			if (StringBufValStringPtr[i] != TRTable[StringBufValStringPtr[i]]) TotalChanged++;
		    (   StringBufValStringPtr[i]  = TRTable[StringBufValStringPtr[i]]);
		}
	}
	
	// Now, replace the original string value in the input list with the modified one.
	// Shame we have to do this step; but MOA won't let us modify the actual string value in the list.

	RE_TryErr(StringWithNULsToMMValue((char *)StringBufValStringPtr, StringBufferLength, TempReturnStringVal));
	MustReleaseTempReturnStringVal = 1;
	RE_TryMoaOrMem(pMmList->SetValueByIndex(&StringBufferListValue, 1, &TempReturnStringVal));

LEAVE_FUNCTION:

	RE_MaybeValRelease(&TempReturnStringVal, MustReleaseTempReturnStringVal);	

	RE_MaybeFreePtr(InputMap2);
	RE_MaybeFreePtr(OutputMap2);

	RE_MaybeFreePtr(InputMap);
	RE_MaybeFreePtr(OutputMap);

	RE_MaybeValRelPntr(&OutputPatVal,   MustReleaseOutputPatValStringPtr);
	RE_MaybeValRelPntr(&InputPatVal,    MustReleaseInputPatValStringPtr);
	RE_MaybeValRelPntr(&StringBufVal,   MustReleaseStringBufValStringPtr);
	RE_MaybeValRelease(&StringBufVal,   MustReleaseStringBufVal);	
	RE_MaybeValRelease(&LengthIntValue, MustReleaseLengthIntValue);	
	
	if (Err == REGERR_SUCCESS)
	{
		// Return the number of items modified.
		pMmValue->IntegerToValue(TotalChanged, &callPtr->resultValue);
	}
	else
	{
		// Return an error code.
		pMmValue->IntegerToValue(Err, &callPtr->resultValue);
	}

	return(Err);
}


//----------------------------------------------------------------------------
// PRegEx_SetOrGetBooleanFlag
//
// Helper function for entry points that just get or set a boolean in StateInfo.
// 
// Implements:
//		PRegEx_CallbackAbort
//		PRegEx_CallbackStop
//		PRegEx_CallbackSkip
//		PRegEx_CallbackLast
//		PRegEx_ErrorsToMessageWindow
//
//----------------------------------------------------------------------------
long CREGEXPRESSIONScript::PRegEx_SetOrGetBooleanFlag(PMoaMmCallInfo callPtr, long argNum, long *myFlag) 
{
	long Err = REGERR_SUCCESS;

	long TotalArguments = callPtr->nargs;
	
	if (TotalArguments >= argNum)
	{
		// Argument provided: Set a value.
		MoaMmValue		myBooleanVal;
		long      		myBoolean = 0;
		
		GetArgByIndex(argNum, &myBooleanVal);
		pMmValue->ValueToInteger(&myBooleanVal, &myBoolean);
		
		// Force to boolean value of 1 or zero.
		myBoolean = myBoolean || 0;
		myBoolean = myBoolean && 1;

		*myFlag   = myBoolean;
	}
	
	// Whether or not an argument was provided, Get the value.
	{
		pMmValue->IntegerToValue(*myFlag, &callPtr->resultValue);
	}

// LEAVE_FUNCTION:

	return(Err);
}

//----------------------------------------------------------------------------
// Main function that handles translating the calls back and forth.
// 
//
//
//
// 
//----------------------------------------------------------------------------
STDMETHODIMP CREGEXPRESSIONScript_IMoaMmXScript::Call(PMoaMmCallInfo callPtr)
{
	MoaError		Err = kMoaErr_NoErr;
	
	// Assume that incoming resultValue is void.  Some functions use
	// this to return void values since MOA evidently offers no way to
	// create one.  Hate having to waste the cycles here on every single
	// call just to get the value for occasional use.  Does someone know
	// a cooler way to get a true VOID value out of MOA?  -- CPT 05/31/2001

	pObj->StateInfo.ARandomVoidValue = callPtr->resultValue;
	
	
	// For most functions that can produce errors, we capture the error code 
	// in StateInfo.LastErrCode.  For the others, we set a flag to suppress
	// warnings of errors from previous messages.
	//
	// This helps LastErr code persist across certain status-only functions... 
	// like PRegEx_LastErrCode itself, and also suppresses repetition of error
	// messages to the message window when debugging is enabled.
	 
	long	SkipErrCode = 0;
	
	#define Get__ErrCode(a) {pObj->StateInfo.MemError = 0;						\
	                         pObj->StateInfo.LastErrCode =                 (a);}
	#define Skip_ErrCode(a) {SkipErrCode = 1;                              {a;}}
	
	#ifdef _DEBUG
	if (!pObj->PrintedDebugMessage)
	{
		pObj->pUtils->PrintMessage1("Loaded DEBUG version of PRegEx %s.\n", (unsigned long)PREGEX_VERSIONSTR);
		pObj->PrintedDebugMessage = 1;
	}
	#endif


	// Do the Call
	switch	(callPtr->methodSelector) 
	{
		case m_PRegEx_SetMatchPattern:				{Get__ErrCode(pObj->PRegEx_SetMatchPattern(callPtr));} break;
		case m_PRegEx_SetSearchString:				{Get__ErrCode(pObj->PRegEx_SetSearchString(callPtr));} break;
		case m_PRegEx_GetNextMatch:					{Get__ErrCode(pObj->PRegEx_GetNextMatch(callPtr));} break;
		case m_PRegEx_ReplaceString: 				{Get__ErrCode(pObj->PRegEx_ReplaceString(callPtr));} break;
		case m_PRegEx_CompiledOK:					{Skip_ErrCode(RETURNINT(pObj->StateInfo.CompiledOK));} break;
		case m_PRegEx_MemError:						{Skip_ErrCode(RETURNINT(pObj->StateInfo.MemError));} break;
		case m_PRegEx_MemErrorSticky:				{Skip_ErrCode(RETURNINT(pObj->StateInfo.MemErrorSticky));} break;
		case m_PRegEx_GetMatchBRCount:				{Skip_ErrCode(RETURNINT(pObj->StateInfo.CurrentTotalBackRefs));} break;
		case m_PRegEx_FoundCount:					{Skip_ErrCode(RETURNINT(pObj->StateInfo.FoundCount));} break;
		case m_re_pos:
		case m_PRegEx_GetPos:						{Skip_ErrCode(RETURNINT(pObj->StateInfo.Pos));} break;
		case m_PRegEx_GetPCREVer:					{Skip_ErrCode(RETURNSTR(pcre_version()));} break;
		case m_PRegEx_GetPRegExVersion:				{Skip_ErrCode(RETURNSTR(PREGEX_VERSIONSTR));} break;
		case m_re_abort:
		case m_PRegEx_CallbackAbort:					{Skip_ErrCode(pObj->PRegEx_SetOrGetBooleanFlag(callPtr, 1, &pObj->StateInfo.CallbackAbort));} break;
		case m_re_stop:
		case m_PRegEx_CallbackStop:					{Skip_ErrCode(pObj->PRegEx_SetOrGetBooleanFlag(callPtr, 1, &pObj->StateInfo.CallbackStop));} break;
		case m_re_skip:
		case m_PRegEx_CallbackSkip:					{Skip_ErrCode(pObj->PRegEx_SetOrGetBooleanFlag(callPtr, 1, &pObj->StateInfo.CallbackSkip));} break;
		case m_re_last:
		case m_PRegEx_CallbackLast:					{Skip_ErrCode(pObj->PRegEx_SetOrGetBooleanFlag(callPtr, 1, &pObj->StateInfo.CallbackLast));} break;
		case m_re_debug:
		case m_PRegEx_ErrorsToMessageWindow:			{Skip_ErrCode(pObj->PRegEx_SetOrGetBooleanFlag(callPtr, 1, &pObj->StateInfo.ErrorsToMessageWindow));} break;
		case m_PRegEx_MemErrorStickyReset:			{Skip_ErrCode(pObj->StateInfo.MemErrorSticky = 0);} break;
		case m_re_get:
		case m_PRegEx_GetMatchString:				{Get__ErrCode(pObj->PRegEx_GetMatchString(callPtr));} break;
		case m_PRegEx_GetMatchStart:					{Get__ErrCode(pObj->PRegEx_GetMatchStart(callPtr));} break;
		case m_PRegEx_GetMatchLen:					{Get__ErrCode(pObj->PRegEx_GetMatchLen(callPtr));} break;
		case m_PRegEx_SetPos:						{Get__ErrCode(pObj->PRegEx_SetPos(callPtr));} break;
		case m_PRegEx_Clear:							{Get__ErrCode(pObj->PRegEx_Clear(callPtr));} break;
		case m_re_quotemeta:
		case m_PRegEx_QuoteMeta:						{Get__ErrCode(pObj->PRegEx_QuoteMeta(callPtr));} break;
		case m_re_m:
		case m_re_search:
		case m_PRegEx_Search:						{Get__ErrCode(pObj->PRegEx_Search(callPtr));} break;
		case m_PRegEx_SearchExec:					{Get__ErrCode(pObj->PRegEx_SearchExec(callPtr));} break;
		case m_PRegEx_SearchBegin:					{Get__ErrCode(pObj->PRegEx_SearchBegin(callPtr));} break;
		case m_PRegEx_SearchContinue:				{Get__ErrCode(pObj->PRegEx_SearchContinue(callPtr));} break;
		case m_re_join:
		case m_PRegEx_Join:							{Get__ErrCode(pObj->PRegEx_Join(callPtr));} break;
		case m_re_split:
		case m_PRegEx_Split:							{Get__ErrCode(pObj->PRegEx_Split(callPtr));} break;
		case m_re_extract:
		case m_PRegEx_ExtractIntoList:				{Get__ErrCode(pObj->PRegEx_ExtractIntoList(callPtr));} break;
		case m_re_extractp:
		case m_PRegEx_ExtractIntoSPList:				{Get__ErrCode(pObj->PRegEx_ExtractIntoSPList(callPtr));} break;
		case m_re_extractps:
		case m_PRegEx_ExtractIntoSPListSym:			{Get__ErrCode(pObj->PRegEx_ExtractIntoSPListSym(callPtr));} break;
		case m_re_map:
		case m_PRegEx_Map:							{Get__ErrCode(pObj->PRegEx_Map(callPtr));} break;
		case m_re_sort:
		case m_PRegEx_Sort:							{Get__ErrCode(pObj->PRegEx_Sort(callPtr));} break;
		case m_re_copy:
		case m_PRegEx_CopyList:						{Get__ErrCode(pObj->PRegEx_CopyList(callPtr));} break;
		case m_re_reverse:
		case m_PRegEx_Reverse:						{Get__ErrCode(pObj->PRegEx_Reverse(callPtr));} break;
		case m_re_grep:
		case m_PRegEx_Grep:							{Get__ErrCode(pObj->PRegEx_Grep(callPtr));} break;
		case m_re_s:
		case m_re_replace:
		case m_PRegEx_Replace:						{Get__ErrCode(pObj->PRegEx_Replace(callPtr));} break;
		case m_PRegEx_ReplaceExec:					{Get__ErrCode(pObj->PRegEx_ReplaceExec(callPtr));} break;
		case m_re_call:
		case m_PRegEx_CallHandler:					{Get__ErrCode(pObj->PRegEx_CallHandler(callPtr));} break;
		case m_re_read:
		case m_PRegEx_ReadEntireFile:				{Get__ErrCode(pObj->PRegEx_ReadEntireFile(callPtr));} break;
		case m_re_write:
		case m_PRegEx_WriteEntireFile:				{Get__ErrCode(pObj->PRegEx_WriteEntireFile(callPtr));} break;
		case m_re_keys:
		case m_PRegEx_Keys:							{Get__ErrCode(pObj->PRegEx_Keys(callPtr));} break;
		case m_re_values:
		case m_PRegEx_Values:						{Get__ErrCode(pObj->PRegEx_Values(callPtr));} break;
		case m_re_slice:
		case m_PRegEx_GetSlice:						{Get__ErrCode(pObj->PRegEx_GetSlice(callPtr));} break;
		case m_re_slice_set:
		case m_PRegEx_SetSlice:						{Get__ErrCode(pObj->PRegEx_SetSlice(callPtr));} break;
		case m_re_list:
		case m_PRegEx_PListToList:					{Get__ErrCode(pObj->PRegEx_PListToList(callPtr));} break;
		case m_re_list_strs:
		case m_PRegEx_PListToListStrings:			{Get__ErrCode(pObj->PRegEx_PListToListStrings(callPtr));} break;
		case m_re_hash:
		case m_PRegEx_ListToSPList:					{Get__ErrCode(pObj->PRegEx_ListToSPList(callPtr));} break;
		case m_re_hash_syms:
		case m_PRegEx_ListToSPListSym:				{Get__ErrCode(pObj->PRegEx_ListToSPListSym(callPtr));} break;
		case m_re_i:
		case m_PRegEx_Interpolate:					{Get__ErrCode(pObj->PRegEx_Interpolate(callPtr));} break;
		case m_re_tr:
		case m_PRegEx_Translate:						{Get__ErrCode(pObj->PRegEx_Translate(callPtr));} break;
		case m_re_err:
		case m_PRegEx_LastErrCode:								{Skip_ErrCode(RETURNINT(pObj->StateInfo.LastErrCode));} break;
		case m_PRegEx_DescribeError:								{Skip_ErrCode(pObj->PRegEx_DescribeError(callPtr));} break;
		case m_PRegEx_ErrCode_OutOfMemory: 						{Skip_ErrCode(RETURNINT(REGERR_OutOfMemory));} break;
		case m_PRegEx_ErrCode_SearchStrLMustBeList: 				{Skip_ErrCode(RETURNINT(REGERR_SearchStrLMustBeList));} break;
		case m_PRegEx_ErrCode_SearchStrLMustContainString: 		{Skip_ErrCode(RETURNINT(REGERR_SearchStrLMustContainString));} break;
		case m_PRegEx_ErrCode_SearchStrLLengthArgMustBeInteger: 	{Skip_ErrCode(RETURNINT(REGERR_SearchStrLLengthArgMustBeInteger));} break;
		case m_PRegEx_ErrCode_REMustNotBeEmpty: 					{Skip_ErrCode(RETURNINT(REGERR_REMustNotBeEmpty));} break;
		case m_PRegEx_ErrCode_REDidNotCompile: 					{Skip_ErrCode(RETURNINT(REGERR_REDidNotCompile));} break;
		case m_PRegEx_ErrCode_InvalidOptionsSpecified: 			{Skip_ErrCode(RETURNINT(REGERR_InvalidOptionsSpecified));} break;
		case m_PRegEx_ErrCode_ReplPatMustBeString: 				{Skip_ErrCode(RETURNINT(REGERR_ReplPatMustBeString));} break;
		case m_PRegEx_ErrCode_CallbackFuncMustBeSymbol: 			{Skip_ErrCode(RETURNINT(REGERR_CallbackFuncMustBeSymbol));} break;
		case m_PRegEx_ErrCode_CallbackFuncDidNotReturnString:	{Skip_ErrCode(RETURNINT(REGERR_CallbackFuncDidNotReturnString));} break;
		case m_PRegEx_ErrCode_QuoteMetaNeedsString: 				{Skip_ErrCode(RETURNINT(REGERR_QuoteMetaNeedsString));} break;
		case m_PRegEx_ErrCode_TriedToMatchWithoutSearchStrL: 	{Skip_ErrCode(RETURNINT(REGERR_TriedToMatchWithoutSearchStrL));} break;
		case m_PRegEx_ErrCode_TriedToMatchWithoutSearchPattern: 	{Skip_ErrCode(RETURNINT(REGERR_TriedToMatchWithoutSearchPattern));} break;
		case m_PRegEx_ErrCode_TriedToReplaceWithoutMatching: 	{Skip_ErrCode(RETURNINT(REGERR_TriedToReplaceWithoutMatching));} break;
		case m_PRegEx_ErrCode_CallbackRequestedAbort: 			{Skip_ErrCode(RETURNINT(REGERR_CallbackRequestedAbort));} break;
		case m_PRegEx_ErrCode_UnexpectedMOAError: 				{Skip_ErrCode(RETURNINT(REGERR_UnexpectedMOAError));} break;
		case m_PRegEx_ErrCode_UnexpectedInternalError: 			{Skip_ErrCode(RETURNINT(REGERR_UnexpectedInternalError));} break;
		case m_PRegEx_ErrCode_CallbackFunctionFailed: 			{Skip_ErrCode(RETURNINT(REGERR_CallbackFunctionFailed));} break;
		case m_PRegEx_ErrCode_ExpectedListArgument: 				{Skip_ErrCode(RETURNINT(REGERR_ExpectedListArgument));} break;
		case m_PRegEx_ErrCode_ExpectedPListArgument: 			{Skip_ErrCode(RETURNINT(REGERR_ExpectedPListArgument));} break;
		case m_PRegEx_ErrCode_GrepNeedsFunctionNameOrPRegEx: 		{Skip_ErrCode(RETURNINT(REGERR_GrepNeedsFunctionNameOrPRegEx));} break;
		case m_PRegEx_ErrCode_ExpectedStringArgument: 			{Skip_ErrCode(RETURNINT(REGERR_ExpectedStringArgument));} break;
		case m_PRegEx_ErrCode_SortFunctionDidNotReturnInteger: 	{Skip_ErrCode(RETURNINT(REGERR_SortFunctionDidNotReturnInteger));} break;
		case m_PRegEx_ErrCode_ListIndicesMustBeIntegers: 		{Skip_ErrCode(RETURNINT(REGERR_ListIndicesMustBeIntegers));} break;
		case m_PRegEx_ErrCode_FileNotFound:					 	{Skip_ErrCode(RETURNINT(REGERR_FileNotFound));} break;
		case m_PRegEx_ErrCode_DirNotFound:					 	{Skip_ErrCode(RETURNINT(REGERR_DirNotFound));} break;
		case m_PRegEx_ErrCode_ErrorOpeningFile:					{Skip_ErrCode(RETURNINT(REGERR_ErrorOpeningFile));} break;
		case m_PRegEx_ErrCode_ErrorReadingFile:					{Skip_ErrCode(RETURNINT(REGERR_ErrorReadingFile));} break;
		case m_PRegEx_ErrCode_ErrorWritingFile:					{Skip_ErrCode(RETURNINT(REGERR_ErrorWritingFile));} break;
	}

	
	// If "PRegEx_ErrorsToMessageWindow" (re_debug) mode is turned on, then
	// we report any error status returned by any 
	// potentially-error-producing PRegEx function to the
	// message window as both a string and an integer.
	
	if (
		(pObj->StateInfo.LastErrCode != REGERR_SUCCESS) && 
		(pObj->StateInfo.ErrorsToMessageWindow) && 
	    (!SkipErrCode) &&												// Disable message if a simple status function was being called.
		(callPtr->methodSelector != m_PRegEx_ErrorsToMessageWindow) &&	// Disable message if we've just changed this flag.
		1)
	{
		pObj->pUtils->PrintMessage2("%s (%d)\n", 
			(unsigned long)pObj->GetErrMessageString(pObj->StateInfo.LastErrCode), 
			(unsigned long)pObj->StateInfo.LastErrCode);
	}
	  
	goto LEAVE_FUNCTION;
	
LEAVE_FUNCTION:	

	X_STD_RETURN(Err);
}

long CREGEXPRESSIONScript::PRegEx_DescribeError(PMoaMmCallInfo callPtr)
{
	long			Err = REGERR_SUCCESS;
	
	long       		TotalArguments = callPtr->nargs;
	
	MoaMmValue		ErrCodeValue;
	MoaMmValueType 	ValueType  = 0;
	
	char *			MyString = NULL;

	// Default code to return information about is most recent "LastErrCode"
	long 			ErrCode = StateInfo.LastErrCode;

	// But if caller passes an error number to us, we describe it instead.
	if (TotalArguments >= 1)
	{
		GetArgByIndex (1, &ErrCodeValue);
		RE_TryType(&ErrCodeValue, kMoaMmValueType_Integer, REGERR_ListIndicesMustBeIntegers);
		RE_TryMoaOrMem(pMmValue->ValueToInteger(&ErrCodeValue, &ErrCode));
	}

	// Get the message string from our table...
	MyString = GetErrMessageString(ErrCode);

	// Try to pass the string to our caller.
	RE_TryMoaOrMem(pMmValue->StringToValue(MyString, &callPtr->resultValue));
	
LEAVE_FUNCTION:

	if (Err == REGERR_ListIndicesMustBeIntegers)
	{
		pMmValue->StringToValue("Error code must be an integer", &callPtr->resultValue);
	}
	else if (Err != REGERR_SUCCESS)
	{
		pMmValue->StringToValue(GetErrMessageString(Err), &callPtr->resultValue);
	}
  
  	return(Err);
}
		  


char * CREGEXPRESSIONScript::GetErrMessageString(long ErrCode)
{
	char * ErrMsg;
	
	switch(ErrCode)
	{
		case 	REGERR_SUCCESS:								{ErrMsg = "";} break;			
		case 	REGERR_OutOfMemory:							{ErrMsg = "PRegEx: Out of memory!";} break;			
		case 	REGERR_SearchStrLMustBeList:				{ErrMsg = "PRegEx: SearchStrL argument must be a Lingo list.";} break;			
		case 	REGERR_SearchStrLMustContainString:			{ErrMsg = "PRegEx: SearchStrL argument must have a string as 1st element.";} break;			
		case 	REGERR_SearchStrLLengthArgMustBeInteger:	{ErrMsg = "PRegEx: SearchStrL 2nd element, if present, must be a non-negative integer.";} break;			
		case 	REGERR_REMustNotBeEmpty:					{ErrMsg = "PRegEx: Regular Expression string must not be empty.";} break;			
		case 	REGERR_REDidNotCompile:						{ErrMsg = "PRegEx: Regular Expression did not compile.";} break;			
		case 	REGERR_InvalidOptionsSpecified:				{ErrMsg = "PRegEx: Invalid options specified.";} break;			
		case 	REGERR_ReplPatMustBeString:					{ErrMsg = "PRegEx: Replacement pattern must be a string.";} break;			
		case 	REGERR_CallbackFuncMustBeSymbol:			{ErrMsg = "PRegEx: Callback function name must be a symbol (like #MyHandler).";} break;			
		case 	REGERR_CallbackFuncDidNotReturnString:		{ErrMsg = "PRegEx: Callback function did not return a string.";} break;			
		case 	REGERR_QuoteMetaNeedsString:				{ErrMsg = "PRegEx: QuoteMeta requires a string argument.";} break;			
		case 	REGERR_TriedToMatchWithoutSearchStrL:		{ErrMsg = "PRegEx: Tried to match with setting a search string.";} break;			
		case 	REGERR_TriedToMatchWithoutSearchPattern:	{ErrMsg = "PRegEx: Tried to match without setting a search pattern (Regular Expression).";} break;			
		case 	REGERR_TriedToReplaceWithoutMatching:		{ErrMsg = "PRegEx: Tried to replace without matching.";} break;			
		case 	REGERR_CallbackRequestedAbort:				{ErrMsg = "PRegEx: Callback aborted at caller's request.";} break;			
		case 	REGERR_UnexpectedMOAError:					{ErrMsg = "PRegEx: Unexpected MOA (Macromedia Open Architecture) error.";} break;			
		case 	REGERR_UnexpectedInternalError:				{ErrMsg = "PRegEx: Unexpected internal error.";} break;			
		case 	REGERR_CallbackFunctionFailed:				{ErrMsg = "PRegEx: Callback function not found.";} break;			
		case 	REGERR_ExpectedListArgument:				{ErrMsg = "PRegEx: Expected a list as argument.";} break;			
		case 	REGERR_ExpectedPListArgument:				{ErrMsg = "PRegEx: Expected a property list as argument.";} break;			
		case 	REGERR_GrepNeedsFunctionNameOrPRegEx:		{ErrMsg = "PRegEx: Grep needs a function name (symbol) or RE (string).";} break;			
		case 	REGERR_ExpectedStringArgument:				{ErrMsg = "PRegEx: Expected a string as argument.";} break;			
		case 	REGERR_SortFunctionDidNotReturnInteger:		{ErrMsg = "PRegEx: Sort function did not return an integer.";} break;			
		case 	REGERR_ListIndicesMustBeIntegers:			{ErrMsg = "PRegEx: List indices must be integers.";} break;			
		case 	REGERR_FileNotFound:						{ErrMsg = "PRegEx: File not found.";} break;			
		case 	REGERR_DirNotFound:							{ErrMsg = "PRegEx: Directory not found.";} break;			
		case 	REGERR_ErrorOpeningFile:					{ErrMsg = "PRegEx: Error opening file.";} break;			
		case 	REGERR_ErrorReadingFile:					{ErrMsg = "PRegEx: Error reading file.";} break;			
		case 	REGERR_ErrorWritingFile:					{ErrMsg = "PRegEx: Error writing file.";} break;			
		default:											{ErrMsg = "PRegEx: Unrecognized error code.";} break;	
	}
	
return(ErrMsg);
}

#ifdef USING_INIT_FROM_DICT
/* --------------------------------- CREGEXPRESSIONScript_IMoaInitFromDict::InitFromDict */
STDMETHODIMP CREGEXPRESSIONScript_IMoaInitFromDict::InitFromDict(PIMoaRegistryEntryDict pRegistryDict)
{
	UNUSED(pRegistryDict);
	X_ENTER
	
	/* variable declarations */
	MoaError err = kMoaErr_NoErr;

	/*
	 *  --> insert additional code -->
	 */

	X_STD_RETURN(err);
	X_EXIT
}
#endif

#ifdef USING_NOTIFICATION_CLIENT
/* --------------------------------- CREGEXPRESSIONScript_IMoaNotificationClient::Notify */
STDMETHODIMP CREGEXPRESSIONScript_IMoaNotificationClient::Notify(ConstPMoaNotifyID nid, PMoaVoid pNData, PMoaVoid pRefCon)
{
	UNUSED(nid);
	UNUSED(pNData);
	UNUSED(pRefCon);
	X_ENTER
	
	/* variable declarations */
	MoaError err = kMoaErr_NoErr;

	/*
	 *  --> insert additional code -->
	 */

	X_STD_RETURN(err);
	X_EXIT
}

#endif


