// Tree class
// Declares static objects, on page 800

#ifndef TREE_H
#define TREE_H

class tree
{
    private:
        static int objectCount; // Static var
    public:
        // Constructor
        tree()
            { objectCount ++; }

        // Accessor function for objectCount
        int getObjectCount() const
            { return objectCount; }
};

// Definition of the static member varioble, written outside the class
int tree::objectCount = 0;

#endif
