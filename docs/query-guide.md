# Query Guide

The program accepts one query at a time after building the index.

```text
index AND search
boolean OR retrieval
NOT sorting
```

`AND` keeps documents that contain both terms. `OR` combines the matching document sets. `NOT` returns all indexed documents except the documents containing the following term.

Queries are case-insensitive because the input is normalized before it is indexed.

