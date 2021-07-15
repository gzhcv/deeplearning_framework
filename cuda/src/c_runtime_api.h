#ifndef DLSYS_C_RUNTIME_API_H
#define DLSYS_C_RUNTIME_API_H

#ifdef __cplusplus
#define DLSYS_EXTERN_C extern "C"
#else
#define DLSYS_EXTERN_C
#endif

#include <cstdint>
#include <cstddef>

#include "dlarray.h"

DLSYS_EXTERN_C {
  typedef int64_t index_t;

  typedef DLArray *DLArrayHandle;

  typedef void *DLStreamHandle;

  int DLArrayAlloc(const index_t *shape, int ndim, DLContext ctx, DLArrayHandle *out);

  int DLArrayFree(DLArrayHandle handle);

  int DLArrayCopyFromTo(DLArrayHandle from, DLArrayHandle to, DLStreamHandle stream);

}
#endif //DLSYS_C_RUNTIME_API_H