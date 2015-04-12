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
 * \defgroup FileAdaptor File plug-in
 * \ingroup Adaptor
 *
 * Use the File plug-in interface to create a custom file plug-in
 * to handle file I/O in place of the server's default
 * operating system-based file system I/O. The File plug-in interface supports a fully
 * asynchronous model for file operations,
 * making it easier to implement network-based file I/O.
 * Currently, this mechanism only supports stream data sources.
 *
 * By default, the server uses
 * a built-in plug-in that talks to the standard operating system file system interface
 * and preserves backward compatibility to previous server versions.
 *
 * @{
 */


#include "FmsAdaptor.h"

class IFmsFileAdaptor;
class IFmsFileResponse;
class IFmsFileAdaptor2;
class IFmsFileResponse2;
class IFmsServerContext;

/**
 * \brief Flash Media Server File plug-in interface version.
 *
 * A number that describes the interface version of the File plug-in. The plug-in
 * is required to return the interface version during a call to <code>FmsCreateFileAdaptor2()</code>.
 */

static  const U16 IFMSFILEADAPTOR_MAJOR_VERSION	= 2;

/**
 * \brief Flash Media Server File plug-in interface version.
 *
 * A number that describes the interface version of the file adaptor. The plugin
 * is required to return the interface version during a call to <code>FmsCreateFileAdaptor2()</code>.
 */
static  const U16 IFMSFILEADAPTOR_MINOR_VERSION	= 0;

/**
* Called by the server to create an instance of the File plug-in.
*
*	@param	pServerCtx
*			A pointer to the server context object (see FmsAdaptor.h) that
*			the plug-in can hold on to and call to query configuration
*			information, perform logging, and so on. This pointer is valid through
*			the lifetime of the plug-in and can be stored and used at any
*			time.
*
*	@param	pResponse
*          A pointer to a response object that can be used by the plug-in
*			to report the completion status of various asynchronous operations.
*			This is done by calling the appropriate IFmsFileResponse function,
* 			such as <code>onOpen()</code>, on the
*			response object. The response object is valid only during the
*			lifetime of the plug-in instance and must not be used after
*			the plug-in has been destroyed.
*
*	@param	pFileAdaptor
*			A pointer to a valid IFmsFileAdaptor instance or <code>null</code>
*			in case of an error.
*/
extern "C" void FCExport FmsCreateFileAdaptor(
	IFmsServerContext* pServerCtx,
	IFmsFileResponse* pResponse,
	IFmsFileAdaptor*& pFileAdaptor );

/**
* Called by the server to create an instance of the File plug-in.
*
*	@param	pServerCtx
*			A pointer to the server context object (see FmsAdaptor.h) that
*			the plug-in can hold on to and call to query configuration
*			information, perform logging, and so on. This pointer is valid through
*			the lifetime of the plug-in and can be stored and used at any
*			time.
*
*	@param	pResponse
*          A void pointer to a response object that can be used by the plug-in
*			to report the completion status of various asynchronous operations.
*			This is done by calling the appropriate IFmsFileResponse function,
* 			such as <code>onOpen()</code>, on the
*			response object. The response object is valid only during the
*			lifetime of the plug-in instance and must not be used after
*			the plug-in has been destroyed.
*
*	@param	pFileAdaptor
*			A void pointer to a valid IFmsFileAdaptor instance or <code>null</code>
*			in case of an error.
*
*  @param	iVersion
*			Returns the plug-in version:
*			-HIWORD = major version.
*			-LOWORD = minor version.
*
*/
extern "C" void FCExport FmsCreateFileAdaptor2(
	IFmsServerContext* pServerCtx,
	void* pResponse,
	void*& pFileAdaptor, U32& iVersion );

/**
* Called by the server to create an instance of the File plug-in.
*
*	@param	pServerCtx
*			A pointer to the server context object (see FmsAdaptor.h) that
*			the plug-in can hold on to and call to query configuration
*			information, perform logging, and so on. This pointer is valid through
*			the lifetime of the plug-in and can be stored and used at any
*			time.
*
*	@param	pResponse
*          A void pointer to a response object that can be used by the plug-in
*			to report the completion status of various asynchronous operations.
*			This is done by calling the appropriate IFmsFileResponse function,
* 			such as <code>onOpen()</code>, on the
*			response object. The response object is valid only during the
*			lifetime of the plug-in instance and must not be used after
*			the plug-in has been destroyed.
*
*	@param	pFileAdaptor
*			A pointer to a valid IFmsFileAdaptor2 instance or <code>null</code>
*			in case of an error.
*
*  @param	iVersion
*			Returns the plug-in version:
*			-HIWORD = major version.
*			-LOWORD = minor version.
*			Should be updated to 2 or more if defining this function.
*
*/
extern "C" void FCExport FmsCreateFileAdaptor3(
	IFmsServerContext* pServerCtx,
	void* pResponse,
	IFmsFileAdaptor2*& pFileAdaptor, U32& iVersion );

/**
* Called when a previously created instance
* of the file plug-in is destroyed. Before returning from this call, the plug-in
* implementation must guarantee that all pending operations have been
* completed or aborted. After returning from the function, the plug-in should
* never implement a callback function on the response object.
*
* The server does not request any more operations
* after it calls this function.
*
*	@param	pFileAdaptor
*			A pointer to a previously created File plug-in instance.
*
*/
extern "C" void FCExport FmsDestroyFileAdaptor(
	IFmsFileAdaptor* pFileAdaptor );

/**
* Called when a previously created instance
* of the File plug-in is destroyed. Before returning from this call, the plug-in
* implementation must guarantee that all pending operations have been
* completed or aborted. After returning from the function, the plug-in should
* never implement a callback function on the response object.
*
* The server does not request any more operations
* after it calls this function.
*
*	@param	pFileAdaptor
*			A pointer to a previously created File plug-in instance.
*
*/
extern "C" void FCExport FmsDestroyFileAdaptor2(
	void* pFileAdaptor );

/**
* Called when a previously created instance
* of the File plug-in is destroyed. Before returning from this call, the plug-in
* implementation must guarantee that all pending operations have been
* completed or aborted. After returning from the function, the plug-in should
* never implement a callback function on the response object.
*
* The server does not request any more operations
* after it calls this function.
*
*	@param	pFileAdaptor
*			A pointer to a previously created File plug-in instance.
*
*/
extern "C" void FCExport FmsDestroyFileAdaptor3(
	IFmsFileAdaptor2* pFileAdaptor );

/**
 * \brief Structure for holding file attribute values.
 *
 * A structure that describes a file attribute and its value. The value is
 * represented as an FmsVariant and can be used to describe typical scalars,
 * such as signed or unsigned integers of various sizes, null-terminated char
 * strings, or unsigned char buffers with explicit sizes.
 */
struct FmsFileAttribute
{
	/**
	 * \brief The enumeration of various file attributes that may be queried.
	 *
	 * The enumeration of various file attributes that may be queried. The
	 * special <code>kAll</code> attribute may only be used in <code>open()</code> or <code>getAttributes()</code>
	 * methods to indicate that all available attributes are needed. However,
	 * it never appears in the response; instead the plug-in
	 * explicitly lists all the available attributes and their values.
	 */
	enum Type {
		kAll,				//!< A special value to indicate all attributes.
		kTimeCreated,		//!< The creation time (32-bit int) in milliseconds.
		kTimeModified,		//!< The modification time (32-bit int) in milliseconds.
		kTimeAccessed,		//!< The last accessed time (32-bit int) in milliseconds.
		kSize,				//!< The file size (64-bit int) in bytes.
		kMode,				//!< The file mode (8-bit int). 0 - file, 0x01 - directory.
		kMaxAttr			//!< The total number of attributes.
	};

	/**
	 * Describes the attribute being held.
	 */
	int attr;

	/**
	 * The value of the attribute being held.
	 */
	FmsVariant value;
};

/**
 * \brief The interface to an asynchronous File plug-in.
 *
 * The server calls the methods on this class to initiate asynchronous file
 * operations. The interface adheres to strict limited memory lifetime
 * requirements, wherein any pointers can be assumed to be valid only within
 * the function call. The read and write buffers are an exception
 * and are valid for the duration of the asynchronous operation.
 * Strings will always be null-terminated and UTF-8 encoded.
 */
class IFmsFileAdaptor
{
	public:

		/**
		 * \brief Various flags to control file and directory removal.
		 *
		 * Various flags to control file and directory removal. Only files are
		 * removed by default. The <code>kDirs</code> flag enables removal of directories
		 * and the <code>kSubDirs</code> flag enables recursive removal of subdirectories. Use the
		 * <code>kEmptyDirs</code> flag to enforce that only empty directories
		 * are removed. Use the <code>kWildCards</code> flag to enable simple DOS
		 * wild cards; they are not enabled by default.
		 */
		enum RemoveFlags
		{
			kFile		= 0,		//!< Allow file removal.
			kDirs		= 0x01,		//!< Allow directory removal.
			kSubDirs	= 0x02,		//!< Allow recursive removal.
			kEmptyDirs	= 0x04,		//!< Remove empty directories only.
			kWildCards	= 0x08,		//!< Enable simple DOS wild cards.

		};


		/**
		 * Opens the specified file. This operation is performed
		 * asynchronously; the handle is returned in the \c onOpen() callback.
		 *
		 *	@param	sFileName
		 *			Null-terminated UTF-8 string containing the name of the file
		 *			to be opened. The lifetime of the string beyond the call is
		 *			not guaranteed. The callee must copy the string if
		 *			necessary.
		 *
		 *	@param	iFlags
		 *			Bit flags describing the mode in which the file is opened.
		 *			The value of the flag must conform to the standard open
		 *			system call on the OS platform that is running the server.
		 *
		 *	@param	iMode
		 *			Creation mode in case the file is being created. The value
		 *			must conform to the standard open system call
		 *			on the OS platform that is running the server.
		 *
		 *	@param	pAttrKeys
		 *			An array of keys for all the attributes being queried; see
		 *			the enumeration in the FmsFileAttribute structure for attributes.
		 *			This array is defined only during this function call; if the
		 *			callee needs it beyond that, it must make a copy.
		 *			This may be null if no attributes need to be reported back
		 *			in \c onOpen().
		 *
		 *	@param	nAttrs
		 *			The number of elements in the \c pAttrKeys array, and should be
		 *			ignored when \c pAttrKeys is null.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int open(
			const char*	sFileName,
			int			iFlags,
			int			iMode,
			int*		pAttrKeys,
			int			nAttrs,
			void*		pCtx ) = 0;


		/**
		 * Requests one or more file attributes for a specified file to
		 * be opened.
		 *
		 *	@param	sFileName
		 *			Null-terminated UTF-8 string containing the name of the file
		 *			to be opened. The lifetime of the string beyond the call is
		 *			not guaranteed; the callee must copy the string if
		 *			necessary.
		 *
		 * 	@param	pAttrKeys
		 *			An array of keys for all the attributes being queried; see
		 *			the enumeration in the FmsFileAttribute structure for various attributes.
		 *			This array is defined only during this function call; if the
		 *			callee needs it beyond that, it must make a copy.
		 *			This will never be null, unlike the usage in \c open().
		 *
		 *	@param	pAttrKeys
		 *          An array of keys for attribute values needed at the time
		 *			the file is opened. This may be null if no attributes are
		 *			needed. The lifetime of the array is not defined beyond the
		 *			call, so the callee must copy the array if necessary.
		 *
		 *	@param	nAttrs
		 *			The number of elements in the <code>pAttrKeys</code> array.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int getAttributes(
			const char*	sFileName,
			int*		pAttrKeys,
			int			nAttrs,
			void*		pCtx ) = 0;


		/**
		 * Requests one or more file attributes for a previously opened file
		 * handle.
		 *
		 *	@param	iHandle
		 *			A handle to a previously opened file.
		 *
		 * 	@param	pAttrKeys
		 *			An array of keys for all the attributes being queried; see
		 *			the enumeration in the FmsFileAttribute struct for various attributes.
		 *			This array is defined only during this function call; if the
		 *			callee needs it beyond that, it must make a copy.
		 *			This will never be null, unlike the usage in \c open().
		 *
		 *	@param	pAttrKeys
		 *          An array of keys for attribute values needed at the time
		 *			the file is opened. This may be null if no attributes are
		 *			needed. The lifetime of the array is not defined beyond the
		 *			call, so the callee must copy the array if necessary.
		 *
		 *	@param	nAttrs
		 *			The number of elements in the \c pAttrKeys array.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int getAttributes(
			int iHandle,
			int* pAttrKeys,
			int nAttrs,
			void* pCtx ) = 0;


		/**
		 * Initiates an asynchronous file read operation.
		 *
		 *	@param	iHandle
		 *			A handle to a previously opened file.
		 *
		 *	@param	uOffset
		 *			The 64-bit file offset at which the read must be performed.
		 *
		 *	@param	pBuffer
		 *			A buffer into which to read the data. This buffer is
		 *			guaranteed to be valid beyond the function call through
		 *			the completion of the asynchronous read operation.
		 *
		 *	@param	nBytes
		 *			The number of bytes to read.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute. The <code>onRead()</code> function is
		 *			called and Flash Media Server is notified that the data has been read.
		 *			A return value of -1 indicates an error. Returning -1 tells Flash Media Server that
		 * 			execution of this command should stop. If you return -1, do not call
		 * 			<code>onRead()</code>.
		 *
		 */
		virtual int read(
			int iHandle,
			I64 uOffset,
			char* pBuffer,
			int nBytes,
			void* pCtx ) = 0;


		/**
		 * Initiates an asynchronous file write operation.
		 *
		 *	@param	iHandle
		 *			A handle to a previously opened file.
		 *
		 *	@param	uOffset
		 *			The 64-bit file offset at which the write must be performed.
		 *
		 *	@param	pBuffer
		 *			A buffer from which to write the data. This buffer is
		 *			guaranteed to be valid beyond the function call through
		 *			the completion of the asynchronous write operation.
		 *
		 *	@param	nBytes
		 *			The number of bytes to be read.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int write(
			int iHandle,
			I64 uOffset,
			char* pBuffer,
			int nBytes,
			void* pCtx ) = 0;

		/**
		 * Initiates an asynchronous file close operation.
		 *
		 *	@param	iHandle
		 *			A handle to a previously opened file.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function if <code>pCtx != 0</code>.
		 *		    If <code>pCtx == 0</code> the result upon completion is not requested by callback.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int close( int iHandle, void* pCtx ) = 0;


		/**
		 * Initiates an asynchronous removal of files or directories.
		 *
		 *	@param	sFileName
		 *			Null-terminated UTF-8 string containing the name of the
		 *			file or directories to be removed. The lifetime of the string beyond the
		 *			function is not guaranteed; the callee must copy the string
		 *			if necessary.
		 *
		 *	@param	uFlags
		 *			Flags to determine removal options: allow directory
		 *			removal, allow recursive removal, remove only empty
		 *			directories, and so on.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback if <code>pCtx != 0</code>.
		 *		    If <code>pCtx == 0</code> the result upon completion is not requested by callback.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int remove(
			const char* sFileName,
			unsigned long uFlags,
			void* pCtx ) = 0;

		/**
		 * Creates one or more directories.
		 *
		 *	@param	sFileName
		 *			Null-terminated UTF-8 string containing the name of the
		 *			directories to be created. The lifetime of the string beyond the
		 *			function is not guaranteed, so the callee must copy the string
		 *			if necessary.
		 *
		 *	@param	pCtx
		 *			An opaque context for this operation that must be returned
		 *			in the corresponding callback function.
		 *
		 *	@return	int
		 *			Returns 0 if the operation is allowed to execute.
		 *			A return value of -1 indicates an error.
		 */
		virtual int createDir(
			const char* sFileName,
			void* pCtx ) = 0;

		virtual ~IFmsFileAdaptor() {}

};

/**
* \brief This interface extends the IFmsFileAdaptor interface. It exposes
* the additional <code>rename()</code> API to the server.
*
* To initiate asynchronous file operations, the server can call the methods on this class
* instead of on the IFmsFileAdaptor class.
*
*/
class IFmsFileAdaptor2 : public virtual IFmsFileAdaptor
{
public:
	/**
	* Initiates an asynchronous file rename/move operation.
	*
	* \version Flash Media Server 4.5
	*
	*	@param	sOldFileName
	*			Null-terminated UTF-8 string containing the pathname of the
	*			file to be renamed.
	*
	*	@param	sNewFileName
	*			Null-terminated UTF-8 string containing the new pathname of the file.
	*			If a file is already present at the destination path, it is overwritten.
	*
	*	@param	pCtx
	*			An opaque context for this operation that must be returned
	*			in the corresponding callback function.
	*
	*	@return	int
	*			Returns 0 if the operation is allowed to execute, -1 otherwise.
	*/
	virtual int rename(
		const char* sOldFileName,
		const char* sNewFileName,
		void* pCtx) = 0;

	/**
	* Initiates an asynchronous file truncate operation.
	*
	* \version Flash Media Server 4.5
	*
	*	@param	iHandle
	*			A handle to a previously opened file.
	*
	*	@param	size
	*			The new size of the file after truncation
	*
	*	@param	pCtx
	*			An opaque context for this operation that must be returned
	*			in the corresponding callback function.
	*
	*	@return	int
	*			Returns 0 if the operation is allowed to execute, -1 otherwise.
	*/
	virtual int truncate(
		int iHandle,
		U64 size,
		void* pCtx) = 0;

};

/**
 * \brief The response interface provided to the File plug-in.
 *
 * The interface to a response object provided to the File plug-in. The
 * plug-in calls back methods on the response object to report completion
 * of previously initiated asynchronous operations.
 * Attributes are reported back in either the <code>onOpen()</code> or <code>onGetAttributes()</code> callback functions.
 * If the attribute value is a pointer quantity, a null-terminated
 * string, or a buffer, the server makes a copy. Since the plug-in
 * need not guarantee the validity beyond the <code>onOpen()</code> or <code>onGetAttributes()</code> callbacks,
 * it can delete the pointers at the end of the call or even use temporary copies.
 * For example, if the plug-in needs to report, the value may be an int, long.
 *
 */
class IFmsFileResponse
{
	public:
		enum {
			/**
			 * Mask to extract system error.
			 */
			kSystemErrors	= 0x0000ffff,	// Mask to extract system error
			/**
			 * Mask to extract vendor error.
			 */
			kVendorError	= 0xffff0000,	// Mask to extract vendor error
			/**
			 * Unimplemented API call.
			 */
			kUnimplemented	= 1,			// Unimplemented API call
			/**
			 * Invalid handle.
			 */
			kInvalidHandle	= 2				// Invalid handle
		};


		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * file open request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	iHandle
		 *			A handle to an open file on success; must be ignored
		 *			otherwise.
		 *
		 *	@param	pAttrs
		 *			An array of attribute values corresponding to those
		 *			requested in the <code>open()</code> call.
		 *
		 *	@param	nAttrs
		 *			The number of elements in the <code>pAttrs</code> array.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onOpen(
			U32 uStatus,
			int iHandle,
			FmsFileAttribute* pAttrs,
			int nAttrs,
			void *pCtx ) = 0;


		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	pAttrValues
		 *			An array of attribute values corresponding to those
		 *			requested in the <code>open()</code> call.
		 *
		 *	@param	nAttrs
		 *			The number of elements in the <code>pAttrs</code> array.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onGetAttributes(
			U32 uStatus,
			FmsFileAttribute* pAttrValues,
			int nAttrs,
			void* pCtx ) = 0;


		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 * <b>Note:</b> Do not call <code>onRead()</code> if a call to <code>read()</code> returns -1.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	pBuffer
		 *			The buffer that was provided for the asynchronous read operation.
		 *
		 *	@param	nBytes
		 *			The number of bytes that were successfully read into the buffer.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onRead( U32 uStatus, void* pBuffer, int nBytes, void* pCtx ) = 0;

		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	nBytes
		 *			The number of bytes that were successfully written out
		 *			from the buffer.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onWrite( U32 uStatus, int nBytes, void* pCtx ) = 0;


		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onClose( U32 uStatus, void* pCtx ) = 0;


		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onRemove( U32 uStatus, void* pCtx ) = 0;

		/**
		 * Plug-in callback to report the completion of an asynchronous
		 * <code>getAttributes()</code> request.
		 *
		 *	@param	uStatus
		 *			0 on success. Otherwise, the error code reported has two
		 *			parts: the lower 16 bits consist of the generic system
		 *			errors, and the upper 16 bits consist of a plug-in
		 *			specific code.
		 *
		 *	@param	pCtx
		 *			The opaque context that was passed into the asynchronous
		 *			operation.
		 */
		virtual void onCreateDir( U32 uStatus, void* pCtx ) = 0;

		virtual ~IFmsFileResponse() {}
};

/**
* \brief This response interface derives from the IFmsFileResponse interface.
*
* If the File plug-in derives from the IFmsFileAdaptor2 interface,
* use the IFmsFileResponse2 interface for the response to Flash Media Server.
*
*/
class IFmsFileResponse2 : public IFmsFileResponse
{
public:
	/**
	* Plug-in callback to report the completion of an asynchronous
	* <code>rename()</code> request.
	*
	* \version Flash Media Server 4.5
	*
	*	@param	uStatus
	*			0 on success. Otherwise, the error code reported has two
	*			parts: the lower 16 bits consist of the generic system
	*			errors, and the upper 16 bits consist of a plug-in
	*			specific code.
	*
	*	@param	pCtx
	*			The opaque context that was passed into the asynchronous
	*			operation.
	*/
	virtual void onRename( U32 uStatus, void* pCtx ) = 0;

	/**
	* Plug-in callback to report the completion of an asynchronous
	* <code>truncate()</code> request.
	*
	* \version Flash Media Server 4.5
	*
	*	@param	uStatus
	*			0 on success. Otherwise, the error code reported has two
	*			parts: the lower 16 bits consist of the generic system
	*			errors, and the upper 16 bits consist of a plug-in
	*			specific code.
	*
	*	@param	pCtx
	*			The opaque context that was passed into the asynchronous
	*			operation.
	*/
	virtual void onTruncate( U32 uStatus, void* pCtx ) = 0;
};

/*@}*/
