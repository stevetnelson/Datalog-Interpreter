This program takes a Datalog Program and interprets it.
It was designed with Finite State Automata to parse and tokenize the input, ensures the grammar of the program was correct, stores all the information, effectively uses rules to create more facts by creating a dependency graph, and answers queries.
This entirely self-made program takes any Datalog program with proper grammar and interprets it from start to finish.
It expects as a command line argument the name of the file containing the datalog program. The output of the program will be to the standard output.
The program explicitly defines the strongly connected component relationship within "Rules" and also explicitly lists all the facts created during Rule Evaluation.
Finally, the program lists the queries and answers them.

Example Input:
"Schemes:
Parent(p,c)
Sibling(a,b)
Ancestor(x,y)

Facts:
Parent('bob','ned').
Parent('jim','bob').
Sibling('sue','ned').

Rules:
Sibling(x,y):-Sibling(y,x).
Ancestor(x,y):-Ancestor(x,z),Parent(z,y).
Ancestor(x,y):-Parent(x,y).

Queries:
Ancestor(x,'ned')?
Sibling('ned','sue')?"



Example Output:
"Dependency Graph
R0:R0
R1:R1,R2
R2:

Rule Evaluation
SCC: R2
Ancestor(x,y) :- Parent(x,y).
  x='bob', y='ned'
  x='jim', y='bob'
1 passes: R2
SCC: R1
Ancestor(x,y) :- Ancestor(x,z),Parent(z,y).
  x='jim', y='ned'
Ancestor(x,y) :- Ancestor(x,z),Parent(z,y).
2 passes: R1
SCC: R0
Sibling(x,y) :- Sibling(y,x).
  a='ned', b='sue'
Sibling(x,y) :- Sibling(y,x).
2 passes: R0

Query Evaluation
Ancestor(x,'ned')? Yes(2)
  x='bob'
  x='jim'
Sibling('ned','sue')? Yes(1)"