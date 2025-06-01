NAME		=	Intern

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC			=	main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp
OBJ			=	$(SRC:.cpp=.o)

HEADER		=	Bureaucrat.hpp AForm.hpp ShrubberyCreationForm.hpp RobotomyRequestForm.hpp PresidentialPardonForm.hpp Intern.hpp

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "\033[32mCompiled using\033[0m\n\n\t<<< c++ -Wall -Wextra -Werror -std=c++98 >>>\n"

%.o: %.cpp $(HEADER)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "\033[34mCleaned\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f *_shrubbery
	@echo "\033[31mCleaned ALL\033[0m\n"

re: fclean all

.PHONY: all clean fclean re