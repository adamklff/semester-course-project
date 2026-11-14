# Login Log Review

A C coursework prototype that reads synthetic login events from a CSV file and flags accounts that reach five failed attempts. It demonstrates array-backed storage and an optional linked-list view.

## Run the example

Use GCC and Make.

```sh
make
./login-review examples/logins.csv
./login-review examples/logins.csv --list
```

The example analyzes six login records and flags `alice`. The input format is an unquoted CSV with four fields: timestamp, username, IPv4 text, and success (`0` or `1`). The rule counts all failures per account for the supplied file. The threshold is set in `include/config.h`.

## Coursework and credit

The original group plan assigned the array and linked list modules to Adam. The runnable follow-up builds on the coursework interfaces and linked-list code from [patch-7](../../tree/patch-7) with AI assistance. Queue, stack, tree, graph, sorting, and search files remain coursework scaffolding and are outside the demo's build.

See the [MIT License](LICENSE).
