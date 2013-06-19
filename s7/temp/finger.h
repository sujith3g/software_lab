/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _FINGER_H_RPCGEN
#define _FINGER_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct finger_out {
	char message[1024];
};
typedef struct finger_out finger_out;

#define FINGER 0x21230000
#define FINGER_VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define MyFinger 1
extern  finger_out * myfinger_1(void *, CLIENT *);
extern  finger_out * myfinger_1_svc(void *, struct svc_req *);
extern int finger_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MyFinger 1
extern  finger_out * myfinger_1();
extern  finger_out * myfinger_1_svc();
extern int finger_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_finger_out (XDR *, finger_out*);

#else /* K&R C */
extern bool_t xdr_finger_out ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_FINGER_H_RPCGEN */