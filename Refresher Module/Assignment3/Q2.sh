#! /bin/bash

function sub()
{
    returnval=$(($1 - $2))
}
function add()
{
    returnval=$(($1 + $2))
}
function mul()
{
    returnval=$(($1 * $2))
}
function div()
{
    returnval=$(($1 / $2))
}
function exp()
{
    returnval=$(($1 ** $2))
}

args=("$@")
i=2
returnval=0
flag=0
if [ "$#" -lt 3 ]
    then echo "Arguments not provided correctly"
else
    while [ $i -lt $# ]
    do
        if [ ${args[0]} = "add" ]
            then    add ${args[i-1]} ${args[i]}
        elif [ ${args[0]} = "sub" ]
            then    sub ${args[i-1]} ${args[i]}
        elif [ ${args[0]} = "mul" ]
            then    mul ${args[i-1]} ${args[i]}
        elif [ ${args[0]} = "div" ]
            then    div ${args[i-1]} ${args[i]}
        elif [ ${args[0]} = "exp" ]
            then    exp ${args[i-1]} ${args[i]}
        else
            echo "Invalid Choice"
            flag=1
            break
        fi 
        args[i]=$returnval
        i=$((i+1))

    done


    if [ "$flag" -eq 0 -a "$#" -gt 1 ]
        then echo ${args[$(($#-1))]} 
    fi
fi
