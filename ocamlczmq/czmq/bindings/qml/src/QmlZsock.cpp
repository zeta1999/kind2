/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/

#include "QmlZsock.h"


///
//  Bind a socket to a formatted endpoint. For tcp:// endpoints, supports   
//  ephemeral ports, if you specify the port number as "*". By default      
//  zsock uses the IANA designated range from C000 (49152) to FFFF (65535). 
//  To override this range, follow the "*" with "[first-last]". Either or   
//  both first and last may be empty. To bind to a random port within the   
//  range, use "!" in place of "*".                                         
//                                                                          
//  Examples:                                                               
//      tcp://127.0.0.1:*           bind to first free port from C000 up    
//      tcp://127.0.0.1:!           bind to random port from C000 to FFFF   
//      tcp://127.0.0.1:*[60000-]   bind to first free port from 60000 up   
//      tcp://127.0.0.1:![-60000]   bind to random port from C000 to 60000  
//      tcp://127.0.0.1:![55000-55999]                                      
//                                  bind to random port from 55000 to 55999 
//                                                                          
//  On success, returns the actual port number used, for tcp:// endpoints,  
//  and 0 for other transports. On failure, returns -1. Note that when using
//  ephemeral ports, a port may be reused by different services without     
//  clients being aware. Protocols that run on ephemeral ports should take  
//  this into account.                                                      
int QmlZsock::bind (const QString &format) {
    return zsock_bind (self, "%s", format.toUtf8().data());
};

///
//  Returns last bound endpoint, if any.
const QString QmlZsock::endpoint () {
    return QString (zsock_endpoint (self));
};

///
//  Unbind a socket from a formatted endpoint.                     
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
int QmlZsock::unbind (const QString &format) {
    return zsock_unbind (self, "%s", format.toUtf8().data());
};

///
//  Connect a socket to a formatted endpoint        
//  Returns 0 if OK, -1 if the endpoint was invalid.
int QmlZsock::connect (const QString &format) {
    return zsock_connect (self, "%s", format.toUtf8().data());
};

///
//  Disconnect a socket from a formatted endpoint                  
//  Returns 0 if OK, -1 if the endpoint was invalid or the function
//  isn't supported.                                               
int QmlZsock::disconnect (const QString &format) {
    return zsock_disconnect (self, "%s", format.toUtf8().data());
};

///
//  Attach a socket to zero or more endpoints. If endpoints is not null,     
//  parses as list of ZeroMQ endpoints, separated by commas, and prefixed by 
//  '@' (to bind the socket) or '>' (to connect the socket). Returns 0 if all
//  endpoints were valid, or -1 if there was a syntax error. If the endpoint 
//  does not start with '@' or '>', the serverish argument defines whether   
//  it is used to bind (serverish = true) or connect (serverish = false).    
int QmlZsock::attach (const QString &endpoints, bool serverish) {
    return zsock_attach (self, endpoints.toUtf8().data(), serverish);
};

///
//  Returns socket type as printable constant string.
const QString QmlZsock::typeStr () {
    return QString (zsock_type_str (self));
};

///
//  Send a 'picture' message to the socket (or actor). The picture is a   
//  string that defines the type of each frame. This makes it easy to send
//  a complex multiframe message in one call. The picture can contain any 
//  of these characters, each corresponding to one or two arguments:      
//                                                                        
//      i = int (signed)                                                  
//      1 = uint8_t                                                       
//      2 = uint16_t                                                      
//      4 = uint32_t                                                      
//      8 = uint64_t                                                      
//      s = char *                                                        
//      b = byte *, size_t (2 arguments)                                  
//      c = zchunk_t *                                                    
//      f = zframe_t *                                                    
//      h = zhashx_t *                                                    
//      U = zuuid_t *                                                     
//      p = void * (sends the pointer value, only meaningful over inproc) 
//      m = zmsg_t * (sends all frames in the zmsg)                       
//      z = sends zero-sized frame (0 arguments)                          
//      u = uint (deprecated)                                             
//                                                                        
//  Note that s, b, c, and f are encoded the same way and the choice is   
//  offered as a convenience to the sender, which may or may not already  
//  have data in a zchunk or zframe. Does not change or take ownership of 
//  any arguments. Returns 0 if successful, -1 if sending failed for any  
//  reason.                                                               
int QmlZsock::send (const QString &picture) {
    return zsock_send (self, picture.toUtf8().data());
};

///
//  Send a 'picture' message to the socket (or actor). This is a va_list 
//  version of zsock_send (), so please consult its documentation for the
//  details.                                                             
int QmlZsock::vsend (const QString &picture, va_list argptr) {
    return zsock_vsend (self, picture.toUtf8().data(), argptr);
};

///
//  Receive a 'picture' message to the socket (or actor). See zsock_send for
//  the format and meaning of the picture. Returns the picture elements into
//  a series of pointers as provided by the caller:                         
//                                                                          
//      i = int * (stores signed integer)                                   
//      4 = uint32_t * (stores 32-bit unsigned integer)                     
//      8 = uint64_t * (stores 64-bit unsigned integer)                     
//      s = char ** (allocates new string)                                  
//      b = byte **, size_t * (2 arguments) (allocates memory)              
//      c = zchunk_t ** (creates zchunk)                                    
//      f = zframe_t ** (creates zframe)                                    
//      U = zuuid_t * (creates a zuuid with the data)                       
//      h = zhashx_t ** (creates zhashx)                                    
//      p = void ** (stores pointer)                                        
//      m = zmsg_t ** (creates a zmsg with the remaing frames)              
//      z = null, asserts empty frame (0 arguments)                         
//      u = uint * (stores unsigned integer, deprecated)                    
//                                                                          
//  Note that zsock_recv creates the returned objects, and the caller must  
//  destroy them when finished with them. The supplied pointers do not need 
//  to be initialized. Returns 0 if successful, or -1 if it failed to recv  
//  a message, in which case the pointers are not modified. When message    
//  frames are truncated (a short message), sets return values to zero/null.
//  If an argument pointer is NULL, does not store any value (skips it).    
//  An 'n' picture matches an empty frame; if the message does not match,   
//  the method will return -1.                                              
int QmlZsock::recv (const QString &picture) {
    return zsock_recv (self, picture.toUtf8().data());
};

///
//  Receive a 'picture' message from the socket (or actor). This is a    
//  va_list version of zsock_recv (), so please consult its documentation
//  for the details.                                                     
int QmlZsock::vrecv (const QString &picture, va_list argptr) {
    return zsock_vrecv (self, picture.toUtf8().data(), argptr);
};

///
//  Send a binary encoded 'picture' message to the socket (or actor). This 
//  method is similar to zsock_send, except the arguments are encoded in a 
//  binary format that is compatible with zproto, and is designed to reduce
//  memory allocations. The pattern argument is a string that defines the  
//  type of each argument. Supports these argument types:                  
//                                                                         
//   pattern    C type                  zproto type:                       
//      1       uint8_t                 type = "number" size = "1"         
//      2       uint16_t                type = "number" size = "2"         
//      4       uint32_t                type = "number" size = "3"         
//      8       uint64_t                type = "number" size = "4"         
//      s       char *, 0-255 chars     type = "string"                    
//      S       char *, 0-2^32-1 chars  type = "longstr"                   
//      c       zchunk_t *              type = "chunk"                     
//      f       zframe_t *              type = "frame"                     
//      u       zuuid_t *               type = "uuid"                      
//      m       zmsg_t *                type = "msg"                       
//      p       void *, sends pointer value, only over inproc              
//                                                                         
//  Does not change or take ownership of any arguments. Returns 0 if       
//  successful, -1 if sending failed for any reason.                       
int QmlZsock::bsend (const QString &picture) {
    return zsock_bsend (self, picture.toUtf8().data());
};

///
//  Receive a binary encoded 'picture' message from the socket (or actor).  
//  This method is similar to zsock_recv, except the arguments are encoded  
//  in a binary format that is compatible with zproto, and is designed to   
//  reduce memory allocations. The pattern argument is a string that defines
//  the type of each argument. See zsock_bsend for the supported argument   
//  types. All arguments must be pointers; this call sets them to point to  
//  values held on a per-socket basis. Do not modify or destroy the returned
//  values. Returns 0 if successful, or -1 if it failed to read a message.  
int QmlZsock::brecv (const QString &picture) {
    return zsock_brecv (self, picture.toUtf8().data());
};

///
//  Return socket routing ID if any. This returns 0 if the socket is not
//  of type ZMQ_SERVER or if no request was already received on it.     
uint32_t QmlZsock::routingId () {
    return zsock_routing_id (self);
};

///
//  Set routing ID on socket. The socket MUST be of type ZMQ_SERVER.        
//  This will be used when sending messages on the socket via the zsock API.
void QmlZsock::setRoutingId (uint32_t routingId) {
    zsock_set_routing_id (self, routingId);
};

///
//  Set socket to use unbounded pipes (HWM=0); use this in cases when you are
//  totally certain the message volume can fit in memory. This method works  
//  across all versions of ZeroMQ. Takes a polymorphic socket reference.     
void QmlZsock::setUnbounded () {
    zsock_set_unbounded (self);
};

///
//  Send a signal over a socket. A signal is a short message carrying a   
//  success/failure code (by convention, 0 means OK). Signals are encoded 
//  to be distinguishable from "normal" messages. Accepts a zsock_t or a  
//  zactor_t argument, and returns 0 if successful, -1 if the signal could
//  not be sent. Takes a polymorphic socket reference.                    
int QmlZsock::signal (byte status) {
    return zsock_signal (self, status);
};

///
//  Wait on a signal. Use this to coordinate between threads, over pipe  
//  pairs. Blocks until the signal is received. Returns -1 on error, 0 or
//  greater on success. Accepts a zsock_t or a zactor_t as argument.     
//  Takes a polymorphic socket reference.                                
int QmlZsock::wait () {
    return zsock_wait (self);
};

///
//  If there is a partial message still waiting on the socket, remove and    
//  discard it. This is useful when reading partial messages, to get specific
//  message types.                                                           
void QmlZsock::flush () {
    zsock_flush (self);
};

///
//  Get socket option `tos`.
int QmlZsock::tos () {
    return zsock_tos (self);
};

///
//  Set socket option `tos`.
void QmlZsock::setTos (int tos) {
    zsock_set_tos (self, tos);
};

///
//  Set socket option `router_handover`.
void QmlZsock::setRouterHandover (int routerHandover) {
    zsock_set_router_handover (self, routerHandover);
};

///
//  Set socket option `router_mandatory`.
void QmlZsock::setRouterMandatory (int routerMandatory) {
    zsock_set_router_mandatory (self, routerMandatory);
};

///
//  Set socket option `probe_router`.
void QmlZsock::setProbeRouter (int probeRouter) {
    zsock_set_probe_router (self, probeRouter);
};

///
//  Set socket option `req_relaxed`.
void QmlZsock::setReqRelaxed (int reqRelaxed) {
    zsock_set_req_relaxed (self, reqRelaxed);
};

///
//  Set socket option `req_correlate`.
void QmlZsock::setReqCorrelate (int reqCorrelate) {
    zsock_set_req_correlate (self, reqCorrelate);
};

///
//  Set socket option `conflate`.
void QmlZsock::setConflate (int conflate) {
    zsock_set_conflate (self, conflate);
};

///
//  Get socket option `zap_domain`.
QString QmlZsock::zapDomain () {
    char *retStr_ = zsock_zap_domain (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `zap_domain`.
void QmlZsock::setZapDomain (const QString &zapDomain) {
    zsock_set_zap_domain (self, zapDomain.toUtf8().data());
};

///
//  Get socket option `mechanism`.
int QmlZsock::mechanism () {
    return zsock_mechanism (self);
};

///
//  Get socket option `plain_server`.
int QmlZsock::plainServer () {
    return zsock_plain_server (self);
};

///
//  Set socket option `plain_server`.
void QmlZsock::setPlainServer (int plainServer) {
    zsock_set_plain_server (self, plainServer);
};

///
//  Get socket option `plain_username`.
QString QmlZsock::plainUsername () {
    char *retStr_ = zsock_plain_username (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `plain_username`.
void QmlZsock::setPlainUsername (const QString &plainUsername) {
    zsock_set_plain_username (self, plainUsername.toUtf8().data());
};

///
//  Get socket option `plain_password`.
QString QmlZsock::plainPassword () {
    char *retStr_ = zsock_plain_password (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `plain_password`.
void QmlZsock::setPlainPassword (const QString &plainPassword) {
    zsock_set_plain_password (self, plainPassword.toUtf8().data());
};

///
//  Get socket option `curve_server`.
int QmlZsock::curveServer () {
    return zsock_curve_server (self);
};

///
//  Set socket option `curve_server`.
void QmlZsock::setCurveServer (int curveServer) {
    zsock_set_curve_server (self, curveServer);
};

///
//  Get socket option `curve_publickey`.
QString QmlZsock::curvePublickey () {
    char *retStr_ = zsock_curve_publickey (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `curve_publickey`.
void QmlZsock::setCurvePublickey (const QString &curvePublickey) {
    zsock_set_curve_publickey (self, curvePublickey.toUtf8().data());
};

///
//  Set socket option `curve_publickey` from 32-octet binary
void QmlZsock::setCurvePublickeyBin (const byte *curvePublickey) {
    zsock_set_curve_publickey_bin (self, curvePublickey);
};

///
//  Get socket option `curve_secretkey`.
QString QmlZsock::curveSecretkey () {
    char *retStr_ = zsock_curve_secretkey (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `curve_secretkey`.
void QmlZsock::setCurveSecretkey (const QString &curveSecretkey) {
    zsock_set_curve_secretkey (self, curveSecretkey.toUtf8().data());
};

///
//  Set socket option `curve_secretkey` from 32-octet binary
void QmlZsock::setCurveSecretkeyBin (const byte *curveSecretkey) {
    zsock_set_curve_secretkey_bin (self, curveSecretkey);
};

///
//  Get socket option `curve_serverkey`.
QString QmlZsock::curveServerkey () {
    char *retStr_ = zsock_curve_serverkey (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `curve_serverkey`.
void QmlZsock::setCurveServerkey (const QString &curveServerkey) {
    zsock_set_curve_serverkey (self, curveServerkey.toUtf8().data());
};

///
//  Set socket option `curve_serverkey` from 32-octet binary
void QmlZsock::setCurveServerkeyBin (const byte *curveServerkey) {
    zsock_set_curve_serverkey_bin (self, curveServerkey);
};

///
//  Get socket option `gssapi_server`.
int QmlZsock::gssapiServer () {
    return zsock_gssapi_server (self);
};

///
//  Set socket option `gssapi_server`.
void QmlZsock::setGssapiServer (int gssapiServer) {
    zsock_set_gssapi_server (self, gssapiServer);
};

///
//  Get socket option `gssapi_plaintext`.
int QmlZsock::gssapiPlaintext () {
    return zsock_gssapi_plaintext (self);
};

///
//  Set socket option `gssapi_plaintext`.
void QmlZsock::setGssapiPlaintext (int gssapiPlaintext) {
    zsock_set_gssapi_plaintext (self, gssapiPlaintext);
};

///
//  Get socket option `gssapi_principal`.
QString QmlZsock::gssapiPrincipal () {
    char *retStr_ = zsock_gssapi_principal (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `gssapi_principal`.
void QmlZsock::setGssapiPrincipal (const QString &gssapiPrincipal) {
    zsock_set_gssapi_principal (self, gssapiPrincipal.toUtf8().data());
};

///
//  Get socket option `gssapi_service_principal`.
QString QmlZsock::gssapiServicePrincipal () {
    char *retStr_ = zsock_gssapi_service_principal (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `gssapi_service_principal`.
void QmlZsock::setGssapiServicePrincipal (const QString &gssapiServicePrincipal) {
    zsock_set_gssapi_service_principal (self, gssapiServicePrincipal.toUtf8().data());
};

///
//  Get socket option `ipv6`.
int QmlZsock::ipv6 () {
    return zsock_ipv6 (self);
};

///
//  Set socket option `ipv6`.
void QmlZsock::setIpv6 (int ipv6) {
    zsock_set_ipv6 (self, ipv6);
};

///
//  Get socket option `immediate`.
int QmlZsock::immediate () {
    return zsock_immediate (self);
};

///
//  Set socket option `immediate`.
void QmlZsock::setImmediate (int immediate) {
    zsock_set_immediate (self, immediate);
};

///
//  Set socket option `router_raw`.
void QmlZsock::setRouterRaw (int routerRaw) {
    zsock_set_router_raw (self, routerRaw);
};

///
//  Get socket option `ipv4only`.
int QmlZsock::ipv4only () {
    return zsock_ipv4only (self);
};

///
//  Set socket option `ipv4only`.
void QmlZsock::setIpv4only (int ipv4only) {
    zsock_set_ipv4only (self, ipv4only);
};

///
//  Set socket option `delay_attach_on_connect`.
void QmlZsock::setDelayAttachOnConnect (int delayAttachOnConnect) {
    zsock_set_delay_attach_on_connect (self, delayAttachOnConnect);
};

///
//  Get socket option `type`.
int QmlZsock::type () {
    return zsock_type (self);
};

///
//  Get socket option `sndhwm`.
int QmlZsock::sndhwm () {
    return zsock_sndhwm (self);
};

///
//  Set socket option `sndhwm`.
void QmlZsock::setSndhwm (int sndhwm) {
    zsock_set_sndhwm (self, sndhwm);
};

///
//  Get socket option `rcvhwm`.
int QmlZsock::rcvhwm () {
    return zsock_rcvhwm (self);
};

///
//  Set socket option `rcvhwm`.
void QmlZsock::setRcvhwm (int rcvhwm) {
    zsock_set_rcvhwm (self, rcvhwm);
};

///
//  Get socket option `affinity`.
int QmlZsock::affinity () {
    return zsock_affinity (self);
};

///
//  Set socket option `affinity`.
void QmlZsock::setAffinity (int affinity) {
    zsock_set_affinity (self, affinity);
};

///
//  Set socket option `subscribe`.
void QmlZsock::setSubscribe (const QString &subscribe) {
    zsock_set_subscribe (self, subscribe.toUtf8().data());
};

///
//  Set socket option `unsubscribe`.
void QmlZsock::setUnsubscribe (const QString &unsubscribe) {
    zsock_set_unsubscribe (self, unsubscribe.toUtf8().data());
};

///
//  Get socket option `identity`.
QString QmlZsock::identity () {
    char *retStr_ = zsock_identity (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `identity`.
void QmlZsock::setIdentity (const QString &identity) {
    zsock_set_identity (self, identity.toUtf8().data());
};

///
//  Get socket option `rate`.
int QmlZsock::rate () {
    return zsock_rate (self);
};

///
//  Set socket option `rate`.
void QmlZsock::setRate (int rate) {
    zsock_set_rate (self, rate);
};

///
//  Get socket option `recovery_ivl`.
int QmlZsock::recoveryIvl () {
    return zsock_recovery_ivl (self);
};

///
//  Set socket option `recovery_ivl`.
void QmlZsock::setRecoveryIvl (int recoveryIvl) {
    zsock_set_recovery_ivl (self, recoveryIvl);
};

///
//  Get socket option `sndbuf`.
int QmlZsock::sndbuf () {
    return zsock_sndbuf (self);
};

///
//  Set socket option `sndbuf`.
void QmlZsock::setSndbuf (int sndbuf) {
    zsock_set_sndbuf (self, sndbuf);
};

///
//  Get socket option `rcvbuf`.
int QmlZsock::rcvbuf () {
    return zsock_rcvbuf (self);
};

///
//  Set socket option `rcvbuf`.
void QmlZsock::setRcvbuf (int rcvbuf) {
    zsock_set_rcvbuf (self, rcvbuf);
};

///
//  Get socket option `linger`.
int QmlZsock::linger () {
    return zsock_linger (self);
};

///
//  Set socket option `linger`.
void QmlZsock::setLinger (int linger) {
    zsock_set_linger (self, linger);
};

///
//  Get socket option `reconnect_ivl`.
int QmlZsock::reconnectIvl () {
    return zsock_reconnect_ivl (self);
};

///
//  Set socket option `reconnect_ivl`.
void QmlZsock::setReconnectIvl (int reconnectIvl) {
    zsock_set_reconnect_ivl (self, reconnectIvl);
};

///
//  Get socket option `reconnect_ivl_max`.
int QmlZsock::reconnectIvlMax () {
    return zsock_reconnect_ivl_max (self);
};

///
//  Set socket option `reconnect_ivl_max`.
void QmlZsock::setReconnectIvlMax (int reconnectIvlMax) {
    zsock_set_reconnect_ivl_max (self, reconnectIvlMax);
};

///
//  Get socket option `backlog`.
int QmlZsock::backlog () {
    return zsock_backlog (self);
};

///
//  Set socket option `backlog`.
void QmlZsock::setBacklog (int backlog) {
    zsock_set_backlog (self, backlog);
};

///
//  Get socket option `maxmsgsize`.
int QmlZsock::maxmsgsize () {
    return zsock_maxmsgsize (self);
};

///
//  Set socket option `maxmsgsize`.
void QmlZsock::setMaxmsgsize (int maxmsgsize) {
    zsock_set_maxmsgsize (self, maxmsgsize);
};

///
//  Get socket option `multicast_hops`.
int QmlZsock::multicastHops () {
    return zsock_multicast_hops (self);
};

///
//  Set socket option `multicast_hops`.
void QmlZsock::setMulticastHops (int multicastHops) {
    zsock_set_multicast_hops (self, multicastHops);
};

///
//  Get socket option `rcvtimeo`.
int QmlZsock::rcvtimeo () {
    return zsock_rcvtimeo (self);
};

///
//  Set socket option `rcvtimeo`.
void QmlZsock::setRcvtimeo (int rcvtimeo) {
    zsock_set_rcvtimeo (self, rcvtimeo);
};

///
//  Get socket option `sndtimeo`.
int QmlZsock::sndtimeo () {
    return zsock_sndtimeo (self);
};

///
//  Set socket option `sndtimeo`.
void QmlZsock::setSndtimeo (int sndtimeo) {
    zsock_set_sndtimeo (self, sndtimeo);
};

///
//  Set socket option `xpub_verbose`.
void QmlZsock::setXpubVerbose (int xpubVerbose) {
    zsock_set_xpub_verbose (self, xpubVerbose);
};

///
//  Get socket option `tcp_keepalive`.
int QmlZsock::tcpKeepalive () {
    return zsock_tcp_keepalive (self);
};

///
//  Set socket option `tcp_keepalive`.
void QmlZsock::setTcpKeepalive (int tcpKeepalive) {
    zsock_set_tcp_keepalive (self, tcpKeepalive);
};

///
//  Get socket option `tcp_keepalive_idle`.
int QmlZsock::tcpKeepaliveIdle () {
    return zsock_tcp_keepalive_idle (self);
};

///
//  Set socket option `tcp_keepalive_idle`.
void QmlZsock::setTcpKeepaliveIdle (int tcpKeepaliveIdle) {
    zsock_set_tcp_keepalive_idle (self, tcpKeepaliveIdle);
};

///
//  Get socket option `tcp_keepalive_cnt`.
int QmlZsock::tcpKeepaliveCnt () {
    return zsock_tcp_keepalive_cnt (self);
};

///
//  Set socket option `tcp_keepalive_cnt`.
void QmlZsock::setTcpKeepaliveCnt (int tcpKeepaliveCnt) {
    zsock_set_tcp_keepalive_cnt (self, tcpKeepaliveCnt);
};

///
//  Get socket option `tcp_keepalive_intvl`.
int QmlZsock::tcpKeepaliveIntvl () {
    return zsock_tcp_keepalive_intvl (self);
};

///
//  Set socket option `tcp_keepalive_intvl`.
void QmlZsock::setTcpKeepaliveIntvl (int tcpKeepaliveIntvl) {
    zsock_set_tcp_keepalive_intvl (self, tcpKeepaliveIntvl);
};

///
//  Get socket option `tcp_accept_filter`.
QString QmlZsock::tcpAcceptFilter () {
    char *retStr_ = zsock_tcp_accept_filter (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};

///
//  Set socket option `tcp_accept_filter`.
void QmlZsock::setTcpAcceptFilter (const QString &tcpAcceptFilter) {
    zsock_set_tcp_accept_filter (self, tcpAcceptFilter.toUtf8().data());
};

///
//  Get socket option `rcvmore`.
int QmlZsock::rcvmore () {
    return zsock_rcvmore (self);
};

///
//  Get socket option `fd`.
SOCKET QmlZsock::fd () {
    return zsock_fd (self);
};

///
//  Get socket option `events`.
int QmlZsock::events () {
    return zsock_events (self);
};

///
//  Get socket option `last_endpoint`.
QString QmlZsock::lastEndpoint () {
    char *retStr_ = zsock_last_endpoint (self);
    QString retQStr_ = QString (retStr_);
    free (retStr_);
    return retQStr_;
};


QObject* QmlZsock::qmlAttachedProperties(QObject* object) {
    return new QmlZsockAttached(object);
}


///
//  Create a PUB socket. Default action is bind.
QmlZsock *QmlZsockAttached::newPub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a SUB socket, and optionally subscribe to some prefix string. Default
//  action is connect.                                                          
QmlZsock *QmlZsockAttached::newSub (const QString &endpoint, const QString &subscribe) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_sub (endpoint.toUtf8().data(), subscribe.toUtf8().data());
    return retQ_;
};

///
//  Create a REQ socket. Default action is connect.
QmlZsock *QmlZsockAttached::newReq (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_req (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a REP socket. Default action is bind.
QmlZsock *QmlZsockAttached::newRep (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_rep (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a DEALER socket. Default action is connect.
QmlZsock *QmlZsockAttached::newDealer (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_dealer (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a ROUTER socket. Default action is bind.
QmlZsock *QmlZsockAttached::newRouter (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_router (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PUSH socket. Default action is connect.
QmlZsock *QmlZsockAttached::newPush (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_push (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PULL socket. Default action is bind.
QmlZsock *QmlZsockAttached::newPull (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pull (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create an XPUB socket. Default action is bind.
QmlZsock *QmlZsockAttached::newXpub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_xpub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create an XSUB socket. Default action is connect.
QmlZsock *QmlZsockAttached::newXsub (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_xsub (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a PAIR socket. Default action is connect.
QmlZsock *QmlZsockAttached::newPair (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_pair (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a STREAM socket. Default action is connect.
QmlZsock *QmlZsockAttached::newStream (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_stream (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a SERVER socket. Default action is bind.
QmlZsock *QmlZsockAttached::newServer (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_server (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Create a CLIENT socket. Default action is connect.
QmlZsock *QmlZsockAttached::newClient (const QString &endpoint) {
    QmlZsock *retQ_ = new QmlZsock ();
    retQ_->self = zsock_new_client (endpoint.toUtf8().data());
    return retQ_;
};

///
//  Probe the supplied object, and report if it looks like a zsock_t.
//  Takes a polymorphic socket reference.                            
bool QmlZsockAttached::is (void *self) {
    return zsock_is (self);
};

///
//  Probe the supplied reference. If it looks like a zsock_t instance, return
//  the underlying libzmq socket handle; else if it looks like a file        
//  descriptor, return NULL; else if it looks like a libzmq socket handle,   
//  return the supplied value. Takes a polymorphic socket reference.         
void *QmlZsockAttached::resolve (void *self) {
    return zsock_resolve (self);
};

///
//  Self test of this class.
void QmlZsockAttached::test (bool verbose) {
    zsock_test (verbose);
};

///
//  Create a new socket. Returns the new socket, or NULL if the new socket
//  could not be created. Note that the symbol zsock_new (and other       
//  constructors/destructors for zsock) are redirected to the *_checked   
//  variant, enabling intelligent socket leak detection. This can have    
//  performance implications if you use a LOT of sockets. To turn off this
//  redirection behaviour, define ZSOCK_NOCHECK.                          
QmlZsock *QmlZsockAttached::construct (int type) {
    QmlZsock *qmlSelf = new QmlZsock ();
    qmlSelf->self = zsock_new (type);
    return qmlSelf;
};

///
//  Destroy the socket. You must use this for any socket created via the
//  zsock_new method.                                                   
void QmlZsockAttached::destruct (QmlZsock *qmlSelf) {
    zsock_destroy (&qmlSelf->self);
};

/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
*/