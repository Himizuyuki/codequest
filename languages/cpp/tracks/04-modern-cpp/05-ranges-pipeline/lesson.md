# Lesson: ranges and views (C++20)

## Range algorithms: pass the container
```cpp
std::ranges::sort(v);                               // instead of std::sort(v.begin(), v.end())
auto it = std::ranges::find(v, 42);
bool any = std::ranges::any_of(v, [](int x) { return x < 0; });
```

## Projections: "compare by this"
Most range algorithms take an optional *projection*, applied to each element before comparing:
```cpp
std::ranges::sort(people, {}, &Person::age);                           // by age, default comparator
std::ranges::sort(words, std::greater{}, [](const std::string& w) { return w.size(); });   // longest first
```
No more comparator lambdas that repeat `a.x < b.x`.

## Views: lazy pipelines
```cpp
auto pipeline = v | std::views::filter([](int x) { return x % 2 == 0; })
                  | std::views::transform([](int x) { return x * x; })
                  | std::views::take(3);
for (int x : pipeline) out.push_back(x);
```
A view does **no work when created**. Elements are pulled through one by one while you iterate, so `take(3)`
stops after the third match, and `std::views::iota(1)` (1, 2, 3, ... forever) is fine as long as something
later limits it. Others: `drop`, `take_while`, `drop_while`, `reverse`, `keys`, `values`, `split`, `join`.

## The C++20 quirks
1. **No `ranges::to`.** Turning a view back into a `vector` (`| std::ranges::to<std::vector>()`) arrived in
   C++23. In C++20: loop and `push_back`, or `std::ranges::copy(view, std::back_inserter(out))`.
2. **Views do not own.** `auto v = get_vector() | std::views::filter(f);` would refer to a destroyed temporary;
   the library refuses to compile it for rvalue containers, and algorithms on temporaries return
   `std::ranges::dangling` instead of an iterator. Keep the container alive in a variable.
3. **`filter` caches `begin()`**, so a filter view is not usable through `const&`, and modifying the underlying
   elements so they stop matching the predicate while iterating is undefined behavior.
4. **Lazy means re-evaluated.** Looping over a `transform` view twice runs the function twice. If the function
   is expensive or has side effects, materialise the result once.
5. **`take` wants a signed count** (the range's difference type): cast a `size_t`.
6. **Compile errors are long.** Read the *first* error and look for "constraints not satisfied".

## When to use what
Simple loop over one container: a range-for is still great. Several stages or early stopping: a pipeline is
clearer and avoids temporary vectors.
