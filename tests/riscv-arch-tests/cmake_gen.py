#!/usr/bin/env python3

import re
import yaml
import os


#cur_path = pathlib.Path(__file__).parent.resolve()
cur_path = os.path.dirname(os.path.abspath(__file__))

makefile_path = "/nfs/lab13/users/martian_16/work/spike_task/spike_testing_repo/Makefile.DUT-spike"
yaml_path = "/nfs/lab13/users/martian_16/work/spike_task/spike_testing_repo/tests/riscv-arch-tests/test_list.yaml" 
cmakefile_path = f"{cur_path}/CMakeLists.txt"

start_width = 20
total_width = 79


#compiler_path = "/work/tools/rvv-gcc/gcc14-linux/bin/riscv64-unknown-linux-gnu-c++"
compiler_path = "${LINUX_CXX_COMPILER}"
compiler_march_str = "-march=${COMPILER_MARCH} -mabi=lp64"
compiler_common_flags_str = "-static -mcmodel=medany -fvisibility=hidden -nostdlib -nostartfiles -g"


spike_gold_path = "/nfs/lab13/users/martian_16/work/spike_task/spike_gold_install/bin/spike"
spike_test_path = "${SPIKE_PATH}"
#spike_isa = "rv64imafdcv_Zicbom_Zicbop_Zicboz_Zicsr_Zifencei_Zihpm_Zmmul_Zfh_Zba_Zbb_Zbc_Zbs_Zk_Zvbb_Zvkg_Zvknha_Zvknhb_Zvl512b_Svnapot"
spike_isa = "${SPIKE_ISA}"
#spike --isa=rv64imafdcv_Zicbom_Zicbop_Zicboz_Zicsr_Zifencei_Zihpm_Zmm     ul_Zfh_Zba_Zbb_Zbc_Zbs_Zk_Zvbb_Zvkg_Zvknha_Zvknhb_Zvl512b_Svnapot +signature=/nfs/lab13/users/martian_16/work/spike_task/riscof_spike/riscof_work/rv64i_m/A/src/amoadd.d-01.S/dut/DUT-spike.signature +signature-granularity=8 my.elf


#makefile = open(makefile_path, 'r').readlines()
#
#targets = {}
#
#for line_num in range(len(makefile)):
#line = makefile[line_num].strip()
#pattern = r"^TARGET\d+"
#if re.search(pattern, line):
#	clean_line = line.replace(' :', '')
#	next_line = makefile[line_num + 1]
#		print(clean_line)
#		print(next_line.strip().split(';'))
#
#print(makefile)

def load_yaml(yaml_path):
    with open(yaml_path) as stream:
        try:
            yaml_data = yaml.safe_load(stream)
        except yaml.YAMLError as exc:
            print(exc)
    return yaml_data

def get_test_name(entry_name):
    return os.path.basename(entry_name).replace('.S', '')

def get_test_ext(entry_name):
    return entry_name.split('/')[1]

def write_test_header(fh, entry_name):
    test_name = get_test_name(entry_name)
    test_ext  = get_test_ext(entry_name)
    start_pattern = '=' * start_width
    stop_pattern  = '=' * (total_width - start_width - len(test_name) - len(test_ext) - 3)
    fh.write(f"#{start_pattern} {test_ext}/{test_name} {stop_pattern}\n")

def write_test_footer(fh, entry_name):
    pattern = '=' * total_width
    fh.write(f"#{pattern}\n\n")

def write_test_body(fh, yaml_data, entry_name):
    test_name = get_test_name(entry_name)
    test_ext  = get_test_ext(entry_name)

    macro_str = ""
    for macro in  yaml_data[entry_name]['macros']:
      m, v = macro.split('=')
      macro_str += f"-D{macro} "


    create_dir_cmd = "mkdir -p ${CMAKE_BINARY_DIR}/riscv-arch-tests/" + test_ext + "/" + test_name
    compile_cmd = f"{compiler_path} {compiler_march_str} {compiler_common_flags_str} " + \
                    '-T ${RISCV_ARCH_TESTS}/env/link.ld ' + \
                    '-I ${RISCV_ARCH_TESTS}/env/ ' + \
                    '${RISCV_ARCH_TESTS}/' + yaml_data[entry_name]['test_path'] + " " + \
                    '-o  ${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/test.elf " + \
                    f'{macro_str}'
    spike_gold_cmd = f"{spike_gold_path} --isa={spike_isa} +signature-granularity=8 +signature=" + \
                     '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/signature.gold " + \
                     '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/test.elf"
    spike_test_cmd = f"{spike_test_path} --isa={spike_isa} +signature-granularity=8 +signature=" + \
                     '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/signature.test " + \
                     '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/test.elf"
    diff_cmd = "diff " + \
                '${RISCV_ARCH_TESTS}/' + yaml_data[entry_name]['test_path'].replace('.S', ".gold") + " " + \
                '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/signature.test"
#    diff_cmd = "diff " + \
#                '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/signature.gold" + " " + \
#                '${CMAKE_BINARY_DIR}/riscv-arch-tests/' + test_ext + "/" + test_name + "/signature.test"

    test_str = f'''add_test(NAME    "{test_ext}/{test_name}"
         COMMAND "bash" "-c" "{create_dir_cmd};
                              {compile_cmd};
                              {spike_test_cmd};
                              {diff_cmd}"
         )'''
    fh.write(f"{test_str}\n")

def write_test_entry(fh, yaml_data, entry_name):
    write_test_header(fh=fh, entry_name=entry_name)

    print(cur_path + '/' + entry_name)
#    print(get_test_name(entry_name=entry_name))
#    print(yaml_data[entry_name])

    write_test_body(fh=fh, yaml_data=yaml_data, entry_name=entry_name)
    write_test_label(fh=fh, entry_name=entry_name)
    write_test_footer(fh=fh, entry_name=entry_name)

def write_test_label(fh, entry_name):
    test_name = get_test_name(entry_name)
    test_ext  = get_test_ext(entry_name)
    fh.write(f'set_tests_properties("{test_ext}/{test_name}" PROPERTIES LABELS "{test_ext}")\n')

def generate_cmake(yaml_data, cmakefile_path):

    cmake_file = open(cmakefile_path, 'w')

    for entry in yaml_data:
        write_test_entry(fh=cmake_file, yaml_data=yaml_data, entry_name=entry)

    #print(yaml_data.keys())

    cmake_file.close()


data = load_yaml(yaml_path=yaml_path)
generate_cmake(yaml_data=data, cmakefile_path=cmakefile_path)


