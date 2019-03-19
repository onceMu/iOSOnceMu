import UIKit

var str = "Hello, playground"

var ss = "This is first xxx"

let scrollView = UIScrollView.init()

print("xxxx %@",scrollView)

let number : Int = 10

let height : Float = 0.0

var this = "xxxxxx"

let yes = true

let no = false

let houseDay = 12;
var timeOfDay = ""

if houseDay < 6 {
    timeOfDay = "倾城"
}else if houseDay < 12 {
    timeOfDay = "早上"
}else if houseDay < 17 {
    timeOfDay = "中午"
}else if houseDay < 20 {
    timeOfDay = "晚上"
}else {
    timeOfDay = "半夜"
}


var sum = 1
while sum < 100 {
    sum = sum * (sum + 1)
}

repeat {
    sum = sum + 1
} while sum < 2000
