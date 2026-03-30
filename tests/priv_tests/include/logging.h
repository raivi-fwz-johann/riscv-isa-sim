#ifndef LOGGING_H
#define LOGGING_H

#include <stdlib.h>
#include <sys_utils.h>
#include <test_utils.h>


#ifndef LOG_LEVEL
#define LOG_LEVEL   LOG_INFO
#endif

#define CDFLT  "\x1B[0m"
#define CRED  "\x1B[31m"
#define CGRN  "\x1B[32m"
#define CYEL  "\x1B[33m"
#define CBLU  "\x1B[34m"
#define CMAG  "\x1B[35m"
#define CCYN  "\x1B[36m"
#define CWHT  "\x1B[37m"

#define LOG_NONE      (0)	
#define LOG_ERROR	  (1)
#define LOG_INFO      (2)
#define LOG_DETAIL    (3)
#define LOG_WARNING   (4)
#define LOG_VERBOSE   (5)
#define LOG_DEBUG     (6)

#if LOG_LEVEL >= LOG_ERROR
# define ERROR(str...)	{\
    printf(CRED "ERROR: " CDFLT str );\
    printf(" (%s, %d)\n", __func__, __LINE__);\
    exit(1);\
    while(1);\
}
#else
# define ERROR(...) { exit(-1); while(1); }
#endif

#if LOG_LEVEL >= LOG_INFO
# define INFO(str...)	{ printf(str); printf("\n"); }
#else
# define INFO(...)
#endif

#if LOG_LEVEL >= LOG_DETAIL
# define DETAIL(str...)	{ printf(str); printf("\n"); }
#else
# define DETAIL(...)
#endif

#if LOG_LEVEL >= LOG_WARNING
# define WARN(str...)	{ printf(CYEL "WARNING: " CDFLT str); printf("\n"); }
#else
# define WARN(...)
#endif

#if LOG_LEVEL >= LOG_VERBOSE
# define VERBOSE(str...)	{ printf("VERBOSE: " str); printf("\n"); }
#else
# define VERBOSE(...)
#endif

#if LOG_LEVEL >= LOG_DEBUG
# define DEBUG(str...)	{ printf("DEBUG: " str); printf("\n"); }
#else
# define DEBUG(...)
#endif


#define INFO_PRINT(var) {\
    INFO(#var ": 0x%llx", (var));\
}

#define INFO_PRINT_CSR(csr){\
    INFO(#csr ": 0x%llx", CSRR(csr));\
}

#define INFO_PRINT_XCEPT(){\
    INFO("excpt.triggered = %d", excpt.triggered);\
    INFO("excpt.priv = %s", priv_strs[excpt.priv]);\
    INFO("excpt.cause = 0x%llx", excpt.cause);\
    INFO("excpt.tval = 0x%llx", excpt.tval);\
    INFO("excpt.tval2 = 0x%llx", excpt.tval2);\
    INFO("excpt.tinst = 0x%llx", excpt.tinst);\
}

#define DEBUG_PRINT(var) {\
    DEBUG(#var ": 0x%llx", (var));\
}

#define DEBUG_PRINT_CSR(csr){\
    DEBUG(#csr ": 0x%llx", CSRR(csr));\
}

#define DEBUG_PRINT_XCEPT(){\
    DEBUG("excpt.triggered = %d", excpt.triggered);\
    DEBUG("excpt.priv = %s", priv_strs[excpt.priv]);\
    DEBUG("excpt.cause = 0x%llx", excpt.cause);\
    DEBUG("excpt.tval = 0x%llx", excpt.tval);\
    DEBUG("excpt.tval2 = 0x%llx", excpt.tval2);\
    INFO("excpt.tinst = 0x%llx", excpt.tinst);\
}


#endif
