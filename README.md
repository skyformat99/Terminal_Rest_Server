# Example rest server in C for SmartPay Inc.

If you're not me, or hiring me: you shouldn't be seeing this.

I didn't get a lot of time to do this within my schedule; so if I can contextualise this, I would state that this is the product of an 8 hour work stretch from absolute scratch.

I also would like to say that I prioritised overall structural completeness because it's more important to you to see how I make code. Also worked on bottom-up correctness: so there's no tests on the server layer (though, it is implemented).

If I were to do this again, I probably would have written the acceptance tests first so that I could use a TDD approach.


## Scructure

### Code

- `model.h` struct and function definitions (the C equivalent of code-to-interface)
- `persistence.c` Implementation of persistence (as a in-memory linked list)
- `parser.c` json-c based implementation of the parsing components
- `rest.c` Business logic implementation as a set of REST methods (agnostic to server implementation)
- `tests.c` C-Unit tests file.  Not compiled when packing deployable of doing unit tests.
- `main.c` microhttpd based implementation of the server component.  Not compiled with tests (though, this could be changed so that the microhttpd components can be tested with C-Unit)

### Extra

- `makefile` A simple makefile to run tests and package deployables.
- `acceptance-test.sh` A bash file that uses CURL to do some simple testing of the server. 

## Usage (makefile)

### Pre-Requisites

The following need to be installed:

- GCC
- make (and makeutils)
- cunit 
- json-c 
- microhttpd

### Building

```
make server-compile
```

### Unit Tests

```
make unit-test
```

### Acceptance Tests

```
make acceptance-test
```


## Things I would have Done.

- I did the storage as a linked list, mostly to prove I understand pointer arithmetic.  In practice this wouldn't be such a good idea.
- I didn't have time to add threading to this, which would be absoultely needed if there isn't an opportunity to use a persistence library to the project that's already threadsafe.
- I considered using libjson, but it's callback based, and while it would be more robust if done right, that would take longer
- Added an authentication layer.  Not necessarily an entire ldap/JWT/Oauth2, but at least an auth header.
- Added TLS support.  Given these are terminals, I'd probably implement 
- In reality bash is a poor candidate: I'd rather use something like cucumber or fitnesse to do the testing 
- I'd rather have UUID's for IDs but I started with longs tto make the problem simpler to start with.
- Better test reporting (for regression) and some coverage metrics.
- add linting to the make file (or better yet, run it through SonarQube)