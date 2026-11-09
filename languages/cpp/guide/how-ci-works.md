# How progress tracking (CI) works

**CI** (continuous integration) means "a robot runs your checks every time you push code".
On GitHub the robot is called **GitHub Actions**: when you `git push`, GitHub starts a
fresh Linux machine, checks out your repo, and runs the steps listed in
`.github/workflows/*.yml`. You do not install or run anything yourself, and it is free for
public repos (and has a generous free tier for private ones).

## What happens in CodeQuest
1. You solve a problem locally and check it with `./learn test <problem>`.
2. You `git add`, `git commit`, `git push`.
3. GitHub runs `.github/workflows/verify.yml`: it builds every problem against *your*
   `solution.cpp` files and runs the tests.
4. It writes the results to `progress.json` and `PROGRESS.md` and commits them back
   (with `[skip ci]` in the message so that commit does not trigger another run).
5. Open `PROGRESS.md` on GitHub to see what is solved, when, and your streak.

Only problems whose tests really pass are counted - the robot checks, not you.

## Where to watch it
GitHub repo, **Actions** tab: green check = passed, red cross = failed (click it for the log).

## Reproduce it on your machine
CI runs the same command you can run yourself: `./learn progress --write`.

## The solutions repo
`codequestsolutions` has its own workflow. It checks out *both* repos and runs
`./learn check-refs`, which proves that every reference solution passes its tests. That guards
against shipping a broken problem. It also runs weekly to catch drift.
