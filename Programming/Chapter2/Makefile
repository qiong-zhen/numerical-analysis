# Makefile  
  
CXX = g++  
CXXFLAGS = -std=c++11 -Wall -Wextra -I.  
TARGET = MyMathLibrary  
  
SRCS = B.cpp C.cpp D.cpp  E.cpp F.cpp # 添加其他源文件  
OBJS = $(SRCS:.cpp=.o)  
  
all: $(TARGET)  
  
$(TARGET): $(OBJS)  
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  
  
clean:  
	rm -f $(OBJS) $(TARGET)