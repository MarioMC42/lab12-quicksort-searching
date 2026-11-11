/*
 * Course: COEN 2220 - Programming 2
 * Name: Mario A. Marrero Colón
 * Lab: Lab 12 - Quicksort and Searching
 * Description: Independent implementation example for final project
 * Due date: 10/nov/2026
 */

#include <iostream>
#include <string>
using namespace std;

struct OrderPreview
{
    int orderId, priority;
    string orderType, OrderStatus, building;
};

const int CAP = 6;

void displayOrders(const OrderPreview orders[], int count);
void displayView(OrderPreview *view[], int count);
void swapOrderPointers(OrderPreview *&left, OrderPreview *&right);
int compareOrders(const OrderPreview *left, const OrderPreview *right);
int partitionView(OrderPreview *view[], int first, int last);
void quickSortView(OrderPreview *view[], int first, int last);
int findOrderInView(OrderPreview *view[], int count, int targetId);

int main()
{
    OrderPreview orders[CAP] =
    {
        {420, 1, "Delivery", "Pending", "Biblioteca"},
        {180, 3, "Delivery", "In Progress", "Ingenieria"},
        {650, 1, "Dine-in", "Pending", "Cafeteria-Lunch"},
        {310, 3, "Delivery", "Pending", "Biblioteca"},
        {205, 3, "Delivery", "Pending", "Biblioteca"},
        {900, 2, "Delivery", "Completed", "Ingenieria"}
    };

    OrderPreview *view[CAP];
    int logicalCount = 0;

    cout << "E1: Original orders before building the active delivery view" << endl;
    displayOrders(orders, CAP);

    // E1: Keep only active DELIVERY orders in the view.
    for (int index = 0; index < CAP; index++)
    {
        if (orders[index].orderType == "Delivery" &&
            (orders[index].OrderStatus == "Pending" ||
             orders[index].OrderStatus == "In Progress"))
        {
            view[logicalCount] = &orders[index];
            logicalCount++;
        }
    }

    cout << "\nE2: Active delivery report sorted by building, priority desc, ID asc" << endl;
    quickSortView(view, 0, logicalCount - 1);
    displayView(view, logicalCount);

    // E3: Query by ID in the already sorted report view.
    int targetId;
    cout << "\nE3: Enter the order ID to search: ";
    if (!(cin >> targetId))
    {
        cout << "Invalid ID input." << endl;
        return 1;
    }

    int position = findOrderInView(view, logicalCount, targetId);
    if (position == -1)
    {
        cout << "Order not found in the active delivery report." << endl;
    }
    else
    {
        cout << "Found in report: " << view[position]->building
             << " | Status: " << view[position]->OrderStatus
             << " | Priority: " << view[position]->priority << endl;
    }

    // E4: Original orders must remain unchanged.
    cout << "\nE4: Original orders after creating the report and query" << endl;
    displayOrders(orders, CAP);

    return 0;
}

void displayOrders(const OrderPreview orders[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Order ID: " << orders[index].orderId
             << " | Priority: " << orders[index].priority
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].OrderStatus
             << " | Building: " << orders[index].building << endl;
    }
}

void displayView(OrderPreview *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Order ID: " << view[index]->orderId
             << " | Building: " << view[index]->building
             << " | Priority: " << view[index]->priority
             << " | Status: " << view[index]->OrderStatus << endl;
    }
}

void swapOrderPointers(OrderPreview *&left, OrderPreview *&right)
{
    OrderPreview *saved = left;
    left = right;
    right = saved;
}

int compareOrders(const OrderPreview *left, const OrderPreview *right)
{
    if (left->building != right->building)
    {
        return left->building < right->building ? -1 : 1;
    }
    if (left->priority != right->priority)
    {
        return left->priority > right->priority ? -1 : 1;
    }
    if (left->orderId != right->orderId)
    {
        return left->orderId < right->orderId ? -1 : 1;
    }
    return 0;
}

int partitionView(OrderPreview *view[], int first, int last)
{
    int middle = first + (last - first) / 2;
    swapOrderPointers(view[first], view[middle]);

    OrderPreview *pivot = view[first];
    int boundary = first;

    for (int scan = first + 1; scan <= last; scan++)
    {
        if (compareOrders(view[scan], pivot) < 0)
        {
            boundary++;
            swapOrderPointers(view[boundary], view[scan]);
        }
    }

    swapOrderPointers(view[first], view[boundary]);
    return boundary;
}

void quickSortView(OrderPreview *view[], int first, int last)
{
    if (first >= last)
    {
        return;
    }

    int pivotIndex = partitionView(view, first, last);
    quickSortView(view, first, pivotIndex - 1);
    quickSortView(view, pivotIndex + 1, last);
}

int findOrderInView(OrderPreview *view[], int count, int targetId)
{
    for (int index = 0; index < count; index++)
    {
        if (view[index]->orderId == targetId)
        {
            return index;
        }
    }
    return -1;
}
