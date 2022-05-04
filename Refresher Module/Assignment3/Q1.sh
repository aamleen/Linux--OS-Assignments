#! /bin/bash

IFS='/' read -r -a date <<< "$1"

months31=(1 3 5 7 8 10 12)
months30=(4 6 9 11)

if [ ${date[0]} -gt 0 ]
then
    if [[ " ${months31[*]} " =~ " ${date[1]} " ]]
        then if [ ${date[0]} -lt 32 ]
            then   cal ${date[1]} ${date[2]} 
            else
                echo "Invalid Date entered"
            fi
    elif [[ " ${months30[*]} " =~ " ${date[1]} " ]]
        then if [ ${date[0]} -lt 31 ]
            then   cal ${date[1]} ${date[2]} 
            else
                echo "Invalid Date entered"
            fi
    elif [ ${date[1]} -eq 2 ]
        then if [ $((${date[2]}%4)) -eq 0 -a ${date[0]} -lt 30  ]
            then cal ${date[1]} ${date[2]}
            elif [ $((${date[2]}%4)) -gt 0 -a ${date[0]} -lt 29 ]
            then cal ${date[1]} ${date[2]}
            else
                echo "Invalid Date entered!!"
            fi
    else
        echo "Invalid Date Entered!!"
    fi
else
    echo "Invalid Date Entered!!"
fi
