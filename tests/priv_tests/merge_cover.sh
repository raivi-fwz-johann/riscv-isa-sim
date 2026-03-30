log_file=$1

while read line; do
    line=$(echo "${line}" | grep "PASSED" | grep -v "TEST")
    [ -z "${line}" ] && continue

    # remove colour codes
    line=$(echo "${line}" | sed -r "s/\x1B\[([0-9]{1,3}(;[0-9]{1,2};?)?)?[mGK]//g")
    
    
    test=$(echo "${line}" | awk '{print $1;}')
    result=$(echo "${line}" | awk '{print $2;}')
    
    if [ ${result} = PASSED ]; then
        echo "privileged_${test} = pass"
    else
        echo "privileged_${test} = fail"
    fi

done <${log_file}
