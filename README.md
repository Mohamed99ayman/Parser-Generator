# Parser Generator
A simple parser generator that takes an LL(1) grammar (CFG) as input, the parser can also eliminate left recursion and apply left factoring transformation.

The parser creates a parsing table, which takes a sequence of characters and tries to match the sequence against the grammar. 

Predictive parsing chooses the correct production by looking ahead at the input without the need for recursive-descent parsing.

## Error Recovery

If the input grammar is not LL(1), an appropriate error message should be produced. The generated parser is required to produce some representation of the leftmost derivation for a correct input. If an error is encountered, a panic-mode error recovery routine is to be called to print an error message and to resume parsing.



