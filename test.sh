#!/bin/bash

ARG=$1
PS=./push_swap
CHECKER=./checker
OFFICIAL_CHECKER=./checker_Mac
tests=100

if [ "$ARG" != "" ]; then
  tests=$ARG
fi

test() {
  ko=0
  total=0
  min=9999999
  max=0
  total_result="OK"
  checker_ok="OK"
  for ((i = 0; i < $tests; i++)); do
    list=$(seq 1 $1 | sort -R | tr '\n' ' ')
    $PS $list > stdout
    count=$(< stdout wc -l)
    if [ $count -lt $min ]; then
      min=$count
    elif [ $count -gt $max ]; then
      max=$count
    fi
    total=$((total + $count))
    result=$(< stdout $CHECKER $list)
    official_result=$(< stdout $OFFICIAL_CHECKER $list)
    if [ "$official_result" != "$result" ]; then
      echo $list > "checker_$1_$ko.txt"
      echo "Checker is not ok!"
    fi
    if [ "$result" == "KO" ]; then
      echo $list > "$1_$ko.txt"
      total_result=$result
      ((ko++))
    fi
    echo $list --- $result \($count moves\)
  done
  echo push swap: $total_result checker: $checker_ok Test $1 - min $min, max $max, avg $(($total / $tests))
  rm stdout
}

test 3
test 5
test 50
test 100
test 500