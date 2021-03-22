#语法规则
# targets...:prerequisites...
# 目标文件...:先决条件
# target 这 一 个 或 多 个 的 目 标 文 件 依 赖 于 	prerequisites 中 的 文 件
#	command
main:main.c
	gcc  main.c -o main

.PHONY:clean
clean:
	-rm main

#.PHONY 意思表示 clean 是一个“伪目标”
#而在 rm 命令前面加了一个小减号的意思就是,也许某些文件出现问题,但不要管,继续做后面的事。
#当然，也可以这样
#clean:
#	-rm main
#但这是不推荐的，如果在当前目录下，存在一个clean，那么就不执行clean后面的规则了