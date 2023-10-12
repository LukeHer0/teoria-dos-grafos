SUBDIRS = Bellman-Ford Dijkstra Kruskal Prim

BAT = ./Bat1/Bat1.sh

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
.PHONY: all $(SUBDIRS)

run:
	$(BAT)