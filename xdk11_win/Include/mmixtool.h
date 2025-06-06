/*
ADOBE SYSTEMS INCORPORATED
Copyright 1994 - 2007 Adobe Macromedia Software LLC
All Rights Reserved

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/

#ifndef _H_mmixtool
#define _H_mmixtool

/* ================================================================================

	Purpose:
	
	Director tool interface.
	
=================================================================================== */

#ifdef _H_drixtool

#error Don't include both mmixtool.h.h and drixtool.h.

#endif

#ifndef _H_moaxtra
#include "moaxtra.h" 
#endif

#ifndef _H_moastdif
#include "moastdif.h"		
#endif

#ifndef _H_mmtypes
#include "mmtypes.h"
#endif

/* ----------------------------------------------------------------------------
/
/	IMoaRegister
/
/ --------------------------------------------------------------------------- */

/* This interface is defined in moastdif.h.  A class must be implemented
   which supports this interface; the Register() method should register
   information for each tool supported by this xtra.  
   Register() must add dictionary entries for:
   
   displayNameString
   displayCategoryString
   alwaysEnabled

*/


/* ----------------------------------------------------------------------------
/
/	IMoaMmXTool - Tool interface
/
/ --------------------------------------------------------------------------- */

/* IID_IMoaMmXTool: ACCFF6D4001810D50000080007FC20C1 */
DEFINE_GUID(IID_IMoaMmXTool, 0xACCFF6D4L, 0x0018, 0x10D5, 0x00, 0x00, 0x08, 
				0x00, 0x07, 0xFC, 0x20, 0xC1);


#undef INTERFACE
#define INTERFACE IMoaMmXTool

DECLARE_INTERFACE_(IMoaMmXTool, IMoaUnknown)

/* Description
<p>
The <tt>IMoaMmXTool </tt>interface provides a mechanism for providing
authoring-time tools that are listed in the Xtras menu.  For more on
implementing <tt>IMoaMmXTool</tt>, see the chapter "Tools Xtras" in the
<i>Development Guide</i> document.  In addition to this interface, Tools Xtras
implement the <tt>IMoaRegister</tt> interface to inform the host application of
its capabilities, menu name, and other details.  This interface is called by
the host application to get the enable state of your tool (unless you're
"<tt>alwaysEnabled</tt>") and to invoke the tool.  <p>
*/

{
	STD_IUNKNOWN_METHODS

	STDMETHOD(Invoke)(THIS)
		PURE;

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=211><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=379>Succeeded, tool invoked
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" 
WIDTH=211><TT>kMoaMmErr_ToolDisabled</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=379>Failed because tool is disabled
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=211><TT>kMoaErr_OutOfMem</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=379>Failed due to memory error
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" 
WIDTH=211><TT>kMoaMmErr_InternalError</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=379>Failed due to internal error
</TD></TR>
</TABLE>
*/

/* Description
Called when your tool is selected by the user.  You can do a multitude of
operations from putting up a modal dialog or a modeless window, or immediately
executing some operation; it's up to you.  See the documentation for the
Multimedia Services and Director Services callbacks for an idea of the
functionality available.
*/

	STDMETHOD(GetEnabled)(THIS_
		PMoaMmEnabledState pEnabledState) 
		PURE;

/* Returns
<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=223><TT>kMoaErr_NoErr</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=367>Succeeded, value at 
<TT><I><FONT SIZE=2 FACE="Courier New">pEnabledState </FONT></I></TT>set
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" 
WIDTH=223><TT>kMoaMmErr_NotImplemented</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=367>Tool is specified as 
<TT>&quot;alwaysEnabled&quot; </TT>in registry.
</TD></TR>
</TABLE>
*/

/* Description
<p>
Called by the host application to obtain the state of your tool. Set the value
at <tt><i>pEnabledState </i></tt>depending on whether or not it's okay for the
user to invoke your tool at this time. The following values are valid for
<tt><i>pEnabledState</i></tt>: <p>

<TABLE BORDER="2">
<TR><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=247><B>Value</B></TD>
<TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343><B>Description</B>
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" 
WIDTH=247><TT>kMoaMmEnabledState_Disabled</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343>Tool cannot be invoked now
</TD></TR>

<TR><TD ALIGN="LEFT" VALIGN="TOP" 
WIDTH=247><TT>kMoaMmEnabledState_Enabled</TT>
</TD><TD ALIGN="LEFT" VALIGN="TOP" WIDTH=343>Tool can be invoked now
</TD></TR>
</TABLE>
<p>
If you registered a value of <tt>TRUE</tt> for the
<tt>kMoaMmDictKey_AlwaysEnabled </tt>key in your <tt>IMoaRegister::Register()
</tt>implementation, the host application assumes you're always enabled and
never calls this method. <p>
*/

};

typedef IMoaMmXTool FAR * PIMoaMmXTool;


/* Old names for compatability with Dir 5.0 xtras. */


#define IMoaDrXTool			IMoaMmXTool
#define IID_IMoaDrXTool		IID_IMoaMmXTool
#define PIMoaDrXTool		PIMoaMmXTool


#endif /* _H_mmixtool */

