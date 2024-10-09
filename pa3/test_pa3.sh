PA=pa3

echo "Compiling ..."
make clean && make

echo "Running ..."
./fp_analyzer_f special > output_f.txt
./fp_analyzer_f < input_${PA}_f.txt >> output_f.txt
./fp_analyzer_d special > output_d.txt
./fp_analyzer_d < input_${PA}_d.txt >> output_d.txt

echo "FLOAT -- Diffing ..."
DIFF=$(diff -b expected_${PA}_f.txt output_f.txt)
if [ "$DIFF" != "" ]
then
    echo "\nXXXXXXXX UNEXPECTED OUTPUT: XXXXXXXX\n"
    echo "$DIFF\n"
else
    echo "\n======== CORRECT ========\n"
fi

echo "DOUBLE -- Diffing ..."
DIFF=$(diff -b expected_${PA}_d.txt output_d.txt)
if [ "$DIFF" != "" ]
then
    echo "\nXXXXXXXX UNEXPECTED OUTPUT: XXXXXXXX\n"
    echo "$DIFF\n"
else
    echo "\n======== CORRECT ========\n"
fi

rm -f output*.txt
make clean

