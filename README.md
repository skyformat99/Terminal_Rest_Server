# Example rest server in C for SmartPay Inc.

If you're not me, or hiring me: you shouldn't be seeing this.

I didn't get a lot of time to do this within my schedule; so if I can contextualise this, I would state that this is the product of an 8 hour work stretch from absolute scratch.

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
- add linting to the make file
- 
