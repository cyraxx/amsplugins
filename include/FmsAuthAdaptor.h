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
#if !defined( FmsAuthAdaptor_H )
#define  FmsAuthAdaptor_H

#pragma once

#include "FmsAdaptor.h"
#include "FmsAuthEvents.h"

/**
 * \defgroup AuthAdaptor Authorization plug-in
 * \ingroup Adaptor
 *
 * An Authorization plug-in controls client access to the server.
 *
 * When the server starts, it indexes all events listed in the Authorization plug-in.
 * The Authorization plug-in examines events in the incoming connection requests.
 * Some events require only that the server be notified. In these cases, the server continues operating, as
 * authorization is not required. Other events require authorization before the server
 * can deliver or publish the event.
 *
 * Each event permits access to certain properties, which can be either read-only or read-write.
 * These properties and events are listed in <i><a href="http://www.adobe.com/support/documentation/">
 * Flash Media Interactive Server Plug-in Developer Guide</a></i>.
 *
 * The server expects the following main entry points in the plug-in:
 *   <ul>
 *     <li> FmsCreateAuthAdaptor: Creates an Authorization plug-in.
 *     <li> FmsDestroyAuthAdaptor: Destroys an Authorization plug-in created with <code>FmsCreateAuthAdaptor</code>.
 *     <li> FmsCreateAuthAdaptor2: Creates an Authorization plug-in. Use this method to
 *			call <code>IFmsAuthServerContext::getClientStats</code>.
 *     <li> FmsDestroyAuthAdaptor2: Destroys an Authorization plug-in created with <code>FmsCreateAuthAdaptor2</code>.
 *	   <li> FmsCreateAuthAdaptor3: Creates an Authorization plug-in. Use this method to use
 *          <code>IFmsAuthServerContext2</code> to deliver status codes and an error description to the client when
 *			the plug-in does not authorize an event.
 *     <li> FmsDestroyAuthAdaptor3: Destroys an Authorization plug-in created with <code>FmsCreateAuthAdaptor3</code>.
 *   </ul>
 *
 *
 * @{
 */

static  const U16 INTERFACE_MAJOR_VERSION	= 2;
static  const U16 INTERFACE_MINOR_VERSION	= 0;

/**
 * This struct defines the client statistics passed from the server in a call to
 * <code>IFmsAuthServerContext::getClientStats</code>.
 */

struct FmsClientStats
{
	INT64		bytes_in; 	 //!< Total number of bytes received.
	INT64		bytes_out;	 //!< Total number of bytes sent.
	U32			msg_in;      //!< Total number of messages received.
	U32			msg_out;     //!< Total number of messages sent.
	U32			msg_dropped; //!< Total number of messages dropped.
};
typedef FmsClientStats* FmsClientStatsPtr;

class IFmsAuthServerContext;
class IFmsAuthServerContext2;
class IFmsAuthAdaptor;
class IFmsServerContext;
class IFmsAuthEvent;


/**
 * Called by the server to create an instance of the Authorization plug-in.
 *
 *  @param	pAuthServerCtx
 *			A pointer to the IFmsServerContext object (see FmsAdaptor.h) that
 *			the plug-in can use to query configuration
 *			information, perform logging, and so on. This pointer is valid through
 *			the lifetime of the plug-in and can be stashed and used at any
 *			time.
 *
 *  @param	pAuthAdaptor
 *			A pointer to an Authorization plug-in.
 *
 */

extern "C" void FCExport FmsCreateAuthAdaptor(IFmsAuthServerContext* pAuthServerCtx, IFmsAuthAdaptor*& pAuthAdaptor);

/**
 * Called by the server to create an instance of the Authorization plug-in.
 * Use this creator if you want to call <code>IFmsAuthServerContext::getClientStats</code>.
 * This creator passes the plug-in version number to the server. Only Flash Media Server 3.5(and above)
 * checks the plug-in version number and only Flash Media Server 3.5(and above) supports the
 * <code>getClientStats</code> method.
 *
 *  @param	pAuthServerCtx
 *			A pointer to the IFmsServerContext object (see FmsAdaptor.h) that
 *			the plug-in can use to query configuration
 *			information, perform logging, and so on. This pointer is valid through
 *			the lifetime of the plug-in and can be stashed and used at any
 *			time.
 *
 *  @param	pAuthAdaptor
 *			A pointer to an Authorization plug-in.
 *
 *  @param	iVersion
 *			Returns the plug-in version:
 *			-HIWORD = major version.
 *			-LOWORD = minor version.
 *
 */

extern "C" void FCExport FmsCreateAuthAdaptor2(IFmsAuthServerContext* pAuthServerCtx,
								IFmsAuthAdaptor*& pAuthAdaptor, U32& iVersion);

/**
* Called by the server to create an instance of the Authorization plug-in.
* Use this creator if you want to call <code>IFmsAuthServerContext2::onAuthorize</code> to
* pass on the reason string, status code and error code along with the authorization failure flag.
* This creator passes the plug-in version number to the server. Only Flash Media Server 4
* supports this extension of <code>onAuthorize</code> method, where description for unauthorize
* can be specified.
*
*  @param	pAuthServerCtx
*			A pointer to the IFmsServerContext object (see FmsAdaptor.h) that
*			the plug-in can use to query configuration
*			information, perform logging, and so on. This pointer is valid through
*			the lifetime of the plug-in and can be stashed and used at any
*			time.
*
*  @param	pAuthAdaptor
*			A pointer to an Authorization plug-in.
*
*  @param	iVersion
*			Returns the plug-in version:
*			-HIWORD = major version.
*			-LOWORD = minor version.
*
*/
extern "C" void FCExport FmsCreateAuthAdaptor3(IFmsAuthServerContext2* pAuthServerCtx,
											   IFmsAuthAdaptor*& pAuthAdaptor, U32& iVersion);

/**
 * Called by the server to destroy an instance
 * of the Authorization plug-in created by <code>FmsCreateAuthAdaptor</code>.
 *
 *  @param	pAuthAdaptor
 *			A pointer to an Authorization plug-in.
 *
 */

extern "C" void FCExport FmsDestroyAuthAdaptor(
	IFmsAuthAdaptor* pAuthAdaptor );

/**
 * Called by the server to destroy an instance
 * of the Authorization plug-in created by <code>FmsCreateAuthAdaptor2</code>.
 *
 *  @param	pAuthAdaptor
 *			A pointer to an Authorization plug-in.
 *
 */

extern "C" void FCExport FmsDestroyAuthAdaptor2(
	IFmsAuthAdaptor* pAuthAdaptor );

/**
* Called by the server to destroy an instance
* of the Authorization plug-in created by <code>FmsCreateAuthAdaptor3</code>.
*
*  @param	pAuthAdaptor
*			A pointer to an Authorization plug-in.
*
*/

extern "C" void FCExport FmsDestroyAuthAdaptor3(
	IFmsAuthAdaptor* pAuthAdaptor );


/**
 * \brief The interface to an asynchronous Authorization plug-in. The plug-in calls the methods
 * on this class to initiate, cancel, or authorize asynchronous operations. The interface is subject
 * to strict limited memory lifetime requirements, and pointers can be
 * assumed to be valid only within the function call. The read and
 * write buffers are an exception and are valid for the entire
 * asynchronous operation. Strings are null-terminated and UTF-8
 * encoded.
 */

class IFmsAuthServerContext : public IFmsServerContext
{

	public:


	/**
	* Authorizes server events.
	* This plug-in call should complete a pending server operation.
	*
	*	@param pAev
	*	    A pointer to an authorization event.
	*
	*	@param bAuthorized
	*		The Boolean value to authorize the event.
	*
	*/
		virtual void onAuthorize(IFmsAuthEvent* pAev, bool bAuthorized) = 0;


	/**
	* Provides notification completion.
	* This plug-in call should notify the server that an event is not needed anymore.
	*
	*	@param pAev
	*	    A pointer to an authorization event.
	*
	*/
		virtual void onNotify(const IFmsAuthEvent* pAev) = 0;

	/**
	 * Tells the server to exclude receiving specified
	 * events after the plug-in is loaded. This call is made once, and
	 * event selection is valid through the lifetime of the plug-in.
     *
	 *	@param  aevBit
	 *			The array from a <code>getEvents()</code> call (authorization or notification) of
	 * 			32-bit integers, where each bit in the integer represents an event according to
	 *			an EventType definition in the IFmsAuthEvent class.
	 *
	 *	@param  eventId
	 *			An array indicating the events to exclude,
	 *			where each member is represented by an event type according to an
	 *			EventType definition in the IFmsAuthEvent class.
	 *
	 *	@param  count The size of the array.
	 *
	 *	@param  count1 The size of the array.
	 *
	 */

		virtual void excludeEvents(I32 aevBit[], int count, IFmsAuthEvent::EventType eventId[], int count1) = 0;

     /**
	* Requests client statistics from the server.
	*
	*	@param  clientStatsHandle
	*           The client stats handle in 64-bit value
	*
	*	@param  baseStats
	*           The client statistics that the server provides
	*
	*/
		virtual bool getClientStats(I64 clientStatsHandle, FmsClientStats& baseStats) = 0;

     /**
	  * Called by the server to destroy an object.
      *
      */

	protected:
		virtual ~IFmsAuthServerContext() {}

};

/**
* \brief This interface extends IFmsAuthServerContext to delivers status codes and an error description to the client when the Authorization plug-in
* does not authorize an event. To use this interface, use the <code>FmsCreateAuthAdaptor3()</code> and <code>FmsDestroyAuthAdaptor3()</code> methods.
*/

class IFmsAuthServerContext2 : public IFmsAuthServerContext
{
public:

	/**
 	* The server sends these codes to the client to describe an authorization failure.
 	*/

	enum StatusCode
	{
		kDefaultStatus,					//!< Returns the default Flash Media Server status for the event type.

		kNC_CONNECT_SUCCESS,			//!< "NetConnection.Connect.Success"
		kNC_CONNECT_FAILED,				//!< "NetConnection.Connect.Failed"
		kNC_CONNECT_REJECT,				//!< "NetConnection.Connect.Rejected"
		kNC_CONNECT_CLOSE,				//!< "NetConnection.Connect.Closed"
		kNC_CONNECT_INVALID_APP,		//!< "NetConnection.Connect.InvalidApp"
		kNC_CONNECT_SHUTDOWN,			//!< "NetConnection.Connect.AppShutdown"

		kNS_FAILED,						//!< "NetStream.Failed"
		kNS_CONNECT_FAILED,				//!< "NetStream.Connect.Failed"

		kNS_PLAY_STOP,					//!< "NetStream.Play.Stop"
		kNS_PLAY_FAILED,				//!< "NetStream.Play.Failed"
		kNS_PLAY_STREAM_NOT_FOUND,		//!< "NetStream.Play.StreamNotFound"
		kNS_PLAY_STREAMCHANGED,			//!< "NetStream.Play.StreamChanged"
		kNS_PLAY_STREAMDELETED,			//!< "NetStream.Play.StreamDeleted"

		kNS_RECORD_STOP,				//!< "NetStream.Record.Stop"
		kNS_RECORD_NO_ACCESS,			//!< "NetStream.Record.NoAccess"
		kNS_RECORD_ALREADY_EXISTS,		//!< "NetStream.Record.AlreadyExists"
		kNS_RECORD_INSUFFICIENTSPACE,	//!< "NetStream.Record.DiskQuotaExceeded"

		kNS_PUBLISH_BADNAME,			//!< "NetStream.Publish.BadName"
		kNS_PUBLISH_MCAST_FAILED,		//!< "NetStream.Publish.MCastFailed"
		kNS_SEEK_FAILED,				//!< "NetStream.Seek.Failed"
		kNS_INVALID_ARGUMENTS,			//!< "NetStream.InvalidArg"

		kNC_GROUP_CONNECT_FAILED,		//!< "NetGroup.Connect.Failed"
		kNC_GROUP_CONNECT_CLOSED,		//!< "NetGroup.Connect.Closed"
	};

	/**
	* The description of the authentication failure.
	* You can define the error code and the reason string. The server sends the status code.
	*/

	struct  AuthFailureDesc
	{
	public:

		/**
		* The constructor function.
		*
		* @param	reason
		*			By default, the reason string is null.
		*
		* @param 	statusCode
		*			Status code sent to the client with an error description string describing the failure.
		*
		* @param 	errorCode
		*			When an event is not authorized, the error code is logged as x-status in the Auth Event logs.
		* 			If an error code is 0 then 401 is logged or if not specified (-1 by default), value specified in statusCode is logged.
		*
		*/

		AuthFailureDesc(const char* reason = 0, StatusCode statusCode = kDefaultStatus, int errorCode = 0)
			:m_reasonStr(reason),
			m_statusCode(statusCode),
			m_errorCode(errorCode)
		{}

		/**
		* A user-defined error code that is logged as x-status in the Auth Event logs when an event is unauthorized.
		* If this value is set to 0 then 401 is logged, else if not specified (-1 by default) the value specified in statusCode is logged.
		*/

		int m_errorCode;

		/**
		* Defines the reason for the Authorization failure for the event. This is passed to the client in the <code>description</code> field of the <code>onStatus</code> <code>info</code> object.
		*/

		const char* m_reasonStr;

		/**
		* An enumeration that maps to the Flash Media Server status codes. This value is passed to the client in the <code>code</code> field of the <code>onStatus</code> <code>info</code> object.
		* If this value is not defined or is set to <code>kDefaultStatus</code>, the status code is delivered as it was with IFmsAuthServerContext.
		*/

		StatusCode m_statusCode;
	};

	/**
	* Authorizes server events.
	* This call should complete a pending server operation.
	*
	*	@param pAev
	*	    A pointer to an authorization event.
	*
	*	@param bAuthorized
	*		The Boolean value to authorize the event.
	*
	*	@param desc
	*		An input parameter that is a pointer to AuthFailureDesc. Defines the reason and error code for the authorization failure.
	*		The auth module owns the pointer.
	*
	*/
	virtual void onAuthorize(IFmsAuthEvent* pAev, bool bAuthorized, const AuthFailureDesc* desc) = 0;

};

/**
 * \brief The interface to a response object provided to the Authorization plug-in.
 * The server calls the appropriate method upon receiving the event.
 */

class IFmsAuthAdaptor
{
	public:

		/**
		 * Reports the arrival of a server event.
		 * The server operation is pending until the plug-in calls
         * <code>authorizeEvent()</code> with a Boolean authorization status.
		 *
		 *	@param  pAev
		 *			A pointer to an authorization event.
		 *
		 */
		virtual void authorize(IFmsAuthEvent* pAev) = 0;

		/**
		 * Reports the arrival of a server event.
		 * Server operation continues because authorization is not required.
		 *
		 **	@param	pAev
		 *			pointer to IFmsAuthEvent
		 *
		 */
		virtual void notify(IFmsAuthEvent* pAev) = 0;

		/**
		 * Cancels receiving particular
		 * server events after the plug-in is loaded. This call is made once, and
		 * event selection is valid through the lifetime of the plug-in.
         *
		 *
		 *	@param  aevBitAuth
		 *			An array of 32-bit integers, where each bit in the integer
		 *			represents an event according to an EventType definition in
		 *			the IFmsAuthEvent class.
		 *          To cancel receiving a particular event, set the value of the bit to 1; otherwise,
		 *          the server calls <code>authorize()</code> when it receives the event.
		 *          This parameter represents authorization bits.
		 *
		 * @param	aevBitNotf
		 *			An array of 32-bit integers where each bit in the integer
		 *			represents an event according to an EventType definition in
		 *			the IFmsAuthEvent class.
		 *          To cancel receiving a particular event, set the value of the bit to 1; otherwise,
		 *          the server calls <code>notify()</code> when it receives the event.
		 *          This parameter represents notification bits.
		 *
		 *	@param  count The size of the array. With 32 or fewer events, the array size is 1.
		 *	With 33-64 events, the array size is 2, and so on.
		 *
		 */
		 virtual void getEvents(I32 aevBitAuth[], I32 aevBitNotf[], unsigned int count) = 0;

	 /**
	  * Called by the server to destroy an object.
	  *
      */
	 virtual ~IFmsAuthAdaptor() {}


};

#endif

/*@}*/


