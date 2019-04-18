# lem-in
Algorithmic project 42 (Unit Factory). Graph Theory.


Purpose: 
Move ants throw links from start to end.
Links and nodes represented as graph.
Ants start their movment form room marked ##start and finish at room marked ##end.
Only one ant can be in room by a turn (except ##start and ##end rooms)

Algorythm:
My aproach (that not so good with superposition maps is to find shorter way and block it nodes by BFS.
Than I try to increas flow in graph by finding any ways, thats unique and adding them to solution.
