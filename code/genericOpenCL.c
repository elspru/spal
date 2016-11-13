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
//#include <regex.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "genericOpenCL.h"

#define MAX_SOURCE_SIZE (0x100000)
#define MAX_FILENAME_LONG (0xFF)
#define INFO_LENGTH 4096

const char *interpret_return_number(cl_int return_number) {
  switch (return_number) {
  case CL_SUCCESS:
    return "CL_SUCCESS";
  case CL_DEVICE_NOT_FOUND:
    return "CL_DEVICE_NOT_FOUND";
  case CL_DEVICE_NOT_AVAILABLE:
    return "CL_DEVICE_NOT_AVAILABLE";
  case CL_COMPILER_NOT_AVAILABLE:
    return "CL_COMPILER_NOT_AVAILABLE";
  case CL_MEM_OBJECT_ALLOCATION_FAILURE:
    return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
  case CL_OUT_OF_RESOURCES:
    return "CL_OUT_OF_RESOURCES";
  case CL_OUT_OF_HOST_MEMORY:
    return "CL_OUT_OF_HOST_MEMORY";
  case CL_PROFILING_INFO_NOT_AVAILABLE:
    return "CL_PROFILING_INFO_NOT_AVAILABLE";
  case CL_MEM_COPY_OVERLAP:
    return "CL_MEM_COPY_OVERLAP";
  case CL_IMAGE_FORMAT_MISMATCH:
    return "CL_IMAGE_FORMAT_MISMATCH";
  case CL_IMAGE_FORMAT_NOT_SUPPORTED:
    return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
  case CL_BUILD_PROGRAM_FAILURE:
    return "CL_BUILD_PROGRAM_FAILURE";
  case CL_MAP_FAILURE:
    return "CL_MAP_FAILURE";
  case CL_MISALIGNED_SUB_BUFFER_OFFSET:
    return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
  case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
    return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
  case CL_INVALID_VALUE:
    return "CL_INVALID_VALUE";
  case CL_INVALID_DEVICE_TYPE:
    return "CL_INVALID_DEVICE_TYPE";
  case CL_INVALID_PLATFORM:
    return "CL_INVALID_PLATFORM";
  case CL_INVALID_DEVICE:
    return "CL_INVALID_DEVICE";
  case CL_INVALID_CONTEXT:
    return "CL_INVALID_CONTEXT";
  case CL_INVALID_QUEUE_PROPERTIES:
    return "CL_INVALID_QUEUE_PROPERTIES";
  case CL_INVALID_COMMAND_QUEUE:
    return "CL_INVALID_COMMAND_QUEUE";
  case CL_INVALID_HOST_PTR:
    return "CL_INVALID_HOST_PTR";
  case CL_INVALID_MEM_OBJECT:
    return "CL_INVALID_MEM_OBJECT";
  case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
    return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
  case CL_INVALID_IMAGE_SIZE:
    return "CL_INVALID_IMAGE_SIZE";
  case CL_INVALID_SAMPLER:
    return "CL_INVALID_SAMPLER";
  case CL_INVALID_BINARY:
    return "CL_INVALID_BINARY";
  case CL_INVALID_BUILD_OPTIONS:
    return "CL_INVALID_BUILD_OPTIONS";
  case CL_INVALID_PROGRAM:
    return "CL_INVALID_PROGRAM";
  case CL_INVALID_PROGRAM_EXECUTABLE:
    return "CL_INVALID_PROGRAM_EXECUTABLE";
  case CL_INVALID_KERNEL_NAME:
    return "CL_INVALID_KERNEL_NAME";
  case CL_INVALID_KERNEL_DEFINITION:
    return "CL_INVALID_KERNEL_DEFINITION";
  case CL_INVALID_KERNEL:
    return "CL_INVALID_KERNEL";
  case CL_INVALID_ARG_INDEX:
    return "CL_INVALID_ARG_INDEX";
  case CL_INVALID_ARG_VALUE:
    return "CL_INVALID_ARG_VALUE";
  case CL_INVALID_ARG_SIZE:
    return "CL_INVALID_ARG_SIZE";
  case CL_INVALID_KERNEL_ARGS:
    return "CL_INVALID_KERNEL_ARGS";
  case CL_INVALID_WORK_DIMENSION:
    return "CL_INVALID_WORK_DIMENSION";
  case CL_INVALID_WORK_GROUP_SIZE:
    return "CL_INVALID_WORK_GROUP_SIZE";
  case CL_INVALID_WORK_ITEM_SIZE:
    return "CL_INVALID_WORK_ITEM_SIZE";
  case CL_INVALID_GLOBAL_OFFSET:
    return "CL_INVALID_GLOBAL_OFFSET";
  case CL_INVALID_EVENT_WAIT_LIST:
    return "CL_INVALID_EVENT_WAIT_LIST";
  case CL_INVALID_EVENT:
    return "CL_INVALID_EVENT";
  case CL_INVALID_OPERATION:
    return "CL_INVALID_OPERATION";
  case CL_INVALID_GL_OBJECT:
    return "CL_INVALID_GL_OBJECT";
  case CL_INVALID_BUFFER_SIZE:
    return "CL_INVALID_BUFFER_SIZE";
  case CL_INVALID_MIP_LEVEL:
    return "CL_INVALID_MIP_LEVEL";
  case CL_INVALID_GLOBAL_WORK_SIZE:
    return "CL_INVALID_GLOBAL_WORK_SIZE";
  case CL_INVALID_PROPERTY:
    return "CL_INVALID_PROPERTY";
  default:
    return "unknown OPEN_CL error";
  }
}

int success_verification(cl_int return_number) {
  if (return_number == CL_SUCCESS) {
    return (1 == 1);
  } else {
    fprintf(stderr, "%d: ", (unsigned int)return_number);
    fprintf(stderr, "%s\n", interpret_return_number(return_number));
    return (1 == 0);
  }
}

float diagnoseOpenCLnumber(cl_platform_id platform) {
#define VERSION_LENGTH 64
  char complete_version[VERSION_LENGTH];
  size_t realSize = 0;
  clGetPlatformInfo(platform, CL_PLATFORM_VERSION, VERSION_LENGTH,
                    &complete_version, &realSize);
  char version[4];
  version[3] = 0;
  memcpy(version, &complete_version[7], 3);
  // printf("V %s %f\n", version, version_float);
  float version_float = (float)atof(version);
  return version_float;
}

void getInfo() {
  /* get info */
  cl_uint numEntries = 5;
  cl_platform_id platforms[5];
  cl_uint num_platforms = 0;
  uint8_t platform_indexFinger = 0;
  cl_int return_number;
  // cl_int result;
  return_number = clGetPlatformIDs(numEntries, platforms, &num_platforms);
  if (!(success_verification(return_number))) {
    fprintf(stderr, "getPlatformId failed \n");
    return;
  }
  printf("###################\n");
  printf("# of platforms \t%d\n", num_platforms);
  for (; platform_indexFinger < num_platforms; ++platform_indexFinger) {
    printf("#################\n");
    char platformInfo[INFO_LENGTH];
    memset(platformInfo, 0, INFO_LENGTH);
    size_t realSize = 0;
    memset(platformInfo, 0, INFO_LENGTH);
    printf("Platform #: \t%d\n", platform_indexFinger);
    return_number =
        clGetPlatformInfo(platforms[platform_indexFinger], CL_PLATFORM_VENDOR,
                          INFO_LENGTH, &platformInfo, &realSize);
    if (!(success_verification(return_number))) {
      return;
    }
    printf("vendor: \t%s \n", platformInfo);
    memset(platformInfo, 0, INFO_LENGTH);
    return_number =
        clGetPlatformInfo(platforms[platform_indexFinger], CL_PLATFORM_NAME,
                          INFO_LENGTH, &platformInfo, &realSize);
    if (!(success_verification(return_number))) {
      fprintf(stderr, "getPlatformInfo Failed \n");
    }
    printf("name: \t\t%s \n", platformInfo);
    memset(platformInfo, 0, INFO_LENGTH);
    return_number =
        clGetPlatformInfo(platforms[platform_indexFinger], CL_PLATFORM_VERSION,
                          INFO_LENGTH, &platformInfo, &realSize);

    if (!(success_verification(return_number))) {
      return;
    }
    printf("version: \t%s \n", platformInfo);

    memset(platformInfo, 0, INFO_LENGTH);
    return_number =
        clGetPlatformInfo(platforms[platform_indexFinger], CL_PLATFORM_PROFILE,
                          INFO_LENGTH, &platformInfo, &realSize);
    if (!(success_verification(return_number))) {
      return;
    }
    printf("profile: \t%s \n", platformInfo);
    return_number = clGetPlatformInfo(platforms[platform_indexFinger],
                                      CL_PLATFORM_EXTENSIONS, INFO_LENGTH,
                                      &platformInfo, &realSize);
    if (!(success_verification(return_number))) {
      return;
    }
    printf("extensions: \t%s \n", platformInfo);

    cl_device_id deviceID[4];
    cl_uint num_devices;
    clGetDeviceIDs(platforms[platform_indexFinger], CL_DEVICE_TYPE_ALL, 8,
                   deviceID, &num_devices);
    if (!success_verification(return_number)) {
      return;
    }
    printf("# of devices: \t%d\n", num_devices);

    // cl_ulong deviceType[2];
    cl_ulong globalCacheSize = 0;
    cl_ulong globalMemSize = 0;
    cl_ulong localMemSize = 0;
    cl_ulong constantBufferSize = 0;
    cl_ulong memAllocSize = 0;
    // size_t maxParameterSize = 0;
    size_t workGroupSize = 0;
    cl_uint workItemDimensions = 0;
    cl_uint maxComputeUnits = 0;
    cl_uint clockFreq = 0;
    size_t workItemSizes[6];
    char deviceName[256];
    memset(deviceName, 0, 256);
    cl_uint i = 0;
    cl_uint dimension_indexFinger = 0;
    for (i = 0; i < num_devices; i++) {
      return_number = clGetDeviceInfo(deviceID[i], CL_DEVICE_NAME, 256,
                                      deviceName, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number = clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_COMPUTE_UNITS,
                                      8, &maxComputeUnits, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number = clGetDeviceInfo(
          deviceID[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, 8, &clockFreq, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number = clGetDeviceInfo(deviceID[i], CL_DEVICE_LOCAL_MEM_SIZE, 16,
                                      &localMemSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number =
          clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, 8,
                          &constantBufferSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number =
          clGetDeviceInfo(deviceID[i], CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, 8,
                          &globalCacheSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number = clGetDeviceInfo(deviceID[i], CL_DEVICE_GLOBAL_MEM_SIZE, 8,
                                      &globalMemSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number = clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_MEM_ALLOC_SIZE,
                                      8, &memAllocSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number =
          clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, 8,
                          &workGroupSize, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number =
          clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, 8,
                          &workItemDimensions, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      return_number =
          clGetDeviceInfo(deviceID[i], CL_DEVICE_MAX_WORK_ITEM_SIZES, 25,
                          workItemSizes, &realSize);
      if (!success_verification(return_number)) {
        return;
      }
      printf("#######\nDEVICE: \t%d\n", i);
      printf("name: \t\t\t%s \n", deviceName);
      printf("compute units: \t\t%u \n", (unsigned int)maxComputeUnits);
      printf("clockFreq: \t\t%u MHz \n", (unsigned int)clockFreq);
      printf("localMemSize: \t\t%lu bytes \n", (unsigned long)localMemSize);
      printf("constant buffer size: \t%lu bytes \n",
             (unsigned long)constantBufferSize);
      printf("globalCacheSize: \t%lu bytes\n", (unsigned long)globalCacheSize);
      printf("globalMemSize: \t\t%lu bytes\n", (unsigned long)globalMemSize);
      printf("memory allocation size:\t%ld bytes\n",
             (unsigned long)memAllocSize);
      printf("max work group size:\t%d workers \n",
             (unsigned int)workGroupSize);
      printf("max work item dimensions:\t%d \n",
             (unsigned int)workItemDimensions);
      for (dimension_indexFinger = 0;
           dimension_indexFinger < workItemDimensions;
           ++dimension_indexFinger) {
        printf("dimension %X max work item size %lu workers\n",
               (unsigned int)dimension_indexFinger,
               (unsigned long)workItemSizes[1]);
      }
    }
  }
}

static void found_and_switch(const size_t input_text_long,
                             const char *input_text, const char *found_text,
                             const char *switch_text,
                             const size_t produce_length, char *produce) {
  assert(input_text_long <= produce_length);
  assert(input_text != NULL);
  assert(found_text != NULL);
  assert(switch_text != NULL);
  const size_t found_text_long = strlen(found_text);
  const size_t switch_text_long = strlen(switch_text);
  size_t input_indexFinger = 0;
  size_t produce_indexFinger = 0;
  size_t found_indexFinger = 0;
  uint8_t found = (0 == 1);
  for (; input_indexFinger < input_text_long; ++input_indexFinger) {
    if (input_text[input_indexFinger] == found_text[0]) {
      for (found_indexFinger = 1; found_indexFinger < found_text_long;
           ++found_indexFinger) {
        if (input_text[input_indexFinger + found_indexFinger] !=
            found_text[found_indexFinger]) {
          break;
        } else if (found_indexFinger == found_text_long - 1) {
          found = (1 == 1);
        }
      }
      if (found) {
        input_indexFinger += found_text_long;
        for (found_indexFinger = 0; found_indexFinger < switch_text_long;
             ++found_indexFinger) {
          produce[produce_indexFinger] = switch_text[found_indexFinger];
          ++produce_indexFinger;
        }
      }
    } else {
      produce[produce_indexFinger] = input_text[input_indexFinger];
      ++produce_indexFinger;
    }
  }
}

int seed_program_probe(const cl_device_id device_id, const cl_context context,
                       char *filename, cl_program *program /*,
                            cl_kernel *kernel*/) {
  /* Load the source code containing the kernel*/
  cl_int return_number;
  FILE *fp;
  char *source_text;
  size_t source_size;
  // char news_pad[0x100];
  //// if the file extension is not .cl return error
  ///* Execute regular expression */
  // regex_t regex;
  // return_number = regexec(&regex, filename, 0, NULL, 0);
  // if (!return_number) {
  //} else if (return_number == REG_NOMATCH) {
  //  fprintf(stderr, "%s, a .cl termination, absence, admonition\n", filename);
  //  exit(1);
  //} else {
  //  regerror(return_number, &regex, news_pad, sizeof(news_pad));
  //  fprintf(stderr, "Regex match failed: %s\n", news_pad);
  //  exit(1);
  //}

  ///* Free memory allocated to the pattern buffer by regcomp() */
  // regfree(&regex);

  // open the file
  fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Failed to open file %s %s:%d.\n", filename, __FILE__,
            __LINE__);
    return return_number;
  }
  source_text = (char *)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_text, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);
  /* create program */

  *program =
      clCreateProgramWithSource(context, 1, (const char **)&source_text,
                                (const size_t *)&source_size, &return_number);
  free(source_text);
  if (!success_verification(return_number)) {
    fprintf(stderr, "Failed to create OpenCL program. %s:%d\n", __FILE__,
            __LINE__);
    return return_number;
  }
  // if no lines start with either kernel or _kernel return error
  /* Build Kernel Program */
  return_number = clBuildProgram(*program, 1, &device_id, NULL, NULL, NULL);
  if (!success_verification(return_number)) {
    // return any error messages
    char compile_newspaper[INFO_LENGTH];
    char compile_newspaper_produce[INFO_LENGTH];
    char filename_switch[MAX_FILENAME_LONG];
    memset(compile_newspaper, 0, INFO_LENGTH);
    size_t compile_newspaper_long = 0;
    size_t cl_build_status = 0;
    return_number =
        clGetProgramBuildInfo(*program, device_id, CL_PROGRAM_BUILD_STATUS, 1,
                              &cl_build_status, &compile_newspaper_long);
    fprintf(stderr, "CL_BUILD_STATUS 0x%X, 0x%X\n",
            (unsigned int)compile_newspaper_long,
            (unsigned int)cl_build_status);
    return_number = clGetProgramBuildInfo(
        *program, device_id, CL_PROGRAM_BUILD_LOG, INFO_LENGTH,
        compile_newspaper, &compile_newspaper_long);
    sprintf(filename_switch, "%s:", filename);
    found_and_switch(compile_newspaper_long, compile_newspaper, "<source>",
                     filename_switch, INFO_LENGTH, compile_newspaper_produce);
    fprintf(stderr, "compile_newspaper 0x%X\n",
            (unsigned int)compile_newspaper_long);
    fprintf(stderr, "%s\n", compile_newspaper_produce);
    fprintf(stderr, "Failed to build OpenCL program. %s:%d\n", __FILE__,
            __LINE__);
    return return_number;
  }
  // const char * seed_name = "hello";
  // find all lines starting with kernel or _kernel
  //  and get their kernel names likely via regexp
  // for each kernel name attempt to compile it
  //*kernel = clCreateKernel(*program, seed_name, &return_number);
  // if (!success_verification(return_number)) {
  //  // cleanUpOpenCL(context, command_waiting_line, program, kernel,
  //  // memoryObjects,
  //  //              numberOfMemoryObjects);
  //  fprintf(stderr, "Failed to create OpenCL kernel. %s:%d\n", __FILE__,
  //          __LINE__);
  //  exit(1);
  //}
  return 0;
}
int seed_program_establish(const cl_device_id device_id,
                           const cl_context context, char *filename,
                           char *seed_name, cl_program *program,
                           cl_kernel *kernel) {
  /* Load the source code containing the kernel*/
  cl_int return_number;
  FILE *fp;
  char *source_text;
  size_t source_size;
  //  // if the file extension is not .cl return error
  //  /* Execute regular expression */
  //  char news_pad[0x100];
  //  regex_t regex;
  //  return_number = regexec(&regex, filename, 0, NULL, 0);
  //  if (!return_number) {
  //  } else if (return_number == REG_NOMATCH) {
  //    fprintf(stderr, "%s, a .cl termination, absence, admonition\n",
  //    filename);
  //    exit(1);
  //  } else {
  //    regerror(return_number, &regex, news_pad, sizeof(news_pad));
  //    fprintf(stderr, "Regex match failed: %s\n", news_pad);
  //    exit(1);
  //  }
  //
  //  /* Free memory allocated to the pattern buffer by regcomp() */
  //  regfree(&regex);
  //
  // open the file
  fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Failed to open file %s %s:%d.\n", filename, __FILE__,
            __LINE__);
    return 1;
  }
  source_text = (char *)malloc(MAX_SOURCE_SIZE);
  source_size = fread(source_text, 1, MAX_SOURCE_SIZE, fp);
  fclose(fp);
  /* create program */

  *program =
      clCreateProgramWithSource(context, 1, (const char **)&source_text,
                                (const size_t *)&source_size, &return_number);
  free(source_text);
  if (!success_verification(return_number)) {
    fprintf(stderr, "Failed to create OpenCL program. %s:%d\n", __FILE__,
            __LINE__);
    return return_number;
  }
  /* Build Kernel Program */
  return_number = clBuildProgram(*program, 1, &device_id, NULL, NULL, NULL);
  if (!success_verification(return_number)) {
    char compile_newspaper[INFO_LENGTH];
    memset(compile_newspaper, 0, INFO_LENGTH);
    size_t compile_newspaper_long = 0;
    size_t cl_build_status = 0;
    return_number =
        clGetProgramBuildInfo(*program, device_id, CL_PROGRAM_BUILD_STATUS, 1,
                              &cl_build_status, &compile_newspaper_long);
    fprintf(stderr, "CL_BUILD_STATUS 0x%X, 0x%X\n",
            (unsigned int)compile_newspaper_long,
            (unsigned int)cl_build_status);
    return_number = clGetProgramBuildInfo(
        *program, device_id, CL_PROGRAM_BUILD_LOG, INFO_LENGTH,
        compile_newspaper, &compile_newspaper_long);
    fprintf(stderr, "compile_newspaper 0x%X, %s\n",
            (unsigned int)compile_newspaper_long, compile_newspaper);
    fprintf(stderr, "Failed to build OpenCL program. %s:%d\n", __FILE__,
            __LINE__);
    return return_number;
  }
  *kernel = clCreateKernel(*program, seed_name, &return_number);
  if (!success_verification(return_number)) {
    // cleanUpOpenCL(context, command_waiting_line, program, kernel,
    // memoryObjects,
    //              numberOfMemoryObjects);
    fprintf(stderr, "Failed to create OpenCL kernel. %s:%d\n", __FILE__,
            __LINE__);
    return return_number;
  }
  return 0;
}

//#define TRUE  1
// int seed_input_giving(const cl_kernel seed, const uint8_t input_series_long,
// const void ** input_series) {
//  uint8_t input_indexFinger = 0;
//  int success = TRUE;
//  for(; input_indexFinger < input_series_long; ++input_indexFinger) {
//    success &= success_verification(clSetKernelArg(seed, input_indexFinger,
//        input_series[input_indexFinger][0],
//        input_series[input_indexFinger][1]));
//  }
//  return 0;
//}

void sclGetHardwareByType(const cl_device_type device_type, const int iDevice,
                          int *found, sclHard *Hardware) {
  cl_uint i;
  sclHard hardware;
  hardware.platform = NULL;
  cl_int err;
  cl_uint nPlatforms, nDevices = 0;
  cl_char vendor_name[1024];
  cl_char device_name[1024];
  char platformName[256];

  *found = 0;
  cl_platform_id platforms[NB_MAX_PLATFORMS];
  cl_device_id devices[NB_MAX_PLATFORMS][NB_MAX_DEVICES_PER_PLATFORM];

  /*Get platform info ###################################################### */
  err = clGetPlatformIDs(NB_MAX_PLATFORMS, platforms, &nPlatforms);
  // fprintf( stdout, "\n Number of platforms found: %d \n",nPlatforms);
  /* ###################################################### */

  if (nPlatforms == 0) {
    fprintf(stderr, "\nNo OpenCL platforms found.\n");
    *found = 0;
  } else {
    for (i = 0; i < nPlatforms; ++i) {
      if (hardware.platform != NULL) {
        i = nPlatforms;
        break;
      }
      err =
          clGetDeviceIDs(platforms[i], device_type, NB_MAX_DEVICES_PER_PLATFORM,
                         &devices[i][0], &nDevices);
      if (err != CL_SUCCESS) {
        fprintf(stderr, "\nError clGetDeviceIDs");
        fprintf(stderr, " %s:%d \n", __FILE__, __LINE__);
        success_verification(err);
        break;
        exit(-1);
      }

      if (nDevices > 0) {
        // device_type found, return it
        hardware.platform = platforms[i];
        hardware.device = devices[i][(iDevice < (int)nDevices ? iDevice : 0)];
        hardware.context =
            clCreateContext(0, 1, &hardware.device, NULL, NULL, &err);
        if (err != CL_SUCCESS) {
          fprintf(stderr, "\nError 3");
          success_verification(err);
          fprintf(stderr, " %s:%d \n", __FILE__, __LINE__);
          exit(-1);
        };
#ifdef CL_VERSION_2_0
        float version_float = diagnoseOpenCLnumber(hardware.platform);
        if (version_float >= 2.0f) {
          // const cl_queue_properties properties[] =
          // {CL_QUEUE_PROFILING_ENABLE};
          hardware.queue = clCreateCommandQueueWithProperties(
              hardware.context, hardware.device, NULL, &err);
          if (err != CL_SUCCESS) {
            fprintf(stderr, "\nError 3.1");
            fprintf(stderr, " %s:%d \n", __FILE__, __LINE__);
            success_verification(err);
            exit(-1);
          };
        } else {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
          hardware.queue =
              clCreateCommandQueue(hardware.context, hardware.device,
                                   CL_QUEUE_PROFILING_ENABLE, &err);
#ifdef CL_VERSION_2_0
#pragma GCC diagnostic pop
        }
#endif
        if (err != CL_SUCCESS) {
          fprintf(stderr, "\nError 3.1");
          fprintf(stderr, " %s:%d \n", __FILE__, __LINE__);
          success_verification(err);
          exit(-1);
        };
        /* deviceType 0 = GPU | deviceType 1 = CPU | deviceType 2 = Accelerator
         * | deviceType 3 = other */
        hardware.deviceType =
            (device_type == CL_DEVICE_TYPE_GPU
                 ? 0
                 : (device_type == CL_DEVICE_TYPE_CPU
                        ? 1
                        : (device_type == CL_DEVICE_TYPE_ACCELERATOR ? 2 : 3)));

        // some info
        platformName[0] = '\0';
        vendor_name[0] = '\0';
        device_name[0] = '\0';

        err = clGetPlatformInfo(hardware.platform, CL_PLATFORM_VENDOR,
                                (size_t)256, (void *)platformName, NULL);
        err |= clGetDeviceInfo(hardware.device, CL_DEVICE_VENDOR,
                               sizeof(vendor_name), vendor_name, NULL);
        err |= clGetDeviceInfo(hardware.device, CL_DEVICE_NAME,
                               sizeof(device_name), device_name, NULL);
        if (err != CL_SUCCESS) {
          fprintf(stderr, "\nError getting platform + vendor + device name");
          success_verification(err);
        }
        fprintf(stdout, "\nUsing platform: %s - Vendor: %s\nDevice name: %s\n",
                platformName, vendor_name, device_name);

        *found = 1;
      }
    }
  }

  *Hardware = hardware;
}

void sclGetHardware(const int iDevice, sclHard *CPUHardware) {
  int found = 0;
  sclGetHardwareByType(CL_DEVICE_TYPE_ALL, iDevice, &found, CPUHardware);
}
