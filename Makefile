# compiler

CC  = g++

#----------------------------------------------------------

# obj files

OBJ = obj/main.o          \
	  obj/vector.o        \
	  obj/logs.o          \
	  obj/coordsys.o      \
	  obj/graphics.o	  \
	  obj/raycast_test.o  \
	  obj/raycast.o

#----------------------------------------------------------

CXXFLAGS = -O2 -g

#----------------------------------------------------------

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#----------------------------------------------------------

# bool flag - shows whether use flags ot not

USE_FLAGS = 0

#----------------------------------------------------------

ifeq ($(USE_FLAGS), 1)

	FLAGS = -lubsan -D NDEBUG -g -std=c++20 -fmax-errors=1 				\
			-Wall -Wextra -Weffc++ -Waggressive-loop-optimizations  	\
			-Wc++0x-compat -Wc++11-compat -Wc++14-compat  				\
			-Wcast-qual -Wchar-subscripts -Wconditionally-supported 	\
			-Wconversion  -Wctor-dtor-privacy -Wempty-body 				\
			-Wfloat-equal -Wformat-nonliteral -Wformat-security 		\
			-Wformat-signedness -Wformat=2 -Winline  -Wlogical-op 		\
			-Wmissing-declarations  -Wnon-virtual-dtor -Wopenmp-simd	\
			-Woverloaded-virtual -Wpacked -Wpointer-arith 				\
			-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo	\
			-Wstack-usage=8192  -Wstrict-null-sentinel 					\
			-Wstrict-overflow=2 -Wsuggest-attribute=noreturn 			\
			-Wsuggest-final-methods -Wsuggest-final-types  				\
			-Wsuggest-override -Wswitch-default -Wswitch-enum 			\
			-Wsync-nand -Wundef  -Wunreachable-code -Wunused 			\
			-Wuseless-cast -Wvariadic-macros -Wno-literal-suffix 		\
			-Wno-missing-field-initializers -Wno-narrowing				\
			-Wno-old-style-cast -Wno-varargs -fcheck-new 				\
			-fsized-deallocation  -fstack-protector 					\
			-fstrict-overflow   -flto-odr-type-merging 					\
			-fno-omit-frame-pointer -fPIE -fsanitize=address  			\
			-fsanitize=bool -fsanitize=bounds -fsanitize=enum  			\
			-fsanitize=float-cast-overflow 								\
			-fsanitize=float-divide-by-zero 							\
			-fsanitize=integer-divide-by-zero -fsanitize=leak 			\
			-fsanitize=nonnull-attribute -fsanitize=null 				\
			-fsanitize=object-size -fsanitize=return 					\
			-fsanitize=returns-nonnull-attribute -fsanitize=shift 		\
			-fsanitize=signed-integer-overflow -fsanitize=undefined 	\
			-fsanitize=unreachable -fsanitize=vla-bound 				\
			-fsanitize=vptr -lm -pie

else

	FLAGS =

endif

#==========================================================

all: dir raycast_

#----------------------------------------------------------

.PHONY: dir clean

dir:
	mkdir -p obj

clean:
	rm obj/*.o raycast

#----------------------------------------------------------

raycast_: $(OBJ)
	$(CC) $(OBJ) $(SFML_FLAGS) -o raycast_test

obj/main.o:     src/main.cpp include/raycast_test/raycast_test.hpp
	$(CC) 		src/main.cpp              			-c -o obj/main.o     	  $(FLAGS) $(CXXFLAGS) 

obj/vector.o:	src/vector/vector.cpp include/vector/vector.hpp
	$(CC) 		src/vector/vector.cpp     			-c -o obj/vector.o   	  $(FLAGS) $(CXXFLAGS)

obj/graphics.o: src/graphics/graphics.cpp include/graphics/graphics.hpp include/vector/vector.hpp \
																    include/coordsys/coordsys.hpp
	$(CC)		src/graphics/graphics.cpp 			-c -o obj/graphics.o 	  $(FLAGS) $(CXXFLAGS)

obj/logs.o:     src/logs/logs.cpp include/logs/errors.h include/logs/logs.h codegen/err_descr.txt
	$(CC) 		src/logs/logs.cpp 			        -c -o obj/logs.o     	  $(FLAGS) $(CXXFLAGS)

obj/coordsys.o: src/coordsys/coordsys.cpp include/coordsys/coordsys.hpp
	$(CC) 		src/coordsys/coordsys.cpp 			-c -o obj/coordsys.o 	  $(FLAGS) $(CXXFLAGS) 

obj/raycast_test.o:  src/raycast_test/raycast_test.cpp include/raycast_test/raycast_test.hpp \
													   include/graphics/graphics.hpp \
													   include/raycast_test/raycast_test_conf.hpp
	$(CC)		src/raycast_test/raycast_test.cpp 	-c -o obj/raycast_test.o 	  $(FLAGS) $(CXXFLAGS)

obj/raycast.o:	src/raycast/raycast.cpp include/raycast/raycast.hpp 
	$(CC)		src/raycast/raycast.cpp				-c -o obj/raycast.o       $(FLAGS) $(CXXFLAGS)	