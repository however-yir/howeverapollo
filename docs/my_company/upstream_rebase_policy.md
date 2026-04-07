# Modified by however-yir autonomous driving team

# Upstream Rebase Policy

## Cadence

- Rebase from upstream Apollo **once per month**.
- Recommended window: first Tuesday of each month.

## Process

1. Fetch upstream and fast sanity check.
2. Rebase customization branch on latest upstream master.
3. Run additive test matrix:
   - `//modules/my_company/...` unit tests
   - scenario replay smoke test
   - interface compatibility check
4. Create rebase report and track conflicts.

## Conflict Handling Rule

- Keep “only-add” principle as first priority.
- If a conflict requires trunk modification, document reason and risk.
