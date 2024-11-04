CC = g++
Flags = -ldl -D _DEBUG -lsfml-graphics -lsfml-window -lsfml-system  
Debug_flags = -ldl -D _DEBUG -lsfml-graphics -lsfml-window -lsfml-system  -ggdb3 -std=c++17 -O0 -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

all: src/main.cpp src/widget/widget.cpp src/graphic_structures/vector/vector.cpp src/graphic_structures/color/color.cpp src/widget/window/window.cpp src/widget/window/canvas/canvas.cpp src/widget/button/button.cpp src/widget/widget_manager/widget_manager.cpp src/widget/window/menu/menu.cpp src/widget/window/master_window/master_window.cpp src/widget/window/header/header.cpp src/widget/window/scrollbar/scrollbar.cpp src/widget/button/clock/clock.cpp src/widget/button/palette/palette.cpp src/plugin/tools/tools.cpp src/plugin/tools/palette/palette.cpp src/widget/texture_widget/texture_widget.cpp src/plugin/filter/filter.cpp src/widget/layout/layout.cpp src/widget/text/text.cpp src/graphics/convert_sfml_functions.cpp src/graphics/circleshape/circleshape.cpp src/graphics/rectangleshape/rectangleshape.cpp src/graphics/sprite/sfml_texture.cpp src/graphics/rendertexture/rendertexture.cpp src/graphics/text/text.cpp src/plugin/plugin_data.cpp src/catmullRom/catmull.cpp src/graphics/curve_plot/curve_plot.cpp src/graphic_structures/color/hsl_luma_color.cpp src/widget/window/curve_window/curve_window.cpp  
	$(CC) -fPIE -Wl,--export-dynamic src/main.cpp src/widget/widget.cpp src/graphic_structures/vector/vector.cpp src/graphic_structures/color/color.cpp src/widget/window/window.cpp src/widget/window/canvas/canvas.cpp src/widget/button/button.cpp src/widget/widget_manager/widget_manager.cpp src/widget/window/menu/menu.cpp src/widget/window/master_window/master_window.cpp src/widget/window/header/header.cpp src/widget/window/scrollbar/scrollbar.cpp src/widget/button/clock/clock.cpp src/widget/button/palette/palette.cpp src/plugin/tools/tools.cpp src/plugin/tools/palette/palette.cpp src/widget/texture_widget/texture_widget.cpp src/plugin/filter/filter.cpp src/widget/layout/layout.cpp src/widget/text/text.cpp src/graphics/convert_sfml_functions.cpp src/graphics/circleshape/circleshape.cpp src/graphics/rectangleshape/rectangleshape.cpp src/graphics/sprite/sfml_texture.cpp src/graphics/rendertexture/rendertexture.cpp src/graphics/text/text.cpp src/plugin/plugin_data.cpp src/catmullRom/catmull.cpp src/graphics/curve_plot/curve_plot.cpp src/graphic_structures/color/hsl_luma_color.cpp src/widget/window/curve_window/curve_window.cpp  $(Flags) -o w_manager
	./w_manager

build_udp_client: udp/udp.cpp udp/udp_client.cpp 
	$(CC) udp/udp_client.cpp udp/udp.cpp $(Debug_flags) -o udp/udp_client
build_udp_server: udp/udp.cpp udp/udp_server.cpp 
	$(CC) udp/udp_server.cpp udp/udp.cpp $(Debug_flags) -o udp/udp_server
build_tcp_client: tcp/tcp.cpp tcp/tcp_client.cpp 
	$(CC) tcp/tcp_client.cpp tcp/tcp.cpp $(Debug_flags) -o tcp/tcp_client
build_tcp_server: tcp/tcp.cpp tcp/tcp_server.cpp 
	$(CC) tcp/tcp_server.cpp tcp/tcp.cpp $(Debug_flags) -o tcp/tcp_server
start_udp_server:
	./udp/udp_server 4457 
start_udp_client:
	./udp/udp_client 4457 
start_tcp_server:
	./tcp/tcp_server 4459 
start_tcp_client:
	./tcp/tcp_client 4459 