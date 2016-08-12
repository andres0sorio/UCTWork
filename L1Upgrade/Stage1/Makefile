# Generic make file for LaTeX: requires GNU make




TEXFILE	= output.tex
#TEXFILE	= scratch.tex



.PHONY: dvi ps pdf clean

pdf:	$(TEXFILE:.tex=.pdf)
ps:	$(TEXFILE:.tex=.ps)
dvi:	$(TEXFILE:.tex=.dvi)
aux:	$(TEXFILE:.tex=)


%.dvi: %.tex
	( \
	latex $<; \
	while grep -q "Rerun to get cross-references right." $(<:.tex=.log); \
	do \
		latex $<; \
	done \
	)

%.ps: %.dvi
	dvips -q -t letter $< -o $(<:.dvi=.ps)

%.pdf: %.ps
	ps2pdf -dPDFSETTINGS=/prepress $<
	@rm -f \
	$(TEXFILE:.tex=.log) \
	$(TEXFILE:.tex=.out) \
	$(TEXFILE:.tex=.dvi) \
	$(TEXFILE:.tex=.aux) \
	$(TEXFILE:.tex=.ps)

clean:
	@rm -f \
	$(TEXFILE:.tex=.log) \
	$(TEXFILE:.tex=.out) \
	$(TEXFILE:.tex=.aux) \
	$(TEXFILE:.tex=.dvi) \
	$(TEXFILE:.tex=.pdf) \
	$(TEXFILE:.tex=.ps)
