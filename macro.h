#ifndef MACRO_H
#define MACRO_H

#define ASSERT(exp)  if (!exp) fprintf(stderr, "Error: " #exp " evaluated as false\n")
#define EXEC(f)      if (f != NULL) f()

#endif/* MACRO_H */
