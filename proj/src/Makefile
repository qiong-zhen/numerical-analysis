CXX = g++
CXXFLAGS = -std=c++11 -Wall -I"D:/HuaweiMoveData/Users/谭希1/Desktop/proj/proj/include/eigen"

# 目标文件
TARGETS = test_ppform test_bsplines

# 源文件
SOURCES_PPFORM = test_ppform.cpp
SOURCES_BSPLINES = test_bsplines.cpp

# 头文件依赖
HEADERS = ppform.h Bsplines.h

# 默认目标
all: $(TARGETS)

# 编译规则
test_ppform: $(SOURCES_PPFORM) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES_PPFORM) -o $@

test_bsplines: $(SOURCES_BSPLINES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES_BSPLINES) -o $@

# 清理规则
clean:
	rm -f $(TARGETS) *.txt *.png

# 运行测试
test: $(TARGETS)
	./test_ppform
	./test_bsplines

# 绘图脚本
plot: test
	python plot_results.py
	python plot_bsplines.py

.PHONY: all clean test plot 