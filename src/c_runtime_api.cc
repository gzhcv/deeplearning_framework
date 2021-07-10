#include "c_runtime_api.h"
#include "cpu_device_api.h"
#include "runtime_base.h"

#include <array>
#include <thread>

using namespace std;

class DeviceAPIManager {
 public:
  static const int kMaxDeviceAPI = 8;

  static DeviceAPI *Get(DLContext ctx) {
    return Global()->GetAPI(ctx.device_type);
  }

 private:
  std::array<DeviceAPI*, kMaxDeviceAPI> api_;

  DeviceAPIManager() {
    std::fill(api_.begin(), api_.end(), nullptr);
    static CPUDeviceAPI cpu_device_api_inst;
    api_[kCPU] = static_cast<DeviceAPI *>(&cpu_device_api_inst);
  }

  static DeviceAPIManager *Global() {
    static DeviceAPIManager inst;
    return &inst;
  }

  DeviceAPI *GetAPI(DLDeviceType type) {
    if (api_[type] == nullptr) {
      std::cerr << "Device API not supported!" <<std::endl;
      exit(EXIT_FAILURE);
    }
    return api_[type];
  }

};

inline DLArray* DLArrayCreate_() {
  DLArray* arr = new DLArray();
  arr->shape = nullptr;
  arr->ndim = 0;
  arr->data = nullptr;
  return arr;
}

inline void DLArrayFree_(DLArray* arr) {
  // need to complete free memory.
  if (arr->data != nullptr) {
    DeviceAPIManager::Get(arr->ctx)->FreeDataSpace(arr->ctx, arr->data);
  }
}

inline size_t GetDataSize(DLArray* arr) {
  size_t size = 1;
  for (index_t i = 0; i < arr->ndim; i++)
    size *= arr->shape[i];
  // why multiply 4
  size *= 4;
  return size;
}

inline size_t GetDataAlignment(DLArray* arr) {
  // why is 8
  return 8;
}

int DLArrayAlloc(const index_t* shape, int ndim,
                 DLContext ctx, DLArrayHandle* out) {
  DLArray* arr;

  API_BEGIN()
    arr = DLArrayCreate_();
    arr->ndim = ndim;
    index_t* shape_copy = new index_t[ndim];
    std::copy(shape, shape + ndim, shape_copy);
    arr->shape = shape_copy;
    arr->ctx = ctx;
    size_t size = GetDataSize(arr);
    size_t alignment = GetDataAlignment(arr);
    arr->data = DeviceAPIManager::Get(ctx)->AllocDataSpace(ctx, size, alignment);
    *out = arr;
  API_END_HANDLE_ERROR(DLArrayFree_(arr));
}

int DLArrayFree(DLArrayHandle handle) {
  API_BEGIN()
    DLArray *arr = handle;
    DLArrayFree_(arr);
  API_END();
}

int DLArrayCopyFromTo(DLArrayHandle from, DLArrayHandle to, DLStreamHandle stream) {
  API_BEGIN()
    size_t from_size = GetDataSize(from);
    size_t to_size = GetDataSize(to);
    assert(from_size == to_size);
    DLContext ctx = from->ctx;

    // ???
    if (ctx.device_type == kCPU) {
      ctx = to->ctx;
    }
    DeviceAPIManager::Get(ctx)->CopyDataFromTo(from->data, to->data, from_size,
                                               from->ctx, to->ctx, stream);
  API_END()
}