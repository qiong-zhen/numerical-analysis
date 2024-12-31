CXX = g++
CXXFLAGS = -std=c++11 -Wall -I"D:/HuaweiMoveData/Users/谭希1/Desktop/proj/proj/include/eigen"

# 目标文件
TARGETS = runge_spline spline_C spline_D spline_E spline_F

# 源文件
SOURCES_A = A.cpp
SOURCES_C = C.cpp
SOURCES_D = D.cpp
SOURCES_E = E.cpp
SOURCES_F = F.cpp


# 头文件依赖
HEADERS = src/ppform.h

# 默认目标
all: $(TARGETS)

# 编译规则
runge_spline: $(SOURCES_A) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_A)

spline_C: $(SOURCES_C) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_C)

spline_D: $(SOURCES_D) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_D)

spline_E: $(SOURCES_E) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_E)

spline_F: $(SOURCES_F) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_F)


# 创建figure目录
figure:
	mkdir -p figure

# 清理规则
clean:
	rm -f $(TARGETS) *.txt
	rm -rf figure/

# 运行测试
test: $(TARGETS) figure
	./runge_spline
	./spline_C
	./spline_D
	./spline_E
	./spline_F


# 绘图脚本
plot: test
	python plot_runge.py
	python plot_C.py
	python plot_D.py
	python plot_E.py
	python plot_F.py
	

.PHONY: all clean test plot figure