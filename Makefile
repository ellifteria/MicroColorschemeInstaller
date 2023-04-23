USER =

main: check-user install_scheme.c
	cc -DUSER='"$(USER)"' -o instllschm -Wall install_scheme.c 
	
check-user:
ifndef USER
	$(error USER is undefined)
endif
