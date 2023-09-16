# Public Subscribe System (PSS)

Welcome to the Public Subscribe System (PSS) project! This C-based system enables publishers to upload content into various categories, and subscribers can consume content they have subscribed to. This README provides an overview of both Phase A (basic data structures) and Phase B (advanced data structures) of the PSS project.

## Phase A - Basic Data Structures

In Phase A, we focus on implementing the fundamental data structures and functions for the PSS. These structures and functions form the foundation of the system.

### Data Structures

1. **Group Structure (`struct Group`):** Represents a content group and contains information about subscribers and content in that group.

2. **SubInfo Structure (`struct SubInfo`):** Stores subscriber information and their subscriptions in a **Sorted Singly Linked List**.

3. **Subscription Structure (`struct Subscription`):** Represents a subscription to a content group in a **Singly Linked List**.

4. **Info Structure (`struct Info`):** Holds information about uploaded content in a **Sorted Doubly Linked List**.

### Functions

- **initialize:** Initializes the data structures for the system.

- **Insert_Info:** Inserts information into specified groups.

- **Subscriber_Registration:** Registers a subscriber in the system and assigns them to specified groups.

- **Consume:** Displays content available to a subscriber.

- **Delete_Subscriber:** Removes a subscriber from the system.

- **Print_all:** Prints the current state of data structures.

## Phase B - Advanced Data Structures

In Phase B, we enhance the PSS by introducing more advanced data structures and a new function called **Prune** to optimize content management.

### Updated Data Structures

1. **SubInfo Structure (`struct SubInfo`):** Stores subscriber information and their subscriptions in a **Hash Table** using a **Universal Hashing Function**.

2. **Info Structure (`struct Info`):** Holds information about uploaded content in a **Doubly Linked Binary Search Tree**.

3. **Consumption Structure('struct TreeInfo'):** Holds information about subscriber's consumed content, using the new **Prune** function, in a **Sorted Leaf-Oriented Binary Search Tree**.

### New Function

- **Prune:** Removes outdated content, optimizing the system's performance and storage usage.

## Conclusion

The Public Subscribe System (PSS) project represents a journey of software development and system design. In Phase A, we established the foundational data structures and functions for content management and subscription handling. Phase B brought advanced data structures, including hash tables and binary search trees, along with the optimization of content management through the introduction of the Prune function.

This project showcases the development of a sophisticated subscription-based content management system, offering valuable insights into data organization, algorithm optimization, and system architecture. It serves as a testament to the skills and expertise gained throughout the project's lifecycle.

The PSS project demonstrates the capability to design and implement a real-world system, making it a valuable addition to my software development portfolio. It represents a stepping stone in my journey to becoming a proficient software developer.


## Author

- [Nikolaos Barmparousis](https://github.com/nikbarb810)

## License

This project is licensed under the [MIT License](LICENSE).


