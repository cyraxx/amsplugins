/*----------------------------------------------------------------------------+
 |       ___     _       _                                                    |
 |      /   |   | |     | |                                                   |
 |     / /| | __| | ___ | |__   ___                                           |
 |    / /_| |/ _  |/ _ \|  _ \ / _ \                                          |
 |   / ___  | (_| | (_) | |_) |  __/                                          |
 |  /_/   |_|\__,_|\___/|____/ \___|                                          |
 |                                                                            |
 |  Copyright (c) 2006, Adobe Systems Incorporated.                           |
 |  All rights reserved.                                                      |
 |                                                                            |
 |  NOTICE:  All information contained herein is, and remains the property    |
 |  of Adobe Macromedia Software LLC and its suppliers, if any. The           |
 |  intellectual and technical concepts contained herein are proprietary to   |
 |  Adobe Macromedia Software LLC and its suppliers and may be covered by     |
 |  U.S. and Foreign Patents, patents in process, and are protected by trade  |
 |  secret or copyright law. Dissemination of this information or             |
 |  reproduction of this material is strictly forbidden unless prior written  |
 |  permission is obtained from Adobe Macromedia Software LLC.                |
 |                                                                            |
 |          Adobe Systems Incorporated       415.832.2000                     |
 |          601 Townsend Street              415.832.2020 fax                 |
 |          San Francisco, CA 94103                                           |
 |                                                                            |
 +----------------------------------------------------------------------------*/
#if !defined( FmsAuthActions_H )
#define  FmsAuthActions_H

class IFmsAuthEvent;

class IFmsAuthEvent;

	/**
	*
	* \brief Disconnects a specified client.
	*/
	class IFmsDisconnectAction : public IFmsAuthEvent::IFmsAction
	{
		public:

		/**
		* Sets the ID of the client to disconnect. If a client ID is not set, the client associated with the event is disconnected.
		*
		*	@param
		*		field kI64 variant (see the FmsVariant structure).
		*
		*	@return
		*		S_SUCCESS If the operation is successful.
		*/
		virtual IFmsAuthEvent::Status setClientId(const FmsVariant& field) = 0;

	};

	/**
	*
	* \brief Calls a method on a Client object or on an application object in
	* a server-side script. You must define the method to be called in the server-side script.
	*/
	class IFmsNotifyAction : public IFmsAuthEvent::IFmsAction
	{
		public:

		/**
		* Sets the ID of the client on which to call the method.
		*
		*	@param
		*		field kI64 variant (see the FmsVariant class).
		*		If you set a value, the method is called on the Client object in the server-side script.
		* If you don't set a value, the method is called on the application object in the server-side script.
		*
		*/
		virtual IFmsAuthEvent::Status setClientId(const FmsVariant& field) = 0;

		/**
		* Gets the method name.
		*
		*	@return
		*		kString variant
		*
		*/
		virtual const FmsVariant& getMethodName() const = 0;

		/**
		* Sets the method name.
		*
		*	@param
		*		field kString variant
		*
		*/
		virtual IFmsAuthEvent::Status setMethodName(const FmsVariant& field) = 0;

		/**
		* Gets a parameter by index.
		*
		*	@param iIndex
		*		The index of a parameter, starting from 0.
		*
		*	@return
		*		A pointer to a variant; 0 means no parameter was found.
		*
		*/
		virtual const  FmsVariant* getParam(unsigned int iIndex) const = 0;

		/**
		* Removes a parameter or a range of parameters from the specified positions.
		*
		*	@param iFirst The first index value.
		*
		*	@param iLast The last index value.
		*
		*	@return
		*		S_SUCCESS If the parameter was removed.
		*/
		virtual IFmsAuthEvent::Status removeParam(unsigned int iFirst, unsigned int iLast) = 0;


		/**
		* Adds a parameter to the method to call in the server-side script.
		*
		*	@param
		*		field variant
		*
		*	@return
		*		S_SUCCESS If the parameter was added.
		*
		*/
		virtual IFmsAuthEvent::Status addParam(const FmsVariant& field) = 0;

		/**
		* Returns the number of parameters in the method.
		*
		*/
		virtual unsigned int getNumParams() const = 0;

	};

#endif


