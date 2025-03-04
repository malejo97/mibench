CC = $(CROSS_COMPILE)gcc

FILE = bitcnt_1.c bitcnt_2.c bitcnt_3.c bitcnt_4.c bitcnts.c bitfiles.c bitstrng.c bstr_i.c 

bitcnts: ${FILE} Makefile
	$(CC) -static ${FILE} -O3 -o bitcnts --specs=rdimon.specs
	#$(CC) -nostdlib -static ${FILE} -O3 -o bitcnts
#--specs=nosys.specs

clean:
	rm -rf bitcnts output*
