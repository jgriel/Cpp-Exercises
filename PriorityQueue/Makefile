all:
	g++ Graph.cpp -Wall -g GraphTests.cpp -o graph-tests
	g++ BetterPriorityQueue.cpp Graph.cpp -Wall -g BPQTests.cpp -o bpq-tests
	g++ Graph.cpp BetterPriorityQueue.cpp -Wall -g Dijkstra.cpp -o dijkstra

runGraph:
	./graph-tests

runQueue:
	./bpq-tests

runDijkstra:
	./dijkstra