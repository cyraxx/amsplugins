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
#if !defined( FmsAuthEvents_H )
#define  FmsAuthEvents_H

#include "FmsAdaptor.h"

class IFmsDisconnectAction;
class IFmsNotifyAction;

/**
 *
 * \brief The interface to an event object provided to the Authorization plug-in.
 *
 */
class IFmsAuthEvent
{
	public:

		/**
		* \brief The enumeration of event types.
	    */
		enum EventType 	{
			E_APPSTART = 0,			//!< Start an application.
			E_APPSTOP,				//!< Stop an application.
			E_CONNECT,				//!< A client established a TCP control connection to the server.
			E_DISCONNECT,			//!< The TCP connection between the client and the server is broken.
			E_FILENAME_TRANSFORM,	//!< The server has requested permission to map the logical filename requested by a client.
			E_PLAY,					//!< Play a stream.
			E_STOP,					//!< Stop a stream.
			E_SEEK,					//!< Seek a stream.
			E_PAUSE,				//!< Pause delivery of a stream.
			E_PUBLISH,				//!< Publish a stream.
			E_UNPUBLISH,			//!< Unpublish a stream.
			E_LOADSEGMENT,			//!< Load a segment.
			E_ACTION,				//!< An action attached to an event was executed.
			E_CODEC_CHANGE,			//!< New codec is discovered in the stream.
			E_RECORD,				//!< Record a stream
			E_RECORD_STOP,			//!< Stop recording a stream
   			E_CLIENT_PAUSE, 		//!< Client smart-pauses a stream.
			E_SWF_VERIFY,			//!< SWF Verification is about to be performed for this client
			E_SWF_VERIFY_COMPLETE,	//!< SWF Verification has completed for this client
			E_CLIENT_SEEK,			//!< Client smart-seek a stream.
			E_START_TRANSMIT,		//!< Start stream transmission
			E_STOP_TRANSMIT,		//!< Stop stream transmission
			E_PRTMP_WHITELIST,		//!< Load swf/air whitelists
			E_MAXEVENT				//!< The total number of events in the enum field.
		};

		/**
		* \brief The enumeration of event fields.
	    */
		enum Field 	{
			F_CLIENT_URI = 0,			//!< Type:String	The URI the client specified to connect to the server. The value does not include the application name or instance name.
			F_CLIENT_ID,				//!< Type:I64		A 64-bit integer value (I64) that uniquely identifies the client (this value is not unique across processes).
			F_CLIENT_IP,				//!< Type:String	The client IP address.
			F_CLIENT_SECURE,			//!< Type:I8		A Boolean value indicating whether a connection is secure (\c true) or not (\c false)
			F_CLIENT_VHOST,				//!< Type:String	The virtual host of the application the client is connected to.
			F_CLIENT_REFERRER,			//!< Type:String	The URL of the SWF file or server where this connection originated.
			F_CLIENT_PAGE_URL,			//!< Type:String	The URL of the client SWF file. (This field is set only when clients use Flash Player 8 or above).
			F_CLIENT_AMF_ENCODING,		//!< Type:I8		The AMF (Action Message Format) encoding of the client.
			F_CLIENT_USER_AGENT,		//!< Type:String	The client user-agent.
			F_CLIENT_READ_ACCESS,		//!< Type:String	A string of directories containing application resources (shared objects and streams) to which the client has read access.
			F_CLIENT_WRITE_ACCESS,		//!< Type:String	A string of directories containing application resources (shared objects and streams) to which the client has write access.
			F_CLIENT_READ_ACCESS_LOCK,	//!< Type:I8		A Boolean value preventing a server-side script from setting the \c Client.readAccess property (\c true), or not (\c false).
			F_CLIENT_WRITE_ACCESS_LOCK,	//!< Type:I8		A Boolean value preventing a server-side script from setting the \c Client.writeAccess property (\c true), or not (\c false).
			F_CLIENT_AUDIO_CODECS,		//!< Type:I32		A list of audio codecs supported on the client.
			F_CLIENT_VIDEO_CODECS,		//!< Type:I32		A list of video codecs supported on the client.
			F_CLIENT_TYPE,				//!< Type:I32		The client type. Possible values are Normal, Group, GroupElement (a client connected through as edge server), Service, All.
			F_CLIENT_PROTO,				//!< Type:String	The protocol the client used to connect to the server.
			F_CLIENT_URI_STEM,			//!< Type:String	The stem of the URI, without the query.
			F_APP_URI,					//!< Type:String	The client URI of the application to which the client connected. The value does not include the server name or port information.
			F_APP_NAME,					//!< Type:String	The application name.
			F_APP_INST,					//!< Type:String	The application instance name.
			F_STREAM_NAME,				//!< Type:String	The stream name.
			F_STREAM_PATH,				//!< Type:String	The physical path of the stream on the server. When the plug-in is deployed on an edge server, the physical path of the cache.
			F_STREAM_TYPE,				//!< Type:String	The file type of the stream.
			F_STREAM_LENGTH,			//!< Type:Float		The length of the stream; for stream events other than \c E_PLAY, use the \c F_STREAM_SEEK_POSITION, \c F_SEGMENT_START and \c F_SEGMENT_END fields.
			F_STREAM_POSITION,			//!< Type:Float		The position of the stream; for stream events other than \c E_PLAY, use the \c F_STREAM_SEEK_POSITION, \c F_STREAM_PAUSE_TIME, \c F_SEGMENT_START, and \c F_SEGMENT_END fields.
			F_STREAM_IGNORE,			//!< Type:I8		A Boolean value indicating whether to ignore timestamps (\c true), or not (\c false).
			F_STREAM_RESET,				//!< Type:I8		A Boolean value indicating whether to allow adding a stream to a playlist (\c true), or not (\c false); for stream events other than \c E_PLAY, use \c F_STREAM_PUBLISH_TYPE.
			F_STREAM_QUERY,				//!< Type:String	A query appended to a stream, for example, \c streamName?streamQuery.

			F_CLIENT_AUDIO_SAMPLE_ACCESS, //!< Type:String	Gives the client access to raw, uncompressed audio data from streams in the specified folders.
			F_CLIENT_VIDEO_SAMPLE_ACCESS, //!< Type:String	Gives the client access to raw, uncompressed video data from streams in the specified folders.
            F_CLIENT_AUDIO_SAMPLE_ACCESS_LOCK,  //!< Type:I8 A Boolean value preventing a server-side script from setting the \c Client.audioSampleAccess property (\c true), or not (\c false).
            F_CLIENT_VIDEO_SAMPLE_ACCESS_LOCK,  //!<Type:I8 A Boolean value preventing a server-side script from setting the \c Client.videoSampleAccess property (\c true), or not (\c false).
			F_CLIENT_REDIRECT_URI,		//!< Type:String	A URI to redirect the connection to.
			F_STREAM_PAUSE,				//!< Type:I8		A Boolean value indicating whether to pause or unpause; available in \c E_PAUSE only.
			F_STREAM_PAUSE_TIME,		//!< Type:Float		The time at which a stream is paused; available in \c E_PAUSE only.
			F_STREAM_PAUSE_TOGGLE,		//!< The stream pause toggle; available in \c E_PAUSE only.
			F_STREAM_SEEK_POSITION,		//!< Type:I8		The position to which the stream should seek; available in \c E_SEEK only.
			F_STREAM_PUBLISH_TYPE,		//!< Type:I32		The stream publishing type (available for \c E_PUBLISH only): 0 for record, 1 for record and append to existing stream, 2 for record and append to existing stream while preserving gaps in the recording, -1 for live.
			F_STREAM_PUBLISH_BROADCAST, //!< Type:I32		Broadcast or multicast; currently not supported.
			F_SEGMENT_START,			//!< Type:I64		The segment start boundary in bytes; available in \c E_LOADSEGMENT only.
			F_SEGMENT_END,				//!< Type:I64		The segment end boundary in bytes; available in \c E_LOADSEGMENT only.
			F_OLD_STREAM_NAME,			//!< Type:String	Old stream for switch/swap
			F_OLD_STREAM_QUERY,			//!< Type:String	Old stream query for switch/swap
			F_OLD_STREAM_TYPE,			//!< Type:String	Old stream type for switch/swap
			F_STREAM_TRANSITION,		//!< Type:String	Transition mode string for switch/swap
			F_CLIENT_STATS_HANDLE,		//!< Type:I64		A string that uniquely identifies the client stats handle
			F_STREAM_ID,				//!< Type:I32		The stream id.
			F_STREAM_CODEC_TYPE,		//!< Type:U16		The codec type discovered in the stream; available in \c E_CODEC only.
 			F_STREAM_CODEC,				//!< Type:U16		The codec value discovered in the stream; available in \c E_CODEC only.
			F_STREAM_RECORD_MAXSIZE,	//!< Type:Float		Maximum size (in kb) of a stream recording; available in \c E_RECORD only.
			F_STREAM_RECORD_MAXDURATION,//!< Type:Float		Maximum duration (in sec) of a stream recording; available in \c E_RECORD only.
			F_CLIENT_NEAR_NONCE,		//!< Type:String	The near nonce of the client
			F_CLIENT_FAR_NONCE,			//!< Type:String	The far nonce of the client
			F_CLIENT_PROTO_VER,			//!< Type:String	The version of the protocol that was used to connect to the server.
 			F_STREAM_LIVE_PUBLISH_PENDING, //!< Type:I32	A Boolean value. If false, when a client plays a stream and issues a c\ SWITCH transition and the stream is not yet published the client receives a NetStream.Play.StreamNotFound message.  If true, the client does not receive the message because FMS waits for the stream to publish.
 			F_STREAM_OFFSET,			//!< Type:Float		The offset value when transition is in offset mode.
			F_CLIENT_SWFV_VERSION,		//!< Type:I8		During SWF Verification, the version of the protocol
			F_CLIENT_SWFV_DIGEST,		//!< Type:U8*		During SWF Verification, the 32-byte hash digest, as a byte buffer
			F_CLIENT_SWFV_DEPTH,		//!< Type:I64		During SWF Verification, the 64-bit size of the original SWF that corresponds with the digest
			F_CLIENT_SWFV_TTL,			//!< Type:I32		During SWF Verification, the time to live (in sec) of each SWF hash in cache.
			F_STREAM_TRANSMIT_POSITION,	//!< Type:Float		The position to which the stream should start/stop; available in \c E_START_TRANSMIT and \c E_STOP_TRANSMIT only.
			F_CLIENT_CONNECT_TIME,		//!< Type:I64		The time the client connected to FMS in seconds since Jan 1, 1970. This field can be retrieved from any event that has an associated client.  The \c getField() function returns \c S_SUCCESS if this field is successful retrieved.
			F_CLIENT_USERDATA,			//!< Type:U8*		Context data associated with a client.  This field can be set or retrieved from any authorization event that has an associated client.The \c getField() and \c setField() functions return \c S_SUCCESS if user data is successfully get or set.  You can set anything that can be stored in an FmsVariant.  When setting data, FMS makes a copy before saving.  When getting data, the plug-in should make a copy if the data needs to remain valid past the lifetime of the event.
			F_CLIENT_NEAR_ID,			//!< Type:String	The near id of the client
			F_CLIENT_FAR_ID,			//!< Type:String	The far id of the client
			F_CLIENT_FORWARDED_FOR,		//!< Type:String	Any x-forwarded-for header included by HTTP Proxy on an RTMPT session
			F_CLIENT_SWFV_RESULT,		//!< Type:I32		The completed result of a SWF Verification attempt
			F_CLIENT_DIFFSERV_BITS,		//!< Type:U8		dscp bits to be used in setsockopt for a particular net connection
			F_CLIENT_DIFFSERV_MASK,		//!< Type:U8		dscp mask to be used for the setsockopt
			F_CLIENT_SWFV_EXCEPTION,	//!< Type:I8		The completed result of a SWF Verification attempt
            F_STREAM_LIVE_EVENT,		//!< Type:String	The stream live event.
			F_APP_PRTMP,				//!< Type:I8		A boolean value indicating whether RTMP streaming is protected  
 			F_APP_PRTMP_COMMON_KEY_FILE,//!< Type:String	A string to specify the path to the common key file 
			F_APP_PRTMP_VIDEO_ENC_LEVEL,//!< Type:U32		A number to specify the encryption level 
			F_APP_PRTMP_UPDATE_INTERVAL,//!< Type:I32		A number to specify how often (in min) the DRM metadata will be updated 
			F_APP_PRTMP_SWF_VERIFICATION,//!< Type:I8		A boolean value indicating whether SWF Verification is enabled 
			F_APP_PRTMP_SWF_WHITELIST_FOLDER,//!< Type:String A string to specify the path to the whitelist folder for SWF Verification  
			F_APP_PRTMP_SWF_WHITELIST,	//!< Type:String	A string containing one or more SWF digests delimited by '\n'
			F_APP_PRTMP_AIR_WHITELIST,	//!< Type:String	A string containing one or more AIR identifiers delimited by '\n'
			F_MAXFIELD					//!< The total number of fields in the \c enum field.
		};

		/// all possible match returns for the F_CLIENT_SWFV_RESULT field
		enum eSWFMatch { 
			eNO_FILE,		//!< SWF File was not present
			eNO_DEPTH,		//!< SWF File could not hash to the requested depth
			eNO_MATCH,		//!< Hash produced does not match the client's hash
			ePARTIAL_MATCH,	//!< Partial file SWF Hash Match
			eFINAL_MATCH,	//!< Complete file SWF Hash Match
			eREMOTE_MISS,	//!< Edge SWF Hash Cache missed (not called here)
			eTIMEOUT,		//!< SWF Hash Response Timeout
			eNO_SUPPORT,	//!< Client cannot support SWF Hashing
			eWRONG_VERSION	//!< Hash is the wrong SWF Verification version
		}; 

		/**
		* \brief The enumeration of error return
		*/
		enum Status  {
			S_SUCCESS = 0,			//!< Success.
			S_INVALID_FIELD,		//!< Wrong field.
			S_INVALID_TYPE,			//!< Wrong type.
			S_INVALID_VALUE,		//!< Wrong value.
			S_READ_ONLY				//!< The event is read only.
		};

		/**
		 * Gets the type of the event.
		 */
		virtual EventType getType() const = 0;

		/**
		 * Gets the field value.
		 */
		virtual Status getField(Field fn, FmsVariant& field) const = 0;

		/**
		 * Sets the field value.
		 */
		virtual Status setField(Field fn, const FmsVariant& field) = 0;

		/**
        * \brief The type of an action. If a plug-in subscribes to an event, the event posts to the plug-in first as a notification event.
        * You can attach actions to notification event at that point. If an event is also an authorization event, it posts again as an
        * authorization event. You can attach actions at that point also. Actions execute in the order in which you attach them to an event.
		*
	    */
		class IFmsAction
		{
			public:

			/**
			* \brief The enumeration of action types
			*/
			enum ActionType	{
				A_DISCONNECT = 0,		//!< Disconnects a client.
				A_CLIENTNOTIFY,			//!< Calls a method on a Client or application object in a server-side script.
				A_MAXACTION				//!< The total number of actions.
			};

			/**
			* Gets the action type.
			*	@return
			*		ActionType
			*/
			virtual ActionType getType() const = 0;
		};

		/**
		* Attaches a disconnect action to an event. The disconnect action disconnects a client from the server when
		* the event it's attached to is executed.
		*
		* Actions execute in the order they're attached to events. This can affect the execution result if there are dependencies.
		*
		*	@param
		*		strText A customized description of an action. Used in the x-comment field of the authEvent.NN.log file if
		* that field and the action event are enabled in the Logging.xml file.
		*
		*	@return
		*		A return pointer to disconnect an action; 0 if an error occurs.
		*
		*/
		virtual IFmsDisconnectAction* addDisconnectAction(const char* strText = 0) = 0;

		/**
		* Attaches a notify action to an event. The notify action calls a method you've defined in a server-side script
		* when the event it's attached to is executed.
		*
		* Actions execute in the order they're attached to events. This can impact the execution result if there are dependencies.
		*
		*	@param
		*		strText A customized description of an action. Used in the comment column of the authEvent.NN.log file if
		* that field and the action event are enabled in the Logging.xml file.
		*
		*	@return
		*		A return pointer to disconnect an action; 0 if an error occurs.
		*
		*/
		virtual IFmsNotifyAction* addNotifyAction(const char* strText = 0) = 0;

	protected:

		/**
		 *
		 * Creates an IFmsAuthEvent object.
		 *
		 */

		IFmsAuthEvent() {}

		/**
	     *
	     * Creates an IFmsAuthEvent object.
         *
		 */

		IFmsAuthEvent(const IFmsAuthEvent& aev) {}

		bool	operator==(const IFmsAuthEvent& aev) const {}

		/**
		 *
		 * Destroys an IFmsAuthEvent object.
		 *
		 */

		virtual ~IFmsAuthEvent() {}

 friend class EventContext;

};

#endif
