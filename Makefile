.PHONY: format
format:
	find . -name '*.hpp' -o -iname '*.cpp' | xargs clang-format -i
