# Vault Transfers (mutex & deadlock)

A bank moves money between accounts from many teller threads at once. Money must never be created,
lost, or overdrawn - and the tellers must never freeze waiting for each other.

```cpp
class Bank {
public:
    explicit Bank(std::vector<long long> balances);     // balances[i] = opening balance of account i

    bool transfer(std::size_t from, std::size_t to, long long amount);
    long long balance(std::size_t account) const;
    long long total() const;
};
```

- **`transfer`** moves `amount` (always `>= 0`) from `from` to `to` and returns `true`. If `from` holds less
  than `amount` it changes nothing and returns `false`. With `from == to` nothing moves; the result still
  says whether the account could afford it.
- **`balance`** returns one account's balance.
- **`total`** returns the sum of all balances as one **consistent snapshot**: since transfers only move money,
  it must *always* equal the opening total, even while transfers are in flight.

Every method may be called from any number of threads at the same time. Account indexes are always valid.

## Example

```cpp
Bank bank({100, 50});
bank.transfer(0, 1, 30);    // true   -> 70, 80
bank.transfer(0, 1, 500);   // false  -> unchanged
bank.total();               // 150, always
```

## The catch

One thread sends 0 -> 1 while another sends 1 -> 0. If each locks "its" source account first and then the
destination, each ends up holding one lock and waiting forever for the other: a **deadlock**. The tests do
exactly this, so a `timeout` result here means your tellers are stuck.

## Notes

- A single mutex for the whole bank is a correct answer and passes. The interview follow-up is "now make
  transfers between unrelated accounts run in parallel" - try the per-account version afterwards.
- As always with threads, passing once is not proof. Reason about every shared variable.
