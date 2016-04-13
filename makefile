CPP=g++

BASE=ctudp.cpp ctudp.h

build: $(BASE)
	$(CPP) -c -fPIC $(BASE)
	$(CPP) -shared -Wl,-soname,libctudp.so -o libctudp.so *.o
install:
	cp -f libctudp.so /usr/lib/
	[ -d /usr/include/ctudp ] || mkdir /usr/include/ctudp
	cp -f *.h /usr/include/ctudp/
uninstall:
	rm -f /usr/lib/libctudp.so
	rm -f /usr/include/ctudp/*.h
	[ -d /usr/include/ctudp ] && rmdir /usr/include/ctudp
test_server: tserver.cpp $(BASE)
	$(CPP) -o server tserver.cpp $(BASE)
test_client: tclient.cpp $(BASE)
	$(CPP) -o client tclient.cpp $(BASE)
test: test_server test_client
clean:
	for file in $$(ls *.o); do rm $$file; done
	for file in $$(ls *.so); do rm $$file; done
	for file in $$(ls *.gch); do rm $$file; done
	if [ -e server ]; then rm server; fi
	if [ -e client ]; then rm client; fi
