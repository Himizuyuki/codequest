# CodeQuest

Learn a programming language by solving fun problems that are checked by real test suites, with
your progress verified and logged by GitHub Actions. C++ (C++20) comes first; the layout is ready
for more languages. It doubles as interview prep.

Reference solutions live in a separate repo:
[codequestsolutions](https://github.com/Himizuyuki/codequestsolutions) (spoilers!).

## Quick start

You need `g++` 13+ (problem 4.10 uses `<format>`; `CXX=clang++ ./learn ...` to switch compilers) and Python 3.

```sh
./learn list              # the roadmap and what you have solved
./learn next              # show the next unsolved problem (statement + links)
./learn lesson 1.1        # a short lesson on the ideas behind the problem
./learn test 1.1          # build + run your solution against the tests
./learn hint 1.1          # stuck? hints one at a time (./learn hint 1.1 2)
./learn guide             # reference notes: complexity, containers, strings, interview tips...
./learn progress          # re-verify everything
./learn sync              # log it: verify, write progress files, commit your solutions, push
```

The loop: **`next` -> read the lesson -> edit `solution.cpp` -> `test` -> commit and push.**
Each test prints PASS/FAIL with what you returned vs. what was expected. Test runs time out
after 10 s, which catches an accidentally quadratic solution.

Everything is also readable on GitHub without the CLI: each problem folder has `problem.md`
and `lesson.md`, `languages/cpp/guide/` has the notes, and [ROADMAP.md](ROADMAP.md) is the plan.

## Layout

```
learn                         the CLI
ROADMAP.md                    the plan: tracks, topics, interview path
progress.json, PROGRESS.md    written by CI from the test results
languages/cpp/
  harness/mini_test.hpp       tiny single-header test framework
  guide/                      reference notes (resources, complexity, containers, strings, ...)
  tracks/<NN-track>/<NN-problem>/
      problem.md              the story and the spec
      lesson.md               a short lesson on the concepts
      solution.cpp            YOUR code (starts as a failing stub)
      tests.cpp               the test suite
      meta.json               title, difficulty, tags, links, hints
.github/workflows/verify.yml  CI
```

## How progress gets logged (CI)

Push to GitHub and the **progress** workflow runs on GitHub's servers (nothing to install or run
on your machine): it builds your `solution.cpp` files against the tests, then commits
`progress.json` and `PROGRESS.md`. Only problems whose tests pass count, and the date you first
solved each one is kept. Watch it in the repo's **Actions** tab. Details: `./learn guide how-ci-works`.

**No CI available?** `./learn sync` does the same job from your own machine: it runs
`progress --write`, commits your `solution.cpp` files plus `progress.json`/`PROGRESS.md`
(message: "Progress: N/34 solved" and what is new), and pushes. Use `--no-push` to commit only.
It pushes over HTTPS with `$GITHUB_PERSONAL_ACCESS_TOKEN` if that is set (never stored), else with
your normal git credentials. If the push is rejected, run `git pull --rebase` and sync again.
If CI is enabled too, the two agree - the first-solved dates are preserved.

If the workflow cannot push, enable it under Settings -> Actions -> General -> Workflow
permissions -> "Read and write permissions".

## Adding a problem

1. Create `languages/cpp/tracks/<track>/<NN-slug>/` with `problem.md`, `lesson.md`, `meta.json`, a
   stub `solution.cpp` that compiles but fails, and `tests.cpp` (copy the `#ifndef SOLUTION`
   header from an existing one). Make tests fail *cleanly* on the stub - never index into a
   result before checking its size.
2. Add `cpp/<track>/<NN-slug>.cpp` to the solutions repo.
3. From this repo run `./learn check-refs --starters`.
