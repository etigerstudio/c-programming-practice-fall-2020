<!-- Heap-backed -->

package main

import "fmt"
import "container/heap"

type seat struct {
	left int //左边空位数
	right int //右边空位数
	iheap [2]int //左堆和右堆下标
}

var seats []seat //总座位信息数组

type seatEntry struct {
	value int //单边空位数
	iarray int //数组下标
}

const (
	LEFT_HEAP = 0
	RIGHT_HEAP = 1
)

type seatHeap struct {
	entries []seatEntry //堆中的部分座位信息
	direction int //左堆还是右堆
}

func (h seatHeap) Len() int { return len(h.entries) }

func (h seatHeap) Less(i, j int) bool {
	return h.entries[i].value >= h.entries[j].value
}

func (h seatHeap) Swap(i, j int) {
	h.entries[i], h.entries[j] = h.entries[j], h.entries[i]
	//将新堆下标写回总座位信息数组
	seats[h.entries[i].iarray].iheap[h.direction] = i
	seats[h.entries[j].iarray].iheap[h.direction] = j
}

func (h* seatHeap) Pop() interface{} {
	ilast := len((*h).entries) - 1
	vlast := ((*h).entries)[ilast]
	(*h).entries = ((*h).entries)[:ilast]
	return vlast
}

func (h* seatHeap) Push(x interface{}) {
	l := len((*h).entries)
	entry := x.(seatEntry)
	seats[entry.iarray].iheap[(*h).direction] = l
	(*h).entries[l] = entry
}

func main() {
	var n, total, reduced int
	fmt.Scanf("%d", &n)

	//分配数组和堆的空间
	seats = make([]seat, n, n)
	lheap := seatHeap{make([]seatEntry, n, n), LEFT_HEAP}
	rheap := seatHeap{make([]seatEntry, n, n), RIGHT_HEAP}
	for i := 0; i < n; i++ {
		var left, right int
		fmt.Scanf("%d%d", &left, &right)
		seats[i] = seat{left, right, [2]int{i, i}}
		lheap.entries[i] = seatEntry{left, i}
		rheap.entries[i] = seatEntry{right, i}
		//记录尚未优化的总需求座位数
		total += 1 + left + right
	}

	//分别初始化左堆右堆
	heap.Init(&lheap)
	heap.Init(&rheap)

	for i := 0; i < n; i++ {
		//弹出左边空位最多和右边空位最多的两个座位
		lentry, rentry := heap.Pop(&lheap).(seatEntry), heap.Pop(&rheap).(seatEntry)

		//重合的部分即为省下座位数量
		if lentry.value >= rentry.value {
			reduced = rentry.value
		} else {
			reduced = lentry.value
		}
		//此次合并是单个座位本身围坐还是两个不同座位？
		//	合并单个座位无需调整
		//	合并两个不同座位需要生成新的座位写回数组和堆
		if lentry.iarray != rentry.iarray {
			ilheap := seats[rentry.iarray].iheap[LEFT_HEAP]
			irheap := seats[lentry.iarray].iheap[RIGHT_HEAP]
			lheap.entries[ilheap].iarray = lentry.iarray
			rheap.entries[irheap].iarray = lentry.iarray
			//生成的新座位
			s := seat{
				left:  seats[lentry.iarray].left,
				right: seats[rentry.iarray].right,
				iheap: [2]int{ilheap, irheap},
			}
			seats[lentry.iarray] = s
			//分别在左堆右堆中，对新生成的座位根据左右空位调整
			heap.Fix(&lheap, ilheap)
			heap.Fix(&rheap, irheap)
		}
		//将省下的座位减掉
		total -= reduced
	}

	fmt.Println(total)
}

<!-- Vanilla (Array-backed) -->

package main

import "fmt"

type seat struct {
	left int
	right int
}

func main() {
	var n, result, combined int
	fmt.Scanf("%d", &n)

	seats := make([]seat, 0, n)
	for i := 0; i < n; i++ {
		var left, right int
		fmt.Scanf("%d%d", &left, &right)
		seats = append(seats, seat{left, right})
		result += 1 + left + right
	}

	for len(seats) > 0 {
		vleft, vright, ileft, iright := maxIndex(seats)

		var s seat
		if vleft >= vright {
			combined = vright
		} else {
			combined = vleft
		}
		if ileft != iright {
			s = seat{seats[iright].left, seats[ileft].right}
			seats[ileft] = s
			seats[iright] = seats[len(seats) - 1]
			seats = seats[:len(seats) - 1]
		} else {
			seats[ileft] = seats[len(seats) - 1]
			seats = seats[:len(seats) - 1]
		}
		result -= combined
	}

	fmt.Println(result)
}

func maxIndex(seats []seat) (vleft, vright, ileft, iright int) {
	for i, s := range seats {
		if i == 0 || s.left > vleft {
			vleft = s.left
			ileft = i
		}
		if i == 0 || s.right > vright {
			vright = s.right
			iright = i
		}
	}
	return
}

func nullSeat() seat {
	return seat{-1, -1}
}