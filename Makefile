CXX = clang++
CXXFLAGS = -g -fsanitize=address

TARGETS = bubble_sort insertion_sort merge_sort selection_sort heap_sort quick_sort \
		  library_sort tim_sort cocktail_sort comb_sort tournament_sort intro_sort \
		  testcase_generator

all: $(TARGETS)

%: %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)