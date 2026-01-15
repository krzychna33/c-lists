MISRA C:2004 (often called "MISRA C2") is a set of 142 coding rules designed to make C code safer and more predictable in embedded systems. Of these, **122 are "Required"** (mandatory unless a formal deviation is documented) and **20 are "Advisory"**.

The following are the most critical rules frequently cited in safety-critical development, categorized by their impact on code safety.

---

## 1. Safety & Undefined Behavior

These rules prevent common C "traps" that lead to crashes or unpredictable hardware states.

* **Rule 1.1 (Required):** All code shall conform to the ISO 9899:1990 (C90) standard. You cannot use modern C99/C11 features unless specifically documented.
* **Rule 1.2 (Required):** No reliance shall be placed on **undefined** or **unspecified behavior**. This covers things like shifting a value by more bits than its width.
* **Rule 9.1 (Required):** Variables with automatic storage (local variables) must be **initialized before use**. This prevents reading "garbage" values from the stack.
* **Rule 20.4 (Required):** Dynamic memory allocation (**malloc, calloc, free, realloc**) shall not be used. In embedded systems, heap fragmentation can cause a system to crash at runtime.

---

## 2. Pointers and Memory

Pointers are the most dangerous part of C; these rules strictly limit how you use them.

* **Rule 11.1 (Required):** Conversions shall not be performed between a pointer to a function and any type other than an integral type.
* **Rule 11.5 (Required):** A pointer shall not be cast to a type that removes **const** or **volatile** qualifiers. Doing so can cause the compiler to optimize away critical hardware reads.
* **Rule 17.4 (Required):** Array indexing (`a[i]`) is the only allowed form of **pointer arithmetic**. Direct arithmetic like `ptr++` or `*(ptr + 5)` is generally prohibited to prevent "walking" off the end of an array.

---

## 3. Control Flow and Complexity

These rules ensure that the logic of the code is easy to follow and test.

* **Rule 14.1 (Required):** There shall be no **unreachable code**. If code can never execute, it often points to a logic error or a "dead" safety check.
* **Rule 14.4 (Required):** The `goto` statement shall not be used.
* **Rule 14.7 (Required):** A function shall have a **single point of exit** at the end. Multiple `return` statements in one function are forbidden because they make it harder to verify that resources (like mutexes) are always released.
* **Rule 15.3 (Required):** The final clause of a `switch` statement shall be the `default` clause. This ensures "unhandled" states are caught.

---

## 4. Types and Conversions

C’s default type-promotion rules are notoriously confusing. MISRA forces you to be explicit.

* **Rule 6.3 (Advisory):** Use `typedefs` that indicate size and signedness (e.g., `uint32_t` instead of `unsigned long`).
* **Rule 10.1 (Required):** Implicit conversions that change signedness or lead to loss of precision are prohibited. You must use an explicit cast.
* **Rule 12.1 (Advisory):** Limited dependence should be placed on **operator precedence**. Use parentheses even if you know the order (e.g., `(a + b) < c` instead of `a + b < c`).

---

## Summary Table: Required vs. Advisory

| Category | Key Rule Examples | Why it matters |
| --- | --- | --- |
| **Environment** | 1.1, 1.2 | Ensures the compiler behaves predictably. |
| **Pointers** | 17.4, 11.5 | Prevents buffer overflows and hardware access bugs. |
| **Control Flow** | 14.4, 14.7 | Simplifies testing and avoids logic errors. |
| **Data Types** | 6.3, 10.1 | Stops "silent" bugs caused by integer promotion. |

**Would you like me to provide a code example showing a common C snippet and how to refactor it to comply with these MISRA rules?**