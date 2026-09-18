#include "gx.hpp"

extern "C" {

// TODO GXSetGPMetric
// TODO GXClearGPMetric
// TODO GXReadGPMetric
// TODO GXReadGP0Metric
// TODO GXReadGP1Metric
// TODO GXReadMemMetric
// TODO GXClearMemMetric
// TODO GXReadPixMetric
// TODO GXClearPixMetric
// TODO GXSetVCacheMetric
// TODO GXReadVCacheMetric
// TODO GXClearVCacheMetric
void GXReadXfRasMetric(u32* xf_wait_in, u32* xf_wait_out, u32* ras_busy, u32* clocks) {
  // Aurora has no hardware XF/RAS counters. These values are only used by the
  // original hang diagnostic, so report an idle software pipeline.
  if (xf_wait_in != nullptr) {
    *xf_wait_in = 0;
  }
  if (xf_wait_out != nullptr) {
    *xf_wait_out = 0;
  }
  if (ras_busy != nullptr) {
    *ras_busy = 0;
  }
  if (clocks != nullptr) {
    *clocks = 0;
  }
}
// TODO GXInitXfRasMetric
// TODO GXReadClksPerVtx
}
