/* Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __MM_JPEG_DBG_H__
#define __MM_JPEG_DBG_H__

#define LOG_DEBUG 1
#define MINIMUM_JPEG_LOG_LEVEL 1

/* Choose debug log level. This will not affect the error logs
   0: turns off CDBG and CDBG_HIGH logs
   1: turns-on CDBG_HIGH logs
   2: turns-on CDBG_HIGH and CDBG logs */
extern volatile uint32_t gMmJpegIntfLogLevel;
extern volatile uint32_t gKpiDebugLevel;

#ifndef LOG_DEBUG
  #ifdef _ANDROID_
    #undef LOG_NIDEBUG
    #undef LOG_TAG
    #define LOG_NIDEBUG 0
    #define LOG_TAG "mm-jpeg-intf"
    #include <log/log.h>
  #else
    #include <stdio.h>
    #define ALOGE CDBG
  #endif
  #undef CDBG
  #define CDBG(fmt, args...) do{}while(0)
#else
  #ifdef _ANDROID_
    #undef LOG_NIDEBUG
    #undef LOG_TAG
    #define LOG_NIDEBUG 0
    #define LOG_TAG "mm-jpeg-intf"
    #include <log/log.h>
    #define CDBG(fmt, args...) ALOGD_IF(gMmJpegIntfLogLevel >= 2, fmt, ##args)
  #else
    #include <stdio.h>
    #define CDBG(fmt, args...) fprintf(stderr, fmt, ##args)
    #define ALOGE(fmt, args...) fprintf(stderr, fmt, ##args)
  #endif
#endif

#ifdef _ANDROID_
  #define CDBG_HIGH(fmt, args...)   ALOGD_IF(gMmJpegIntfLogLevel >= 1, fmt, ##args)
  #define CDBG_ERROR(fmt, args...)  ALOGE(fmt, ##args)
#else
  #define CDBG_HIGH(fmt, args...) fprintf(stderr, fmt, ##args)
  #define CDBG_ERROR(fmt, args...) fprintf(stderr, fmt, ##args)
#endif

#ifndef KPI_DEBUG
#define KPI_DEBUG
#define ATRACE_TAG ATRACE_TAG_CAMERA
#include <cutils/trace.h>

#define KPI_APT 1
#define KPI_DBG 2

#define KPI_ATRACE_INT(name,val) ({\
if (gKpiDebugLevel >= KPI_APT) { \
     atrace_int(ATRACE_TAG, name, val); \
}\
})

#endif
#endif /* __MM_JPEG_DBG_H__ */
