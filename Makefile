CC = g++
Flags = -ldl -D _DEBUG -lsfml-graphics -lsfml-window -lsfml-system  
Debug_flags = -ldl -D _DEBUG -lsfml-graphics -lsfml-window -lsfml-system  -ggdb3 -std=c++17 -O0 -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: build_udp_client build_udp_server build_tcp_client build_tcp_server

build_udp_client: shared.cpp udp/udp.cpp udp/udp_client.cpp 
	$(CC) shared.cpp udp/udp_client.cpp udp/udp.cpp $(Debug_flags) -o udp/udp_client
build_udp_server: shared.cpp udp/udp.cpp udp/udp_server.cpp 
	$(CC) shared.cpp udp/udp_server.cpp udp/udp.cpp $(Debug_flags) -o udp/udp_server
build_tcp_client: shared.cpp tcp/tcp.cpp tcp/tcp_client.cpp 
	$(CC) shared.cpp tcp/tcp_client.cpp tcp/tcp.cpp $(Debug_flags) -o tcp/tcp_client
build_tcp_server: shared.cpp tcp/tcp.cpp tcp/tcp_server.cpp 
	$(CC) shared.cpp tcp/tcp_server.cpp tcp/tcp.cpp $(Debug_flags) -o tcp/tcp_server
start_udp_server:
	./udp/udp_server 4457 
start_udp_client:
	./udp/udp_client 4457 
start_tcp_server:
	./tcp/tcp_server 4465 
start_tcp_client:
	./tcp/tcp_client 4465 