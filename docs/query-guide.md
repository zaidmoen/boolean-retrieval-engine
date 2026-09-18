# Query Guide

The program accepts one query at a time after building the index.

## Operators

The supported operators are:

- `NOT`: excludes matching documents
- `AND`: keeps documents that match both sides
- `OR`: keeps documents that match either side

Operators follow the standard precedence:

1. `NOT`
2. `AND`
3. `OR`

Parentheses can change the evaluation order.

```text
index AND search
boolean OR retrieval
NOT sorting
index OR data AND documents
(index OR data) AND documents
NOT (index OR data)
```

Spaces around parentheses are optional:

```text
(index OR data) AND documents
(index OR data)AND documents
```

Queries and operators are case-insensitive. The following inputs are equivalent:

```text
index AND retrieval
InDeX aNd ReTrIeVaL
```

## Invalid input

The program reports incomplete expressions and unmatched parentheses without closing the prompt.

```text
index AND
(index OR data
()
```

After every valid query, the program prints the matching documents and the execution time in microseconds.
