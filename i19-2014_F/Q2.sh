#!/bin/bash
invalid_input () {
    check=0
    file=$1
    for filename in *
    do
        if [ "$file" = "$filename" ]; then
            check=1
            break;
        fi    
        done
    while [ $check -eq 0 ]
        do
            echo Please enter existing file:
            read file
            for filename in *
            do
            if [ "$file" = "$filename" ]; then
            check=1
            break;
            fi    
            if [ $check -ne 1 ]; then
                echo "File does not exist. Only enter existing filename"
            else 
                check=1
            fi    
        done  
    done    
}
echo -e "Choose one of the four options \n1) View permissions of a file\n2) Search string in File\n3) Copy contents of directory to new file \n4) Change modified date and time of file\nexit) Exit the program" 
read choice
case $choice in
1)
    echo "Option 1 selected at $(date)"
    echo "Enter filename: "
    read file
    invalid_input $file
    
    echo -n "Permissions for file $file are: " 
    permissions=$(ls -l $file)
    permissions=${permissions:0:9}
    echo $permissions
    i=1
    while [ $i -lt 10 ]; 
    do
        j=$(($i-1))
        letter=${permissions:$j:1}
        if [ "$letter" = 'r' ] || [ "$letter" = 'w' ] || [ "$letter" = 'x' ]; then
            if [ $i -lt 3 ]; then
            case $(($j%3)) in
            0) chmod u-x $file ;;
            1) chmod u-r $file ;;
            2) chmod u-w $file ;;
            esac
            elif [ $i -lt 6 ] && [ $i -gt 2 ]; then
        echo "i: $j"
            case $(($j%3)) in
            0) chmod g-x $file ;;
            1) chmod g-r $file ;;
            2) chmod g-w $file ;;
            esac
            else 
             case $(($j%3)) in
            0) chmod o-x $file ;;
            1) chmod o-r $file ;;
            2) chmod o-w $file ;;
            esac
            fi
        else 
        if [ $i -lt 3 ]; then
            case $(($j%3)) in
            0) chmod u+x $file ;;
            1) chmod u+r $file ;;
            2) chmod u+w $file ;;
            esac
            elif [ $i -lt 6 ] && [ $i -gt 2 ]; then
        echo "i+: $j"
            case $(($j%3)) in
            0) chmod g+x $file ;;
            1) chmod g+r $file ;;
            2) chmod g+w $file ;;
            esac
            else 
             case $(($j%3)) in
            0) chmod o+x $file ;;
            1) chmod o+r $file ;;
            2) chmod o+w $file ;;
            esac  
        fi    
        fi
        i=$(($i+1))
    done
    echo -n "Updated permissions for file $file are: "
    permissions=$(ls -l $file)
    permissions=${permissions:0:9}
    echo $permissions 
;;
2)
    echo "Option 2 selected at $(date)"
    echo "Enter filename: "
    read file
    invalid_input $file
    echo "Enter string: "
    read str
    echo -e "Output is in form\nLine number: line it appears in\n"
    grep -n $str $file
;;
3)
    echo "Option 3 selected at $(date)"
    echo "Enter number of lines: "
    read lines
    while [ $lines -lt 1 ]; 
    do
        echo "Please only enter positive values."
        echo "Enter number of lines: "
        read lines
    done
    touch dummy.txt
    i=0
    for filename in *
    do
       case $(($i%2)) in
        0)
            head -n $lines "$filename" >> dummy.txt
        ;;
        1)
            tail -n $lines "$filename" >> dummy.txt
        ;;
        esac
        i=$((i+1))
    done
    echo "Press enter as command requires enter key to move forward"
;;
4)
    echo "Option 4 selected at $(date)"
    echo "Enter filename: "
    read file
    invalid_input $file

    modifieddate=$(date -r $file)
    modifieddate=$(echo $modifieddate | cut -d' ' -f 3)
    currentdate=$(date)
    currentdate=$(echo $currentdate | cut -d' ' -f 3)
    if [ $currentdate -gt $modifieddate ]; then
        touch $file
        echo "File $file modified date and time updated to current"
    fi
;;
exit|Exit|EXIT)
    echo "Exiting program at" $(date)
    exit
;;
*)
    echo "Please only choose the options provided"
    exit
;;
esac
echo "Press enter once again as command requires enter press."
./Q2.sh >> logfile.txt
exit