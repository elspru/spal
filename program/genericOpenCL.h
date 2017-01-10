/*SPEL virtual machine
Copyright (C) 2016  Logan Streondj

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

contact: streondj at gmail dot com
*/

#ifndef GENERIC_H
#define GENERIC_H

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#include <CL/cl.h>
#include <CL/cl_platform.h>
#endif

#define NB_MAX_PLATFORMS 8
#define NB_MAX_DEVICES_PER_PLATFORM 16

typedef struct {
  cl_platform_id platform;
  cl_context context;
  cl_device_id device;
  cl_command_queue queue;
  int nComputeUnits;
  unsigned long int maxPointerSize;
  int deviceType; /* deviceType 0 = GPU | deviceType 1 = CPU | deviceType 2 =
                     Accelerator | deviceType 3 = other */
  int devNum;
} sclHard;

typedef struct {
  cl_program program;
  cl_kernel kernel;
  char kernelName[98];
} sclSoft;

int success_verification(cl_int error_number);

void getInfo();

void sclGetHardware(const int iDevice, sclHard *CPUHardware);

int seed_program_probe(const cl_device_id device_id, const cl_context context,
                       char *filename, cl_program *program /*,
                            cl_kernel *kernel*/);
int seed_program_establish(const cl_device_id device_id,
                           const cl_context context, char *filename,
                           char *seed_name, cl_program *program,
                           cl_kernel *kernel);

float diagnoseOpenCLnumber(cl_platform_id platform);

#define seed_input_giving(seed, indexFinger, input_long, input)                \
  if (success_verification(                                                    \
          clSetKernelArg(kernel, indexFinger, input_long, input))) {           \
    ++indexFinger;                                                             \
  } else {                                                                     \
    fprintf(stderr, "seed input %d error %s:%d", indexFinger, __FILE__,        \
            __LINE__);                                                         \
  }

#endif
