
# source /work/home/proj_common/rvv/env.sh

conda_path=/work/tools/miniconda3
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$(${conda_path}/bin/conda shell.bash hook 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "${conda_path}/etc/profile.d/conda.sh" ]; then
        . "${conda_path}/etc/profile.d/conda.sh"
    else
        export PATH="${conda_path}/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

conda activate sparta_cowork

# export PATH=/work/tools/llvm/bin:$PATH
# export PATH=/work/tools/gcc-10.3.0/bin:$PATH
# export LD_LIBRARY_PATH=/work/tools/gcc-10.3.0/lib64:$LD_LIBRARY_PATH
