//%\begin{document}
/*
\setVersion{0.1}
\begin{Name}{1}{clprobe}{Logan Streondj}{OpenCL Tools}{OpenCL Probe}
Demonstrates OpenCL platform device knowledge xor tries to compile a .cl file
based on input filename.
\end{Name}

\begin{comment}
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
\end{comment}
*/
//\begin{comment}
#define MAX_SOURCE_SIZE (0x100000)

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "genericOpenCL.h"

int main(int ingredient_long, char *ingredient_list[]) {
  //\end{comment}
  //\section{Synopsis}
  //\Prog{clprobe} \Arg{input filename}
  /* \section{Description}
   if there is no filename ingredient then \Prog{clprobe} demonstrates openCL
   which includes the platform and instrument knowledge.
  */
  //\begin{sourcecode}
  if (ingredient_long != 2) {
    fprintf(stderr,
            "no .cl filename ingredient so demonstrating openCL knowledge\n");
    getInfo();
    exit(0);
  }
  //\end{sourcecode}
  /*
  Otherwise /Prog{clprobe} accepts one ingredient, which is the input filename.
  */
  //\begin{sourcecode}
  char *filename = ingredient_list[1];
  //\end{sourcecode}
  /*
  It then sets up a minimal OpenCL environment,
  and attempts to compile it.
  */
  //\begin{sourcecode}
  cl_platform_id platform_id = NULL;
  cl_uint ret_num_platforms;
  cl_context context = 0;
  cl_program program = 0;
  cl_device_id device_id = 0;
  cl_uint ret_num_devices;
  cl_int return_number;

  return_number = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
  if (!success_verification(return_number)) {
    fprintf(stderr, "Failed to get platform id's. %s:%d\n", __FILE__, __LINE__);
    return 1;
  }
  return_number = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1,
                                 &device_id, &ret_num_devices);
  if (!success_verification(return_number)) {
    fprintf(stderr, "Failed to get OpenCL devices. %s:%d\n", __FILE__,
            __LINE__);
    return 1;
  }
  context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &return_number);
  if (!success_verification(return_number)) {
    fprintf(stderr, "Failed to create an OpenCL context. %s:%d\n", __FILE__,
            __LINE__);
    return 1;
  }
  seed_program_probe(device_id, context, filename, &program);
  //\end{sourcecode}
  //\begin{comment}
  // if binary option is set, then for each platform, output a kernel binary
  //  in the form kernel_name.vendor (lower case vendor)

  return 0;
}
//\end{comment}
/*
\section{Bugs}
Still need to add ability to load header files.
\section{Author}
Logan Streondj <streondj at gmail dot com>
\section{See Also}
generic.c \Cmd{libOpenCL}{7}
\section{License}
\doclicenseLongText
*/
//%\end{document}
