/*
The MIT License (MIT)

Copyright (c) 2015 Aurelien Guy-Duche

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


History:
* 2015 creation

*/
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "shortRead.h"

// TODO print usage & help

int main(int argc, char** argv)
{
	gzFile fp = NULL, fp2 = NULL;
	ShortReadPtr reads[2];

	fp = safeGzOpen(argv[1], "r");

	if (argc == 3)
		fp2 = safeGzOpen(argv[2], "r");

	reads[0] = shortReadNext(fp);
	while (reads[0] != NULL)
	{
		if (fp2 != NULL)
			reads[1] = shortReadNext(fp2);
		
		fprintf(stdout, ">%s\n%s\n", reads[0]->name, reads[0]->seq);
		if (fp2 != NULL)
		{
			fprintf(stdout, ">%s\n%s\n", reads[1]->name, reads[1]->seq);
			shortReadFree(reads[1]);
		}
		shortReadFree(reads[0]);
		reads[0] = shortReadNext(fp);
	}

	gzclose(fp);
	if (fp2 != NULL)
		gzclose(fp2);

	return 0;
}