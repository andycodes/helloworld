################################################################################
#Makefile for the entire project
#all executable file copied to "obj" folder

TGTDIR = run

all: 
	@if ! [ -d $(TGTDIR) ] ; then mkdir $(TGTDIR) ; fi
	@echo ******************************[Generating services]*****************************
	@make service -C arch
	@cp -f arch/bin/*.a  $(TGTDIR)
clean:
	@make clean -C arch
	@rm -rf $(TGTDIR)