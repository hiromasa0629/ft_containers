#!/usr/bin/env bash

FILES=(\
	"bounds" \
	"comp" \
	"copy_construct" \
	"empty" \
	"erase" \
	"erase2" \
	"find_count" \
	"insert" \
	"insert2" \
	"ite_arrow" \
	"more" \
	"op_sqbr" \
	"swap" \
	"tricky_construct" \
	"tricky_erase"
)

exe() {
	mkdir -p compare
	echo $1 ; diff <(./one ./srcs/map/"$1".cpp) <(./one ./srcs/map/"$1".cpp std) | cat > compare/"$1"
}

for str in ${FILES[@]}; do
	exe ${str}
done
