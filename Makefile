NAME = ft_gkrellm

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra

SOURCE_FILES = main.cpp \
	Monitor/DateTimeMonitorModule.cpp \
	Data/ModuleData.cpp \
	Display/Gtk3Display.cpp \
	Monitor/OSInfoMonitorModule.cpp \
	Monitor/AMonitorModule.cpp \
	Monitor/NameMonitorModule.cpp \
	Monitor/CPUMonitorModule.cpp \
	Monitor/MemoryMonitorModule.cpp \
	Monitor/NetworkMonitorModule.cpp \
	Monitor/DiskMonitorModule.cpp \
	Display/NcursesDisplay.cpp \
	Display/AMonitorDisplay.cpp

HEADER_FILES = Monitor/IMonitorModule.hpp \
	Display/IMonitorDisplay.hpp \
	Monitor/DateTimeMonitorModule.hpp \
	Data/ModuleData.hpp \
	Display/Gtk3Display.hpp \
	Monitor/OSInfoMonitorModule.hpp \
	Monitor/AMonitorModule.hpp \
	Monitor/NameMonitorModule.hpp \
	Monitor/CPUMonitorModule.hpp \
	Utils/utils.hpp \
	Monitor/MemoryMonitorModule.hpp \
	Monitor/NetworkMonitorModule.hpp \
	Monitor/DiskMonitorModule.hpp \
	Display/NcursesDisplay.hpp \
	Display/AMonitorDisplay.hpp

OBJDIR = obj
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ_FILES = $(addprefix $(OBJDIR)/, $(SOURCE_FILES:.cpp=.o))


all: $(NAME)

$(NAME): build $(OBJ_FILES)
	$(CXX) `pkg-config --libs gtk+-3.0` -lncurses $(OBJ_FILES)  -o $(NAME)

build:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) `pkg-config --cflags gtk+-3.0` $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
