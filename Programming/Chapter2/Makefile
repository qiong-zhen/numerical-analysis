# 定义编译器
CXX = g++

# 定义编译标志
CXXFLAGS = -Wall -g

# 定义源文件和可执行文件
SRC = B.cpp C.cpp D.cpp E.cpp F.cpp
EXE = B C D E F

# 默认目标：编译所有可执行文件
all: $(EXE)

# 定义规则，编译每个源文件为对应的可执行文件
B: B.cpp
	$(CXX) $(CXXFLAGS) -o B B.cpp

C: C.cpp
	$(CXX) $(CXXFLAGS) -o C C.cpp

D: D.cpp
	$(CXX) $(CXXFLAGS) -o D D.cpp

E: E.cpp
	$(CXX) $(CXXFLAGS) -o E E.cpp

F: F.cpp
	$(CXX) $(CXXFLAGS) -o F F.cpp

# 运行所有可执行文件
run: all
	@echo "Running B:"
	@./B
	@echo "Running C:"
	@./C
	@echo "Running D:"
	@./D
	@echo "Running E:"
	@./E
	@echo "Running F:"
	@./F

# 编译 LaTeX 文件成 PDF
report: report.tex
	xelatex report.tex

# 清理编译生成的文件
clean:
	rm -f $(EXE) *.aux *.log *.pdf

# 运行image文件夹下的所有Python脚本
py:
	@echo "Running Python scripts in image folder:"
	@python3 image/B.py
	@python3 image/C.py
	@python3 image/D.py
	@python3 image/E.py
	@python3 image/F.py

# 添加phony目标以避免与真实文件冲突
.PHONY: all run report clean py
