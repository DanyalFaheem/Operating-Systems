#!/bin/bash
pattern=$1
rows=$2
check=0 
if [ "$pattern" != "full" ] && [ "$pattern" != "left" ] && [ "$pattern" != "right" ] && [ "$pattern" != "Full" ] && [ "$pattern" != "Left" ] && [ "$pattern" != "Right" ]; then
    echo "Invalid input for pattern design. Please only choose, full, left, right."
    while [ $check -eq 0 ]
    do
        echo Please enter choice of pattern design:
        read pattern
        if [ "$pattern" != "full" ] && [ "$pattern" != "left" ] && [ "$pattern" != "right" ] && [ "$pattern" != "Full" ] && [ "$pattern" != "Left" ] && [ "$pattern" != "Right" ]; then
            echo "Invalid input for pattern design. Please only choose, full, left, right."
        else 
            check=1
        fi    
    done    
fi
check=0
if [ $rows -lt 1 ]; then
   echo "Invalid input for rows. Please only enter positive values."
   while [ $check -eq 0 ]
    do
        echo Please enter number of rows:
        read rows
        if [ $rows -lt 1 ]; then
            echo "Invalid input for rows. Please only enter positive values."
        else    
            check=1
        fi
    done            
fi
#if [ "$pattern" = "left" ] || [ "$pattern" = "Left" ]; then
case $pattern in
left|Left)
    i=$rows
    stars=1
    while [ $i -gt 0 ]
    do
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        stars=$(( stars+1 ))
        i=$(( i-1 ))
    done    
    i=$(($rows-1))
    stars=$(( stars-2 ))
     while [ $i -gt 0 ]
    do
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        stars=$(( stars-1 ))
        i=$(( i-1 ))
    done    
;;
#fi
#if [ "$pattern" = "right" ] || [ "$pattern" = "Right" ]; then
right|Right)
    i=$rows
    stars=1
    spaces=$(($rows-1))
    while [ $i -gt 0 ]
    do
        k=$spaces
        while [ $k -gt 0 ]
        do
            echo -n " "
            k=$(( k-1 ))
        done
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        spaces=$((spaces-1))
        stars=$(( stars+1 ))
        i=$(( i-1 ))
    done    
    i=$(($rows-1))
    stars=$(( stars-2 ))
    spaces=$((spaces+2))
     while [ $i -gt 0 ]
    do
        k=$spaces
        while [ $k -gt 0 ]
        do
            echo -n " "
            k=$(( k-1 ))
        done
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        spaces=$((spaces+1))
        stars=$(( stars-1 ))
        i=$(( i-1 ))
    done
    ;;    
#fi
#if [ "$pattern" = "full" ] || [ "$pattern" = "Full" ]; then
full|Full) 
    i=$rows
    stars=1
    spaces=$(($rows-1))
    while [ $i -gt 0 ]
    do
        k=$spaces
        while [ $k -gt 0 ]
        do
            echo -n " "
            k=$(( k-1 ))
        done
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        spaces=$((spaces-1))
        stars=$(( stars+2 ))
        i=$(( i-1 ))
    done    
    i=$(($rows-1))
    stars=$(( stars-4 ))
    spaces=$((spaces+2))
     while [ $i -gt 0 ]
    do
        k=$spaces
        while [ $k -gt 0 ]
        do
            echo -n " "
            k=$(( k-1 ))
        done
        j=$stars
        while [ $j -gt 0 ]
        do
            echo -n "*"
            j=$(( j-1 ))
        done
        echo
        spaces=$((spaces+1))
        stars=$(( stars-2 ))
        i=$(( i-1 ))
    done    
;;#fi
*)
echo "Invalid input for pattern design. Please only choose, full, left, right."
    while [ $check -eq 0 ]
    do
        echo Please enter choice of pattern design:
        read pattern
        if [ "$pattern" != "full" ] && [ "$pattern" != "left" ] && [ "$pattern" != "right" ] && [ "$pattern" != "Full" ] && [ "$pattern" != "Left" ] && [ "$pattern" != "Right" ]; then
            echo "Invalid input for pattern design. Please only choose, full, left, right."
        else 
            check=1
        fi    
    done    
    ;;
esac
exit