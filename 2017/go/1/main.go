package main

import (
    "fmt"
    "os"
    "io/ioutil"
)

func check(e error) {
    if e != nil {
        panic(e)
    }
}

func FirstStar(input string) int {
    sum := 0
    for i := 0; i < len(input); i++ {
        if input[i] == input[(i + 1) % len(input)] {
            sum += int(input[i] - '0')
        }
    }
    return sum
}

func SecondStar(input string) int {
    sum := 0
    offset := len(input) / 2
    for i := 0; i < len(input); i++ {
        if input[i] == input[(i + offset) % len(input)] {
            sum += int(input[i] - '0')
        }
    }
    return sum
}

func main() {
    inputBytes, err := ioutil.ReadFile("input.txt")
    check(err)

    input := string(inputBytes)

    if os.Args[1] == "one" {
        fmt.Println(FirstStar(input))
    }

    if os.Args[1] == "two" {
        fmt.Println(SecondStar(input))
    }
}
