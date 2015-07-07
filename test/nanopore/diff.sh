#! /bin/bash

for S in "$@" ; do
	samtools view $S | cut -f 1,2,3,4,6 | grep -vF '@SQ' | grep -F 'M13mp18' | cut -f 1,2,4,5 | LC_ALL=C sort -t '	' -k 1,1 -k 3,3  > $S.tmp
done

join -t '	' -1 1 -2 1 $1.tmp $2.tmp | paste - - | cut -f 1,3,6 > $(dirname "$1")/same.blastBWA.txt
join -t '	' -v 1 -1 1 -2 1 $1.tmp $2.tmp > $(dirname "$1")/only.blast.txt
join -t '	' -v 2 -1 1 -2 1 $1.tmp $2.tmp > $(dirname "$1")/only.bwa.txt
rm -f $1.tmp $2.tmp
