#!/bin/bash
output=$1
output=${output%.*}
output+=".o"
dll=$1
dll=${dll%.*}
dll+=".dll"
gcc -c -v -fPIC $1 -o $output 
gcc -shared -o $dll $output
