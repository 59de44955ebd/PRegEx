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


/*****************************************************************************
 *  INCLUDE FILE(S)
 *  ---------------
 *	This .cpp file should automatically include all the support files needed
 *	for this particular class. In addition, this file may include other .h
 *	files defining additional callback interfaces for use by a third party.   
 ****************************************************************************/ 
#ifndef INITGUID        /* INITGUID causes the actual GUIDs to be declared, */ 
	#define INITGUID      /* not just references to them. Must be declared in */
#endif                  /* only one file. */          

#ifndef _H_cregster
	#include "re_reg.h"
#endif

#include <string.h>

/*****************************************************************************
 *  INTERNAL PROTOTYPES(S)
 *  ----------------------
 *  Declarations for functions used specifically in this file.
 ****************************************************************************/

/*****************************************************************************
 *  INTERNAL ROUTINE(S)
 *  -------------------
 *  Definition of file-specific functions
 ****************************************************************************/

/*****************************************************************************
 *  CLASS INTERFACE(S)
 *  ------------------
 *  The interface(s) implemented by your MOA class are specified here.  Note
 *	that at least one class in your Xtra should implement the IMoaRegister
 *	interface.
 *  NOTE: Because C++ does not use a lpVtbl to reference an interface's
 *	methods, the actual method declaration is done in the .h file.
 *
 *  Syntax:
 *  BEGIN_DEFINE_CLASS_INTERFACE(<class-name>, <interface-name>) 
 ****************************************************************************/ 
BEGIN_DEFINE_CLASS_INTERFACE(CREGEXPRESSIONRegister, IMoaRegister) 
END_DEFINE_CLASS_INTERFACE

/*
 * --> insert additional interface(s) -->
 */

/*****************************************************************************
 *  Data needed for Registering
 *	---------------------------
 *	Specific code needed to register different types of Xtras.  The skeleton
 *	source files include minimal implementations appropriate for each Xtra
 *	type.  Current necessary actions:
 *
 *	Scripting Xtra:					Add the Scripting Xtra Message Table
 *	Sprite Asset Xtra:			Nothing
 *	Tool Xtra:							Nothing
 *	Transition Asset Xtra		Nothing
 *****************************************************************************/ 

/*******************************************************************************
 * SCRIPTING XTRA MESSAGE TABLE DESCRIPTION.
 *
 * The general format is:
 * xtra <nameOfXtra>
 * new object me [ args ... ]
 * <otherHandlerDefintions>
 * --
 * The first line must give the name of the Scripting xtra.
 * The remaining lines give the names of the handlers that this xtra implements
 * along with the required types of the arguments for each handler.
 * 
 * -- Pre-defined handler new 
 * The new handler will be called when a child object is created, 
 * the first argument is always the child object and you defined any remaining arguments.
 * The new handler is the place to initialize any memory required by the child object.
 * 
 * -- Simple Handler Definitions
 * Each handler definition line is format like this:
 * <handlerName> <argType1> <argName1>, <argType2> <argName2> ...
 * The first word is the handler name. Following this are types description for
 * the argument to the handler, each separated by a comma.
 * The argument name <argName>, may be omited.
 * Permited argument types are: 
 * 	integer 
 * 	float
 * 	string
 * 	symbol
 * 	object
 * 	any
 * 	*
 * For integer, float, string, symbol, and object, the type of the argument must 
 * match. The type any means allow any type. The asterisk (*) means any number and 
 * any type of arguments.
 * 
 * The first argument is the child object and is always declared to be of type object.
 * 
 * -- Global Handlers
 * An asterisk (*) preceeding the handler name signifies a global handler.
 * This handler is at the global scope level and can be called from any
 * movie.
 * 
 * -- Xtra level handlers
 * A plus (+) preceeding the handler name signifies an Xtra level handler. 
 * This kind of handler can be called directly from the Xtra reference,
 * without creating a child object.
 * 
 * The enumerated list in beeplngo.H must correspond directly with the msgTable 
 * (i.e. they must be in the same order).
 * 
 *******************************************************************************/ 
 
 /* MODIFY:  */
// "--" is comment
// "*"  after Function Means Variable Parameter List
const static char msgTable1[] = { 
	"xtra PRegEx -- Regular Expresssion Xtra -- http://openxtras.org/ -- Uses Perl-Compatible Regular Expressions (PCRE) --  http://pcre.org/\n"	
	"*PRegEx_SetSearchString object SearchString\n"
	"*PRegEx_SetMatchPattern string PRegExpression,*\n"
	"*PRegEx_GetNextMatch * \n"
	"*PRegEx_ReplaceString string ReplacePattern\n"
	
	"*PRegEx_FoundCount \n"          
	"*PRegEx_GetMatchString *\n"     
	"*PRegEx_GetMatchStart *\n"      
	"*PRegEx_GetMatchLen * \n"       
	"*PRegEx_GetMatchBRCount \n"     
	"*PRegEx_GetPos \n"              
	"*PRegEx_SetPos integer NewPos\n"
	"*PRegEx_Clear *\n"
	
	"*PRegEx_QuoteMeta string StringToBeQuoted\n"
	
	"*PRegEx_Search object SearchString,string PRegExpression,*\n"
	"*PRegEx_SearchExec object SearchString,string PRegExpression,*\n"
	"*PRegEx_SearchBegin object SearchString,string PRegExpression,*\n"
	"*PRegEx_SearchContinue \n"
	
	"*PRegEx_Join object aList,*\n"
	"*PRegEx_Split object SearchString,string PRegExpression,*\n"
	
	"*PRegEx_ExtractIntoList object SearchString,string PRegExpression,*\n"
	"*PRegEx_ExtractIntoSPList object SearchString,string PRegExpression,*\n"
	"*PRegEx_ExtractIntoSPListSym object SearchString,string PRegExpression,*\n"
	
	"*PRegEx_Map object aList, symbol CallbackFunction, *\n"
	"*PRegEx_Sort object aList, integer DeepCopy, symbol CallbackFunction, *\n"
	"*PRegEx_Grep object aList, *\n"

	"*PRegEx_CopyList object aList, *\n"
	"*PRegEx_Reverse object aList, *\n"

	"*PRegEx_Replace object SearchString,string PRegExpression,*\n"
	"*PRegEx_ReplaceExec object SearchString,string PRegExpression,string Options,symbol ReplFunction,*\n"
	
	"*PRegEx_CallHandler symbol CallbackFunction,*\n"
	"*PRegEx_ReadEntireFile string filePath,*\n"
	"*PRegEx_WriteEntireFile string filePath, object StringL,*\n"
	
	"*PRegEx_CallbackAbort *\n"
	"*PRegEx_CallbackStop *\n"
	"*PRegEx_CallbackSkip *\n"
	"*PRegEx_CallbackLast *\n"

	"*PRegEx_GetPCREVersion \n"
	"*PRegEx_GetPRegExVersion\n"
	
	"*PRegEx_LastErrCode \n"            
	"*PRegEx_DescribeError *\n"            
	"*PRegEx_CompiledOK \n"          
	"*PRegEx_MemError \n"            
	"*PRegEx_MemErrorSticky \n"      
	"*PRegEx_MemErrorStickyReset \n" 
	"*PRegEx_ErrorsToMessageWindow * \n" 

	"*PRegEx_Keys object PList, * -- returns: KeyList \n" 
	"*PRegEx_Values object PList, * -- returns: ValueList \n" 

	"*PRegEx_GetSlice    object List, object Keys, * -- returns: SliceList \n" 
	"*PRegEx_SetSlice object List, object Keys, object Values -- returns: List \n" 

	"*PRegEx_PListToList        object PList, *	-- returns: List \n" 
	"*PRegEx_PListToListStrings object PList, *	-- returns: List \n" 

	"*PRegEx_ListToSPList    object List, *	-- returns: SPList \n" 
	"*PRegEx_ListToSPListSym object List, *	-- returns: SPList \n" 

	"*PRegEx_Interpolate string aString, * -- return: SPList \n" 
	"*PRegEx_Translate object SrchStrL, string InputTable, string OutputTable \n" 

	"*re_m object SearchString,string PRegExpression,*\n"
	"*re_s object SearchString,string PRegExpression,*\n"
	"*re_search object SearchString,string PRegExpression,*\n"
	"*re_replace object SearchString,string PRegExpression,*\n"
	"*re_tr object SrchStrL, string InputTable, string OutputTable \n" 
	"*re_extract object SearchString,string PRegExpression,*\n"
	"*re_extractp object SearchString,string PRegExpression,*\n"
	"*re_extractps object SearchString,string PRegExpression,*\n"
	
	"*re_get *\n"
	"*re_pos \n"
	
	"*re_call symbol CallbackFunction,*\n"
	"*re_abort *\n"
	"*re_stop *\n"
	"*re_last *\n"
	"*re_skip *\n"

	"*re_quotemeta string StringToBeQuoted\n"
	"*re_i string aString, * -- return: SPList \n" 

	"*re_split object SearchString,string PRegExpression,*\n"
	"*re_join object aList,*\n"

	"*re_grep object aList, *\n"
	"*re_map object aList, symbol CallbackFunction, *\n"
	"*re_sort object aList, integer DeepCopy, symbol CallbackFunction, *\n"
	"*re_reverse object aList, *\n"
	"*re_copy object aList, *\n"

	"*re_keys object PList, * -- returns: KeyList \n" 
	"*re_values object PList, * -- returns: ValueList \n" 

	"*re_slice    object List, object Keys, * -- returns: SliceList \n" 
	"*re_slice_set object List, object Keys, object Values -- returns: List \n" 

	"*re_list        object PList, *	-- returns: List \n" 
	"*re_list_strs object PList, *	-- returns: List \n" 

	"*re_hash    object List, *	-- returns: SPList \n" 
	"*re_hash_syms object List, *	-- returns: SPList \n" 

	"*re_read string filePath,*\n"
	"*re_write string filePath, object StringL,*\n"
	
	"*re_err \n"            
	"*re_debug * \n" 

	"*PRegEx_ErrCode_OutOfMemory\n"       				//-1
	"*PRegEx_ErrCode_SearchStrLMustBeList\n"				//-2
	"*PRegEx_ErrCode_SearchStrLMustContainString\n"		//-3
	"*PRegEx_ErrCode_SearchStrLLengthArgMustBeInteger\n"	//-4
	"*PRegEx_ErrCode_REMustNotBeEmpty\n"					//-5
	"*PRegEx_ErrCode_REDidNotCompile\n"					//-6
	"*PRegEx_ErrCode_InvalidOptionsSpecified\n"			//-7
	"*PRegEx_ErrCode_ReplPatMustBeString\n"				//-8
	"*PRegEx_ErrCode_CallbackFuncMustBeSymbol\n"			//-9
	"*PRegEx_ErrCode_CallbackFuncDidNotReturnString\n"	//-10
	"*PRegEx_ErrCode_QuoteMetaNeedsString\n"				//-11
	"*PRegEx_ErrCode_TriedToMatchWithoutSearchStrL\n"	//-12
	"*PRegEx_ErrCode_TriedToMatchWithoutSearchPattern\n"	//-13
	"*PRegEx_ErrCode_TriedToReplaceWithoutMatching\n"	//-14
	"*PRegEx_ErrCode_CallbackRequestedAbort\n"			//-15
	"*PRegEx_ErrCode_UnexpectedMOAError\n"				//-16
	"*PRegEx_ErrCode_UnexpectedInternalError\n"			//-17
	"*PRegEx_ErrCode_CallbackFunctionFailed\n"			//-18
	"*PRegEx_ErrCode_ExpectedListArgument\n"				//-19
	"*PRegEx_ErrCode_ExpectedPListArgument\n"			//-20
	"*PRegEx_ErrCode_GrepNeedsFunctionNameOrPRegEx\n"		//-21
	"*PRegEx_ErrCode_ExpectedStringArgument\n"			//-22
	"*PRegEx_ErrCode_SortFunctionDidNotReturnInteger\n"	//-23
	"*PRegEx_ErrCode_ListIndicesMustBeIntegers\n"		//-24
	"*PRegEx_ErrCode_FileNotFound\n"						//-25
	"*PRegEx_ErrCode_DirNotFound\n"						//-26
	"*PRegEx_ErrCode_ErrorOpeningFile\n"					//-27
	"*PRegEx_ErrCode_ErrorReadingFile\n"					//-28
	"*PRegEx_ErrCode_ErrorWritingFile\n"					//-29
};



/*****************************************************************************
 *  CREATE AND DESTROY METHODS
 *  --------------------------
 *  Every interface and class has an associated 'Create' and 'Destroy' pair.
 *  'Create' methods are typically used to acquire interface(s), allocate 
 *  memory, and intialize variables. 'Destroy' methods are typically used to 
 *  release interfaces and free memory.
 *
 * NOTE:  In C++, the local variable 'This' is provided implicitly within 
 * a method implementation.  Thus, there is no need explicitly declare 'This' 
 * as a function parameter. However, this implementation detail doesn’t apply 
 * to the MOA class creator and destructor functions, which are standard C 
 * functions, coded exactly as in like they are in C examples.  
 *
 * Class Syntax:
 * STDMETHODIMP MoaCreate_<class-name>(<class-name> FAR * This)
 * STDMETHODIMP MoaDestroy_<class-name>(<class-name> FAR * This)
 *
 * Interface Syntax:
 * <class_name>_<if_name>::<class_name>_<if_name>(MoaError FAR * pErr)
 * <class_name>_<if_name>::~<class_name>_<if_name>()
 ****************************************************************************/ 

// Constructor
STDMETHODIMP MoaCreate_CREGEXPRESSIONRegister(CREGEXPRESSIONRegister FAR * This)
{
	UNUSED(This);
	X_ENTER

	MoaError		err = kMoaErr_NoErr;

	/*
	 * --> insert additional code -->
	 */

	X_RETURN(MoaError, err);
	X_EXIT
}

// Destructor
STDMETHODIMP_(void) MoaDestroy_CREGEXPRESSIONRegister(CREGEXPRESSIONRegister FAR * This)
{
	UNUSED(This);
	X_ENTER

	/*
	 * --> insert additional code -->
	 */

	X_RETURN_VOID;
	X_EXIT
}

/* ---------------------------------- CREGEXPRESSIONRegister_IMoaRegister Create/Destroy */
CREGEXPRESSIONRegister_IMoaRegister::CREGEXPRESSIONRegister_IMoaRegister(MoaError FAR * pErr)
	{ *pErr = (kMoaErr_NoErr); }
CREGEXPRESSIONRegister_IMoaRegister::~CREGEXPRESSIONRegister_IMoaRegister() {}

/*
 * --> insert additional create/destroy method(s) -->
 */

/*****************************************************************************
 *  METHOD IMPLEMENTATION(S)
 *  ------------------------
 *  This is where the methods to be defined by your MOA class are implemented.
 *  The bulk of the work in implementing Xtras is done here.  NOTE: 'This' is 
 *  implemented implicitly in C++, therefore it isn't used in the argument-
 *	list.
 *
 *  Syntax:
 *  STDMETHODIMP <class-name>_<interface-name>::<method-name>(<argument-list>)
 *****************************************************************************/ 

/* ------------------------------------------- CREGEXPRESSIONRegister_IMoaRegister::Register */
STDMETHODIMP_(MoaError) CREGEXPRESSIONRegister_IMoaRegister::Register(PIMoaCache pCache, 
	PIMoaDict pXtraDict)
{
	X_ENTER

	// variable declaration 
	MoaError 		err = kMoaErr_NoErr;
	PMoaVoid		pMemStr = NULL;
	PIMoaDict 		pRegDict;

	#ifdef USING_LOAD_CONTROL
	MoaLong		loadOptions = (kMoaXlc_PreloadAtLaunch | kMoaXlc_NeverUnload);
	err = pCache->AddRegistryEntry(pXtraDict, &CLSID_CREGEXPRESSIONScript, &IID_IMoaXtraLoadControl, &pRegDict);
	err = pRegDict->Put(kMoaRegType_XtraLoadControlOptions, &loadOptions, 0, kMoaRegKey_XtraLoadControlOptions);
	#endif

	// Register the scripting Xtra 
	if (err = pCache->AddRegistryEntry(pXtraDict, &CLSID_CREGEXPRESSIONScript, &IID_IMoaMmXScript, &pRegDict))
		X_STD_RETURN(err);
	err = pRegDict->Put(kMoaDrDictType_MessageTable, msgTable1, 0, kMoaDrDictKey_MessageTable);

	X_STD_RETURN(err);
	X_EXIT
}
