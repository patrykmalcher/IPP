# Minimalne zabezpieczenie przed
# niepoprawnymi danymi przekazanymi
# do skryptu testującego.
if [[ $# != 2 ]]
then 
    echo "UŻYJ $0 <prog> <dir>"
    exit 1
fi 

prog=$1
dir=$2

for i in $dir/*.in 
do
    echo -e "\033[0;37mTest $i: "

    valgrind --error-exitcode=123 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all \
    --log-file="${i%.in}valgrind.txt" ./$prog < $i > ${i%.in}prog.out 2> ${i%.in}prog.err

    exitcode=$? 

    if diff ${i%.in}prog.out ${i%.in}.out > /dev/null && diff ${i%.in}prog.err ${i%.in}.err > /dev/null
    then 
        echo -n -e "\033[1;32mwynik poprawny "
    else 
        echo -n -e "\033[1;31mwynik niepoprawny "
    fi

    if [ $exitcode = 123 ]
    then
        echo -e "\033[1;37mi \033[1;31mWYCIEK PAMIĘCI!"
    else 
        echo -e "\033[1;37mi \033[1;32mbrak wycieku pamięci."
    fi

    rm ${i%.in}prog.out ${i%.in}prog.err ${i%.in}valgrind.txt
done