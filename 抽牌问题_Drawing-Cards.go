package main

import "fmt"
import "sort"

func main() {
	var n, m int
	fmt.Scanf("%d%d", &n, &m)

	cards := make(map[rune]int)
	for i := 0; i < n; i++ {
		var r rune
		fmt.Scanf("%c", &r)
		cards[r]++
	}

	//取出字典的所有键
	keys := make([]rune, 0, n)
	for k, _ := range cards {
		keys = append(keys, k)
	}

	//降序排序
	sort.Slice(keys, func(i, j int) bool {
		return cards[keys[i]] > cards[keys[j]]
	})

	sum, j, k := 0, 0, 0
	for {
		v := cards[keys[k]]
		remaining := m - j //还剩余几张卡可抽
		if remaining > v {
			//余量充足，全抽出来
			sum += v * v
			j += v
		} else {
			//余量不足，能抽尽抽
			sum += remaining * remaining
			j += remaining
			break
		}

		k++
	}

	fmt.Println(sum)
}