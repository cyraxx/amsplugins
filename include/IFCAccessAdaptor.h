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

/**
 * \defgroup AccessAdaptor Access plug-in
 * \ingroup Adaptor
 *
 * An Access plug-in adds another layer of security to the server;
 * it intercepts connection requests and lets you examine the client and the server
 * to determine whether requests should be accepted, rejected, or redirected before
 * the requests reach the server's script layer.
 *
 * <p>
 * You can code the plug-in to accept, reject, or redirect requests based upon how many
 * users are connected to the server and the amount of bandwidth being consumed. You can set read and write
 * access for files and folders on the server, set permissions to access audio and video
 * bitmap data, and inspect client properties. You could also
 * query your organization's database of users and passwords to determine which connection
 * requests should be allowed. Once the plug-in accepts the connection, you could update
 * the database with a record of the user's access to the server.
 * </p>
 *
 * <p>
 * For more information, see <em><a href="http://www.adobe.com/support/documentation">Flash Media Interactive Server Plug-in Developer Guide</a></em>.
 * </p>
 *
 * @{
 */

#if !defined( IFCAccessAdaptor_H )
#define  IFCAccessAdaptor_H

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

#define	 IFC_ACCESS_ENTRY_PROC	"IFCCreateAccessAdaptor"
#define  STRING_VALUE_BUFFER_LEN 128

class IFCAccessContext;
class IFCStreamInfo;
class IFCAccess;
class IFCAccessAdaptor;

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * Called by the server to create an instance of the Access plug-in.
 *  \param	pServer
 *			A pointer the plug-in can use to query the server for information such as statistics.
 *			This pointer is valid for the lifetime of the plug-in and can be stored and used at any time.
 *
 *  \param	pAdaptor
 *			A pointer to the instantiated plug-in. This is returned to the server and used by the
 *			server to communicate with the plug-in.
 *
 */
extern int FCExport IFCCreateAccessAdaptor(IFCAccessContext* pServer, IFCAccessAdaptor*& pAdaptor);

#ifdef  __cplusplus
}
#endif

/**
 * \brief The interface of an Access plug-in. This is the interface that the server uses to access
 * methods of the plug-in.
 */
class FCExport IFCAccessAdaptor
{
	public:
		inline virtual ~IFCAccessAdaptor() {}

		/**
		 * Called by the server to get the version of the plug-in.
		 *
		 *	\param	iMajor
		 *			The major version of the plug-in.
		 *
		 *	\param	iMinor
		 *			The minor version of the plug-in.
		 *
		 *	\param	iMicro
		 *			The micro version of the plug-in.
		 *
		 */
		virtual void getVersion( int& iMajor, int& iMinor, int& iMicro ) const = 0;

		/**
		 * Called by the server to get a string that describes the plug-in.
		 *
		 */
		virtual const char* getDescription() const = 0;

		/**
		 * Called by the server to notify the plug-in of an access event. The IFCAccess
		 * class lists the supported access events. Write code in this callback method to control
		 * access to the server.
		 *
		 *	\param	pAccess
		 *			A pointer to an access event object that contains information about the access event.
		 *
		 */
		virtual void onAccess( IFCAccess* pAccess ) = 0;
};

/**
 * \brief This interface is implemented by the server and
 * provides the plug-in methods to query the server for information.
 */
class FCExport IFCAccessContext
{
	public:
		/**
		* \brief The enumeration for the statistics in <code>getStats()</code>.
	    	*/
		enum enStats {
			eTOTAL_CONNECTED,	//!< Total connections.
			eBYTES_IN,		//!< Total bytes received.
			eBYTES_OUT		//!< Total bytes sent.
		};

		inline virtual ~IFCAccessContext() {}

		/**
		 * Returns a string indicating the server version. The string format is:
		 * \<major\>,\<minor\>,\<micro\>,\<buildnum\>.
		 * For example:
		 *
		 *	<code>"3,0,0,1"</code>
		 *
		 */
		virtual const char* getVersion() const = 0;

		/**
		 * Returns a string that describes the server. For example:
		 *
		 * <code>"Adobe Flash Media Interactive Server 3"</code>
		 *
		 */
		virtual const char* getDescription() const = 0;

		/**
		 * Returns the specified server statistic.
		 *
		 *	\param	stat
		 *			A statistic to query.
		 *
		 *	\param	strValue
		 *			String buffer into which the server writes the queried statistic.
		 *			The buffer must be at least <code>STRING_VALUE_BUFFER_LEN</code> bytes in length.
		 *
		 *	\param	iValueLen
		 *			Specifies the size of the buffer being
		 *			passed in. This is an in/out parameter. If <code>0</code> is specified, it returns the minimum buffer size
		 *			required: the value of <code>STRING_VALUE_BUFFER_LEN</code>.
		 *
		 */
		virtual bool getStats(enStats stat, char *strValue, int& iValueLen) const = 0;
};

/**
 * The plug-in field names.
 *
 */
namespace fms_access
{

	static const char* FLD_REFERRER		        = "c-referrer";				///< The URI of the SWF file or the server in which this connection originated.
	static const char* FLD_USER_AGENT	        = "c-user-agent";			///< The client user-agent string.
	static const char* FLD_SERVER_URI	        = "s-uri";					///< The URI of server to which the client is connecting.
	static const char* FLD_CLIENT_IP	        = "c-ip";					///< The client IP address.
	static const char* FLD_CLIENT_PROTO         = "c-proto";				///< The protocol the client used to request a connection to the server.
	static const char* FLD_CLIENT_PROTO_VER     = "c-proto-ver";			///< The protocol revision
	static const char* FLD_CLIENT_TYPE          = "c-connect-type";			///< The type of connection; service, group, normal
	static const char* FLD_READ_ACCESS			= "readAccess";				///< Sets read access to server folders that contain streams and shared objects.
	static const char* FLD_WRITE_ACCESS			= "writeAccess";			///< Sets write access to server folders that contain streams and shared objects.
	static const char* FLD_READ_LOCK			= "readAccessLock";			///< Sets read access to server folders and prevents the \c readAccess property from being called by a server-side script.
	static const char* FLD_WRITE_LOCK			= "writeAccessLock";		///< Sets write access to server folders and prevents the \c writeAccess property from being called by a server-side script.
	static const char* FLD_AUDIO_SAMPLE_ACCESS	= "audioSampleAccess";		///< Enables Flash Player to access raw, uncompressed audio data from streams in the specified folders.
	static const char* FLD_VIDEO_SAMPLE_ACCESS	= "videoSampleAccess";		///< Enables Flash Player to access raw, uncompressed video data from streams in the specified folders.
	static const char* FLD_AUDIO_SAMPLE_LOCK	= "audioSampleAccessLock";	///< Enables Flash Player to access audio data from streams and prevents the \c audioSampleAccess property from being called in a server-side script.
	static const char* FLD_VIDEO_SAMPLE_LOCK	= "videoSampleAccessLock";	///< Enables Flash Player to access video data from streams and prevents the \c videoSampleAccess property from being called in a server-side script.
	static const char* FLD_CORE_ID				= "coreIdNum";				///< Specifes which core process handles the client connection. A value of -1 means no core processes are running. Specify this field in calls to <code>setValue()</code> and <code>getValue()</code>.																		///< By default, the server calculates a hash based on the URL. If you specify the coreIdNum field, the server uses the formula "coreIdNum % numprocs instead".
	static const char* FLD_PAGE_URL				= "x-page-url";				///< The URL of the SWF file or the server in which this connection originated.
	static const char* FLD_NEAR_NONCE			= "nearNonce";				///< The near nonce of an RTMPE connection.
	static const char* FLD_FAR_NONCE			= "farNonce";				///< The far nonce of an RTMPE connection.
	static const char* FLD_FORWARDED_FOR		= "x-forwarded-for";		///< x-forwarded-for header as included by proxies on RTMPT packets
}


/**
 * \brief The interface to an access event.  Access events are implemented
 * by the server and are passed to the plug-in in the <code>onAccess()</code> method of
 * IFCAccessAdaptor. The plug-in can use this interface to get information about
 * the access event.  Based on the information provided, the plug-in can take
 * appropriate action for that event.
 *
 * \b Note: The memory for this object is allocated by the server and is released
 * once <code>accept()</code>, <code>reject()</code>, or <code>redirect()</code> are called.
 * Accessing this object after calling one of these methods could access invalid memory and result in
 * unpredictable behavior.
 */
class FCExport IFCAccess
{
	public:

		//! Indicates a client is connected to the server.

		enum Type { CONNECT };

		/**
		 * Returns the type of access event.
		 *
		 */
		virtual Type getType() const = 0;

		/**
		 * Queries information about an event. Currently,
		 * the server supports only the CONNECT event, which indicates a
		 * client is connected to the server. The server returns the information
		 * in a string. The pointer is valid only for the scope of the call. If the
		 * plug-in needs the data to persist longer than the duration of the call,
		 * it must copy the data. The following values can be queried
		 * for a CONNECT event:
		 *
		 *	- <code>c-referrer</code>
		 *	- <code>c-user-agent</code>
		 *	- <code>s-uri</code>
		 *	- <code>c-ip</code>
		 *	- <code>c-proto</code>
		 *	- <code>coreIdNum</code>
		 *  - <code>x-page-url</code>
		 *
		 * For more information, see the documentation for the <code>fms_access</code> namespace.
		 *
		 *	\param	sName
		 *			Name of the value to query.
		 *
		 *
		 */
		virtual const char* getValue( const char* sName ) = 0;

		/**
		 * Allows you to modify event information, if applicable. For a
		 * CONNECT event, you can modify the <code>readAccess</code>, <code>writeAccess</code>,
		 * <code>readAccessLock</code>, <code>writeAccessLock</code>, <code>audioSampleAccess</code>,
		 * <code>videoSampleAccess</code>, <code>audioSampleAccessLock</code>, <code>videoSampleAccessLock</code>,
		 * <code>c-referrer</code>, <code>c-user-agent</code>,<code>s-uri</code>, and <code>coreIdNum</code> fields.
		 *
		 *	\param	sName
		 *			Name of the field to change.
		 *
		 *	\param	sValue
		 *			New value to set.
		 *
		 */
		virtual bool setValue( const char* sName, const char* sValue ) = 0;

		/**
		 * Changes the <code>readAccess</code> property of the connecting client.
		 * This API is deprecated; to set the <code>readAccess</code> and <code>readAccessLock</code> properties,
		 * call \c setValue().
		 *
		 *	\param	sReadAccess
		 *			The read-access permissions to set for this client.
		 *
		 *	\param	bLockAccess
		 *			If true, a server-side script is not allowed to change the client's read access.
		 *
		 */
		virtual bool setReadAccess( const char* sReadAccess, bool bLockAccess = true ) = 0;

		/**
		 * Changes the <code>writeAccess</code> property of the connecting client.
		 * This API is deprecated; to set the <code>writeAccess</code> and <code>writeAccessLock</code> properties,
		 * call <code>setValue()</code>.
		 *
		 *	\param	sWriteAccess
		 *			The write-access permissions to set for this client.
		 *
		 *	\param	bLockAccess
		 *			If true, a server-side script is not allowed to change a client's read access.
		 *
		 */
		virtual bool setWriteAccess( const char* sWriteAccess, bool bLockAccess = true ) = 0;

		/**
		 * Accepts a client connection. A client connection remains pending
		 * until this method (or the <code>reject()</code> method or the <code>redirect()</code> method) is called. The IFCAccess object is no longer
		 * available once this method is called; therefore, this method is an implicit destructor.
		 *
		 */
		virtual void accept() = 0;

		/**
		 * Rejects a client connection. A client connection remains pending
		 * until this method (or the <code>accept()</code> method or the <code>redirect()</code> method) is called. The IFCAccess object is no longer
		 * available once this method is called; therefore, this method is an implicit destructor.
		 *
		 *	\param	sReason
		 *			Specifies a reason for the rejection. This string is set in the <code>description</code> property
		 *			of the info object that is returned to the client.
		 *
		 */
		virtual void reject( const char* sReason ) = 0;

		/**
		 * Redirects the client connection. The URI can be fully rewritten, including the protocol, host, port, application name, and so on.
		 *
		 * A client connection remains pending until this method
		 * (or the <code>accept()</code> method or the <code>reject()</code> method) is called. The IFCAccess object is no longer
		 * available once this method is called, therefore, this method is an implicit destructor.
		 *
		 */
		virtual void redirect( const char* sUri, const char* sReason ) = 0;
};

/*@}*/

#endif	// !defined( IFCAccessAdaptor_H )
