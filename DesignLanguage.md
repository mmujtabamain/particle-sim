### DEBUG

- DEBUG Only code is prefixed with `_`; see [`__scene`](src/lib/BinaryPositionEncoder.hpp#L40)
  > `__scene` because `_` for **debug** and `_` for seperating and applying prefix
- `#if DEBUG == 1` is only used when drawing or printing to console the debug vars; see [`scene.cpp`](src/engine/Scene.cpp#L82)

### GENERAL RULES

- Getters and Setters should no be dependant on other getters and setter
- Use prefix `d` for exceptions
- Public methods should have their first letter capitalized. e.g

### PREFIXES

- `_`: the variable is **debug**
- `m`: The variable in **private** variable and should be modified and accessed by that class only
- `ro`: The variable is **readonly**; Commonly useful for getting `const &`
- `d`: The `getter` or `setter` that **depends** on another `getter` or `setter`

**PREFIX RULES:**:

- Prefix when applied should be seperated from variable name by `_`
- Prefixes can be combined as needed
  - Prefixes should be combined with `_` between them
  - `m_ro_var` represents a variable that is both _readonly_ and _private_
- `_` has highest precedence, i.e `__m_var` is preferred over `m___var`

### GIT

- Create another branch for developement named `dev-yourgithubusername-index`
- Merge branch into `main` when the code has been documented and readable by others
