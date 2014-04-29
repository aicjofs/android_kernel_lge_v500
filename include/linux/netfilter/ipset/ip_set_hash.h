#ifndef __IP_SET_HASH_H
#define __IP_SET_HASH_H

/*                                */
enum {
	/*              */
	IPSET_ERR_HASH_FULL = IPSET_ERR_TYPE_SPECIFIC,
	/*                     */
	IPSET_ERR_HASH_ELEM,
	/*                  */
	IPSET_ERR_INVALID_PROTO,
	/*                                        */
	IPSET_ERR_MISSING_PROTO,
	/*                     */
	IPSET_ERR_HASH_RANGE_UNSUPPORTED,
	/*               */
	IPSET_ERR_HASH_RANGE,
};

#ifdef __KERNEL__

#define IPSET_DEFAULT_HASHSIZE		1024
#define IPSET_MIMINAL_HASHSIZE		64
#define IPSET_DEFAULT_MAXELEM		65536
#define IPSET_DEFAULT_PROBES		4
#define IPSET_DEFAULT_RESIZE		100

#endif /*            */

#endif /*                 */
