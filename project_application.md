# Lab 12 - Project Application

## E1 - Filter and ownership
The report selects IDs 420, 180, 310, and 205 because they are `Delivery`
orders whose status is `Pending` or `In Progress`. It excludes ID 650 because
its type is `Dine-in`, and ID 900 because its status is `Completed`.

The `orders` array owns all six objects. The report view stores borrowed
pointers to the four selected objects; it does not copy, move, or delete them.

## E2 - Report order and algorithm
Observed report IDs: **205, 310, 420, 180**.

- Building ascending places `Biblioteca` before `Ingenieria`.
- Within `Biblioteca`, priority descending places priority 3 (205 and 310)
  before priority 1 (420).
- For the two `Biblioteca` orders with priority 3, ID ascending places 205
  before 310.

The view is sorted with quicksort. Its average time is O(n log n), with a
worst case of O(n^2). Recursive stack space is O(log n) on average and O(n) in
the worst case. The pointer view itself uses O(n) storage.

## E3 - Lookup choice and tests
The report is sorted by building, priority, then ID—not globally by ID—so
binary search by `orderId` cannot safely discard half of the view. The
implemented linear search checks up to n pointers, taking O(n) time and O(1)
extra space.

Test results from the program:
- Found: ID 205 returned Biblioteca, Pending, priority 3.
- Excluded: ID 650 was not found because it is Dine-in and absent from the view.
- Nonexistent: ID 999 was not found.

An additional ID-sorted pointer view would require O(n) more pointer storage
and O(n log n) sorting time. It would enable O(log n) ID searches while leaving
the report's building/priority order intact.

## E4 - Evidence and project connection
Source: [delivery_report_practice.cpp](./delivery_report_practice.cpp)  
Output: [delivery_report_output.txt](./delivery_report_output.txt)

The evidence shows the original records before and after each query. Their
positions and every displayed field match; only the borrowed-pointer view is
sorted. This keeps report ordering separate from the project's operational
FIFO sequence, so producing a report does not reorder the underlying orders.
