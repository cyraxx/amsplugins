/*----------------------------------------------------------------------------+
 |       ___     _       _                                                    |
 |      /   |   | |     | |                                                   |
 |     / /| | __| | ___ | |__   ___                                           |
 |    / /_| |/ _  |/ _ \|  _ \ / _ \                                          |
 |   / ___  | (_| | (_) | |_) |  __/                                          |
 |  /_/   |_|\__,_|\___/|____/ \___|                                          |
 |                                                                            |
 |                                                                            |
 |  ADOBE CONFIDENTIAL                                                        |
 |  __________________                                                        |
 |                                                                            |
 |  Copyright (c) 2003 - 2007, Adobe Systems Incorporated.                    |
 |  All rights reserved.                                                      |
 |                                                                            |
 |  NOTICE:  All information contained herein is, and remains the property    |
 |  of Adobe Systems Incorporated and its suppliers, if any. The intellectual |
 |  and technical concepts contained herein are proprietary to Adobe Systems  |
 |  Incorporated and its suppliers and may be covered by U.S. and Foreign     |
 |  Patents, patents in process, and are protected by trade secret or         |
 |  copyright law. Dissemination of this information or reproduction of this  |
 |  material is strictly forbidden unless prior written permission is         |
 |  obtained from Adobe Systems Incorporated.                                 |
 |                                                                            |
 |          Adobe Systems Incorporated       415.832.2000                     |
 |          601 Townsend Street              415.832.2020 fax                 |
 |          San Francisco, CA 94103                                           |
 |                                                                            |
 +----------------------------------------------------------------------------*/

#pragma once

/**
 * \mainpage Adobe Flash Media Interactive Server Plug-in API Reference
 *
 *
 *
 * \section intro_sec Introduction
 *
 * Adobe Flash Media Interactive Server and Flash Media Development Server provide an extension mechanism that lets
 * developers create plug-ins in C++ that plug into server processes and extend the functionality of the server.
 * Plug-ins are shared library (.dll) files on Windows and .so files on Linux.
 * Flash Media Interactive Server and Flash Media Development Server include Access, File I/O, and
 * Authorization plug-ins.
 *
 *
 * \section install_sec Installation
 *
 * -# Use Microsoft .NET 2003 or Microsoft Visual C++ 2005 to compile plug-ins on Windows. Use GNU Compiler
 * Collection 3.4.x to compile plug-ins on Linux.
 * -# Stop the server.
 * -# Copy the .dll or .so files to the appropriate directory:
 * 	- <b>Access plug-in</b> files go in the <em>RootInstall</em>/modules/access directory.
 * 	- <b>Authorization plug-in</b> files go in the <em>RootInstall</em>/modules/auth directory.
 * 	- <b>File plug-in files</b> go in the <em>RootInstall</em>/modules/fileio directory.
 * -# Restart the server.
 *
 * For more information about developing plug-ins, see <em><a href="http://www.adobe.com/go/learn_fms_plugindg_en">Adobe Flash Media Interactive Server Plug-in Developer Guide</a></em>.
 *
 */

#if !defined( FmsTypes_H )
#define  FmsTypes_H

/*  
Use [u]intN_t if you need exactly N bits. 
Since these typedefs are mandated by the C99 standard, 
they are preferred over rolling your own typedefs. 
*/

#if defined( _WIN32 )

	#include <stddef.h>

	#ifndef FmsModuleTypes
	#define FmsModuleTypes
	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;

	typedef signed __int8 int8_t;
	typedef signed __int16 int16_t;
	typedef signed __int32 int32_t;
	typedef signed __int64 int64_t;
	#endif

	#define INT_PTR				intptr_t 
	#define UINT_PTR			uintptr_t

#else
	#include <stdint.h>
#endif



///
typedef uintptr_t objectid_t;

//Exact-width integer types 
typedef uint8_t	 U8,  *P_U8,  **PP_U8;
typedef uint16_t U16, *P_U16, **PP_U16;
typedef uint32_t U32, *P_U32, **PP_U32;
typedef uint64_t U64, *P_U64, **PP_U64;

typedef int8_t	I8,  *P_I8,  **PP_I8;
typedef int16_t	I16, *P_I16, **PP_I16;
typedef int32_t	I32, *P_I32, **PP_I32;
typedef int64_t	I64, *P_I64, **PP_I64;

#ifdef INT64
	#undef INT64
	#Warning "INT64 should be revisited!"
#endif
typedef I64		INT64;
///lINUX SPECIFIC
#ifndef _WIN32
	#ifdef DWORD
		#undef DWORD
		#Warning "DWORD should be revisited!"
	#endif	
	typedef U32		DWORD;
	#ifdef LONG
		#undef LONG
		#Warning "LONG should be revisited!"
	#endif	
	typedef I32	LONG;
#endif



#endif //!defined( FMS_ADAPTOR_H )


