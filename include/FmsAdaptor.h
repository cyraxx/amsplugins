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
 * \mainpage Adobe Flash Media Server Plug-in API Reference
 *
 *
 *
* \section intro_sec Introduction
 *
 * Use Adobe Flash Media Server C++ plug-ins to extend the functionality of the server.
 * Plug-ins are shared library (.dll) files on Windows and .so files on Linux.
 * Flash Media Enterprise Server, Flash Media Interactive Server, and Flash Media Development Server support Access, File, and
 * Authorization plug-ins. Flash Media Streaming Server supports the Access plug-in only.
 *
 * For information about developing plug-ins, see <em><a href="http://www.adobe.com/go/learn_fms_devguide_en">Adobe Flash Media Server Developer Guide</a></em>.
 *
 */

#if !defined( FMS_ADAPTOR_H )
#define FMS_ADAPTOR_H

#include "FmsTypes.h"

#if defined( _WIN32 )

	#if defined(FC_DLL_EXPORT)
		#define FCExport	__declspec(dllexport)
	#elif defined(FC_LINK_STATIC)
		#define FCExport
	#else
		#define FCExport	__declspec(dllimport)
	#endif

	#pragma warning(disable : 4251)
	#pragma warning(disable : 4275)

#else

	#define FCExport

#endif

#define MKWORD(a, b)       ((U16)(((U8)((U32)(a) & 0xff)) | ((U16)((U8)((U32)(b) & 0xff))) << 8))
#define MKLONG(a, b)       ((long)(((U16)((U32)(a) & 0xffff)) | ((U32)((U16)((U32)(b) & 0xffff))) << 16))
#define LWORD(l)           ((U16)((U32)(l) & 0xffff))
#define HWORD(l)           ((U16)((U32)(l) >> 16))
#define LBYTE(w)           ((U8)((U32)(w) & 0xff))
#define HBYTE(w)           ((U8)((U32)(w) >> 8))

/**
* The definition of client types.
*/
#define TYPE_NORMAL				0x1		///< Normal client.
#define TYPE_GROUP				0x2		///< Group client.
#define TYPE_GROUP_ELEMENT		0x4		///< Group element client.
#define	TYPE_SERVICE			0x8		///< Service client.
#define	TYPE_ALL				0xf		///< All.

/**
* The definition of object encoding (serialization scheme).
*/
#define ENCODE_AMF0				0		///< AMF0 encoding.
#define ENCODE_AMF3				3		///< AMF3 encoding.

/**
 * \brief A tagged variant that holds values of various types.
 *
 * A tagged variant that can hold signed and unsigned integers of various
 * widths, floats, doubles, char* strings, and sized buffers.
 * The type member indicates which of the above is being held. This
 * structure is never more than 12 bytes on 32-bit platforms.
 *
 */
struct FCExport FmsVariant
{
	/// Type tag indicating what is being held in the union.
	enum Type {
		kU8,			///< Type tag for an unsigned 8-bit integer.
		kU16,			///< Type tag for an unsigned 16-bit integer.
		kU32,			///< Type tag for an unsigned 32-bit integer.
		kI8,			///< Type tag for a signed 8-bit integer.
		kI16,			///< Type tag for a signed 16-bit integer.
		kI32,			///< Type tag for a signed 32-bit integer.
		kI64,			///< Type tag for a signed 64-bit integer.
		kFloat,			///< Type tag for a floating point number.
		kDouble,		///< Type tag for a double precision floating-point number.
		kString,		///< Type tag for a null-terminated char* string
		kBuffer			///< Type tag for a sized unsigned char* buffer
	};

	Type type;			///< \brief The value type being held.

	/// An anonymous union of all supported value types.
	union
	{
		U8 u8;			///< Unsigned 8-bit int value
		U16 u16;		///< Unsigned 16-bit int value
		U32 u32;		///< Unsigned 32-bit int value
		I8 i8;			///< Signed 8-bit int value
		I16 i16;		///< Signed 16-bit int value
		I32 i32;		///< Signed 32-bit int value
		I64 i64;		///< Signed 64-bit int value
		float f;		///< Float value
		double d;		///< Double value

		I8* str;		///< Null-terminated char string

		/// A buffer of a specified size.
		struct {
			U8* buf;	///< Unsigned char buffer
			U32 size;	///< Size of unsigned char buffer
		};
	};

	// Convenient setter functions

	/// \brief Set an unsigned 8-bit int value and adjust the type.
	void setU8( U8 val )			{ type = kU8;		u8 = val; }

	/// \brief Set an unsigned 16-bit int value and adjust the type.
	void setU16( U16 val )			{ type = kU16;		u16 = val; }

	/// \brief Set an unsigned 32-bit int value and adjust the type.
	void setU32( U32 val )			{ type = kU32;		u32 = val; }

	/// \brief Set an signed 8-bit int value and adjust the type.
	void setI8( I8 val )			{ type = kI8;		i8 = val; }

	/// \brief Set an signed 16-bit int value and adjust the type.
	void setI16( I16 val )			{ type = kI16;		i16 = val; }

	/// \brief Set an signed 32-bit int value and adjust the type.
	void setI32( I32 val )			{ type = kI32;		i32 = val; }

	/// \brief Set an signed 64-bit int value and adjust the type.
	void setI64( I64 val )			{ type = kI64;		i64 = val; }

	/// \brief Set a float value and adjust the type.
	void setFloat( float val )		{ type = kFloat;	f = val; }

	/// \brief Set a double value and adjust the type.
	void setDouble( double val )	{ type = kDouble;	d = val; }

	/// \brief Set a null terminated string value and adjust the type.
	void setString( I8* val )		{ type = kString;	str = val; }

	/// \brief Set a sized unsigned char buffer and adjust the type.
	void setBuffer( U8* b, U32 sz )	{ type = kBuffer;	buf = b; size = sz; }
};


/**
 * \brief An interface to access the server from the plug-in.
 *
 * The server context is provided to an plug-in when the plug-in is created.
 * The plug-in can use this to query information from the server.
 *
 */
class FCExport IFmsServerContext
{
	public:
		/**
		 * Type of message to log.
		 */
		enum MessageType
		{
			kError,				///< Error message
			kWarning,			///< Warning message
			kInformation,		///< Information message
		};

		/**
		 * Returns the server version:
		 * -HIWORD = major version.
		 * -LOWORD = minor version.
		 * <p>
		 */
		virtual U32 getVersion() = 0;

		/**
		 * Returns the configuration value associated with a filter.
		 *
		 *	\param	pstrKey
		 *			Configuration key name. This must be a UTF-8 string.
		 *			All configuration keys specified here must be located
		 *			in Server.xml under the the Server/Plugins/UserDefined XML tag
		 *			for the plug-in.
		 *			For example, <code>cpstrKey</code> would be "UserKey1" to find a key in
		 *			Server.xml:
		 *
		 *  \verbatim
		 *   <Server>
		 *      <Plugins>
		 *	      <UserDefined>
		 *            <UserKey1>value</UserKey1>
		 *        </UserDefined>
		 *      </Plugins>
		 *   </Server>
		 *  \endverbatim
		 *
		 *	\param	pstrVal
		 *			The buffer to return the value of the configuration key.
		 *
		 *	\param	iBufSize
		 *			Size of the buffer, <code>pstrVal</code>, in bytes.
		 */
		virtual int getConfig(
			const char* pstrKey,
			char** pstrVal,
			int iBufSize ) = 0;

		/**
		 * Called from a library to dump a message into the system
		 * log.
		 *
		 *	\param	pstrMsg
		 *			Log message; this must be a UTF-8 string.
		 *
		 *	\param	suType
		 *			IFmsServerContext::MessageType.
		 *
		 *	\param	boolToEventLog
		 *			Whether to log to the system event log.
		 */
		virtual void log(
			const char* pstrMsg,
			U16 suType,
			bool boolToEventLog = false ) = 0;


		/**
		 * Called by the server to destroy an object.
		 *
		 */

		virtual ~IFmsServerContext()  {}
};

#endif //!defined( FMS_ADAPTOR_H )


