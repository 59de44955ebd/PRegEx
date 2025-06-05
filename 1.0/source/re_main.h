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
#define _H_cscript


/*****************************************************************************
 *  INCLUDE FILE(S)
 *  ---------------
 *	This .h file should automatically include all the support files needed for
 *	this particular class. In addition, this file may include other .h files
 *	defining additional callback interfaces for use by a third party.   
 ****************************************************************************/ 
#ifndef _H_moaxtra		  
	#include "moaxtra.h"
#endif


// Director XDK Related Includes
#include "mmixscrp.h"
#include "mmiservc.h"
#include "driservc.h"
#include "moafile2.h"
#include "moastr2.h"

// PCRE Includes
#include "internal.h" // 

// Xtra Internal Function Error Codes
#define REGERR_SUCCESS          				 0
#define REGERR_OutOfMemory        				-1
#define REGERR_SearchStrLMustBeList 			-2
#define REGERR_SearchStrLMustContainString		-3
#define REGERR_SearchStrLLengthArgMustBeInteger -4
#define REGERR_REMustNotBeEmpty 				-5
#define REGERR_REDidNotCompile 					-6
#define REGERR_InvalidOptionsSpecified 			-7
#define REGERR_ReplPatMustBeString 				-8
#define REGERR_CallbackFuncMustBeSymbol 		-9
#define REGERR_CallbackFuncDidNotReturnString 	-10
#define REGERR_QuoteMetaNeedsString 			-11
#define REGERR_TriedToMatchWithoutSearchStrL 	-12
#define REGERR_TriedToMatchWithoutSearchPattern -13
#define REGERR_TriedToReplaceWithoutMatching	-14
#define REGERR_CallbackRequestedAbort 			-15
#define REGERR_UnexpectedMOAError 				-16
#define REGERR_UnexpectedInternalError 			-17
#define REGERR_CallbackFunctionFailed 			-18
#define REGERR_ExpectedListArgument		 		-19
#define REGERR_ExpectedPListArgument		 	-20
#define REGERR_GrepNeedsFunctionNameOrPRegEx		-21
#define REGERR_ExpectedStringArgument		 	-22
#define REGERR_SortFunctionDidNotReturnInteger 	-23
#define REGERR_ListIndicesMustBeIntegers	 	-24
#define REGERR_FileNotFound					 	-25
#define REGERR_DirNotFound					 	-26
#define REGERR_ErrorOpeningFile					-27
#define REGERR_ErrorReadingFile					-28
#define REGERR_ErrorWritingFile					-29

#define PREGEX_VERSIONSTR "1.00"

#define MemError_LEAVE_FUNCTION            { \
			StateInfo.MemError = 1;          \
			StateInfo.MemErrorSticky = 1;    \
			Err = REGERR_OutOfMemory;        \
			goto LEAVE_FUNCTION;             }

#ifdef macintosh
	#define __min(a,b) (a <= b ? a : b)
	#define __max(a,b) (a  > b ? a : b)
	#define __stdcall
	#define bool unsigned char
#endif

extern "C" {
	void * __stdcall stdcall_malloc( size_t size );
	void __stdcall stdcall_free( void *memblock );

	void * MyMalloc(size_t iDataSize);
	void   MyFree(void * pData);
}



// Maximum Possible Back References
#define MAX_OVECTOR_ENTRIES 99

// StateInfo for the Xtra
typedef struct {
	int InCallBackFunction;
	int MemErrorSticky;
	int MemError;
	int LastErrCode;
	int FoundCount;
	int FoundStringHadZeroWidth; // Used to flag when the last successful match had zero width
	int LastSplitPos;            // Used by Split to remember end of previous match (start of split string)
	int Pos;
	int CompiledOK;
	long ErrorsToMessageWindow;
	int GlobalReplaceOption;
	int ExecOption;
	int CanReplace;
	int MatchFound;
	int Replaced;

	long CurrentTotalBackRefs;
	
	long CurrentStringLen; // Size of the string pointed to in pCurrentString
	                       // The actual amount of bytes allocated may be different
	long EntireMatchLen;   // The Length of the Last Match
	long SearchOffset;     // The starting Position of the Entite Match in pCurrentString

	char * pCurrentString; // Pointer to the Current Full String
	char * pCurrentMatch;  // Pointer to the last match found

	int PCRECompileFlags;
	pcre * pCurrentPattern;
	pcre_extra * pExtraPatternInfo;
	const char * pError;
	int erroroffset;
    unsigned const char * pTables;
	

	MoaMmValue	SearchStringList;
	long		MustReleaseSearchStringList;
	
	MoaMmValue		ARandomVoidValue; // A "void" value that we sneak from resultPtr.


	long CallbackAbort;		// Flags for stopping any looping function that Execs a callback function
	long CallbackStop;	
	long CallbackSkip;	
	long CallbackLast;
	
	int  SearchOvector[MAX_OVECTOR_ENTRIES*3]; // Must be Divisible by 3 and 99 is the Max Allowed
	int  CurrentSearchOvector[MAX_OVECTOR_ENTRIES*3]; // A Local Version of the Last Match
	char SmallPatternBuffer[256];
	long * PushedStateInfo;		// Actually a PREGEXSTATEINFO

} PRegExStateInfo;

// Callback param block for internal callback functions.
typedef struct 
{
	MoaMmSymbol		CallbackFuncSymbol;
	MoaMmValue		CallbackArgValue;
	
	long			CallerRequestsAbort;
	long			CallerRequestsStop;
	long			CallerRequestsSkip;
	long			CallerRequestsLast;
	
	long			CallbackNumArgs;
	MoaMmValue *	CallbackArgList; 	// Pointer to array of MoaMMValues to pass to callback.
		
} PRegExCallbackInfo, *PPRegExCallbackInfo;

// GlobalReplaceInfo block to hold list of pending global-replacements.
typedef struct 
{
	long			NumItems;
	long			NumItemsAllocated;
	
	long * 			FoundStarts;
	long *			FoundLengths;
	char **			ReplaceStrings;
	long *			ReplaceLengths;
	
	long			TotalFoundLengths;
	long			TotalReplaceLengths;
	
	long			HaveLengtheningReplaces;
	
} GlobalReplaceInfo, *PGlobalReplaceInfo;

#define InitPPRegExCallbackInfo(a) (memset((a), 0, sizeof(PRegExCallbackInfo)))

/*****************************************************************************
 *	CLSID
 *	-----
 *	The CLSID is a GUID that unquely identifies your MOA class.  To generate a
 *	GUID, use the genUID.app utility (Mac) or the GUIDGEN.EXE utility (Win).
 *	The following line will produce a pre-compiler error if not replaced with
 *	a valid CLSID.
 ****************************************************************************/ 

DEFINE_GUID(CLSID(CREGEXPRESSIONScript), 
0xd581dfe9, 0xc795, 0x11d4, 0x85, 0xdd, 0xe0, 0xc9, 0x47, 0xc1, 0x0, 0x0);


/*****************************************************************************
 *  CLASS INSTANCE VARIABLES
 *  ------------------------
 *  Class instance variable are variables whose scope is exclusive to the
 *  methods implemented by your MOA class.  Variables necessary for the
 *  implementation of your MOA class should be placed here.
 ****************************************************************************/ 
EXTERN_BEGIN_DEFINE_CLASS_INSTANCE_VARS(CREGEXPRESSIONScript)

	// Director Required Interfaces
	PIMoaMmValue pMmValue;
	PIMoaMmWndWin pMmWndWin;
	PIMoaDrMovie  pDrMovie;
	PIMoaDrUtils  pDrUtils;	
	PIMoaDrPlayer pDrPlayer;
	PIMoaMmList	  pMmList;
	PIMoaMmUtils  pUtils;
	PIMoaFile2    pFile;
	PIMoaStream2  pStream;
	long		  PrintedDebugMessage;

	// PCRE State Info
	PRegExStateInfo StateInfo;

	// Class Functions
	void ClearInternalState(unsigned int bCompleteReset);
	void ClearBackReferenceInformation(void);
	
	long Begin_Internal(PMoaMmCallInfo callPtr);

	long PRegEx_SetMatchPattern         (PMoaMmCallInfo callPtr                                                    );
	long PRegEx_SetMatchPattern_Internal(PMoaMmCallInfo callPtr, long patArgNum, long optsArgNum, long setReturnVal);
	
	long PRegEx_SetSearchString         (PMoaMmCallInfo callPtr                                    );
	long PRegEx_SetSearchString_Internal(PMoaMmCallInfo callPtr, long whichArg, long setReturnVal);

	long PRegEx_GetNextMatch         (PMoaMmCallInfo callPtr                                     );
	long PRegEx_GetNextMatch_Internal(PMoaMmCallInfo callPtr, long noBlastBR, long setReturnVal);

	long PRegEx_ReplaceString         (PMoaMmCallInfo callPtr);
	long PRegEx_ReplaceString_Internal(char * SuppliedReplaceString, long SuppliedReplaceStringLength);

	long GetBackRefStrlen(int BackRefID);
	long CopyBackRefToString(int BackRefID,char * pOutputStr);
	long Interpolate_Internal     (MoaByte * pStr, int Length, MoaByte * pOutputStr, long AllowBackRefs, 
									long AllowVars, PMoaMmValue VarLookup, long * HadBackRefs);
	long ExpandCharRanges_Internal(MoaByte * pStr, unsigned long length, MoaByte * pOutputStr);
	
	long PRegEx_GetMatchString            (PMoaMmCallInfo callPtr);
	// long PRegEx_GetMatchString_Internal   (long BackRefID, PMoaMmValue ResultStringValue);
	long PRegEx_GetMatchString_Internal   (long BackRefID, PMoaMmValue ResultStringValue, long & MustReleaseValue);
	long PRegEx_GetMatchSubString_Internal(long startPos, long endPos, char * whichString, PMoaMmValue ResultStringValue, long & MustReleaseValue);

	long PRegEx_GetMatchString_Internal_Temp(long BackRefID, PMoaMmValue ResultStringValue, long * MustReleaseValue);

	long PRegEx_GetMatchStart(PMoaMmCallInfo callPtr);
	long PRegEx_GetMatchLen(PMoaMmCallInfo callPtr);

	long PRegEx_SetPos(PMoaMmCallInfo callPtr);
	long PRegEx_Clear(PMoaMmCallInfo callPtr);
	long PRegEx_QuoteMeta(PMoaMmCallInfo callPtr);
	long QuoteMetaEngine(MoaByte * pInStr, long InStrLen, MoaByte *pOutStr);

	long PRegEx_Search (PMoaMmCallInfo         callPtr);
	long PRegEx_SearchExec(PMoaMmCallInfo      callPtr);
	long PRegEx_Search_Internal(PMoaMmCallInfo callPtr, long execMode, long setReturnVal);

	long PRegEx_SearchBegin(PMoaMmCallInfo callPtr);
	long PRegEx_SearchContinue(PMoaMmCallInfo callPtr);
	
	long PRegEx_GetRequiredIncomingListArg(PMoaMmCallInfo callPtr, long ArgNum, 
										  long PList, PMoaMmValue IncomingList);

	long PRegEx_GetCallersOrNewInitList(PMoaMmCallInfo callPtr, long ArgNum, long PList, 
									   PMoaMmValue listValue, long * mustRelease);

	long PRegEx_Join                    (PMoaMmCallInfo callPtr);
	long PRegEx_Split                   (PMoaMmCallInfo callPtr);
	long PRegEx_ExtractIntoList         (PMoaMmCallInfo callPtr);
	long PRegEx_ExtractIntoList_Internal(PMoaMmCallInfo callPtr, long splitMode);
	
	long PRegEx_ExtractIntoSPList(PMoaMmCallInfo callPtr);
	long PRegEx_ExtractIntoSPListSym(PMoaMmCallInfo callPtr);
	long PRegEx_ExtractIntoSPList_Internal(PMoaMmCallInfo callPtr, long symbolMode);
	
	long PRegEx_Map          (PMoaMmCallInfo callPtr);
	long PRegEx_Sort         (PMoaMmCallInfo callPtr);
	long PRegEx_Grep         (PMoaMmCallInfo callPtr);

	long PRegEx_CopyList        (PMoaMmCallInfo callPtr);
	long PRegEx_CopyList_Internal (PMoaMmValue origList, PMoaMmValue newList, long AppendMode, long DeepCopy);
	long PRegEx_CopyPList_Internal(PMoaMmValue origList, PMoaMmValue newList, long AppendMode, long DeepCopy);

	long PRegEx_Reverse        (PMoaMmCallInfo callPtr);

	long PRegEx_Replace         (PMoaMmCallInfo callPtr);
	long PRegEx_ReplaceExec     (PMoaMmCallInfo callPtr);

	long PRegEx_CallHandler     (PMoaMmCallInfo callPtr);
	
	long PRegEx_ReadEntireFile     (PMoaMmCallInfo callPtr);
	long PRegEx_WriteEntireFile     (PMoaMmCallInfo callPtr);

	long PRegEx_Replace_Internal(PMoaMmCallInfo callPtr, long execMode);
	
	long PRegEx_SetOrGetBooleanFlag(PMoaMmCallInfo callPtr, long argNum, long *myFlag);

	long AppendMatchStringSegmentToList	 (PMoaMmValue aList, long startPos, long endPos);
	long AppendBackRefsToList    (PMoaMmValue aList);
	long InsertBackRefsIntoSPList(PMoaMmValue aList, PMoaMmValue initialKey, long *haveInitialKey, long symbolMode);
	long SetAProp (PMoaMmValue myList, PMoaMmValue myProp, PMoaMmValue myVal, long symbolMode);

	long StringWithNULsToMMValue(char * pStr,long StrLength,MoaMmValue &pVal);
	
	long PRegEx_SortListThroughLingo(PMoaMmValue ListToSort);
	long PRegEx_GetStringLengthThroughLingo(PMoaMmValue ListToSort);
	
	long PushContext(void);
	long PopContext(void);
	long CheckContext(void);
	
	long PRegEx_Call_Callback_Prep(PMoaMmCallInfo callPtr, 
								  PPRegExCallbackInfo myPPRegExCallbackInfo, 
								  long CallbackFuncArgNum, 
								  PMoaMmValue FirstCallbackArgVal,
								  long SecondCallbackArgArgNum);
								  
	long PRegEx_Call_Callback_Exec(PPRegExCallbackInfo myPPRegExCallbackInfo, 
								  PMoaMmValue CallbackReturnValue, 
								  long *MustReleaseCallbackReturnValue,
								  long RequireStringReturnType);
								  
    long PRegEx_Call_Callback_Prep_AddArgs(PPRegExCallbackInfo myPPRegExCallbackInfo, 
					              PMoaMmValue ArgListOrSingleValue);

	long PRegEx_Call_Callback_Prep_ReplaceArgValue(PPRegExCallbackInfo myPPRegExCallbackInfo, 
												  long argNum,
									              PMoaMmValue newValue);

	long PRegEx_Call_Callback_Exec_2Args(PPRegExCallbackInfo myPPRegExCallbackInfo, 
															PMoaMmValue CallbackReturnValue, 
															long *MustReleaseCallbackReturnValue, 
															long RequireStringReturnType,
															PMoaMmValue Arg1,
															PMoaMmValue Arg2);

	void PRegEx_Call_Callback_Tidy(PPRegExCallbackInfo myPPRegExCallbackInfo);

	long GlobalReplaceList_Init(PGlobalReplaceInfo GrInfo);
	long GlobalReplaceList_Add(PGlobalReplaceInfo GrInfo, long FoundStart, long FoundLength, char * ReplaceString, long ReplaceLength);
	void GlobalReplaceList_Tidy(PGlobalReplaceInfo GrInfo);

	long PRegEx_Keys					(PMoaMmCallInfo callPtr);
	long PRegEx_Values				(PMoaMmCallInfo callPtr);
	long PRegEx_KeysValues_Internal	(PMoaMmCallInfo callPtr, long Mode, long KeysToStrings);

	long PRegEx_GetSlice             (PMoaMmCallInfo callPtr);
	long PRegEx_SetSlice             (PMoaMmCallInfo callPtr);

	long PRegEx_GetSetSlice_Internal (PMoaMmCallInfo callPtr, long SetMode);

	long PRegEx_PListToList			(PMoaMmCallInfo callPtr);
	long PRegEx_PListToListStrings	(PMoaMmCallInfo callPtr);

	long PRegEx_ListToSPList          (PMoaMmCallInfo callPtr                 );
	long PRegEx_ListToSPListSym       (PMoaMmCallInfo callPtr                 );
	long PRegEx_ListToSPList_Internal (PMoaMmCallInfo callPtr, long SymbolMode);

	long PRegEx_Interpolate			(PMoaMmCallInfo callPtr);
	long PRegEx_Translate			(PMoaMmCallInfo callPtr);
	
	long VariableScan (unsigned char * aString, long startPos, long strLength, 
                   long * VarNameStartPos, long * VarNameLength, long * IsSymbol);

	long LookupVariableNameInPropList(MoaByte * myStr, long myStrLength, long AsSymbol, PMoaMmValue VarLookup,
			                             MoaByte ** VarValueString, long * VarValueStringLength);

	long ReplaceBufferBackToCallersList(void);
	long CallersListBackToReplaceBuffer(void);
	
	char * GetErrMessageString(long ErrCode);
	long PRegEx_DescribeError(PMoaMmCallInfo callPtr);

EXTERN_END_DEFINE_CLASS_INSTANCE_VARS

/*****************************************************************************
 *  CLASS INTERFACE(S)
 *  ------------------
 *  The interface(s) implemented by your MOA class are specified here.  Note
 *	that at least one class in your Xtra should implement the IMoaRegister
 *	interface.
 *  NOTE: Because C++ does not use a lpVtbl to reference an interface's methods, 
 *  the actual method declaration is done here.
 *
 *  Syntax:
 *  EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(<class-name>, <interface-name>) 
 *		EXTERN_DEFINE_METHOD(<return-type>, <method-name>,(<argument-list>)) 
 *	EXTERN_END_DEFINE_CLASS_INTERFACE
 ****************************************************************************/ 
EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaMmXScript)
	EXTERN_DEFINE_METHOD(MoaError, Call, (PMoaMmCallInfo))		
EXTERN_END_DEFINE_CLASS_INTERFACE

#ifdef USING_INIT_FROM_DICT
EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaInitFromDict)
	EXTERN_DEFINE_METHOD(MoaError, InitFromDict, (PIMoaRegistryEntryDict))
EXTERN_END_DEFINE_CLASS_INTERFACE
#endif

#ifdef USING_NOTIFICATION_CLIENT
EXTERN_BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONScript, IMoaNotificationClient)
	EXTERN_DEFINE_METHOD(MoaError, Notify, (ConstPMoaNotifyID, PMoaVoid, PMoaVoid))
EXTERN_END_DEFINE_CLASS_INTERFACE
#endif


/* 	MODIFY: This is the enumerated scripting method list. This list should
 *	directly correspond to the msgTable defined in an xxx.CPP file. It is used
 *	to dispatch method calls via the methodSelector. The 'm_XXXX' method must
 *	be last.
 */


enum 
{
m_PRegEx_SetSearchString =0,
m_PRegEx_SetMatchPattern,
m_PRegEx_GetNextMatch,
m_PRegEx_ReplaceString,

m_PRegEx_FoundCount,
m_PRegEx_GetMatchString,
m_PRegEx_GetMatchStart,
m_PRegEx_GetMatchLen,
m_PRegEx_GetMatchBRCount,
m_PRegEx_GetPos,
m_PRegEx_SetPos,
m_PRegEx_Clear,

m_PRegEx_QuoteMeta,

m_PRegEx_Search,                  
m_PRegEx_SearchExec,                  
m_PRegEx_SearchBegin,       
m_PRegEx_SearchContinue,

m_PRegEx_Join,
m_PRegEx_Split,

m_PRegEx_ExtractIntoList,
m_PRegEx_ExtractIntoSPList,
m_PRegEx_ExtractIntoSPListSym,

m_PRegEx_Map,
m_PRegEx_Sort,
m_PRegEx_Grep,

m_PRegEx_CopyList,
m_PRegEx_Reverse,

m_PRegEx_Replace,
m_PRegEx_ReplaceExec,

m_PRegEx_CallHandler,
m_PRegEx_ReadEntireFile,
m_PRegEx_WriteEntireFile,

m_PRegEx_CallbackAbort,
m_PRegEx_CallbackStop,
m_PRegEx_CallbackSkip,
m_PRegEx_CallbackLast,

m_PRegEx_GetPCREVer,
m_PRegEx_GetPRegExVersion,

m_PRegEx_LastErrCode,            
m_PRegEx_DescribeError,           
m_PRegEx_CompiledOK,
m_PRegEx_MemError,
m_PRegEx_MemErrorSticky,
m_PRegEx_MemErrorStickyReset,
m_PRegEx_ErrorsToMessageWindow,

m_PRegEx_Keys,
m_PRegEx_Values,
m_PRegEx_GetSlice,
m_PRegEx_SetSlice,
m_PRegEx_PListToList,
m_PRegEx_PListToListStrings,
m_PRegEx_ListToSPList,
m_PRegEx_ListToSPListSym,
m_PRegEx_Interpolate,
m_PRegEx_Translate,

m_re_m				, // m_PRegEx_Search,
m_re_s				, // m_PRegEx_Replace,
m_re_search			, // m_PRegEx_Search,
m_re_replace		, // m_PRegEx_Replace,
m_re_tr				, // m_PRegEx_Translate,
m_re_extract		, // m_PRegEx_ExtractIntoList,
m_re_extractp		, // m_PRegEx_ExtractIntoSPList,
m_re_extractps		, // m_PRegEx_ExtractIntoSPListSym,

m_re_get		    , // m_PRegEx_GetMatchString,
m_re_pos		    , // m_PRegEx_GetPos,

m_re_call			, // m_PRegEx_CallHandler,
m_re_abort			, // m_PRegEx_CallbackAbort,
m_re_stop			, // m_PRegEx_CallbackStop,
m_re_last			, // m_PRegEx_CallbackLast,
m_re_skip			, // m_PRegEx_CallbackSkip,

m_re_quotemeta		, // m_PRegEx_QuoteMeta,
m_re_i				, // m_PRegEx_Interpolate,

m_re_split			, // m_PRegEx_Split,
m_re_join			, // m_PRegEx_Join,

m_re_grep			, // m_PRegEx_Grep,
m_re_map			, // m_PRegEx_Map,
m_re_sort			, // m_PRegEx_Sort,
m_re_reverse		, // m_PRegEx_Reverse,
m_re_copy			, // m_PRegEx_CopyList,

m_re_keys			, // m_PRegEx_Keys,
m_re_values			, // m_PRegEx_Values,

m_re_slice			, // m_PRegEx_GetSlice,
m_re_slice_set		, // m_PRegEx_SetSlice,

m_re_list			, // m_PRegEx_PListToList,
m_re_list_strs		, // m_PRegEx_PListToListStrings,

m_re_hash			, // m_PRegEx_ListToSPList,
m_re_hash_syms		, // m_PRegEx_ListToSPListSym,

m_re_read			, // m_PRegEx_ReadEntireFile,
m_re_write			, // m_PRegEx_WriteEntireFile,

m_re_err			, // m_PRegEx_LastErrCode,
m_re_debug			, // m_PRegEx_ErrorsToMessageWindow,

m_PRegEx_ErrCode_OutOfMemory,       					//-1
m_PRegEx_ErrCode_SearchStrLMustBeList,				//-2
m_PRegEx_ErrCode_SearchStrLMustContainString,		//-3
m_PRegEx_ErrCode_SearchStrLLengthArgMustBeInteger,	//-4
m_PRegEx_ErrCode_REMustNotBeEmpty,					//-5
m_PRegEx_ErrCode_REDidNotCompile,					//-6
m_PRegEx_ErrCode_InvalidOptionsSpecified,			//-7
m_PRegEx_ErrCode_ReplPatMustBeString,				//-8
m_PRegEx_ErrCode_CallbackFuncMustBeSymbol,			//-9
m_PRegEx_ErrCode_CallbackFuncDidNotReturnString,		//-10
m_PRegEx_ErrCode_QuoteMetaNeedsString,				//-11
m_PRegEx_ErrCode_TriedToMatchWithoutSearchStrL,		//-12
m_PRegEx_ErrCode_TriedToMatchWithoutSearchPattern,	//-13
m_PRegEx_ErrCode_TriedToReplaceWithoutMatching,		//-14
m_PRegEx_ErrCode_CallbackRequestedAbort,				//-15
m_PRegEx_ErrCode_UnexpectedMOAError,					//-16
m_PRegEx_ErrCode_UnexpectedInternalError,			//-17
m_PRegEx_ErrCode_CallbackFunctionFailed,				//-18
m_PRegEx_ErrCode_ExpectedListArgument,				//-19
m_PRegEx_ErrCode_ExpectedPListArgument,				//-20
m_PRegEx_ErrCode_GrepNeedsFunctionNameOrPRegEx,		//-21
m_PRegEx_ErrCode_ExpectedStringArgument,				//-22
m_PRegEx_ErrCode_SortFunctionDidNotReturnInteger,	//-23
m_PRegEx_ErrCode_ListIndicesMustBeIntegers,			//-24
m_PRegEx_ErrCode_FileNotFound,						//-25
m_PRegEx_ErrCode_DirNotFound,						//-26
m_PRegEx_ErrCode_ErrorOpeningFile,					//-27
m_PRegEx_ErrCode_ErrorReadingFile,					//-28
m_PRegEx_ErrCode_ErrorWritingFile,					//-29

m_bogus_last_item

};
#endif // _H_cscript 
