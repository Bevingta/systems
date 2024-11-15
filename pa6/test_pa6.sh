PA1=encode
PA2=decode
INPUT=input.txt
CIPHER=cipher.bin
EXPECTED=expected_pa6.bin
OUTPUT=output.txt

function error_message_check {
    EXPECTED_ERROR_MSG="Usage: ./$1 <input-$2text-file> <output-$3text-file>"
    TMP_FILE=error_msg.txt
    ./$1 2>${TMP_FILE}
    ERROR_MSG=$(<${TMP_FILE})
    if [[ "${ERROR_MSG}" != "${EXPECTED_ERROR_MSG}" ]]
    then
        echo "$1: incorrect error handling."
        exit 1
    fi
    rm -f ${TMP_FILE}
}

echo "Building ..."
make clean > /dev/null
make > /dev/null
if [[ $? -ne 0 ]]
then
    echo "Build failure."
    exit 1
fi

echo "Checking error handling for ${PA1} ..."
error_message_check "${PA1}" "plain" "cipher"

echo "Running ${PA1} ..."
./${PA1} ${INPUT} ${CIPHER}
if [[ $? -ne 0 ]]
then
    echo "${PA1} terminated abnormally."
    exit 1
fi
cmp ${CIPHER} ${EXPECTED} > /dev/null
if [[ $? -ne 0 ]]
then
    echo "${PA1}'s output does not match the expected ciphertext."
    exit 1
fi
echo "Correct."

echo "Checking error handling for ${PA2} ..."
error_message_check "${PA2}" "cipher" "plain"

echo "Running ${PA2} ..."
./${PA2} ${CIPHER} ${OUTPUT}
if [[ $? -ne 0 ]]
then
    echo "${PA2} terminated abnormally."
    exit 1
fi
diff ${OUTPUT} ${INPUT} > /dev/null
if [[ $? -ne 0 ]]
then
    echo "${PA2}'s output does not match the original input."
    exit 1
fi
echo "CORRECT!"
rm -f ${CIPHER} ${OUTPUT} > /dev/null
make clean > /dev/null

