all: a.out

test: a.out
	./a.out

a.out: main.cc
	$(CXX) -o $@ $<

main.cc: main1.cc
	ln -s -f $< $@

clean:
	$(RM) *~

distclean: clean
	$(RM) main.cc
	$(RM) a.out
