# Code Style

## General

- No lines longer than 80 characters
- Avoid global variables
- Avoid long functions and deeply nested control flow
- Avoid `switch` statements
- Order imports/includes/requires alphabetically at the top of the file
- One class/module per file
- Function names should be verbs, not nouns, e.g. `game()` should be `play_game()`. But use nouns for getters/setters for properties: `size()`, not `get_size()`.
- Avoid `is_` prefixes on funcs and vars -- just `empty()` rather than `is_empty()` and `running` rather than `is_running`.
- Class names and vars should be nouns, not verbs
- Var names shouldn't include the type: `people` rather than `people_array`
- Avoid explicit flags/booleans as much as possible; it's OK to use multiple `return`s (but try to reduce the number of returns and paths through a function in general, usually no more than 2-3 returns)
- No nested ternaries
- `return foo` instead of `if (foo) return true else return false`
- Use `if (something)`, not `if (something == true)`
- Avoid using comments when a block of code should be a function, or re-explaining obvious code.
  Too obvious:
  ```cpp
  // store the length of the string in a variable
  const length = string.length;
  ```
  Better:
  ```cpp
  // storing the length improves cache hit rates
  const length = string.length;
  ```
- Limit functions and constructors to no more than 3 parameters, else consider using a config hash/object
- Use the right data type; if a number can't be negative, use an unsigned int.
- When there are long types on function calls or definitions, use intermediate vars or parens like:
  ```cpp
  void foobar(
      std::vector<std::string> &bar,
      std::vector<std::string> &baz,
      std::vector<std::string> &quux
  ) {
     // ...
  }
  ```

## C++

- No [`using namespace std;`](https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice)
- No [`#include <bits/stdc++.h>`](https://stackoverflow.com/questions/31816095/why-should-i-not-include-bits-stdc-h)
- 4 space indentation
- Functions, vars `snake_case`
- Classes, structs `PascalCase`
- No `#define` or `typedef`
- Use references when a copy isn't required
- No C idioms like `malloc`/`free` (except in WASM glue code where unavoidable)
- Avoid macros
- No implementation in headers
- Use smart pointers instead of raw pointers (ideally!)
- Use `const` wherever possible
- Avoid `new`/`delete` where possible
- Avoid iterators and counter-based loops where possible (use range loops or `std::algorithm` functions)
- Whitespace/braces:
  ```cpp
  class Foo {
      const std::vector<std::string>> foobar;

  public:
      std::vector<std::string> foo(
          const std::string &s,
          const int foo,         
          const std::map<Foo, Bar> bar,         
      ) {
          std::vector<std::string> result;

          for (auto &c : s) {
              if (foobar) {
                  result.push_back(whatever);
              }
          }

          return result;
      }
  }
  ```
- Use `auto` only when the type is pretty obvious from context

## JS

- 2 space indentation
- `camelCase`
- No `==`, use `===` for comparisons
- Whitespace/braces:
  ```js
  const {xx, yy, zz} = library();
  
  const max = (a, b) => a >= b ? a : b;
  const sum = a => a.reduce((a, e) => a + e, 0);
  
  class FooBar {
    constructor() {
      this.fooBaz = 42;
    }
  
    barBaz(baz, quux) {
      const [x, y] = blargh(woop, wop);

      for (const foo of bar) {
        if (foo) {
          fetch("foo/bar/baz.json", {
              foo: bar,
              baz: quux,
            })
            .then(res => res.json())
            .then(data => console.log(data))
            .catch(err => console.error(err))
          ;
        }
      }
  
      return {foo: baz, quux};
    }
  }
  ```
- Avoid `var`/`let` where possible, prefer `const`
- Avoid loops other than `for .. of` -- prefer `forEach`/`map`/`filter`/`reduce`
- Prefer promises to callbacks when possible
- Avoid `new Promise` except when unavoidable
- Don't mix `async`/`await` and `then` unless it really makes sense. `then` is fine when cleaner.
- Catch all errors
- Always use semicolons after expressions

## CSS

- `kebab-case`
- Prefer classes to ids
