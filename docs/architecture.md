# Architecture Notes

The program follows a simple pipeline so every Information Retrieval step can be inspected:

1. `DocumentReader` loads sorted `.txt` files and assigns document IDs.
2. `TextProcessor` converts text into lowercase tokens.
3. `InvertedIndex` stores each term and points to a custom linked list of document IDs and frequencies.
4. `IncidenceMatrix` converts the index into a 0/1 term-document table.
5. `BooleanQuery` combines document sets with `AND`, `OR`, and `NOT`.

The index is the main searchable structure. The matrix is also built because it makes the basic Boolean Retrieval model easier to see.
