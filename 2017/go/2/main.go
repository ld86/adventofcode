package main

import (
    "fmt"
    "os"
    "bufio"
    "strings"
    "strconv"
)

func check(e error) {
    if e != nil {
        panic(e)
    }
}

func MinMax (array []int) (int, int) {
    min := array[0]
    max := array[0]
    for _, e := range array {
        if min > e {
            min = e
        }
        if max < e {
            max = e
        }
    }
    return min, max
}

func FirstStar(file *os.File) int {
    scanner := bufio.NewScanner(file)
    sum := 0
	for scanner.Scan() {
        values := make([]int, 0)
        for _, e := range strings.Split(scanner.Text(), "\t") {
            value, err := strconv.Atoi(e)
            check(err)
            values = append(values, value)
        }
        min, max := MinMax(values)
        sum += max - min
	}
    return sum
}

func SecondStar(file *os.File) int {
    scanner := bufio.NewScanner(file)
    sum := 0
	for scanner.Scan() {
        values := make([]int, 0)
        for _, e := range strings.Split(scanner.Text(), "\t") {
            value, err := strconv.Atoi(e)
            check(err)
            values = append(values, value)
        }
        for i := range values {
            for j := range values {
                if i != j && values[i] % values[j] == 0 {
                    sum += values[i] / values[j]
                }
            }
        }
	}
    return sum
}

func main() {
    file, err := os.Open("input.txt")
    check(err)

    if os.Args[1] == "one" {
        fmt.Println(FirstStar(file))
    }

    if os.Args[1] == "two" {
        fmt.Println(SecondStar(file))
    }
}
