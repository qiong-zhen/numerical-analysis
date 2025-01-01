# 定义变量
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./src -I/usr/include/eigen3
LATEX = xelatex
PYTHON = python3
TARGETS = runge_spline spline_C spline_D spline_E spline_F test_bsplines test_ppform
TEX_FILES = doc/design.tex doc/report.tex
PDF_FILES = $(TEX_FILES:.tex=.pdf)
PLOTS = plot_bsplines.py plot_C.py plot_D.py plot_E.py plot_F.py plot_results.py plot_runge.py

all: $(TARGETS) $(PDF_FILES) plot

# 编译 C++ 程序
runge_spline: src/A.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/A.cpp

spline_C: src/C.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/C.cpp

spline_D: src/D.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/D.cpp

spline_E: src/E.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/E.cpp

spline_F: src/F.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/F.cpp

# 新增的 C++ 程序
test_bsplines: src/test_bsplines.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/test_bsplines.cpp

test_ppform: src/test_ppform.cpp src/ppform.h
	$(CXX) $(CXXFLAGS) -o $@ src/test_ppform.cpp

# LaTeX
%.pdf: %.tex
	$(LATEX) -output-directory=$(dir $<) $<

# 测试以及运行
test: $(TARGETS) figure
	./runge_spline
	./spline_C
	./spline_D
	./spline_E
	./spline_F
	./test_bsplines
	./test_ppform

plot: test figure
	cd src && $(PYTHON) plot_runge.py
	cd src && $(PYTHON) plot_bsplines.py
	cd src && $(PYTHON) plot_C.py
	cd src && $(PYTHON) plot_D.py
	cd src && $(PYTHON) plot_E.py
	cd src && $(PYTHON) plot_F.py
	cd src && $(PYTHON) plot_results.py

# clean 清理规则
clean:
	rm -f $(TARGETS)
	rm -f $(PDF_FILES)
	rm -f doc/*.aux doc/*.log doc/*.out
	rm -rf figure/

# 创建 figure 目录
figure:
	mkdir -p figure

.PHONY: all clean test plot figure