It is a small library with classes CPPO and CPPOPtr. CPPO stands for C++ Object. These classes are wrappers around the std::map class, whose key is of type string, and whose value is of type std::any (introduced in the 2017 C++ standard revision). It allows it to hold any object. Therefore it can also hold another map as well. This possibility enables the creation of a hierarchical system of objects. Every CPPO and CPPOPtr object has methods update(), querycpy(), queryptr() and del(). CPPOPtr wraps a pointer to an std::map, while CPPO wraps an std::map. Each method takes a path argument. update() method will replace the given object at the path specified if exists, or create every non-existent path component (std::map) and puts the given object at the last path component. (So it either replaces existent objects, or puts new ones into the hierarchy). querycpy() will return a copy of the object at the specified path. queryptr() will return a pointer to it. del() will delete the object specified at the path. In each class, you can modify the path component separator character, and access the std::map object held by it if necessary. Both classes use independent, static, pure functions that are equivalent to the mentioned methods. They are also publicly accessible and operate on std::map parameters.