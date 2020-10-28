#include "../include/precompiled.hpp"

/*
OutOfMemoryError:
  - if computation requires more heap than can be made available
    by the automatic storage management system
  - If the JVM stack can be dynamically expanded, and expansion is 
    attempted but insufficient memory can be made available
    
StackOverflowError:
  - if computation in a thread requires a larger JVM stack than is permitted
*/