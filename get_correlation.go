package main

import (
	"fmt"
	"os/exec"
	"sort"
	"strconv"
)

func get_correlation(x, amount_LS int,arr *[]float64, done chan int) {
	cmd := exec.Command("/home/nkashk/GolandProjects/test_LS/calculate_correlation.py", strconv.Itoa(x),strconv.Itoa(amount_LS))
	corr_bytes,err := cmd.Output()
	if err != nil {
		fmt.Println(err.Error())
		return
	}
	//fmt.Println(string(corr_bytes))
	corr_str := string(corr_bytes)
	corr_str = corr_str[:len(corr_str)-1]
	if corr, err := strconv.ParseFloat(string(corr_str), 64); err == nil {
		(*arr)[x]=corr
	}
	done <- 0
}

func main(){
	var
	(
		n = 64
		amount_LS=100
		amount_threads=8
	)
	var spearmanr=make([]float64,n)
	fmt.Println("Hello World")
	x := 0
	for x<n {
		var rest int
		if ((n-x)>amount_threads){
			rest=amount_threads
		} else {
			rest=n-x
		}
		j := x
		var chans [] chan int
		for j-x < rest {
			chans=append(chans,make(chan int) )
			go get_correlation(j, amount_LS, &spearmanr,chans[j-x])
			j = j + 1
		}
		for l:=range chans{
			<-chans[l]
		}
		x=x+rest
	}
	sort.Float64s(spearmanr)
	fmt.Println("median correlation : ")
	fmt.Println(spearmanr[n/2])
	fmt.Println("minimum: ")
	fmt.Println(spearmanr[0])
	fmt.Println("maximum:")
	fmt.Println(spearmanr[n-1])
}
