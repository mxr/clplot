# termplot
An ascii chart generator for the terminal written in C++.


# Use 


### Options
| Flag  | Description |   Example  |  Default | Optional |
| ----- | ----------- | ---------- | -------- | -----|
| -d    | Specify data for the chart. Must be in format `[num1, num2, numN]`  | `-d [1,5.1,3,4]`  | None |  Required |
| -h    | Change the height of the chart (in lines)  |  `-h 14`      |  Terminal height | Optional |
| -w    | Change the width of the chart (in columns)  |  `-w 20`      |  Terminal width | Optional |
| -t    | Specify the chart type (line, bar, )  |  `-t bar`      |  `line` | Optional |
| -c    | Change the color of the chart content  |  `-c blue; -c 41`      |  `white` | Optional |