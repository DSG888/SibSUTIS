import time

from .simplexml import Node, XML_ls, XMLescape, ustr

NS_DATA							 = "jabber:x:data"								# XEP-0004
NS_AVATAR						 = "jabber:iq:avatar"							# XEP-0008 (historical)
NS_RPC				 = "jabber:iq:rpc"											# XEP-0009
NS_BROWSE						 = "jabber:iq:browse"							# XEP-0011 (historical)
NS_LAST							 = "jabber:iq:last"								# XEP-0012
NS_OFFLINE						 = "http://jabber.org/protocol/offline"			# XEP-0013
NS_FEATURE						 = "http://jabber.org/protocol/feature-neg"		# XEP-0020
NS_DIALBACK						 = "jabber:server:dialback"						# RFC 3921
NS_EVENT						 = "jabber:x:event"								# XEP-0022 (deprecated)
NS_ENCRYPTED					 = "jabber:x:encrypted"							# XEP-0027
NS_SIGNED						 = "jabber:x:signed"							# XEP-0027
NS_DISCO						 = "http://jabber.org/protocol/disco"			# XEP-0030
NS_DISCO_INFO					 = NS_DISCO + "#info"							# XEP-0030
NS_DISCO_ITEMS					 = NS_DISCO + "#items"							# XEP-0030
NS_ADDRESS						 = "http://jabber.org/protocol/address"			# XEP-0033
NS_STATS			 = "http://jabber.org/protocol/stats"						# XEP-0039
NS_IBB							 = "http://jabber.org/protocol/ibb"				# XEP-0047
NS_MUC							 = "http://jabber.org/protocol/muc"				# XEP-0045
NS_MUC_ADMIN					 = NS_MUC + "#admin"							# XEP-0045
NS_MUC_OWNER					 = NS_MUC + "#owner"							# XEP-0045
NS_MUC_UNIQUE					 = NS_MUC + "#unique"							# XEP-0045
NS_MUC_USER						 = NS_MUC + "#user"								# XEP-0045
NS_MUC_REGISTER					 = NS_MUC + "#register"							# XEP-0045
NS_MUC_REQUEST					 = NS_MUC + "#request"							# XEP-0045
NS_MUC_ROOMCONFIG				 = NS_MUC + "#roomconfig"						# XEP-0045
NS_MUC_ROOMINFO					 = NS_MUC + "#roominfo"							# XEP-0045
NS_MUC_ROOMS					 = NS_MUC + "#rooms"							# XEP-0045
NS_MUC_TRAFIC					 = NS_MUC + "#traffic"							# XEP-0045
NS_GROUPCHAT					 = "gc-1.0"										# XEP-0045
NS_PRIVATE			 = "jabber:iq:private"										# XEP-0049
NS_COMMANDS						 = "http://jabber.org/protocol/commands"		# XEP-0050
NS_VCARD			 = "vcard-temp"												# XEP-0054
NS_SEARCH			 = "jabber:iq:search"										# XEP-0055
NS_PUBSUB			 = "http://jabber.org/protocol/pubsub"						# XEP-0060
NS_BYTESTREAM					 = "http://jabber.org/protocol/bytestreams"		# XEP-0065
NS_OOB				 = "jabber:x:oob"											# XEP-0066
NS_XHTML_IM			 = "http://jabber.org/protocol/xhtml-im"					# XEP-0071
NS_REGISTER			 = "jabber:iq:register"										# XEP-0077
NS_AUTH							 = "jabber:iq:auth"								# XEP-0078
NS_AMP							 = "http://jabber.org/protocol/amp"				# XEP-0079
NS_AMP_ERRORS					 = NS_AMP + "#errors"							# XEP-0079
NS_GEOLOC			 = "http://jabber.org/protocol/geoloc"						# XEP-0080
NS_CHATSTATES					 = "http://jabber.org/protocol/chatstates"		# XEP-0085
NS_TIME				 = "jabber:iq:time"											# XEP-0090 (deprecated)
NS_DELAY						 = "jabber:x:delay"								# XEP-0091 (deprecated)
NS_VERSION			 = "jabber:iq:version"										# XEP-0092
NS_AGENTS						 = "jabber:iq:agents"							# XEP-0094 (historical)
NS_FILE				 = "http://jabber.org/protocol/si/profile/file-transfer"	# XEP-0096
NS_SI				 = "http://jabber.org/protocol/si"							# XEP-0096
NS_GATEWAY			 = "jabber:iq:gateway"										# XEP-0100
NS_MOOD				 = "http://jabber.org/protocol/mood"						# XEP-0107
NS_ACTIVITY						 = "http://jabber.org/protocol/activity"		# XEP-0108
NS_VACATION			 = "http://jabber.org/protocol/vacation"					# XEP-0109
NS_PHYSLOC			 = "http://jabber.org/protocol/physloc"						# XEP-0112
NS_COMPONENT_ACCEPT				 = "jabber:component:accept"					# XEP-0114
NS_CAPS							 = "http://jabber.org/protocol/caps"			# XEP-0115
NS_DATA_VALIDATE	 = "http://jabber.org/protocol/xdata-validate"				# XEP-0122
NS_HTTP_BIND		 = "http://jabber.org/protocol/httpbind"					# XEP-0124
NS_WAITINGLIST		 = "http://jabber.org/protocol/waitinglist"					# XEP-0130
NS_ADMIN						 = "http://jabber.org/protocol/admin"			# XEP-0133
NS_ADMIN_ADD_USER				 = NS_ADMIN + "#add-user"						# XEP-0133
NS_ADMIN_DELETE_USER			 = NS_ADMIN + "#delete-user"					# XEP-0133
NS_ADMIN_DISABLE_USER			 = NS_ADMIN + "#disable-user"					# XEP-0133
NS_ADMIN_REENABLE_USER			 = NS_ADMIN + "#reenable-user"					# XEP-0133
NS_ADMIN_END_USER_SESSION		 = NS_ADMIN + "#end-user-session"				# XEP-0133
NS_ADMIN_GET_USER_PASSWORD		 = NS_ADMIN + "#get-user-password"				# XEP-0133
NS_ADMIN_CHANGE_USER_PASSWORD	 = NS_ADMIN + "#change-user-password"			# XEP-0133
NS_ADMIN_GET_USER_ROSTER		 = NS_ADMIN + "#get-user-roster"				# XEP-0133
NS_ADMIN_GET_USER_LASTLOGIN		 = NS_ADMIN + "#get-user-lastlogin"				# XEP-0133
NS_ADMIN_USER_STATS				 = NS_ADMIN + "#user-stats"						# XEP-0133
NS_ADMIN_EDIT_BLACKLIST			 = NS_ADMIN + "#edit-blacklist"					# XEP-0133
NS_ADMIN_EDIT_WHITELIST			 = NS_ADMIN + "#edit-whitelist"					# XEP-0133
NS_ADMIN_REGISTERED_USERS_NUM	 = NS_ADMIN + "#get-registered-users-num"		# XEP-0133
NS_ADMIN_DISABLED_USERS_NUM		 = NS_ADMIN + "#get-disabled-users-num"			# XEP-0133
NS_ADMIN_ONLINE_USERS_NUM		 = NS_ADMIN + "#get-online-users-num"			# XEP-0133
NS_ADMIN_ACTIVE_USERS_NUM		 = NS_ADMIN + "#get-active-users-num"			# XEP-0133
NS_ADMIN_IDLE_USERS_NUM			 = NS_ADMIN + "#get-idle-users-num"				# XEP-0133
NS_ADMIN_REGISTERED_USERS_LIST	 = NS_ADMIN + "#get-registered-users-list"		# XEP-0133
NS_ADMIN_DISABLED_USERS_LIST	 = NS_ADMIN + "#get-disabled-users-list"		# XEP-0133
NS_ADMIN_ONLINE_USERS_LIST		 = NS_ADMIN + "#get-online-users-list"			# XEP-0133
NS_ADMIN_ACTIVE_USERS_LIST		 = NS_ADMIN + "#get-active-users-list"			# XEP-0133
NS_ADMIN_IDLE_USERS_LIST		 = NS_ADMIN + "#get-idle-users-list"			# XEP-0133
NS_ADMIN_ANNOUNCE				 = NS_ADMIN + "#announce"						# XEP-0133
NS_ADMIN_SET_MOTD				 = NS_ADMIN + "#set-motd"						# XEP-0133
NS_ADMIN_EDIT_MOTD				 = NS_ADMIN + "#edit-motd"						# XEP-0133
NS_ADMIN_DELETE_MOTD			 = NS_ADMIN + "#delete-motd"					# XEP-0133
NS_ADMIN_SET_WELCOME			 = NS_ADMIN + "#set-welcome"					# XEP-0133
NS_ADMIN_DELETE_WELCOME			 = NS_ADMIN + "#delete-welcome"					# XEP-0133
NS_ADMIN_EDIT_ADMIN				 = NS_ADMIN + "#edit-admin"						# XEP-0133
NS_ADMIN_RESTART				 = NS_ADMIN + "#restart"						# XEP-0133
NS_ADMIN_SHUTDOWN				 = NS_ADMIN + "#shutdown"						# XEP-0133
NS_SI_PUB			 = "http://jabber.org/protocol/sipub"						# XEP-0137
NS_COMPRESS			 = "http://jabber.org/protocol/compress"					# XEP-0138
NS_DATA_LAYOUT		 = "http://jabber.org/protocol/xdata-layout"				# XEP-0141
NS_ROSTERX			 = "http://jabber.org/protocol/rosterx"						# XEP-0144
NS_RC				 = "http://jabber.org/protocol/rc"							# XEP-0146
NS_VCARD_UPDATE		 = "vcard-temp:x:update"									# XEP-0153
NS_SOFTWAREINFO		 = "urn:xmpp:dataforms:softwareinfo"						# XEP-0155
NS_URN_OOB			 = "urn:xmpp:bob"											# XEP-0158
NS_CAPTCHA						 = "urn:xmpp:captcha"							# XEP-0158
NS_MEDIA			 = "urn:xmpp:media-element"									# XEP-0158
NS_NICK				 = "http://jabber.org/protocol/nick"						# XEP-0172
NS_RECEIPTS			 = "urn:xmpp:receipts"										# XEP-0184
NS_PING							 = "urn:xmpp:ping"								# XEP-0199
NS_URN_TIME			 = "urn:xmpp:time"											# XEP-0202
NS_URN_ATTENTION	 = "urn:xmpp:attention:0"									# XEP-0224

NS_BIND							 = "urn:ietf:params:xml:ns:xmpp-bind"			# RFC 3920
NS_XMPP_STREAMS		 = "urn:ietf:params:xml:ns:xmpp-streams"					# RFC 3920
NS_STANZAS			 = "urn:ietf:params:xml:ns:xmpp-stanzas"					# RFC 3920
NS_SASL				 = "urn:ietf:params:xml:ns:xmpp-sasl"						# RFC 3920
NS_STREAMS			 = "http://etherx.jabber.org/streams"						# RFC 3920
NS_TLS				 = "urn:ietf:params:xml:ns:xmpp-tls"						# RFC 3920
NS_SERVER			 = "jabber:server"											# RFC 3921
NS_SESSION			 = "urn:ietf:params:xml:ns:xmpp-session"					# RFC 3921
NS_ROSTER			 = "jabber:iq:roster"										# RFC 3921
NS_CLIENT			 = "jabber:client"											# RFC 3921
NS_PRIVACY			 = "jabber:iq:privacy"										# RFC 3921

NS_PRESENCE			 = "presence"												# Jabberd2
NS_COMPONENT_1		 = "http://jabberd.jabberstudio.org/ns/component/1.0"		# Jabberd2
NS_INVISIBLE		 = "presence-invisible"										# Jabberd2
NS_IQ				 = "iq"														# Jabberd2
NS_MESSAGE			 = "message"												# Jabberd2

NS_MUC_FILTER		 = "http://jabber.ru/muc-filter"

STREAM_NOT_AUTHORIZED			 = NS_XMPP_STREAMS + " not-authorized"
STREAM_REMOTE_CONNECTION_FAILED	 = NS_XMPP_STREAMS + " remote-connection-failed"
SASL_MECHANISM_TOO_WEAK			 = NS_SASL + " mechanism-too-weak"
STREAM_XML_NOT_WELL_FORMED		 = NS_XMPP_STREAMS + " xml-not-well-formed"
ERR_JID_MALFORMED				 = NS_STANZAS + " jid-malformed"
STREAM_SEE_OTHER_HOST			 = NS_XMPP_STREAMS + " see-other-host"
STREAM_BAD_NAMESPACE_PREFIX		 = NS_XMPP_STREAMS + " bad-namespace-prefix"
ERR_SERVICE_UNAVAILABLE			 = NS_STANZAS + " service-unavailable"
STREAM_CONNECTION_TIMEOUT		 = NS_XMPP_STREAMS + " connection-timeout"
STREAM_UNSUPPORTED_VERSION		 = NS_XMPP_STREAMS + " unsupported-version"
STREAM_IMPROPER_ADDRESSING		 = NS_XMPP_STREAMS + " improper-addressing"
STREAM_UNDEFINED_CONDITION		 = NS_XMPP_STREAMS + " undefined-condition"
SASL_NOT_AUTHORIZED				 = NS_SASL + " not-authorized"
ERR_GONE						 = NS_STANZAS + " gone"
SASL_TEMPORARY_AUTH_FAILURE		 = NS_SASL + " temporary-auth-failure"
ERR_REMOTE_SERVER_NOT_FOUND		 = NS_STANZAS + " remote-server-not-found"
ERR_UNEXPECTED_REQUEST			 = NS_STANZAS + " unexpected-request"
ERR_RECIPIENT_UNAVAILABLE		 = NS_STANZAS + " recipient-unavailable"
ERR_CONFLICT					 = NS_STANZAS + " conflict"
STREAM_SYSTEM_SHUTDOWN			 = NS_XMPP_STREAMS + " system-shutdown"
STREAM_BAD_FORMAT				 = NS_XMPP_STREAMS + " bad-format"
ERR_SUBSCRIPTION_REQUIRED		 = NS_STANZAS + " subscription-required"
STREAM_INTERNAL_SERVER_ERROR	 = NS_XMPP_STREAMS + " internal-server-error"
ERR_NOT_AUTHORIZED				 = NS_STANZAS + " not-authorized"
SASL_ABORTED					 = NS_SASL + " aborted"
ERR_REGISTRATION_REQUIRED		 = NS_STANZAS + " registration-required"
ERR_INTERNAL_SERVER_ERROR		 = NS_STANZAS + " internal-server-error"
SASL_INCORRECT_ENCODING			 = NS_SASL + " incorrect-encoding"
STREAM_HOST_GONE				 = NS_XMPP_STREAMS + " host-gone"
STREAM_POLICY_VIOLATION			 = NS_XMPP_STREAMS + " policy-violation"
STREAM_INVALID_XML				 = NS_XMPP_STREAMS + " invalid-xml"
STREAM_CONFLICT					 = NS_XMPP_STREAMS + " conflict"
STREAM_RESOURCE_CONSTRAINT		 = NS_XMPP_STREAMS + " resource-constraint"
STREAM_UNSUPPORTED_ENCODING		 = NS_XMPP_STREAMS + " unsupported-encoding"
ERR_NOT_ALLOWED					 = NS_STANZAS + " not-allowed"
ERR_ITEM_NOT_FOUND				 = NS_STANZAS + " item-not-found"
ERR_NOT_ACCEPTABLE				 = NS_STANZAS + " not-acceptable"
STREAM_INVALID_FROM				 = NS_XMPP_STREAMS + " invalid-from"
ERR_FEATURE_NOT_IMPLEMENTED		 = NS_STANZAS + " feature-not-implemented"
ERR_BAD_REQUEST					 = NS_STANZAS + " bad-request"
STREAM_INVALID_ID				 = NS_XMPP_STREAMS + " invalid-id"
STREAM_HOST_UNKNOWN				 = NS_XMPP_STREAMS + " host-unknown"
ERR_UNDEFINED_CONDITION			 = NS_STANZAS + " undefined-condition"
SASL_INVALID_MECHANISM			 = NS_SASL + " invalid-mechanism"
STREAM_RESTRICTED_XML			 = NS_XMPP_STREAMS + " restricted-xml"
ERR_RESOURCE_CONSTRAINT			 = NS_STANZAS + " resource-constraint"
ERR_REMOTE_SERVER_TIMEOUT		 = NS_STANZAS + " remote-server-timeout"
SASL_INVALID_AUTHZID			 = NS_SASL + " invalid-authzid"
ERR_PAYMENT_REQUIRED			 = NS_STANZAS + " payment-required"
STREAM_INVALID_NAMESPACE		 = NS_XMPP_STREAMS + " invalid-namespace"
ERR_REDIRECT					 = NS_STANZAS + " redirect"
STREAM_UNSUPPORTED_STANZA_TYPE	 = NS_XMPP_STREAMS + " unsupported-stanza-type"
ERR_FORBIDDEN					 = NS_STANZAS + " forbidden"

ERRORS = {
	"urn:ietf:params:xml:ns:xmpp-sasl not-authorized": ["", "", "The authentication failed because the initiating entity did not provide valid credentials (this includes but is not limited to the case of an unknown username); sent in reply to a <response/> element or an <auth/> element with initial response data."],
	"urn:ietf:params:xml:ns:xmpp-stanzas payment-required": ["402", "auth", "The requesting entity is not authorized to access the requested service because payment is required."],
	"urn:ietf:params:xml:ns:xmpp-sasl mechanism-too-weak": ["", "", "The mechanism requested by the initiating entity is weaker than server policy permits for that initiating entity; sent in reply to a <response/> element or an <auth/> element with initial response data."],
	"urn:ietf:params:xml:ns:xmpp-streams unsupported-encoding": ["", "", "The initiating entity has encoded the stream in an encoding that is not supported by the server."],
	"urn:ietf:params:xml:ns:xmpp-stanzas remote-server-timeout": ["504", "wait", "A remote server or service specified as part or all of the JID of the intended recipient could not be contacted within a reasonable amount of time."],
	"urn:ietf:params:xml:ns:xmpp-streams remote-connection-failed": ["", "", "The server is unable to properly connect to a remote resource that is required for authentication or authorization."],
	"urn:ietf:params:xml:ns:xmpp-streams restricted-xml": ["", "", "The entity has attempted to send restricted XML features such as a comment, processing instruction, DTD, entity reference, or unescaped character."],
	"urn:ietf:params:xml:ns:xmpp-streams see-other-host": ["", "", "The server will not provide service to the initiating entity but is redirecting traffic to another host."],
	"urn:ietf:params:xml:ns:xmpp-streams xml-not-well-formed": ["", "", "The initiating entity has sent XML that is not well-formed."],
	"urn:ietf:params:xml:ns:xmpp-stanzas subscription-required": ["407", "auth", "The requesting entity is not authorized to access the requested service because a subscription is required."],
	"urn:ietf:params:xml:ns:xmpp-streams internal-server-error": ["", "", "The server has experienced a misconfiguration or an otherwise-undefined internal error that prevents it from servicing the stream."],
	"urn:ietf:params:xml:ns:xmpp-sasl invalid-mechanism": ["", "", "The initiating entity did not provide a mechanism or requested a mechanism that is not supported by the receiving entity; sent in reply to an <auth/> element."],
	"urn:ietf:params:xml:ns:xmpp-streams policy-violation": ["", "", "The entity has violated some local service policy."],
	"urn:ietf:params:xml:ns:xmpp-stanzas conflict": ["409", "cancel", "Access cannot be granted because an existing resource or session exists with the same name or address."],
	"urn:ietf:params:xml:ns:xmpp-streams unsupported-stanza-type": ["", "", "The initiating entity has sent a first-level child of the stream that is not supported by the server."],
	"urn:ietf:params:xml:ns:xmpp-sasl incorrect-encoding": ["", "", "The data provided by the initiating entity could not be processed because the [BASE64]Josefsson, S., The Base16, Base32, and Base64 Data Encodings, July 2003. encoding is incorrect (e.g., because the encoding does not adhere to the definition in Section 3 of [BASE64]Josefsson, S., The Base16, Base32, and Base64 Data Encodings, July 2003.); sent in reply to a <response/> element or an <auth/> element with initial response data."],
	"urn:ietf:params:xml:ns:xmpp-stanzas registration-required": ["407", "auth", "The requesting entity is not authorized to access the requested service because registration is required."],
	"urn:ietf:params:xml:ns:xmpp-streams invalid-id": ["", "", "The stream ID or dialback ID is invalid or does not match an ID previously provided."],
	"urn:ietf:params:xml:ns:xmpp-sasl invalid-authzid": ["", "", "The authzid provided by the initiating entity is invalid, either because it is incorrectly formatted or because the initiating entity does not have permissions to authorize that ID; sent in reply to a <response/> element or an <auth/> element with initial response data."],
	"urn:ietf:params:xml:ns:xmpp-stanzas bad-request": ["400", "modify", "The sender has sent XML that is malformed or that cannot be processed."],
	"urn:ietf:params:xml:ns:xmpp-streams not-authorized": ["", "", "The entity has attempted to send data before the stream has been authenticated, or otherwise is not authorized to perform an action related to stream negotiation."],
	"urn:ietf:params:xml:ns:xmpp-stanzas forbidden": ["403", "auth", "The requesting entity does not possess the required permissions to perform the action."],
	"urn:ietf:params:xml:ns:xmpp-sasl temporary-auth-failure": ["", "", "The authentication failed because of a temporary error condition within the receiving entity; sent in reply to an <auth/> element or <response/> element."],
	"urn:ietf:params:xml:ns:xmpp-streams invalid-namespace": ["", "", "The streams namespace name is something other than \http://etherx.jabber.org/streams\" or the dialback namespace name is something other than \"jabber:server:dialback\"."],
	"urn:ietf:params:xml:ns:xmpp-stanzas feature-not-implemented": ["501", "cancel", "The feature requested is not implemented by the recipient or server and therefore cannot be processed."],
	"urn:ietf:params:xml:ns:xmpp-streams invalid-xml": ["", "", "The entity has sent invalid XML over the stream to a server that performs validation."],
	"urn:ietf:params:xml:ns:xmpp-stanzas item-not-found": ["404", "cancel", "The addressed JID or item requested cannot be found."],
	"urn:ietf:params:xml:ns:xmpp-streams host-gone": ["", "", "The value of the \"to\" attribute provided by the initiating entity in the stream header corresponds to a hostname that is no longer hosted by the server."],
	"urn:ietf:params:xml:ns:xmpp-stanzas recipient-unavailable": ["404", "wait", "The intended recipient is temporarily unavailable."],
	"urn:ietf:params:xml:ns:xmpp-stanzas not-acceptable": ["406", "cancel", "The recipient or server understands the request but is refusing to process it because it does not meet criteria defined by the recipient or server."],
	"urn:ietf:params:xml:ns:xmpp-streams invalid-from": ["cancel", "", "The JID or hostname provided in a \"from\" address does not match an authorized JID or validated domain negotiated between servers via SASL or dialback, or between a client and a server via authentication and resource authorization."],
	"urn:ietf:params:xml:ns:xmpp-streams bad-format": ["", "", "The entity has sent XML that cannot be processed."],
	"urn:ietf:params:xml:ns:xmpp-streams resource-constraint": ["", "", "The server lacks the system resources necessary to service the stream."],
	"urn:ietf:params:xml:ns:xmpp-stanzas undefined-condition": ["500", "", "The condition is undefined."],
	"urn:ietf:params:xml:ns:xmpp-stanzas redirect": ["302", "modify", "The recipient or server is redirecting requests for this information to another entity."],
	"urn:ietf:params:xml:ns:xmpp-streams bad-namespace-prefix": ["", "", "The entity has sent a namespace prefix that is unsupported, or has sent no namespace prefix on an element that requires such a prefix."],
	"urn:ietf:params:xml:ns:xmpp-streams system-shutdown": ["", "", "The server is being shut down and all active streams are being closed."],
	"urn:ietf:params:xml:ns:xmpp-streams conflict": ["", "", "The server is closing the active stream for this entity because a new stream has been initiated that conflicts with the existing stream."],
	"urn:ietf:params:xml:ns:xmpp-streams connection-timeout": ["", "", "The entity has not generated any traffic over the stream for some period of time."],
	"urn:ietf:params:xml:ns:xmpp-stanzas jid-malformed": ["400", "modify", "The value of the \"to\" attribute in the sender's stanza does not adhere to the syntax defined in Addressing Scheme."],
	"urn:ietf:params:xml:ns:xmpp-stanzas resource-constraint": ["500", "wait", "The server or recipient lacks the system resources necessary to service the request."],
	"urn:ietf:params:xml:ns:xmpp-stanzas remote-server-not-found": ["404", "cancel", "A remote server or service specified as part or all of the JID of the intended recipient does not exist."],
	"urn:ietf:params:xml:ns:xmpp-streams unsupported-version": ["", "", "The value of the \"version\" attribute provided by the initiating entity in the stream header specifies a version of XMPP that is not supported by the server."],
	"urn:ietf:params:xml:ns:xmpp-streams host-unknown": ["", "", "The value of the \"to\" attribute provided by the initiating entity in the stream header does not correspond to a hostname that is hosted by the server."],
	"urn:ietf:params:xml:ns:xmpp-stanzas unexpected-request": ["400", "wait", "The recipient or server understood the request but was not expecting it at this time (e.g., the request was out of order)."],
	"urn:ietf:params:xml:ns:xmpp-streams improper-addressing": ["", "", "A stanza sent between two servers lacks a \"to\" or \"from\" attribute (or the attribute has no value)."],
	"urn:ietf:params:xml:ns:xmpp-stanzas not-allowed": ["405", "cancel", "The recipient or server does not allow any entity to perform the action."],
	"urn:ietf:params:xml:ns:xmpp-stanzas internal-server-error": ["500", "wait", "The server could not process the stanza because of a misconfiguration or an otherwise-undefined internal server error."],
	"urn:ietf:params:xml:ns:xmpp-stanzas gone": ["302", "modify", "The recipient or server can no longer be contacted at this address."],
	"urn:ietf:params:xml:ns:xmpp-streams undefined-condition": ["", "", "The error condition is not one of those defined by the other conditions in this list."],
	"urn:ietf:params:xml:ns:xmpp-stanzas service-unavailable": ["503", "cancel", "The server or recipient does not currently provide the requested service."],
	"urn:ietf:params:xml:ns:xmpp-stanzas not-authorized": ["401", "auth", "The sender must provide proper credentials before being allowed to perform the action, or has provided improper credentials."],
	"urn:ietf:params:xml:ns:xmpp-sasl aborted": ["", "", "The receiving entity acknowledges an <abort/> element sent by the initiating entity; sent in reply to the <abort/> element."]
}

_errorcodes = {"302": "redirect", "400": "unexpected-request", "401": "not-authorized", "402": "payment-required", "403": "forbidden", "404": "remote-server-not-found", "405": "not-allowed", "406": "not-acceptable", "407": "subscription-required", "409": "conflict", "500": "undefined-condition", "501": "feature-not-implemented", "503": "service-unavailable", "504": "remote-server-timeout"}

def isResultNode(node):
	"""
	Returns true if the node is a positive reply.
	"""
	return (node and node.getType() == "result")

def isGetNode(node):
	return (node and node.getType() == "get")

def isSetNode(node):
	return (node and node.getType() == "set")

def isErrorNode(node):
	return (node and node.getType() == "error")

class NodeProcessed(Exception):

class StreamError(Exception):

class BadFormat(StreamError):
	pass

class BadNamespacePrefix(StreamError):
	pass

class Conflict(StreamError):
	pass

class ConnectionTimeout(StreamError):
	pass

class HostGone(StreamError):
	pass

class HostUnknown(StreamError):
	pass

class ImproperAddressing(StreamError):
	pass

class InternalServerError(StreamError):
	pass

class InvalidFrom(StreamError):
	pass

class InvalidID(StreamError):
	pass

class InvalidNamespace(StreamError):
	pass

class InvalidXML(StreamError):
	pass

class NotAuthorized(StreamError):
	pass

class PolicyViolation(StreamError):
	pass

class RemoteConnectionFailed(StreamError):
	pass

class ResourceConstraint(StreamError):
	pass

class RestrictedXML(StreamError):
	pass

class SeeOtherHost(StreamError):
	pass

class SystemShutdown(StreamError):
	pass

class UndefinedCondition(StreamError):
	pass

class UnsupportedEncoding(StreamError):
	pass

class UnsupportedStanzaType(StreamError):
	pass

class UnsupportedVersion(StreamError):
	pass

class XMLNotWellFormed(StreamError):
	pass

stream_exceptions = {"bad-format": BadFormat, "bad-namespace-prefix": BadNamespacePrefix, "conflict": Conflict, "connection-timeout": ConnectionTimeout, "host-gone": HostGone, "host-unknown": HostUnknown, "improper-addressing": ImproperAddressing, "internal-server-error": InternalServerError, "invalid-from": InvalidFrom, "invalid-id": InvalidID, "invalid-namespace": InvalidNamespace, "invalid-xml": InvalidXML, "not-authorized": NotAuthorized, "policy-violation": PolicyViolation, "remote-connection-failed": RemoteConnectionFailed, "resource-constraint": ResourceConstraint, "restricted-xml": RestrictedXML, "see-other-host": SeeOtherHost, "system-shutdown": SystemShutdown, "undefined-condition": UndefinedCondition, "unsupported-encoding": UnsupportedEncoding, "unsupported-stanza-type": UnsupportedStanzaType, "unsupported-version": UnsupportedVersion, "xml-not-well-formed": XMLNotWellFormed}

class JID:
	def __init__(self, jid=None, node="", domain="", resource=""):
		if not jid and not domain:
			raise ValueError("JID must contain at least domain name")
		elif isinstance(jid, self.__class__):
			self.node, self.domain, self.resource = jid.node, jid.domain, jid.resource
		elif domain:
			self.node, self.domain, self.resource = node, domain, resource
		else:
			if jid.find("@") + 1:
				self.node, jid = jid.split("@", 1)
			else:
				self.node = ""
			if jid.find("/") + 1:
				self.domain, self.resource = jid.split("/", 1)
			else:
				self.domain, self.resource = jid, ""

	def getNode(self):
		return self.node

	def setNode(self, node):
		self.node = node.lower()

	def getDomain(self):
		return self.domain

	def setDomain(self, domain):
		self.domain = domain.lower()

	def getResource(self):
		return self.resource

	def setResource(self, resource):
		self.resource = resource

	def getStripped(self):
		return self.__str__(0)

	def __eq__(self, other):
		try:
			other = JID(other)
		except ValueError:
			return False
		return self.resource == other.resource and self.__str__(0) == other.__str__(0)

	def __ne__(self, other):
		return not self.__eq__(other)

	def bareMatch(self, other):
		return self.__str__(0) == JID(other).__str__(0)

	def __str__(self, wresource=1):
		jid = "@".join((self.node, self.domain)) if self.node else self.domain
		if wresource and self.resource:
			jid = "/".join((jid, self.resource))
		return jid

	def __hash__(self):
		return hash(self.__str__())

class Protocol(Node):
	def __init__(self, name=None, to=None, typ=None, frm=None, attrs={}, payload=[], timestamp=None, xmlns=None, node=None):
		if not attrs:
			attrs = {}
		if to:
			attrs["to"] = to
		if frm:
			attrs["from"] = frm
		if typ:
			attrs["type"] = typ
		Node.__init__(self, tag=name, attrs=attrs, payload=payload, node=node)
		if not node and xmlns:
			self.setNamespace(xmlns)
		if self["to"]:
			self.setTo(self["to"])
		if self["from"]:
			self.setFrom(self["from"])
		if node and isinstance(node, self.__class__) and self.__class__ == node.__class__ and "id" in self.attrs:
			del self.attrs["id"]
		self.timestamp = None
		for x in self.getTags("x", namespace=NS_DELAY):
			try:
				if not self.getTimestamp() or x.getAttr("stamp") < self.getTimestamp():
					self.setTimestamp(x.getAttr("stamp"))
			except Exception:
				pass
		if timestamp is not None:
			self.setTimestamp(timestamp) # To auto-timestamp stanza just pass timestamp=""

	def getTo(self):
		try:
			to = self["to"]
		except Exception:
			to = None
		return to

	def getFrom(self):
		try:
			frm = self["from"]
		except Exception:
			frm = None
		return frm

	def getTimestamp(self):
		return self.timestamp

	def getID(self):
		return self.getAttr("id")

	def setTo(self, val):
		self.setAttr("to", JID(val))

	def getType(self):
		return self.getAttr("type")

	def setFrom(self, val):
		self.setAttr("from", JID(val))

	def setType(self, val):
		self.setAttr("type", val)

	def setID(self, val):
		self.setAttr("id", val)

	def getError(self):
		errtag = self.getTag("error")
		if errtag:
			for tag in errtag.getChildren():
				if tag.getName() != "text":
					return tag.getName()
			return errtag.getData()

	def getErrorCode(self):
		return self.getTagAttr("error", "code")

	def setError(self, error, code=None):
		if code:
			if str(code) in _errorcodes.keys():
				error = ErrorNode(_errorcodes[str(code)], text=error)
			else:
				error = ErrorNode(ERR_UNDEFINED_CONDITION, code=code, typ="cancel", text=error)
		elif isinstance(error, basestring):
			error = ErrorNode(error)
		self.setType("error")
		self.addChild(node=error)

	def setTimestamp(self, val=None):
		if not val:
			val = time.strftime("%Y%m%dT%H:%M:%S", time.gmtime())
		self.timestamp = val
		self.setTag("x", {"stamp": self.timestamp}, namespace=NS_DELAY)

	def getProperties(self):
		props = []
		for child in self.getChildren():
			prop = child.getNamespace()
			if prop not in props:
				props.append(prop)
		return props

	def __setitem__(self, item, val):
		if item in ["to", "from"]:
			val = JID(val)
		return self.setAttr(item, val)

class Message(Protocol):
	def __init__(self, to=None, body=None, typ=None, subject=None, attrs={}, frm=None, payload=[], timestamp=None, xmlns=NS_CLIENT, node=None):
		Protocol.__init__(self, "message", to=to, typ=typ, attrs=attrs, frm=frm, payload=payload, timestamp=timestamp, xmlns=xmlns, node=node)
		if body:
			self.setBody(body)
		if subject:
			self.setSubject(subject)

	def getBody(self):
		return self.getTagData("body")

	def getSubject(self):
		return self.getTagData("subject")

	def getThread(self):
		return self.getTagData("thread")

	def setBody(self, val):
		self.setTagData("body", val)

	def setSubject(self, val):
		self.setTagData("subject", val)

	def setThread(self, val):
		self.setTagData("thread", val)

	def buildReply(self, text=None):
		msg = Message(to=self.getFrom(), frm=self.getTo(), body=text)
		thr = self.getThread()
		if thr:
			msg.setThread(thr)
		return msg

class Presence(Protocol):
	def __init__(self, to=None, typ=None, priority=None, show=None, status=None, attrs={}, frm=None, timestamp=None, payload=[], xmlns=NS_CLIENT, node=None):
		Protocol.__init__(self, "presence", to=to, typ=typ, attrs=attrs, frm=frm, payload=payload, timestamp=timestamp, xmlns=xmlns, node=node)
		if priority:
			self.setPriority(priority)
		if show:
			self.setShow(show)
		if status:
			self.setStatus(status)

	def getPriority(self):
		return self.getTagData("priority")

	def getShow(self):
		return self.getTagData("show")

	def getStatus(self):
		return self.getTagData("status")

	def setPriority(self, val):
		self.setTagData("priority", val)

	def setShow(self, val):
		self.setTagData("show", val)

	def setStatus(self, val):
		self.setTagData("status", val)

	def _muc_getItemAttr(self, tag, attr):
		for xtag in self.getTags("x", namespace=NS_MUC_USER):
			for child in xtag.getTags(tag):
				return child.getAttr(attr)

	def _muc_getSubTagDataAttr(self, tag, attr):
		for xtag in self.getTags("x", namespace=NS_MUC_USER):
			for child in xtag.getTags("item"):
				for cchild in child.getTags(tag):
					return cchild.getData(), cchild.getAttr(attr)
		return None, None

	def getRole(self):
		return self._muc_getItemAttr("item", "role")

	def getAffiliation(self):
		return self._muc_getItemAttr("item", "affiliation")

	def getNick(self):
		return self._muc_getItemAttr("item", "nick")

	def getJid(self):
		return self._muc_getItemAttr("item", "jid")

	def getReason(self):
		return self._muc_getSubTagDataAttr("reason", "")[0]

	def getActor(self):
		return self._muc_getSubTagDataAttr("actor", "jid")[1]

	def getStatusCode(self):
		return self._muc_getItemAttr("status", "code")

class Iq(Protocol):
	def __init__(self, typ=None, queryNS=None, attrs={}, to=None, frm=None, payload=[], xmlns=NS_CLIENT, node=None):
		Protocol.__init__(self, "iq", to=to, typ=typ, attrs=attrs, frm=frm, xmlns=xmlns, node=node)
		if payload:
			self.setQueryPayload(payload)
		if queryNS:
			self.setQueryNS(queryNS)

	def getQuery(self):
		return self.getTag("query")

	def getQueryNS(self):
		tag = self.getTag("query")
		if tag:
			return tag.getNamespace()

	def getQuerynode(self):
		return self.getTagAttr("query", "node")

	def getQueryPayload(self):
		tag = self.getTag("query")
		if tag:
			return tag.getPayload()

	def getQueryChildren(self):
		tag = self.getTag("query")
		if tag:
			return tag.getChildren()

	def setQuery(self, name=None):
		query = self.getQuery()
		if query is None:
			query = self.addChild("query")
		if name is not None:
			query.setName(name)
		return query

	def setQueryNS(self, namespace):
		"""
		Set the namespace of the "query" child element.
		"""
		self.setTag("query").setNamespace(namespace)

	def setQueryPayload(self, payload):
		self.setTag("query").setPayload(payload)

	def setQuerynode(self, node):
		self.setTagAttr("query", "node", node)

	def buildReply(self, typ):
		iq = Iq(typ, to=self.getFrom(), frm=self.getTo(), attrs={"id": self.getID()})
		if self.getTag("query"):
			iq.setQueryNS(self.getQueryNS())
		if self.getTagAttr("query", "node"):
			iq.setQuerynode(self.getQuerynode())
		return iq

class ErrorNode(Node):
	def __init__(self, name, code=None, typ=None, text=None):
		if name in ERRORS:
			cod, type, txt = ERRORS[name]
			ns = name.split()[0]
		else:
			cod, ns, type, txt = "500", NS_STANZAS, "cancel", ""
		if typ:
			type = typ
		if code:
			cod = code
		if text:
			txt = text
		Node.__init__(self, "error", {}, [Node(name)])
		if type:
			self.setAttr("type", type)
		if not cod:
			self.setName("stream:error")
		if txt:
			self.addChild(node=Node(ns + " text", {}, [txt]))
		if cod:
			self.setAttr("code", cod)

class Error(Protocol):
	def __init__(self, node, error, reply=1):
		if reply:
			Protocol.__init__(self, to=node.getFrom(), frm=node.getTo(), node=node)
		else:
			Protocol.__init__(self, node=node)
		self.setError(error)
		if node.getType() == "error":
			self.__str__ = self.__dupstr__

	def __dupstr__(self, dup1=None, dup2=None):
		return ""

class DataField(Node):
	def __init__(self, name=None, value=None, typ=None, required=0, label=None, desc=None, options=[], node=None):
		Node.__init__(self, "field", node=node)
		if name:
			self.setVar(name)
		if isinstance(value, (list, tuple)):
			self.setValues(value)
		elif value:
			self.setValue(value)
		if typ:
			self.setType(typ)
		if required:
			self.setRequired(required)
		if label:
			self.setLabel(label)
		if desc:
			self.setDesc(desc)
		if options:
			self.setOptions(options)

	def setRequired(self, req=1):
		if req:
			self.setTag("required")
		else:
			try:
				self.delChild("required")
			except ValueError:
				return None

	def isRequired(self):
		return self.getTag("required")

	def setLabel(self, label):
		self.setAttr("label", label)

	def getLabel(self):
		return self.getAttr("label")

	def setDesc(self, desc):
		self.setTagData("desc", desc)

	def getDesc(self):
		return self.getTagData("desc")

	def setValue(self, val):
		self.setTagData("value", val)

	def getValue(self):
		return self.getTagData("value")

	def setValues(self, ls):
		while self.getTag("value"):
			self.delChild("value")
		for val in ls:
			self.addValue(val)

	def addValue(self, val):
		self.addChild("value", {}, [val])

	def getValues(self):
		ret = []
		for tag in self.getTags("value"):
			ret.append(tag.getData())
		return ret

	def getOptions(self):
		ret = []
		for tag in self.getTags("option"):
			ret.append([tag.getAttr("label"), tag.getTagData("value")])
		return ret

	def setOptions(self, ls):
		while self.getTag("option"):
			self.delChild("option")
		for opt in ls:
			self.addOption(opt)

	def addOption(self, opt):
		if isinstance(opt, basestring):
			self.addChild("option").setTagData("value", opt)
		else:
			self.addChild("option", {"label": opt[0]}).setTagData("value", opt[1])

	def getType(self):
		return self.getAttr("type")

	def setType(self, val):
		return self.setAttr("type", val)

	def getVar(self):
		return self.getAttr("var")

	def setVar(self, val):
		return self.setAttr("var", val)

class DataReported(Node):
	def __init__(self, node=None):
		Node.__init__(self, "reported", node=node)
		if node:
			newkids = []
			for n in self.getChildren():
				if n.getName() == "field":
					newkids.append(DataField(node=n))
				else:
					newkids.append(n)
			self.kids = newkids

	def getField(self, name):
		return self.getTag("field", attrs={"var": name})

	def setField(self, name, typ=None, label=None, desc=None, options=[]):
		field = self.getField(name)
		if not field:
			field = self.addChild(node=DataField(name, None, typ, 0, label, desc=desc, options=options))
		return field

	def asDict(self):
		ret = {}
		for field in self.getTags("field"):
			name = field.getAttr("var")
			typ = field.getType()
			if isinstance(typ, basestring) and typ.endswith("-multi"):
				val = []
				for i in field.getTags("value"):
					val.append(i.getData())
			else:
				val = field.getTagData("value")
			ret[name] = val
		if self.getTag("instructions"):
			ret["instructions"] = self.getInstructions()
		return ret

	def __getitem__(self, name):
		item = self.getField(name)
		if item:
			return item.getValue()
		raise IndexError("No such field")

	def __setitem__(self, name, val):
		return self.setField(name).setValue(val)

class DataItem(Node):
	def __init__(self, node=None):
		Node.__init__(self, "item", node=node)
		if node:
			newkids = []
			for n in self.getChildren():
				if n.getName() == "field":
					newkids.append(DataField(node=n))
				else:
					newkids.append(n)
			self.kids = newkids

	def getField(self, name):
		return self.getTag("field", attrs={"var": name})

	def setField(self, name, value=None, typ=None, desc=None, options=[]):
		field = self.getField(name)
		if not field:
			field = self.addChild(node=DataField(name, value, typ, desc=desc, options=options))
		return field

	def asDict(self):
		ret = {}
		for field in self.getTags("field"):
			name = field.getAttr("var")
			typ = field.getType()
			if isinstance(typ, basestring) and typ.endswith("-multi"):
				val = []
				for i in field.getTags("value"):
					val.append(i.getData())
			else:
				val = field.getTagData("value")
			ret[name] = val
		if self.getTag("instructions"):
			ret["instructions"] = self.getInstructions()
		return ret

	def __getitem__(self, name):
		item = self.getField(name)
		if item:
			return item.getValue()
		raise IndexError("No such field")

	def __setitem__(self, name, val):
		return self.setField(name).setValue(val)

class DataForm(Node):
	def __init__(self, typ=None, data=[], title=None, node=None):
		Node.__init__(self, "x", node=node)
		if node:
			newkids = []
			for n in self.getChildren():
				if n.getName() == "field":
					newkids.append(DataField(node=n))
				elif n.getName() == "item":
					newkids.append(DataItem(node=n))
				elif n.getName() == "reported":
					newkids.append(DataReported(node=n))
				else:
					newkids.append(n)
			self.kids = newkids
		if typ:
			self.setType(typ)
		self.setNamespace(NS_DATA)
		if title:
			self.setTitle(title)
		if isinstance(data, dict):
			newdata = []
			for name in data.keys():
				newdata.append(DataField(name, data[name]))
			data = newdata
		for child in data:
			if isinstance(child, basestring):
				self.addInstructions(child)
			elif isinstance(child, DataField):
				self.kids.append(child)
			elif isinstance(child, DataItem):
				self.kids.append(child)
			elif isinstance(child, DataReported):
				self.kids.append(child)
			else:
				self.kids.append(DataField(node=child))

	def getType(self):
		return self.getAttr("type")

	def setType(self, typ):
		self.setAttr("type", typ)

	def getTitle(self):
		return self.getTagData("title")

	def setTitle(self, text):
		self.setTagData("title", text)

	def getInstructions(self):
		return self.getTagData("instructions")

	def setInstructions(self, text):
		self.setTagData("instructions", text)

	def addInstructions(self, text):
		self.addChild("instructions", {}, [text])

	def getField(self, name):
		return self.getTag("field", attrs={"var": name})

	def setField(self, name, value=None, typ=None, desc=None, options=[]):
		field = self.getField(name)
		if not field:
			field = self.addChild(node=DataField(name, value, typ, desc=desc, options=options))
		return field

	def asDict(self):
		ret = {}
		for field in self.getTags("field"):
			name = field.getAttr("var")
			typ = field.getType()
			if isinstance(typ, basestring) and typ.endswith("-multi"):
				val = []
				for i in field.getTags("value"):
					val.append(i.getData())
			else:
				val = field.getTagData("value")
			ret[name] = val
		if self.getTag("instructions"):
			ret["instructions"] = self.getInstructions()
		return ret

	def __getitem__(self, name):
		item = self.getField(name)
		if item:
			return item.getValue()
		raise IndexError("No such field")

	def __setitem__(self, name, val):
		return self.setField(name).setValue(val)
