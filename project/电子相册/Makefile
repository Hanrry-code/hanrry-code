vpath %.c  = src/
vpath %.so = lib/

main:
	# 调用子Makefile
	$(MAKE) -C src/ main
install:
	#调用子Makefile
	$(MAKE) -C src/ libphoto.so

clean:
	$(RM) main
	$(MAKE) -C src/ clean
distclean:
	$(MAKE) -C src/ distclean

.PHONY: install clean distclean
