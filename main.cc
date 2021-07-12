#include <cstdio>
#include <iostream>
#include "src/c_runtime_api.h"
#include "src/dlarray.h"

using namespace std;

int main() {

    DLContext ctx;
    ctx.device_id = 0;
    ctx.device_type =kCPU;

    int ndim = 2;

    int64_t shape[]={4,2};

    auto *out = new DLArrayHandle();

    DLArrayAlloc(shape,ndim, ctx, out);

    cout<<(*out)->shape[0]<<" "<<(*out)->shape[1]<<endl;
    
    return 0;
}