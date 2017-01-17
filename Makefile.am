#SPEL virtual machine
#Copyright (C) 2016  Logan Streondj
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU Affero General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Affero General Public License for more details.
#
#You should have received a copy of the GNU Affero General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#contact: streondj at gmail dot com
#
SUBDIRS = .

noinst_LIBRARIES =  library/library_seed.a \
                    library/library_genericOpenCL.a \
                    library/library_dictionary.a \
                    # library/library_simpleCL.a \
                    # library/library_programmer.a  \
                    # library/library_random.a 


library_library_seed_a_SOURCES = program/seed.c program/seed.h
library_library_seed_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)#\
 #        -Wstack-usage=256 # data bytes per warp

library_library_genericOpenCL_a_SOURCES = program/genericOpenCL.c program/genericOpenCL.h
library_library_genericOpenCL_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)
      #   -Wstack-usage=256 # data bytes per warp

#library_library_simpleCL_a_SOURCES = program/simple-opencl/simpleCL.c program/simple-opencl/simpleCL.h
#library_library_simpleCL_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)
#      #   -Wstack-usage=256 # data bytes per warp

library_library_dictionary_a_SOURCES = program/dictionary.c \
                program/dictionary.h
library_library_dictionary_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)#\
     #    -Wstack-usage=32 # data bytes per warp

#library_library_programmer_a_SOURCES = program/machine_programmer/programmer.c
#library_library_programmer_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)\
#         -Wstack-usage=256 # data bytes per warp

#library_library_random_a_SOURCES = program/machine_programmer/random.c
#library_library_random_a_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS)\
#         -Wstack-usage=256 # data bytes per warp

# vm 
bin_PROGRAMS = binary/encoding binary/clprobe binary/spal binary/spal_dictionary
binary_spal_SOURCES = program/spal_compile.c 
binary_spal_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS) # \
     #    -Wstack-usage=32768  #L1 Cache
binary_spal_LDADD =  library/library_seed.a \
          library/library_genericOpenCL.a library/library_dictionary.a 
#          library/library_simpleCL.a

#binary_programmer_SOURCES = program/opencl_programmer.c 
#binary_programmer_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS) \
#         -Wstack-usage=32768  #L1 Cache
#binary_programmer_LDADD = library/library_seed.a \
#          library/library_genericOpenCL.a library/library_dictionary.a\
#          library/library_simpleCL.a
# library/library_programmer.a library/library_random.a 

binary_encoding_SOURCES = program/encoding.c
binary_encoding_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS) # \
  #       -Wstack-usage=32768  #L1 Cache
binary_encoding_LDADD = library/library_seed.a \
          library/library_genericOpenCL.a library/library_dictionary.a
#          library/library_simpleCL.a

binary_clprobe_SOURCES = program/clprobe.c
binary_clprobe_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS) # \
       #  -Wstack-usage=32768  #L1 Cache
binary_clprobe_LDADD = library/library_genericOpenCL.a 


binary_spal_dictionary_SOURCES = program/spal_dictionary.c
binary_spal_dictionary_CFLAGS = -I$(top_srcdir) $(MY_CFLAGS) # \
       #  -Wstack-usage=32768  #L1 Cache
binary_spal_dictionary_LDADD = library/library_genericOpenCL.a \
  library/library_seed.a  library/library_dictionary.a 

# TESTS
#TESTS = check_vm
#check_PROGRAMS = check_vm
#check_vm_SOURCES = check/check_ACC_vm.c \
#    $(top_builddir)/program/seed/seed.h
#check_vm_CFLAGS = @CHECK_CFLAGS@
#check_vm_LDADD = $(top_builddir)/library/library_seed.a @CHECK_LIBS@
