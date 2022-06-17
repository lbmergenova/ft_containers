NAME_VEC = test
NAME_VEC_STD = test_std
INTRA_STD = std_intra
INTRA_FT = ft_intra
SRCS_VEC = test.cpp
MAIN = main_intra.cpp
HEADERS= map.hpp rb_tree.hpp stack.hpp utility.hpp \
		iterator_traits.hpp pair.hpp set.hpp tree_iterator.hpp vector.hpp

all: $(NAME_VEC)

$(NAME_VEC): $(SRCS_VEC) $(HEADERS)
	@ c++ -std=c++98 -Wall -Wextra -Werror $(SRCS_VEC) -o $(NAME_VEC)
	@ c++ -std=c++98 -Wall -Wextra -Werror $(SRCS_VEC) -D FLAG=1 -o $(NAME_VEC_STD)

run:
	@./test ft_out.txt
	@./test_std std_out.txt
	@echo "\nDIFFERENCE BETWIN FILE:"
	@diff "ft_out.txt" "std_out.txt"
	@echo "END DIFF"

intra: $(HEADERS) $(MAIN)
	@ c++ -std=c++98 -Wall -Wextra -Werror $(MAIN) -o $(INTRA_FT)
	@ c++ -std=c++98 -Wall -Wextra -Werror $(MAIN) -D FLAG=1 -o $(INTRA_STD)

clean:
	@ rm -f $(NAME_VEC)
	@ rm -f $(NAME_VEC_STD)
	@ rm -f $(INTRA_FT)
	@ rm -f $(INTRA_STD)
	@ rm -f ft_out.txt
	@ rm -f std_out.txt

re : clean all
