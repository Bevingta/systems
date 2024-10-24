APP=stats_mod
PA=pa4
INPUT=input_${PA}.txt
EXPECTED=expected_${PA}.txt
OUTPUT=output.txt

rm -f ${APP}
make ${APP} > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Build failure."
    exit 1
fi
./${APP} < ${INPUT} > /dev/null
if [[ $? -ne 0 ]]
then
    echo "${PA} terminated abnormally."
    exit 1
else
    ./${APP} < ${INPUT} > ${OUTPUT}
fi
diff ${OUTPUT} ${EXPECTED} > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Actual results do not match expected results."
else
    echo "PASSED"
fi
rm -f ${OUTPUT}


