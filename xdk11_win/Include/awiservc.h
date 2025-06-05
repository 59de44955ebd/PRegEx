/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_awiservc
#define _H_awiservc

/*
	Purpose:
	
	Interface and class definitions for Authorware-specific services.	
*/

#ifndef _H_awtypes
#include "awtypes.h"
#endif

#ifndef _H_mmiservc
#include "mmiservc.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* ----------------------------------------------------------------------------
/
/	Notification types
/
/ -------------------------------------------------------------------------- */


DEFINE_GUID(NID_AwNPaletteChanged, 0xAF37A967L, 0x0021, 0x7E22, 0x00, 0x00, 0x08, 
							0x00, 0x07, 0xF7, 0x8F, 0xBF);

DEFINE_GUID(NID_AwNStep, 0xAF37A967L, 0x0021, 0x7E24, 0x00, 0x00, 0x08, 0x00, 
							0x07, 0xF7, 0x8F, 0xBF);

DEFINE_GUID(NID_AwNIdle, 0xAF37A967L, 0x0021, 0x7E26, 0x00, 0x00, 0x08, 0x00,
							0x07, 0xF7, 0x8F, 0xBF);



/* ----------------------------------------------------------------------------
/
/  IMoaAwEventSender
/
/ -------------------------------------------------------------------------- */


DEFINE_GUID(IID_IMoaAwEventSender, 0x161D29ACL, 0x438C, 0x11D0, 0x8A, 0x0E,
0x08, 0x00, 0x07, 0xF7, 0x8F, 0xBF);

#undef INTERFACE
#define INTERFACE IMoaAwEventSender

DECLARE_INTERFACE_(IMoaAwEventSender, IMoaUnknown)
/* Description

The <tt>IMoaAwEventSender</tt> interface is implemented by an Xtra to
provide information about the kind of
events it can send to Authorware so that Authorware can present this
information to the user in the Event Response
Properties dialog.  Any Xtra that uses the <TT>SendSpriteEvent</TT>
function must implement the <TT>IMoaAwEventSender interface </TT>in the
same class that implements its <TT>IMoaMmXAsset</TT> interface.  If you
want the Xtra-level sender name to appear in
the Event Response Properties dialog, you must add a registry entry for it
in the MOA cache.

*/
{
	STD_IUNKNOWN_METHODS
 

	STDMETHOD(GetXtraEventDescriptions) (THIS_
		PMoaChar pDescriptions, /*Pointer to a string  containing the list of event descriptions that the Xtra sends for all its instances*/
		MoaLong	maxLen /*The maximum number of characters that will be copied into the string*/
		)
		PURE;

	
/* Category
Event methods
*/

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355> Function call succeeded
</TD></TR>
*/

/* Description

This method returns as a string the list of event descriptions that the
Xtra sends for all its instances.
It is the caller's responsibility to allocate the string.  No more than
<TT>maxLen</TT> characters will
be copied into the string.  The events in this list are the events that are
common to all instance sof the
Xtra (events that can be sent by any of its instantiated icons).

The format of the returned string is
<tt>    "eventName1 argtype1 argname1, argtype2 argname2... -- description
<crlf> eventName2..."</tt>

Valid argument types are int, integer, float, rect, point, symbol, string,
any, *.  This is the same general
format as for Scripting Xtra message tables.

If you don't want a particular event to appear in the list of available
events in the Authorware Response
Properties dialog, precede it with a '/'.
*/


	STDMETHOD(GetInstanceEventDescriptions) (THIS_
		PMoaChar pDescriptions,  /*Pointer to a string  containing the list of event descriptions that the Xtra sends for all its instances*/
		MoaLong	maxLen /*The maximum number of characters that will be copied into the string*/
		)
		PURE;

/* Category
Event methods
*/

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355> Function call succeeded
</TD></TR>
*/

/* Description
For senders which are assets, this returns the list of events sent by this
specific instance of the asset.

The format of the returned string is
<tt>    "eventName1 argtype1 argname1, argtype2 argname2... -- description
<crlf> eventName2..."</tt>

Valid argument types are int, integer, float, rect, point, symbol, string,
any, *.  This is the same general
format as for Scripting Xtra message tables.

*/



	STDMETHOD(GetSenderXtraName) (THIS_
		PMoaChar pName, /*Pointer to a string  containing Xtra name*/
		MoaLong	maxLen /*The maximum number of characters that will be copied into the string*/
		)
		PURE;	

/* Category
Event methods
*/

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355> Function call succeeded
</TD></TR>
*/

/* Description

This method returns the name of the Xtra as shown in the list of event
senders in Authorware's
Reponse Properties dialog for the Event Response type.   For Scripting
Xtras, you should return
the same string that you used to identify your Xtra in the message table of
your Scripting Xtra.  For Asset
Xtras, you should return the same string as the display name for the Asset Xtra.

Return an empty string if you don't want the Xtra to appear in the Response
Properties dialog sender list.
*/

	STDMETHOD(HandleReply) (THIS_ 
					MoaMmSymbol	eventName,/*Symbol naming this event*/
					PMoaMmValue pReply,	/*Pointer to the value of the reply generated by Authorware*/
					PMoaVoid replyRefcon /*Data that is passed back when a reply is sent back*/
					)
					PURE;	


/* Category
Event methods
*/

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355> Function call succeeded
</TD></TR>
*/

/* Description
Processes a reply from Authorware, generated by an earlier call to
<tt>SendEventWithReply</tt>.  <tt>pEventName</tt> and
<tt>replyRefcon </tt>are the same values passed in to
<tt>SendEventWithReply</tt>.
<tt>pEventName</tt> is a string naming this event for example, "mouseClick").
<tt>replyRefcon </tt> is data that is passed back to the
<tt>HandleReply</tt> method of the <tt>pSender</tt> when a reply is sent
back.
<tt>pReply</tt> is the value of the reply
generated by Authorware.

*/
};

typedef IMoaAwEventSender FAR * PIMoaAwEventSender;

/* ----------------------------------------------------------------------------
/
/  IMoaAwPiece
/
/ -------------------------------------------------------------------------- */

// {ECFE0820-1329-11d0-85BC-00C04FD44677}
DEFINE_GUID(IID_IMoaAwPiece, 0xecfe0820, 0x1329, 0x11d0, 0x85, 0xbc, 0x0,
				0xc0, 0x4f, 0xd4, 0x46, 0x77);

#undef INTERFACE
#define INTERFACE IMoaAwPiece

DECLARE_INTERFACE_(IMoaAwPiece, IMoaUnknown)
/* Description

The <tt>IMoaAwPiece</tt> interface provides the Authorware piece specific
MOA services. These include methods which deal with expressions, variables,
palettes, file location, and imaging support.

*/
{
	STD_IUNKNOWN_METHODS
	


	STDMETHOD(GetMediaBitmap)	(THIS_
					MoaMmWinHandle *bitmap,
					MoaMmHpal		palette,
					MoaAwIconId		iconId
					)
					PURE;
/* Category

Media

*/
/* Returns

 kMoaErr_NoErr if function call succeeded

*/
/* Description

Return the media of the given display icon in bitmap format, as a dib on windows or a pict on the mac.
The palette parameter is ignored on the Macintosh.
On windows if no palette is passed it will use the default palette.

*/
	STDMETHOD(GetMediaImage)	(THIS_
					MoaMmWinHandle *image,
					MoaAwIconId		iconId
					)
					PURE;
/* Category

Media

*/
/* Returns

 kMoaErr_NoErr if function call succeeded

*/
/* Description

Return the media of the given display icon in vector format, as a metafile on windows or a pict on the mac

*/

	STDMETHOD(EvalExpression) (THIS_
		ConstPMoaChar  pExpression, /*Pointer to the string containing the expression to evaluate*/
		PMoaMmValue  pResult, /*Pointer to the result of the expression */
		MoaAwExprFlags  exprAttribs, /*A flag that represents attributes of the expression including. <tt>kMoaAwExprFlag_IsScript</tt>*/
		MoaLong  FAR  *pErrStart, /* Pointer to the starting location of the invalid text in the expression*/
		MoaLong  FAR  *pErrEnd /* Pointer to the starting location of the invalid text in the expression*/
		)
		PURE;
/* Category

Expressions

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355> Function call succeeded
</TD></TR>
*/
/* Description

Evaluates an expression or script supplied as a string and returns the result.

*/

	STDMETHOD(GetIconId)	(THIS_
		ConstPMoaChar  pIconTitle, /*Pointer to the string containing an icon title*/
		PMoaAwIconId  pIconId /*Pointer to the icon identification number*/
		)
		PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaAwErr_UndefinedIcon</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>No icon with that title
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=235><TT>kMoaAwErr_TitleNotUnique</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>More than one icon has that title
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=235><TT>kMoaAwErr_ReservedTitle</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>This title can't be
referenced. The icon title is a null string or one of the following values:
"Untitled", "Calcs from Map", "DeletedIcon", "DeletedFunction", or
"DeletedVariable".
</TD></TR>
*/
/* Description

Looks up the unique identificaiton number assigned to the icon whose title
is at <tt>pIconTitle</tt>.

*/

	STDMETHOD(GetVariable) (THIS_
		ConstPMoaChar  pVarName, /*Pointer to the string containing a variable name*/
		MoaAwIconId  atIconId, /*The id of an @-reference icon. Optional.*/
		PMoaMmValue  pValue /*Pointer to the value of the variable*/
		)
		PURE;
/* Category

Variables

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Gets the value of a variable, passing in its name and optionally the id of
an @-reference icon.

*/

	STDMETHOD(SetVariable) (THIS_
		ConstPMoaChar  pVarName, /*Pointer to the string containing a variable name*/
		MoaAwIconId  atIconId, /*The id of an @-reference icon. Optional.*/
		MoaBoolParam  createVar, /*Boolean. Set to TRUE to create a new temporary variable*/
		PMoaMmValue  pValue/*Pointer to the value to which you want to set the variable*/
					)
					PURE;
/* Category

Variables

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Sets the value of a variable.  Pass in the variable name and optionally the
id of an @-reference icon.
If you want to create a new temporary variable, pass TRUE as
<tt><i>createVar</i></tt>.

*/

	STDMETHOD(GetPalette) (THIS_
		PMoaMmHpal  phPal /*Pointer to the handle of the currently active palette*/
					)
					PURE;
/* Category

Palette

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Gets a handle of the currently active palette.

*/

	STDMETHOD(SetPalette) (THIS_
		MoaMmHpal  hPal, /*Handle to the palette*/
		MoaBool  raw, /*Boolean. If TRUE, the palette is used as supplied. */
		MoaLong  sysColors /*Value specifying how static system colors are handled:  SP_STATIC, SP_NOSTATIC, SP_PIECE, SP_DEFAULT */
					)
					PURE;
/* Category

Palette

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_OutOfMem /TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Out of memory
</TD></TR>

*/
/* Description

Sets the current palette for the piece.  If <tt><i>raw</i></tt> is TRUE,
the palette is used as supplied, otherwise Authorware applies its palette
transformation. <tt><i>sysColors</i></tt> specifies how to handle
the static system colors; it can have one of the following values:
SP_STATIC, SP_NOSTATIC, SP_PIECE, SP_DEFAULT.

*/

	STDMETHOD_(void, ResetPalette) (THIS)
					PURE;
/* Category

Palette

*/
/* Description

Sets the currently active palette back to the default Authorware palette.

*/

	STDMETHOD(ResolveFileName) (THIS_
		ConstPMoaChar  pFileName, /*Pointer to the string containing a file name*/
		PMoaChar  pPathName, /*Pointer to the path name*/
		MoaLong  maxLen /*Value specifying the maximum length of <tt><i>pPathName</i></tt>*/
					)
					PURE;
/* Category

File Location

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_FileNotFound</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>File not found
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP"
WIDTH=235><TT>kMoaErr_OutOfMem</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Out of memory
</TD></TR>

*/
/* Description

Tries to find the file specified in <tt><i>pFileName</i></tt> using the
active search path and
returns it in <tt><i>pPathName</i></tt> up to <tt><i>maxLen </i></tt>bytes.

*/

	STDMETHOD(GetPresentationWindowGC) (THIS_
		PIMoaMmGC FAR *  ppWindowGC /*Pointer to the GC of the presentation window*/
					)
					PURE;
/* Category

Imaging support

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaMmErr_GCNotAvailable</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Presentation window doesn't exist
</TD></TR>

*/
/* Description

Returns the graphic context for the presentation window.

*/


	STDMETHOD(SendEvent) (THIS_ 
					MoaMmSymbol eventName, /*Symbol naming this event; for example, #mouseClick*/
					PIMoaAwEventSender pSender, /*Pointer to the instantiated interface of the sender of this event*/
					MoaLong nArgs, /*Number of arguments provided in the <tt><i>pArgs</i></tt> list*/
					PMoaMmValue	pArgs /*Pointer to the first of the list of arguments to be passed to along with the event*/
					)
					PURE;

/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Sends an event to the piece.  The sender icon id of this event will be
tagged as coming from the icon
associated with this sprite/asset.  Authorware queues up the event and
processes it asynchronously.
The call returns immediately.  No reply is expected by the sender and the
sender's <tt>HandleReply()</tt> method
will not be called for this event, even if a reply is generated for it from
Authorware.

*/




	STDMETHOD(SendEventWithReply) (THIS_ 
					MoaMmSymbol eventName, /*Symbol naming this event; for example, #mouseClick*/
					PIMoaAwEventSender pSender, /*Pointer to the instantiated interface of the sender of this event*/
					MoaLong nArgs, /*Number of arguments provided in the <tt><i>pArgs</i></tt> list*/
					PMoaMmValue	pArgs, /*Pointer to the first of the list of arguments to be passed to along with the event*/
					PMoaVoid replyRefcon /* Data that is passed back to the <tt>HandleReply</tt> method of the <tt><i>pSender</i></tt> when a reply is sent back*/
					)
					PURE;

/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Sends an event to the piece and expects a reply.  The sender icon id of
this event will be tagged as
coming from the icon associated with this sprite/asset.  Authorware queues
up the event and
processes it asynchronously.  The call returns immediately and at some
point later in time
the <tt>HandleReply()</tt> method of the sender is called to pass back the
reply from Authorware.
<tt><i>replyRefcon</i></tt> can be used by the sender to decide which event
this was a reply for and how to process the reply. */

};


typedef IMoaAwPiece FAR * PIMoaAwPiece;


/* ----------------------------------------------------------------------------
/
/  IMoaAwPlayer
/
/ -------------------------------------------------------------------------- */


DEFINE_GUID(IID_IMoaAwPlayer, 0x73D73CFAL, 0x54E9, 0x11CF, 0x96, 0x7F, 0x08, 
				0x00, 0x07, 0xEF, 0x54, 0x49);

#undef INTERFACE
#define INTERFACE IMoaAwPlayer

DECLARE_INTERFACE_(IMoaAwPlayer, IMoaUnknown)
/* Description

The <tt>IMoaAwPlayer</tt> interface provides Authorware player-specific
services.

*/
{
	STD_IUNKNOWN_METHODS
	
	STDMETHOD(GetActivePiece) (THIS_ 
		PIMoaAwPiece FAR *  ppIMoaAwPiece /*Pointer to the interface*/
					)
					PURE;
/* Category

Piece

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Returns an interface that can be used to access the currently active piece.

*/


	STDMETHOD_(void, CloseSoundDriver) (THIS)
					PURE;
/* Category

Sound

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

On Windows, this call stops any sounds currently playing and closes the MCI
sound driver. This should be called by an Xtra before playing sounds using MCI
to ensure that Authorware isn't holding the sound device. (Authorware 
normally holds the sound driver open for a few seconds after playing a sound 
so that any subsequent sounds won't have to suffer the delay associated with 
reopening the sound driver.) This call does nothing on the Macintosh.

*/
};

typedef IMoaAwPlayer FAR * PIMoaAwPlayer;


 /* ----------------------------------------------------------------------------
/
/  IMoaAwSaveState
/
/ -------------------------------------------------------------------------- */


DEFINE_GUID(IID_IMoaAwSaveState, 0x18DBCCF2L, 0x3671, 0x11D0, 0x82, 0xA3,
0x08, 0x00, 0x07, 0xF7, 0x8F, 0xBF);

#undef INTERFACE
#define INTERFACE IMoaAwSaveState

DECLARE_INTERFACE_(IMoaAwSaveState, IMoaUnknown)
/* Description

The <tt>IMoaAwSaveState</tt> interface is optionally supplied by an asset,
sprite actor, or
scripting Xtra.  Authorware obtains it through a QueryInterface on
<tt>IMoaMmXAsset</tt>, <tt>IMoaMmXSpriteActor</tt>,
or <tt>IMoaDrXLingo</tt>.  It provides a way for these objects to persist
from one session to the next,
that is,  when a piece resumes after quit.

*/
{
	STD_IUNKNOWN_METHODS

		
	STDMETHOD(GetStreamOutSaveDataSize) (THIS_ 
		MoaUlong FAR *pSizeBytes /*Pointer to the size of the data needed to save the state of this object*/
					)
					PURE;
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Returns the size of the data needed to save the state of this object.
Properties and media need not be
saved again since they are already part of the object.
 
*/


	STDMETHOD(StreamOutSaveData) (THIS_
					PIMoaStream			pOutStream
					)
					PURE;
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Authorware calls this function to let the object save its save data.
  
*/


	STDMETHOD(StreamInSaveData) (THIS_
					PIMoaStream			pInStream
					)
					PURE;
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

When a session is resuming, Authorware calls this after the object has been
created and its properties loaded.

*/

};

typedef IMoaAwSaveState FAR * PIMoaAwSaveState;



/* ----------------------------------------------------------------------------
/
/	IMoaAwAssetCallback - Authroware-specific callback interface for asset Xtras.
/
/ --------------------------------------------------------------------------- */

DEFINE_GUID(IID_IMoaAwAssetCallback, 0x91432b40, 0x3dce, 0x11d0, 0x81,
0x51, 0x0, 0xaa, 0x0, 0x5f, 0x3c, 0x8);

#undef INTERFACE
#define INTERFACE IMoaAwAssetCallback

DECLARE_INTERFACE_(IMoaAwAssetCallback, IMoaUnknown)
{
	STD_IUNKNOWN_METHODS

	STDMETHOD(GetIconId)	(THIS_
		PMoaAwIconId  pIconId /*Pointer to the unique identification number assigned to this asset's icon*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Puts the unique identification number assigned to this asset's icon into
<tt><i>*pIconId</i></tt>. This
identification number is persistent across sessions. Authorware currently
reassigns identification numbers
when files are packaged, so don't store hard references to identification
numbers in your
property or media data.

*/

	STDMETHOD(StoreExpression) (THIS_ 
		ConstPMoaChar  pExpression, /*Pointer to a string containing the expression*/
		MoaLong  expressionId, /*An Xtra-specified constant (between 1 and 100) used to track a particular expression*/
		MoaAwExprFlags  exprAttribs, /*A flag that represents attributes of the expression including. <tt>kMoaAwExprFlag_IsScript</tt>*/
		MoaBoolParam errorUI, /*Boolean. If FALSE, any error value is returned silently.*/
		MoaLong  FAR  *pErrStart, /* Pointer to the starting location of the invalid text in the expression*/
		MoaLong  FAR  *pErrEnd /* Pointer to the starting location of the invalid text in the expression*/
		)
		PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Called at authoring time to compile and store an expression.
<tt><i>pExpression</i></tt>is a pointer to a string containing the
expression. <tt><i>expressionId</i></tt> is an Xtra-specified constant
(between 1 and 100) used to track a particular expression.
<tt><i>exprAttribs</i></tt> is a flag that represents attributes of the
expression including. <tt>kMoaAwExprFlag_IsScript</tt>. <p>
If <tt><i>errorUI</i></tt> is FALSE, any error value is returned silently;
if it is TRUE and an error occurs, this method puts up an error dialog,
dialogs allowing undefined variables or functions to be defined, or both.
If an error occurs <tt><i>pErrStart</i></tt> and <tt><i>pErrEnd</i></tt>
will contain the start and end of the invalid text in the expression. This
method only works at authoring time.

*/

	STDMETHOD(GetExpressionLength) (THIS_ 
		MoaLong  expressionId, /*ID of the expression*/
		MoaLong FAR  *  pLength /*Pointer to the length of the expression text in bytes, not including the terminating null character*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Returns the length (in bytes, not including the terminating null character) 
of the expression text
associated with the stored expression.  The expression must have been
stored previously with <tt>StoreExpression()</tt>. This method only works
at authoring time.

*/

	STDMETHOD(GetExpression) (THIS_ 
		MoaLong  expressionId, /*ID of the expression*/
		PMoaChar  pExpression, /*Pointer to the string containing the expression text*/
		MoaLong  maxLen /*Value specifying the maximum length of <tt><i>pExpression</i></tt>*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Retrieves the text for a previously stored expression. The expression must
have been stored previously with <tt>StoreExpression()</tt>. This method
only works at authoring time.

*/

	STDMETHOD(DeleteExpression) (THIS_ 
		MoaLong  expressionId /*ID of the expression*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Removes an expression. The expression must have been stored previously with
<tt>StoreExpression()</tt>. This method only works at authoring time.

*/


	STDMETHOD(EvalExpression) (THIS_ 
		MoaLong  expressionId, /*ID of the expression*/
		PMoaMmValue  pResult /*Pointer to the result of the expression evaluation*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Evaluates a stored expression. <tt><i>pResult</i></tt> contains the result in
the specified format. The expression must have been stored previously with
<tt>StoreExpression()</tt>.

*/


	STDMETHOD(WatchExpression) (THIS_ 
		MoaLong  expressionId, /*ID of the expression*/
		PMoaMmValue  pInitialValue /*Pointer to the initial value of the expression*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Set a watch on a given expression. The expression must have been stored
previously with <tt>StoreExpression()</tt>.  When the expression value
changes, the Xtra's <tt>Notify()</tt> procedure will be called.  If an
initial value is not specified (<tt><i>pInitialValue</i></tt> is null),
this method evaluates the expression once to establish its initial value.
	
*/

	STDMETHOD(StopWatchExpression) (THIS_ 
		MoaLong  expressionId /*ID of the expression*/
					)
					PURE;
/* Category

Expressions

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Stops a watch that has been started previously.

*/
};

typedef IMoaAwAssetCallback FAR * PIMoaAwAssetCallback;


/* ----------------------------------------------------------------------------
/
/	IMoaAwSpriteCallback - Authroware-specific callback interface for 
/	sprite assets.
/
/ --------------------------------------------------------------------------- */

// {50A45060-473C-11d0-8151-00AA005F3C08}
DEFINE_GUID(IID_IMoaAwSpriteCallback, 0x50a45060, 0x473c, 0x11d0, 0x81,
0x51, 0x0, 0xaa, 0x0, 0x5f, 0x3c, 0x8);

#undef INTERFACE
#define INTERFACE IMoaAwSpriteCallback

DECLARE_INTERFACE_(IMoaAwSpriteCallback, IMoaUnknown)
{
	STD_IUNKNOWN_METHODS

	STDMETHOD(GetPiece) (THIS_ 
		PIMoaAwPiece FAR *  ppIMoaAwPiece /*Pointer to the interface*/
					)
					PURE;
/* Category

Piece

*/
/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Returns an interface that can be used to access the piece to which this 
sprite belongs.

*/


	STDMETHOD(SendSpriteEvent) (THIS_ 
		MoaMmSymbol eventName, /*Symbol naming this event; for example, #mouseClick"*/
		MoaLong nArgs, /*Number of arguments provided in the <tt><i>pArgs</i></tt> list*/
		PMoaMmValue  pArgs /*Pointer to the first of the list of arguments to be passed to along with the event*/
		)
		PURE;

/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Sends an event to piece containing this sprite.  The sender icon id of this
event will be tagged as coming from the icon associated with this
sprite/asset.  Authorware queues up the event and processes it
asynchronously. The call returns immediately.  No reply is expected by the
sender and the sender's <tt>HandleReply()</tt> method will not be called
for this event, even if a reply is generated for it from Authorware.

*/


	STDMETHOD(SendSpriteEventWithReply) (THIS_ 
		MoaMmSymbol eventName, /*Symbol naming this event; for example, #mouseClick"*/
		MoaLong nArgs, /*Number of arguments provided in the <tt><i>pArgs</i></tt> list*/
		PMoaMmValue  pArgs, /*Pointer to the first of the list of arguments to be passed to along with the event*/
		PMoaVoid   replyRefcon/* Data that is passed back to the <tt>HandleReply</tt> method of the <tt><i>pSender</i></tt> when a reply is sent back*/
		)
		PURE;

/* Returns

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=235><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=355>Function call succeeded
</TD></TR>

*/
/* Description

Sends an event to piece containing this sprite.   The sender icon id of
this event will be tagged as
coming from the icon associated with this sprite/asset.  Authorware queues
up the event and
processes it asynchronously.  The call returns immediately and at some
point later in time
the <tt>HandleReply()</tt> method of the sender is called to pass back the
reply from Authorware.
<tt><i>replyRefcon</i></tt>  can be used by the sender to decide which
event this was a reply for and how to process the reply. */
};

typedef IMoaAwSpriteCallback FAR * PIMoaAwSpriteCallback;

/*
----------------------------------------------------------------------------
*/

#undef INTERFACE


#ifdef __cplusplus
}
#endif
	
#endif /* _H_awiservc */





