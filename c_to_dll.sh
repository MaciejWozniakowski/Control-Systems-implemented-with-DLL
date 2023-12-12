#!/bin/bash
output=$1
output=${output%.*}
output+=".o"
dll=$1
dll=${dll%.*}
dll+=".dll"
gcc -c -fPIC $1 -o $output -lm
gcc -shared -o $dll $output
