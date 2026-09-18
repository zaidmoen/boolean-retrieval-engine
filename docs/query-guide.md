# Query Guide

The program accepts one query at a time after building the index.

```text
index AND search
boolean OR retrieval
NOT sorting
```

The operators follow the usual Boolean precedence:

1. `NOT`
2. `AND`
3. `OR`

For example, `index OR search AND engine` evaluates the `AND` part first.

`AND` keeps documents that contain both terms. `OR` combines the matching document sets. `NOT` returns all indexed documents except the documents containing the following term.

Queries are case-insensitive because the input is normalized before it is indexed.
