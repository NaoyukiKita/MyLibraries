package main
import (
    "fmt"
    "os"
    "bufio"
    "strconv"
    "sort"
)   

// scans numbers given in a row.
func ScanArr(N int, arr []int) {
	var sc *bufio.Scanner = bufio.NewScanner(os.Stdin)
	sc.Split(bufio.ScanWords)
	
	var n, ele int
	for n = 0; n < N; n++ {
		sc.Scan()
		ele, _ = strconv.Atoi(sc.Text())
		arr[n] = ele
	}
}

// returns keys in ascending order, and corresponding values.
func MapSort(m map[int]int) ([]int, []int) {
    var keys[] int = make([]int, 0)
	for k := range m { keys = append(keys, k) }

	sort.Ints(keys)

    var values[] int = make([]int, 0)
	for _, k := range keys { values = append(values, m[k]) }
	
	return keys, values
}