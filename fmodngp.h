/* ==================================================================================================== */
/* FMOD Ex - NGP development header file. Copyright (c), Firelight Technologies Pty, Ltd. 2004-2014.    */
/*                                                                                                      */
/* Use this header to allow setting of thread affinities for FMOD threads.                              */
/*                                                                                                      */
/* ==================================================================================================== */

#ifndef _FMOD_NGP_H
#define _FMOD_NGP_H

#include "fmod.h"

/*
[ENUM]
[
    [DESCRIPTION]
    NGP thread affinity to use in FMOD_NGP_EXTRADRIVERDATA

    [PLATFORMS]
    NGP
]
*/
typedef enum
{
    FMOD_NGP_THREADAFFINITY_CPU2,      /* Run thread on CPU2 */
    FMOD_NGP_THREADAFFINITY_CPU0,      /* Run thread on CPU0 */
    FMOD_NGP_THREADAFFINITY_CPU1,      /* Run thread on CPU1 */
} FMOD_NGP_THREADAFFINITY;

/*
[STRUCTURE] 
[
    [DESCRIPTION]
    When initializing system provide this as extradriverdata to set thread affinities for FMOD threads.

    [PLATFORMS]
    NGP
]
*/
typedef struct FMOD_NGP_EXTRADRIVERDATA
{
	FMOD_NGP_THREADAFFINITY mixeraffinity;           /* [in] CPU affinity mask of FMOD mixer thread */
	FMOD_NGP_THREADAFFINITY ngsupdateaffinity;       /* [in] CPU affinity mask of FMOD NGS update thread */
	FMOD_NGP_THREADAFFINITY ngsoutputaffinity;       /* [in] CPU affinity mask of FMOD NGS output thread */
	FMOD_NGP_THREADAFFINITY streamaffinity;          /* [in] CPU affinity mask of FMOD stream thread */
	FMOD_NGP_THREADAFFINITY nonblockingaffinity;     /* [in] CPU affinity mask of FMOD nonblocking thread */
	FMOD_NGP_THREADAFFINITY fileaffinity;            /* [in] CPU affinity mask of FMOD file thread */
	FMOD_NGP_THREADAFFINITY geometryaffinity;        /* [in] CPU affinity mask of FMOD geometry thread */
	FMOD_NGP_THREADAFFINITY recordupdateaffinity;    /* [in] CPU affinity mask of FMOD record update thread */
    unsigned int at9TotalCh;                         /* [in] Total number of ATRAC9 channels available for libaudiodec, limited to 16 */
} FMOD_NGP_EXTRADRIVERDATA;

#endif


