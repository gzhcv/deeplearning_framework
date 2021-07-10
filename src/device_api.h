#ifndef DLSYS_DEVICE_API_H
#define DLSYS_DEVICE_API_H

#include <cassert>
#include <cstring>

class DeviceAPI {
 public:
  DeviceAPI() = default;

  virtual ~DeviceAPI() = default; // 基类

  virtual void *AllocDataSpace(DLContext ctx, size_t size, size_t alignment) = 0;

  virtual void FreeDataSpace(DLContext ctx, void *ptr) = 0;

  virtual void CopyDataFromTo(const void *from, void *to, size_t size,
                              DLContext ctx_from, DLContext ctx_to,
                              DLStreamHandle stream) = 0;

  virtual void StreamSync(DLContext ctx, DLStreamHandle stream) = 0;

};
#endif //DLSYS_DEVICE_API_H