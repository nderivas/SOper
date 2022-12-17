for i in {1..100}
do
    if [[ `expr $i % 2` == 0 ]]
    then
        echo "$i - nor"
    else
        echo "$i - err" 1>&2;
    fi
    sleep 1
done