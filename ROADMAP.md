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
- [x] 1.4 Palindrome Detective - two indices, `isalnum`/`tolower`, one-deletion variant
- [x] 1.5 Space Telegram - run-length encoding / decoding, parsing numbers
- [ ] Digit Alchemist - digits of a number, sums, reversing, overflow-safe
- [x] 1.6 Prime Sieve - nested loops, `vector<bool>`, sieve of Eratosthenes
- [x] 1.7 Snake in a Box - 2D vectors, spiral traversal
- [ ] Swap Station - references vs. pointers vs. values (`void swap(int&, int&)`)
- [ ] Const Detective - `const`, `const&`, which overload is called

## Track 02 - STL & Containers
`vector`, `deque`, `stack`/`queue`, `map`/`unordered_map`, `set`, `priority_queue`, `<algorithm>`, lambdas, iterators.
- [x] 2.1 Word Frequency - `unordered_map`, sorting with a lambda
- [x] 2.2 Anagram Detective - grouping by a canonical key
- [x] 2.3 Arcade Leaderboard - multi-key sort, `std::tie`, strict weak ordering
- [ ] Unique Visitors - `set`/`unordered_set`, set operations
- [x] 2.4 Running Median - two heaps (`priority_queue`), a small class
- [ ] Hot Potato - `deque`/`queue` simulation (Josephus)
- [ ] Iterator Pipeline - `std::transform`, `std::remove_if` + erase, `accumulate`
- [ ] Inventory Merge - nested maps, structured bindings
- [ ] Sort Anything - sort by multiple keys, stable sort, `std::pair`/`std::tuple` ordering
- [x] 2.5 Spring Cleaning - erasing safely, C++20 `std::erase_if`, iterator invalidation

## Track 03 - Algorithms (interview patterns)
Each pattern: one easy intro, then harder variants.
- [x] 3.1 Treasure Pairs (Two Sum) - hash map
- [x] 3.2 Bracket Inspector - stack
- [x] 3.3 Water Tank - two pointers (container with most water)
- [x] 3.4 Longest Streak - sliding window (longest substring without repeats)
- [ ] More two pointers: sorted-array dedupe, three sum
- [ ] More sliding window: max sum subarray of size k, minimum window substring
- [ ] Prefix sums: subarray sum equals k, range-sum queries
- [x] 3.5 Bookshelf Search - binary search, lower bound, integer square root
- [x] 3.8 Meeting Merger - sort then sweep (merge intervals)
- [ ] More binary search: search in rotated array, first bad version
- [ ] Linked lists: reverse, detect cycle, merge two lists
- [ ] Trees: depth, level order, validate BST, lowest common ancestor
- [x] 3.6 Maze Runner - BFS shortest path on a grid
- [ ] More BFS: number of islands, word ladder
- [ ] Graphs DFS: connected components, topological sort, cycle detection
- [ ] Heaps: k-th largest, top-k frequent, merge k sorted lists
- [ ] Recursion & backtracking: subsets, permutations, N-queens
- [x] 3.7 Coin Machine - 1-D dynamic programming (coin change)
- [ ] More DP: climbing stairs, longest common subsequence, knapsack
- [ ] Greedy: jump game, task scheduler
- [ ] Union-find and tries: accounts merge, autocomplete
- [ ] Bit tricks: single number, count bits, power of two

## Track 04 - Modern C++ (11 -> 23)
- [x] 4.1 Vending Machine - `std::optional`, `from_chars`
- [x] 4.2 Lambda Factory - captures, `mutable`, `std::function`, dangling references
- [x] 4.3 Shape Zoo - `std::variant`, `std::visit`, `overloaded`, `<numbers>`
- [x] 4.4 Spaceship Sorter - `operator<=>`, ordering categories (C++20)
- [x] 4.5 Ranges Pipeline - views, projections, laziness (C++20)
- [x] 4.6 Concept Bouncer - concepts, `requires`, `if constexpr` (C++20)
- [x] 4.7 No-Copy Parser - `std::span`, `string_view`, `starts_with` (C++20)
- [x] 4.8 Compile-Time Kitchen - `constexpr`, `consteval`, `constinit` (C++20)
- [x] 4.9 Integer Traps - `<bit>`, `std::cmp_less`, `std::midpoint`, `std::ssize` (C++20)
- [x] 4.10 Receipt Printer - `std::format` (C++20)
- [ ] Structured bindings and `if` with initializer - split a log line
- [ ] Templates - a generic `Stack<T>`, function templates
- [ ] Designated initializers, `using enum`, `std::source_location` (C++20)
- [ ] `std::expected` (C++23) - errors without exceptions
- [ ] Coroutines - a hand-written generator (C++20)

## Track 05 - Systems & Memory
- [ ] Pointers & arrays - pointer arithmetic, `sizeof`, decay
- [x] 5.1 Moving Truck - rule of five: copy, move, `noexcept`
- [x] 5.2 Tower of Nodes - `unique_ptr` ownership, recursive-destructor stack overflow
- [x] 5.3 Parallel Sum - `std::jthread`, `std::atomic`, data races (C++20)
- [ ] RAII - a `ScopeGuard`, a file handle wrapper
- [ ] `shared_ptr` / `weak_ptr` - cycles and how to break them
- [ ] Object lifetime - dangling references and how to spot them
- [ ] Memory layout - struct padding, alignment, `sizeof` puzzles
- [ ] Inheritance & virtual functions - vtables, slicing, virtual destructors
- [ ] Producer/consumer - `condition_variable`, a blocking queue
- [ ] Atomics & memory order - a spinlock, a lock-free counter
- [ ] Undefined behavior museum - spot the UB (overflow, out-of-bounds, use-after-free)

## Track 06 - Interview Drills
- [x] 6.1 LRU Cache - `std::list` + `unordered_map`, iterator stability
- [ ] More design classics: min stack, rate limiter, tiny autocomplete, iterator over nested lists
- [ ] Timed mocks (45 min, 2 problems) with a self-review checklist
- [ ] "Explain your complexity" write-up template next to each solution
- [ ] C++ gotcha quiz: UB, slicing, ODR, integer promotion, `vector<bool>`
- [ ] Behavioral prep notes: STAR stories template

## Guide notes (`./learn guide`)
- [x] resources (links), complexity, containers, strings, interview-tips, how-ci-works, patterns, cpp20-quirks
- [ ] templates, memory-model, concurrency

## Open questions
- Reorder or drop anything? Anything missing for the roles you apply to?
- Add a spaced-repetition mode (re-surface solved problems after N days)?
- Next languages after C++ (Python? Rust?) - the layout is `languages/<name>/`.
- Optional later: a Codespaces/devcontainer so you can code from any browser.
