# Roadmap

The plan for a complete, basics-first path through C++ and interview prep. `[x]` = exists today,
`[ ]` = planned. Problems keep the story style (fun, small, testable); each gets a lesson and links.

## Which C++?

The baseline is **C++20** (g++ 13 / clang 16+). Interviews rarely test brand-new features; they
test STL fluency, complexity analysis and clean code, and most platforms accept C++17/20. So
modern features show up where they make code *better* (ranges, `span`, `optional`, structured
bindings), and track 04 teaches C++23 bits like `std::expected` so nothing surprises you.

## How to follow it

| Phase | Tracks | Goal |
|---|---|---|
| 1. Basics | 01 | Be comfortable writing small functions, loops, strings |
| 2. Toolbox | 02 + guide notes | Know the STL containers and when to use each |
| 3. Patterns | 03 | Recognize the ~15 classic problem patterns |
| 4. Depth | 04 + 05 | The "C++ specific" questions: modern features, memory, concurrency |
| 5. Interview mode | 06 + revisit 03 | Timed practice, design questions, communication |

Rule of thumb: ~1 problem a day. Read the lesson, try without hints for 20 minutes, then hint.

## Track 01 - Fundamentals
Types and operators, control flow, functions, strings, arrays/vectors, references, `const`.
- [x] 1.1 FizzBuzz Reloaded - loops, `%`, building strings
- [x] 1.2 Secret Agent Cipher - `char` arithmetic, modulo with negatives, overflow
- [x] 1.3 Time-Travelling Clock - tables, greedy, parsing (Roman numerals)
- [ ] Palindrome Detective - two indices, `isalnum`/`tolower`
- [ ] Space Telegram - run-length encoding / decoding
- [ ] Digit Alchemist - digits of a number, sums, reversing, overflow-safe
- [ ] Prime Sieve - nested loops, `vector<bool>`, sieve of Eratosthenes
- [ ] Snake in a Box - 2D vectors, spiral traversal
- [ ] Swap Station - references vs. pointers vs. values (`void swap(int&, int&)`)
- [ ] Const Detective - `const`, `const&`, which overload is called

## Track 02 - STL & Containers
`vector`, `deque`, `stack`/`queue`, `map`/`unordered_map`, `set`, `priority_queue`, `<algorithm>`, lambdas, iterators.
- [x] 2.1 Word Frequency - `unordered_map`, sorting with a lambda
- [x] 2.2 Anagram Detective - grouping by a canonical key
- [ ] Leaderboard - `std::map`, custom comparators, `lower_bound`
- [ ] Unique Visitors - `set`/`unordered_set`, set operations
- [ ] Running Median - two heaps (`priority_queue`)
- [ ] Hot Potato - `deque`/`queue` simulation (Josephus)
- [ ] Iterator Pipeline - `std::transform`, `std::remove_if` + erase, `accumulate`
- [ ] Inventory Merge - nested maps, structured bindings
- [ ] Sort Anything - sort by multiple keys, stable sort, `std::pair`/`std::tuple` ordering
- [ ] Iterator Invalidation Quiz - what breaks when you `push_back` while looping

## Track 03 - Algorithms (interview patterns)
Each pattern: one easy intro, then harder variants.
- [x] 3.1 Treasure Pairs (Two Sum) - hash map
- [x] 3.2 Bracket Inspector - stack
- [ ] Two pointers: sorted-array dedupe, container with most water, three sum
- [ ] Sliding window: longest substring without repeats, max sum subarray of size k
- [ ] Prefix sums: subarray sum equals k, range-sum queries
- [ ] Binary search: first bad version, search in rotated array, square root
- [ ] Sorting & intervals: merge intervals, meeting rooms
- [ ] Linked lists: reverse, detect cycle, merge two lists
- [ ] Trees: depth, level order, validate BST, lowest common ancestor
- [ ] Graphs BFS: shortest path in a maze, number of islands, word ladder
- [ ] Graphs DFS: connected components, topological sort, cycle detection
- [ ] Heaps: k-th largest, top-k frequent, merge k sorted lists
- [ ] Recursion & backtracking: subsets, permutations, N-queens
- [ ] Dynamic programming: climbing stairs, coin change, longest common subsequence, knapsack
- [ ] Greedy: jump game, task scheduler
- [ ] Union-find and tries: accounts merge, autocomplete
- [ ] Bit tricks: single number, count bits, power of two

## Track 04 - Modern C++ (11 -> 23)
- [x] 4.1 Vending Machine - `std::optional`, `from_chars`
- [ ] Structured bindings and `if` with initializer - split a log line
- [ ] Move semantics - write a movable `Buffer`, see copies vs moves
- [ ] Lambdas & `std::function` - event dispatcher, captures (by value / by reference)
- [ ] `std::variant` + `std::visit` - a tiny expression evaluator
- [ ] Ranges and views (C++20) - lazy pipelines (`filter`, `transform`, `take`)
- [ ] Concepts (C++20) - constrain a generic `sum`/`max_of`
- [ ] Templates - a generic `Stack<T>`, function templates, `constexpr if`
- [ ] `span` and `string_view` - no-copy parsing
- [ ] `constexpr` - compile-time lookup tables
- [ ] `std::expected` (C++23) - errors without exceptions
- [ ] Three-way comparison `<=>` (C++20) - sortable structs for free

## Track 05 - Systems & Memory
- [ ] Pointers & arrays - pointer arithmetic, `sizeof`, decay
- [ ] RAII - a `ScopeGuard`, a file handle wrapper
- [ ] `unique_ptr` / `shared_ptr` - a linked list without leaks, ownership diagrams
- [ ] Rule of 0/3/5 - a dynamic array with copy and move
- [ ] Object lifetime - dangling references and how to spot them
- [ ] Memory layout - struct padding, alignment, `sizeof` puzzles
- [ ] Inheritance & virtual functions - vtables, slicing, virtual destructors
- [ ] Threads - `std::thread`, `mutex`, a parallel sum
- [ ] Producer/consumer - `condition_variable`, a blocking queue
- [ ] Atomics & memory order - a spinlock, a lock-free counter
- [ ] Undefined behavior museum - spot the UB (overflow, out-of-bounds, use-after-free)

## Track 06 - Interview Drills
- [ ] Design classics: LRU cache, min stack, rate limiter, tiny autocomplete, iterator over nested lists
- [ ] Timed mocks (45 min, 2 problems) with a self-review checklist
- [ ] "Explain your complexity" write-up template next to each solution
- [ ] C++ gotcha quiz: UB, slicing, ODR, integer promotion, `vector<bool>`
- [ ] Behavioral prep notes: STAR stories template

## Guide notes (`./learn guide`)
- [x] resources (links), complexity, containers, strings, interview-tips, how-ci-works
- [ ] algorithms-patterns (how to recognize each pattern), templates, memory-model, concurrency

## Open questions
- Reorder or drop anything? Anything missing for the roles you apply to?
- Add a spaced-repetition mode (re-surface solved problems after N days)?
- Next languages after C++ (Python? Rust?) - the layout is `languages/<name>/`.
- Optional later: a Codespaces/devcontainer so you can code from any browser.
