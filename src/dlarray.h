#ifndef DLSYS_DLARRAY_H
#define DLSYS_DLARRAY_H

#ifdef __cplusplus
#define DLSYS_EXTERN_C extern "C"
#else
#define DLSYS_EXTERN_C
#endif

#include <cstddef>
#include <cstdint>

DLSYS_EXTERN_C {
  typedef enum {
    kCPU = 1,
    kGPU = 2,
  } DLDeviceType;

  typedef struct {
    int device_id;
    DLDeviceType device_type;
  } DLContext;

  typedef struct {
    void *data;
    DLContext ctx;
    int ndim;
    int64_t *shape;
  } DLArray;
}
#endif //DLSYS_DLARRAY_H