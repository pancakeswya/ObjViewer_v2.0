//
// gif.h
// by Charlie Tangora
// Public domain.
// Email me : ctangora -at- gmail -dot- com
//
// This file offers a simple, very limited way to create animated GIFs directly
// in code.
//
// Those looking for particular cleverness are likely to be disappointed; it's
// pretty much a straight-ahead implementation of the GIF format with optional
// Floyd-Steinberg dithering. (It does at least use delta encoding - only the
// changed portions of each frame are saved.)
//
// So resulting files are often quite large. The hope is that it will be handy
// nonetheless as a quick and easily-integrated way for programs to spit out
// animations.
//
// Only RGBA8 is currently supported as an input format. (The alpha is ignored.)
//
// If capturing a buffer with a bottom-left origin (such as OpenGL), define
// GIF_FLIP_VERT to automatically flip the buffer data when writing the image
// (the buffer itself is unchanged.
//
// USAGE:
// Create a GifWriter struct. Pass it to GifBegin() to initialize and write the
// header. Pass subsequent frames to GifWriteFrame(). Finally, call GifEnd() to
// close the file handle and free memory.
//

#ifndef GIF_H_
#define GIF_H_

// Define these macros to hook into a custom memory allocator.
// TEMP_MALLOC and TEMP_FREE will only be called in stack fashion - frees in the
// reverse order of mallocs and any temp memory allocated by a function will be
// freed before it exits. MALLOC and FREE are used only by GifBegin and GifEnd
// respectively (to allocate a buffer the size of the image, which is used to
// find changed pixels for delta-encoding.)

#ifndef GIF_TEMP_MALLOC
#include <stdlib.h>
#define GIF_TEMP_MALLOC malloc
#endif

#ifndef GIF_TEMP_FREE
#include <stdlib.h>
#define GIF_TEMP_FREE free
#endif

#ifndef GIF_MALLOC
#include <stdlib.h>
#define GIF_MALLOC malloc
#endif

#ifndef GIF_FREE
#include <stdlib.h>
#define GIF_FREE free
#endif

#ifndef GIF_FLIP_VERT
#define GIF_FLIP_VERT
#endif

#include <stdbool.h>  // for bool macros
#include <stdint.h>   // for integer typedefs
#include <stdio.h>    // for FILE*
#include <string.h>   // for memcpy and bzero

typedef struct {
  FILE* f;
  uint8_t* oldImage;
  bool firstFrame;
} GifWriter;

#ifdef __cplusplus
extern "C" {
#endif

bool GifBegin(GifWriter* writer, const char* filename, uint32_t width,
              uint32_t height, uint32_t delay, int32_t bitDepth, bool dither);
bool GifWriteFrame(GifWriter* writer, const uint8_t* image, uint32_t width,
                   uint32_t height, uint32_t delay, int bitDepth, bool dither);
bool GifEnd(GifWriter* writer);

#ifdef __cplusplus
}
#endif

#endif  // GIF_H_
