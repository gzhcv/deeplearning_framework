#ifndef DLSYS_CUDA_DEVICE_API_H
#define DLSYS_CUDA_DEVICE_API_H

#include "c_runtime_api.h"
#include "device_api.h"
#include <cuda_runtime.h>

#include <cassert>
#include <cstring>

class CUDADeviceAPI : public DeviceAPI {
 public:
  void *AllocDataSpace(DLContext ctx, size_t size, size_t alignment) final;

  virtual void FreeDataSpace(DLContext ctx, void *ptr) final;

  virtual void CopyDataFromTo(const void *from, void *to, size_t size,
                              DLContext ctx_from, DLContext ctx_to,
                              DLStreamHandle stream) final;

  virtual void StreamSync(DLContext ctx, DLStreamHandle stream) final;

};
#endif //DLSYS_CUDA_DEVICE_API_H