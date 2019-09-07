# clplot
An ascii chart generator for the terminal written in C++.


## Installation

Install with git:
```bash
git clone this
make
make install
./chart -d [1,2,3]
```

## Usage
<b>clplot</b> comes with many options for style, customization, and chart types.
#### Options:
<pre>
-d
    -  Specify data for the chart, in format `[num1, num2, numN]` 
    -  ex: -d [1,5.1,3,4]
    -  Required 
-t
    Specify the chart type (line, bar, )  |  `-t bar`      |  `line` | Optional |
-c
    Change the color of the chart content  |  `-c blue; -c 41`      |  `white` | Optional |
-h
    Change the height of the chart (in lines)  |  `-h 14`      |  Terminal height | Optional |
-w
    Change the width of the chart (in columns)  |  `-w 20`      |  Terminal width | Optional |
-p
    Specify the coordinate for the top left corner of the chart.  |  `-p 5,6`      |  0,0  | Optional |

-n, --bits=BITS
    Set the number of bits to modify. Default is one bit.
</pre>

## See also

- [fast](github.com/k-vernooy/fast): an implementation of cplot that monitors internet speed.
- [k-vernooy.github.io/projects/clplot](https://k-vernooy.github.io/projects/clplot) - a page with full documentation and example usages and quick projects for clplot.

## Compatibility

As of now, only tested on macOS - should work on linux as well.